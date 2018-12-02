/*
 * =====================================================================================
 *
 *       Filename:  CTransaction.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/02/2018 11:04:33 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  enze (), 767201935@qq.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "WalletService/CTransaction.h"
#include "WalletService/CTxIndex.h"
#include "WalletService/CTxOutPoint.h"
#include "WalletService/CTxInPoint.h"
#include "WalletService/WalletServ.h"
#include "BlockEngine/CBlockIndex.h"
#include "DAO/DaoServ.h"
#include "CommonBase/ProtocSerialize.h"
#include "ProtocSrc/Transaction.pb.h"
using namespace Enze;
//////////////////////////////////////////////////////////////////////////////
//
// CTransaction
//

// �ж���߽����ܲ��ܱ����ܣ�����ܽ��ܽ���Ӧ�Ľ��׷���ȫ�ֱ�����mapTransactions��mapNextTx��
bool CTransaction::AcceptTransaction(bool fCheckInputs, bool* pfMissingInputs)
{
    if (pfMissingInputs)
        *pfMissingInputs = false;

	// �һ����׽����ڿ�����Ч���һ����ײ�����Ϊһ�������Ľ���
    // Coinbase is only valid in a block, not as a loose transaction
    if (IsCoinBase())
        return error("AcceptTransaction() : coinbase as individual tx");

    if (!CheckTransaction())
        return error("AcceptTransaction() : CheckTransaction failed");

	// �жϵ�ǰ�����Ƿ������Ѿ����յ�����
    // Do we already have it?
    uint256 hash = GetHash();
    map<uint256, CTransaction>& mapTransactions = WalletServ::getInstance()->getMapTransactions();
    map<COutPoint, CInPoint>& mapNextTx = WalletServ::getInstance()->getMapNextTx();
    if (mapTransactions.count(hash)) // �ж��ڴ����map���Ƿ��Ѿ�����
        return false;
    if (fCheckInputs)
        if (DaoServ::getInstance()->ContainsTx(hash)) // �жϽ���db���Ƿ��Ѿ�����
            return false;

	// �жϵ�ǰ���׶����Ƿ���ڴ��еĽ��׶����б��ͻ
    // Check for conflicts with in-memory transactions
    CTransaction* ptxOld = NULL;
    for (int i = 0; i < m_vTxIn.size(); i++)
    {
        COutPoint outpoint = m_vTxIn[i].m_cPrevOut;
		// ���ݵ�ǰ���׶�Ӧ�����뽻�ף���ö�Ӧ���뽻�׶�Ӧ���������
        if (mapNextTx.count(outpoint))
        {
            // Allow replacing with a newer version of the same transaction
			// i ==0 Ϊcoinbase��Ҳ����coinbase�����滻
            if (i != 0)
                return false;
			// ����ڵ�ǰ���׸��ϵĽ���
            ptxOld = mapNextTx[outpoint].m_pcTrans;
            if (!IsNewerThan(*ptxOld)) // �ж��Ƿ��ԭ�����׸��£�ͨ��nSequences�ж�
                return false;
            for (int i = 0; i < m_vTxIn.size(); i++)
            {
                COutPoint outpoint = m_vTxIn[i].m_cPrevOut;
				// ��ǰ���׵��������ڴ����mapNextTx��Ӧ�������������ڣ��Ҷ�ָ��ԭ���ϵĽ��ף�����մ˽���
                if (!mapNextTx.count(outpoint) || mapNextTx[outpoint].m_pcTrans != ptxOld)
                    return false;
            }
            break;
        }
    }

	// ��ǰ���׽���У�������ǰ���׶�Ӧ�����Ϊ���ѱ��
    // Check against previous transactions
    map<uint256, CTxIndex> mapUnused;
    int64 nFees = 0;
    if (fCheckInputs && !ConnectInputs(mapUnused, CDiskTxPos(1,1,1), 0, nFees, false, false))
    {
        if (pfMissingInputs)
            *pfMissingInputs = true;
        return error("AcceptTransaction() : ConnectInputs failed %s", hash.ToString().substr(0,6).c_str());
    }

	// ����ǰ���״洢���ڴ棬����ϵĽ��״��ڣ�����ڴ��н���Ӧ�Ľ����Ƴ�
    // Store transaction in memory
    {
        if (ptxOld)
        {
            printf("mapTransaction.erase(%s) replacing with new version\n", ptxOld->GetHash().ToString().c_str());
            mapTransactions.erase(ptxOld->GetHash());
        }
		// ����ǰ���״洢���ڴ������
        AddToMemoryPool();
    }

	// ����ϵĽ��״��ڣ����Ǯ���н��ϵĽ����Ƴ�
    ///// are we sure this is ok when loading transactions or restoring block txes
    // If updated, erase old tx from wallet
    if (ptxOld)
		// �����״�Ǯ��ӳ�����mapWallet���Ƴ���ͬʱ�����״�CWalletDB���Ƴ�
        WalletServ::getInstance()->EraseFromWallet(ptxOld->GetHash());

    printf("AcceptTransaction(): accepted %s\n", hash.ToString().substr(0,6).c_str());
    return true;
}

// ����ǰ�������ӵ��ڴ��mapTransactions,mapNextTx�У����Ҹ��½��׸��µĴ���
bool CTransaction::AddToMemoryPool()
{
    // Add to memory pool without checking anything.  Don't call this directly,
    // call AcceptTransaction to properly check the transaction first.
    map<uint256, CTransaction>& mapTransactions = WalletServ::getInstance()->getMapTransactions();
    map<COutPoint, CInPoint>& mapNextTx = WalletServ::getInstance()->getMapNextTx();
    {
        uint256 hash = GetHash();
        mapTransactions[hash] = *this; // ����ǰ���׷��뵽�ڴ����mapTransactions��
		// ���»������ö�Ӧ��mapNextTx �ǵĽ��׶�Ӧ������������Ӧ���Ǳ�����
        for (int i = 0; i < m_vTxIn.size(); i++)
            mapNextTx[m_vTxIn[i].m_cPrevOut] = CInPoint(&mapTransactions[hash], i);

		// ��¼���ױ����µĴ���
        WalletServ::getInstance()->incrTransactionsUpdatedTime();
    }
    return true;
}

// ����ǰ���״��ڴ����mapTransactions��mapNextTx���Ƴ����������ӽ��׶�Ӧ�ĸ��´���
bool CTransaction::RemoveFromMemoryPool()
{
    // Remove transaction from memory pool
    map<uint256, CTransaction>& mapTransactions = WalletServ::getInstance()->getMapTransactions();
    map<COutPoint, CInPoint>& mapNextTx = WalletServ::getInstance()->getMapNextTx();
    {
        foreach(const CTxIn& txin, m_vTxIn)
            mapNextTx.erase(txin.m_cPrevOut);
        mapTransactions.erase(GetHash());
        WalletServ::getInstance()->incrTransactionsUpdatedTime();
    }
    return true;
}

// �Ͽ��������룬�����ͷŽ��׶�Ӧ�������ռ�ã������ͷŽ��������Ӧ�Ľ��������ı��ռ��
bool CTransaction::DisconnectInputs()
{
	// ���������ó�ǰһ�����׶�Ӧ�Ļ��ѱ��ָ��
    // Relinquish previous transactions' spent pointers
    if (!IsCoinBase()) // �һ�
    {
        foreach(const CTxIn& txin, m_vTxIn)
        {
            COutPoint prevout = txin.m_cPrevOut;

            // Get prev txindex from disk
            CTxIndex txindex;
			// �����ݿ��ж�ȡ��Ӧ�Ľ��׵�����
            if (!DaoServ::getInstance()->ReadTxIndex(prevout.m_u256Hash, txindex))
                return error("DisconnectInputs() : ReadTxIndex failed");

            if (prevout.m_nIndex >= txindex.m_vSpent.size())
                return error("DisconnectInputs() : prevout.m_nIndex out of range");

            // Mark outpoint as not spent
            txindex.m_vSpent[prevout.m_nIndex].SetNull();

            // Write back
            DaoServ::getInstance()->UpdateTxIndex(prevout.m_u256Hash, txindex);
        }
    }

	// ����ǰ���״ӽ������������Ƴ�
    // Remove transaction from index
    if (!DaoServ::getInstance()->EraseTxIndex(*this))
        return error("DisconnectInputs() : EraseTxPos failed");

    return true;
}

// �����������ӣ�����Ӧ�Ľ�������ռ�ö�Ӧ�Ľ�������Ļ��ѱ��
bool CTransaction::ConnectInputs(map<uint256, CTxIndex>& mapTestPool, const CDiskTxPos& posThisTx, int m_nCurHeight, int64& nFees, bool fBlock, bool fMiner, int64 nMinFee)
{
	// ռ��ǰһ�����׶�Ӧ�Ļ���ָ��
    // Take over previous transactions' spent pointers
    if (!IsCoinBase())
    {
        map<uint256, CTransaction>& mapTransactions = WalletServ::getInstance()->getMapTransactions();
        const int nBestHeight = BlockEngine::getInstance()->getBestHeight();
        CBlockIndex* pindexBest = BlockEngine::getInstance()->getBestIndex();
        int64 nValueIn = 0;
        for (int i = 0; i < m_vTxIn.size(); i++)
        {
            COutPoint prevout = m_vTxIn[i].m_cPrevOut;

            // Read txindex
            CTxIndex txindex;
            bool fFound = true;
            if (fMiner && mapTestPool.count(prevout.m_u256Hash))
            {
                // Get txindex from current proposed changes
                txindex = mapTestPool[prevout.m_u256Hash];
            }
            else
            {
                // Read txindex from txdb
                fFound = DaoServ::getInstance()->ReadTxIndex(prevout.m_u256Hash, txindex);
            }
            if (!fFound && (fBlock || fMiner))
                return fMiner ? false : error("ConnectInputs() : %s prev tx %s index entry not found", GetHash().ToString().substr(0,6).c_str(),  prevout.m_u256Hash.ToString().substr(0,6).c_str());

            // Read txPrev
            CTransaction txPrev;
            if (!fFound || txindex.m_cDiskPos == CDiskTxPos(1,1,1))
            {
                // Get prev tx from single transactions in memory
  //              CRITICAL_BLOCK(cs_mapTransactions)
                {
                    if (!mapTransactions.count(prevout.m_u256Hash))
                        return error("ConnectInputs() : %s mapTransactions prev not found %s", GetHash().ToString().substr(0,6).c_str(),  prevout.m_u256Hash.ToString().substr(0,6).c_str());
                    txPrev = mapTransactions[prevout.m_u256Hash];
                }
                if (!fFound)
                    txindex.m_vSpent.resize(txPrev.m_vTxOut.size());
            }
            else
            {
                // Get prev tx from disk
                if (!txPrev.ReadFromDisk(txindex.m_cDiskPos))
                    return error("ConnectInputs() : %s ReadFromDisk prev tx %s failed", GetHash().ToString().substr(0,6).c_str(),  prevout.m_u256Hash.ToString().substr(0,6).c_str());
            }

            if (prevout.m_nIndex >= txPrev.m_vTxOut.size() || prevout.m_nIndex >= txindex.m_vSpent.size())
                return error("ConnectInputs() : %s prevout.m_nIndex out of range %d %d %d", GetHash().ToString().substr(0,6).c_str(), prevout.m_nIndex, txPrev.m_vTxOut.size(), txindex.m_vSpent.size());

            // If prev is coinbase, check that it's matured
            if (txPrev.IsCoinBase())
                for (CBlockIndex* pindex = pindexBest; pindex && nBestHeight - pindex->m_nCurHeight < COINBASE_MATURITY-1; pindex = pindex->m_pPrevBlkIndex)
                    if (pindex->m_nBlockPos == txindex.m_cDiskPos.m_nBlockPos && pindex->m_nFile == txindex.m_cDiskPos.m_nFile)
                        return error("ConnectInputs() : tried to spend coinbase at depth %d", nBestHeight - pindex->m_nCurHeight);

            // Verify signature
            if (!VerifySignature(txPrev, *this, i))
                return error("ConnectInputs() : %s VerifySignature failed", GetHash().ToString().substr(0,6).c_str());

            // Check for conflicts
            if (!txindex.m_vSpent[prevout.m_nIndex].IsNull())
                return fMiner ? false : error("ConnectInputs() : %s prev tx already used at %s", GetHash().ToString().substr(0,6).c_str(), txindex.m_vSpent[prevout.m_nIndex].ToString().c_str());

			// ���ǰһ�����׶�Ӧ�Ľ���������Ӧ�Ļ��ѱ��
            // Mark outpoints as spent
            txindex.m_vSpent[prevout.m_nIndex] = posThisTx;

            // Write back
            if (fBlock)
                DaoServ::getInstance()->UpdateTxIndex(prevout.m_u256Hash, txindex);
            else if (fMiner)
                mapTestPool[prevout.m_u256Hash] = txindex;

            nValueIn += txPrev.m_vTxOut[prevout.m_nIndex].m_nValue;
        }

        // Tally transaction fees
        int64 nTxFee = nValueIn - GetValueOut();
        if (nTxFee < 0)
            return error("ConnectInputs() : %s nTxFee < 0", GetHash().ToString().substr(0,6).c_str());
        if (nTxFee < nMinFee)
            return false;
        nFees += nTxFee;
    }

    if (fBlock)
    {
        // Add transaction to disk index
        if (!DaoServ::getInstance()->AddTxIndex(*this, posThisTx, m_nCurHeight))
            return error("ConnectInputs() : AddTxPos failed");
    }
    else if (fMiner)
    {
		// ����ǿ󹤣�����Ӧ�Ľ��׷����Ӧ�Ľ��ײ��Գ���
        // Add transaction to test pool
        mapTestPool[GetHash()] = CTxIndex(CDiskTxPos(1,1,1), m_vTxOut.size());
    }

    return true;
}

// �ͻ����������룬�Խ��ױ��������֤
bool CTransaction::ClientConnectInputs()
{
    if (IsCoinBase())
        return false;

	// ռ��ǰһ�����׶�Ӧ�Ļ��ѱ��
    // Take over previous transactions' spent pointers
    map<uint256, CTransaction>& mapTransactions = WalletServ::getInstance()->getMapTransactions();
    {
        int64 nValueIn = 0;
        for (int i = 0; i < m_vTxIn.size(); i++)
        {
            // Get prev tx from single transactions in memory
            COutPoint prevout = m_vTxIn[i].m_cPrevOut;
            if (!mapTransactions.count(prevout.m_u256Hash))
                return false;
            CTransaction& txPrev = mapTransactions[prevout.m_u256Hash];

            if (prevout.m_nIndex >= txPrev.m_vTxOut.size())
                return false;

            // Verify signature
            if (!VerifySignature(txPrev, *this, i))
                return error("ConnectInputs() : VerifySignature failed");

            ///// this is redundant with the mapNextTx stuff, not sure which I want to get rid of
            ///// this has to go away now that posNext is gone
            // // Check for conflicts
            // if (!txPrev.vout[prevout.m_nIndex].posNext.IsNull())
            //     return error("ConnectInputs() : prev tx already used");
            //
            // // Flag outpoints as used
            // txPrev.vout[prevout.m_nIndex].posNext = posThisTx;

            nValueIn += txPrev.m_vTxOut[prevout.m_nIndex].m_nValue;
        }
        if (GetValueOut() > nValueIn)
            return false;
    }

    return true;
}


void CTransaction::SetNull()
{
    m_nCurVersion = 1;
    m_vTxIn.clear();
    m_vTxOut.clear();
    m_nLockTime = 0;
}

bool CTransaction::IsNull() const
{
    return (m_vTxIn.empty() && m_vTxOut.empty());
}

uint256 CTransaction::GetHash() const
{
  //  printf("CTransaction::GetHash--TxInSz[%d]--TxOutSz[%d]\n", m_vTxIn.size(), m_vTxOut.size());
  //  printf("CTransaction::GetHash--scriptsz[%d]--TxOutSz[%d]\n", m_vTxIn[0].m_cScriptSig.size(), m_vTxOut.size());

    Transaction cProtoc;
    SeriaTransaction(*this, cProtoc);
    string strSerial;
    cProtoc.SerializePartialToString(&strSerial);
    printf("CTransaction::GetHash--strSize[%d], protoSz[%d]\n", strSerial.length(), cProtoc.ByteSize());
    return Hash(strSerial.begin(), strSerial.end());
   // return SerializeHash(*this);
}

// �ж��Ƿ������յĽ���
bool CTransaction::IsFinal() const
{
    // �������ʱ�����0��������ʱ��С�������ĳ��ȣ���˵�������յĽ���
    const int& nBestHeight = BlockEngine::getInstance()->getBestHeight();
    if (m_nLockTime == 0 || m_nLockTime < nBestHeight)
        return true;
    foreach(const CTxIn& txin, m_vTxIn)
        if (!txin.IsFinal())
            return false;
    return true;
}
// �Ա���ͬ�Ľ�����һ�����µ㣺������ͬ����Ľ����ж���һ������
bool CTransaction::IsNewerThan(const CTransaction& old) const
{
    if (m_vTxIn.size() != old.m_vTxIn.size())
        return false;
    for (int i = 0; i < m_vTxIn.size(); i++)
        if (m_vTxIn[i].m_cPrevOut != old.m_vTxIn[i].m_cPrevOut)
            return false;

    bool fNewer = false;
    unsigned int nLowest = UINT_MAX;
    for (int i = 0; i < m_vTxIn.size(); i++)
    {
        if (m_vTxIn[i].m_uSequence != old.m_vTxIn[i].m_uSequence)
        {
            if (m_vTxIn[i].m_uSequence <= nLowest)
            {
                fNewer = false;
                nLowest = m_vTxIn[i].m_uSequence;
            }
            if (old.m_vTxIn[i].m_uSequence < nLowest)
            {
                fNewer = true;
                nLowest = old.m_vTxIn[i].m_uSequence;
            }
        }
    }
    return fNewer;
}

// �жϵ�ǰ�����Ƿ��Ǳһ����ף��һ����׵��ص��ǽ��������СΪ1�����Ƕ�Ӧ����������Ϊ��
bool CTransaction::IsCoinBase() const
{
    return (m_vTxIn.size() == 1 && m_vTxIn[0].m_cPrevOut.IsNull());
}
/* ����߽��׽��м�飺
(1)���׶�Ӧ�������������б�����Ϊ��
(2)���׶�Ӧ���������С��0
(3)����Ǳһ����ף����Ӧ������ֻ��Ϊ1���Ҷ�Ӧ������ǩ����С���ܴ���100
(4)����ǷǱһ����ף����Ӧ�Ľ���������������Ϊ��
*/
bool CTransaction::CheckTransaction() const
{
    // Basic checks that don't depend on any context
    if (m_vTxIn.empty() || m_vTxOut.empty())
        return error("CTransaction::CheckTransaction() : m_vTxIn or m_vTxOut empty");

    // Check for negative values
    foreach(const CTxOut& txout, m_vTxOut)
        if (txout.m_nValue < 0)
            return error("CTransaction::CheckTransaction() : txout.nValue negative");

    if (IsCoinBase())
    {
        if (m_vTxIn[0].m_cScriptSig.size() < 2 || m_vTxIn[0].m_cScriptSig.size() > 1000)
            return error("CTransaction::CheckTransaction() : coinbase script size");
    }
    else
    {
        foreach(const CTxIn& txin, m_vTxIn)
            if (txin.m_cPrevOut.IsNull())
                return error("CTransaction::CheckTransaction() : preout is null");
    }

    return true;
}

// �жϵ�ǰ�Ľ����Ƿ�����ڵ㱾��Ľ��ף�������б��У�
bool CTransaction::IsMine() const
{
    foreach(const CTxOut& txout, m_vTxOut)
        if (txout.IsMine())
            return true;
    return false;
}

// ��õ�ǰ�����ܵ����룺�跽
int64 CTransaction::GetDebit() const
{
    int64 nDebit = 0;
    foreach(const CTxIn& txin, m_vTxIn)
        nDebit += txin.GetDebit();
    return nDebit;
}

// ��õ�ǰ�����ܵĴ��������ڽڵ������
int64 CTransaction::GetCredit() const
{
    int64 nCredit = 0;
    foreach(const CTxOut& txout, m_vTxOut)
        nCredit += txout.GetCredit();
    return nCredit;
}

// ��ȡ���׶�Ӧ����������֮��
int64 CTransaction::GetValueOut() const
{
    int64 nValueOut = 0;
    foreach(const CTxOut& txout, m_vTxOut)
    {
        if (txout.m_nValue < 0)
            throw runtime_error("CTransaction::GetValueOut() : negative value");
        nValueOut += txout.m_nValue;
    }
    return nValueOut;
}
// ��ȡ���׶�Ӧ����С���׷ѣ���СС��10000�ֽ����Ӧ����С���׷�Ϊ0������Ϊ���մ�С���м��㽻�׷�
// Transaction fee requirements, mainly only needed for flood control
// Under 10K (about 80 inputs) is free for first 100 transactions
// Base rate is 0.01 per KB
int64 CTransaction::GetMinFee(bool fDiscount) const
{
    return 0;
    // Base fee is 1 cent per kilobyte
    printf("error %s ---%d\n", __FILE__, __LINE__);
    //unsigned int nBytes = ::GetSerializeSize(*this, SER_NETWORK);
    unsigned int nBytes = 0;//::GetSerializeSize(*this, SER_NETWORK);
    int64 nMinFee = (1 + (int64)nBytes / 1000) * CENT;

    // First 100 transactions in a block are free
    if (fDiscount && nBytes < 10000)
        nMinFee = 0;

    // To limit dust spam, require a 0.01 fee if any output is less than 0.01
    if (nMinFee < CENT)
        foreach(const CTxOut& txout, m_vTxOut)
            if (txout.m_nValue < CENT)
                nMinFee = CENT;

    return nMinFee;
}

// ��Ӳ���н��ж�ȡ
bool CTransaction::ReadFromDisk(const CDiskTxPos& pos, FILE** pfileRet)
{
    CAutoFile filein = BlockEngine::getInstance()->OpenBlockFile(pos.m_nFile, 0, pfileRet ? "rb+" : "rb");
    if (!filein)
        return error("CTransaction::ReadFromDisk() : OpenBlockFile failed");

    // Read transaction
    if (fseek(filein, pos.m_nTxPos, SEEK_SET) != 0)
        return error("CTransaction::ReadFromDisk() : fseek failed");
    filein >> *this;

    // Return file pointer
    if (pfileRet)
    {
        if (fseek(filein, pos.m_nTxPos, SEEK_SET) != 0)
            return error("CTransaction::ReadFromDisk() : second fseek failed");
        *pfileRet = filein.release();
    }
    return true;
}




string CTransaction::ToString() const
{
    string str;
    str += strprintf("CTransaction(hash=%s, ver=%d, m_vTxIn.size=%d, m_vTxOut.size=%d, nLockTime=%d)\n",
        GetHash().ToString().substr(0,6).c_str(),
        m_nCurVersion,
        m_vTxIn.size(),
        m_vTxOut.size(),
        m_nLockTime);
    for (int i = 0; i < m_vTxIn.size(); i++)
        str += "    " + m_vTxIn[i].ToString() + "\n";
    for (int i = 0; i < m_vTxOut.size(); i++)
        str += "    " + m_vTxOut[i].ToString() + "\n";
    return str;
}

void CTransaction::print() const
{
    printf("%s", ToString().c_str());
}

bool Enze::operator!=(const CTransaction& a, const CTransaction& b)
{
    return !(a == b);
}

bool Enze::operator==(const CTransaction& a, const CTransaction& b)
{
    return (a.m_nCurVersion  == b.m_nCurVersion &&
            a.m_vTxIn       == b.m_vTxIn &&
            a.m_vTxOut      == b.m_vTxOut &&
            a.m_nLockTime == b.m_nLockTime);
}

/* EOF */

