/*
 * =====================================================================================
 *
 *       Filename:  WalletServ.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/14/2018 04:01:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  enze (), 767201935@qq.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "CommonBase/uint256.h"
#include "CommonBase/base58.h"
#include "CommonBase/ProtocSerialize.h"
#include "ProtocSrc/Transaction.pb.h"
#include "DAO/DaoServ.h"
#include "BlockEngine/BlockEngine.h"
#include "WalletService/WalletServ.h"
#include "WalletService/CTransaction.h"
#include "WalletService/CMerkleTx.h"
#include "WalletService/CWalletTx.h"
#include "WalletService/CTxInPoint.h"
#include "WalletService/CTxIndex.h"
#include "NetWorkService/CInv.h"

using namespace Enze;

WalletServ* WalletServ::m_pInstance = NULL;
pthread_mutex_t WalletServ::m_mutexLock;

WalletServ* WalletServ::getInstance()
{
    if (NULL == m_pInstance)
    {
        pthread_mutex_lock(&m_mutexLock); 
        
        if (NULL == m_pInstance) 
        {
            m_pInstance = new WalletServ();
        }
        
        pthread_mutex_unlock(&m_mutexLock); 
    
    }
    
    return m_pInstance;
}

void WalletServ::Destory()
{
    pthread_mutex_lock(&m_mutexLock); 
    if (NULL != m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
    pthread_mutex_unlock(&m_mutexLock); 

}

void WalletServ::initiation()
{
    //
    // Load data files
    //
    string strErrors;

    printf("Loading wallet...\n");
    if (!LoadWallet())
        strErrors += "Error loading wallet.dat      \n";

    printf("Done loading\n");

    //// debug print
    printf("mapKeys.size() = %d\n",         m_mapKeys.size());
    printf("mapPubKeys.size() = %d\n",      m_mapPubKeys.size());
    printf("mapWallet.size() = %d\n",       m_mapWallet.size());
    printf("mapAddressBook.size() = %d\n",  m_mapAddressBook.size());
    map<string, string>::iterator it = m_mapAddressBook.begin();
    for (;it != m_mapAddressBook.end(); ++it) {
        printf("mapAddressBook, key[%s]--value[%s]\n", it->first.c_str(), it->second.c_str());

    }

    if (!strErrors.empty())
    {
        printf("Initiation Error\n");
        exit(-1);
    }

}

WalletServ::WalletServ()
{
    m_nTransactionsUpdated = 0; // ÿ�ζ�mapTransactions�н��׽��и��£����Ը��ֶν���++����
    m_nTransactionFee = 0; // ���׷���

}

WalletServ::~WalletServ()
{

}

bool WalletServ::LoadWallet()
{
    vector<unsigned char> vchDefaultKey;
    if (!DaoServ::getInstance()->LoadWallet(vchDefaultKey))
        return false;
    printf("%s---%d---\n", __FILE__, __LINE__);
    if (m_mapKeys.count(vchDefaultKey))
    {
        printf("%s---%d---add key at mem\n", __FILE__, __LINE__);
        // Set keyUser
        m_keyUser.SetPubKey(vchDefaultKey);
        m_keyUser.SetPrivKey(m_mapKeys[vchDefaultKey]);
    }
    else
    {
        printf("%s---%d---add key at db\n", __FILE__, __LINE__);
        // Create new keyUser and set as default key
        RandAddSeed(true);
        m_keyUser.MakeNewKey();
        if (!AddKey(m_keyUser))
            return false;
        if (!DaoServ::getInstance()->SetAddressBookName(PubKeyToAddress(m_keyUser.GetPubKey()), "Enze"))
            return false;
        DaoServ::getInstance()->WriteDefaultKey(m_keyUser.GetPubKey());
    }
    printf("%s---%d---\n", __FILE__, __LINE__);
    return true;
}

//////////////////////////////////////////////////////////////////////////////
//
// mapKeys
//
// ����Ӧkey����Ϣ��ŵ���Ӧ��ȫ�ֱ�����
bool WalletServ::AddKey(const CKey& key)
{
     printf("%s---%d--%s\n", __FILE__, __LINE__, __func__);
    {
        m_mapKeys[key.GetPubKey()] = key.GetPrivKey();
        m_mapPubKeys[Hash160(key.GetPubKey())] = key.GetPubKey();
    }
     printf("%s---%d--%s\n", __FILE__, __LINE__, __func__);

    return DaoServ::getInstance()->WriteKey(key.GetPubKey(), key.GetPrivKey());
}
// �����µĹ�˽Կ��
vector<unsigned char> WalletServ::GenerateNewKey()
{
    CKey key;
    key.MakeNewKey();
    if (!AddKey(key))
        throw runtime_error("GenerateNewKey() : AddKey failed\n");
    return key.GetPubKey();
}




//////////////////////////////////////////////////////////////////////////////
//
// mapWallet
//
// ����ǰ�������ӵ�Ǯ��mapWallet�У�������룬������£�mapWallet������źͱ��ڵ���صĽ���
bool WalletServ::AddToWallet(const CWalletTx& wtxIn)
{
    uint256 hash = wtxIn.GetHash();
 //   CRITICAL_BLOCK(cs_mapWallet)
    {
        // Inserts only if not already there, returns tx inserted or tx found
        pair<map<uint256, CWalletTx>::iterator, bool> ret = m_mapWallet.insert(make_pair(hash, wtxIn));
        CWalletTx& wtx = (*ret.first).second;
        bool fInsertedNew = ret.second; // �ж��Ƿ����²���ģ�Ҳ����ԭ����ӦmapWallet��û�У�
        if (fInsertedNew)
            wtx.m_uTimeReceived = GetAdjustedTime(); // ���ױ��ڵ���յ�ʱ��

        //// debug print
        printf("AddToWallet %s  %s\n", wtxIn.GetHash().ToString().substr(0,6).c_str(), fInsertedNew ? "new" : "update");

        if (!fInsertedNew)
        {
			// ��ǰ�����Ѿ���mapWallet�д���
            // Merge
            bool fUpdated = false;
            if (wtxIn.m_hashBlock != 0 && wtxIn.m_hashBlock != wtx.m_hashBlock)
            {
                wtx.m_hashBlock = wtxIn.m_hashBlock;
                fUpdated = true;
            }
            if (wtxIn.m_nIndex != -1 && (wtxIn.m_vMerkleBranch != wtx.m_vMerkleBranch || wtxIn.m_nIndex != wtx.m_nIndex))
            {
                wtx.m_vMerkleBranch = wtxIn.m_vMerkleBranch;
                wtx.m_nIndex = wtxIn.m_nIndex;
                fUpdated = true;
            }
            if (wtxIn.m_bFromMe && wtxIn.m_bFromMe != wtx.m_bFromMe)
            {
                wtx.m_bFromMe = wtxIn.m_bFromMe;
                fUpdated = true;
            }
            if (wtxIn.m_bSpent && wtxIn.m_bSpent != wtx.m_bSpent)
            {
                wtx.m_bSpent = wtxIn.m_bSpent;
                fUpdated = true;
            }
            if (!fUpdated)
                return true;
        }

        // Write to disk
        if (!wtx.WriteToDisk())
            return false;

        // Notify UI
        m_vWalletUpdated.push_back(make_pair(hash, fInsertedNew));
    }

    // Refresh UI
    //MainFrameRepaint();
    return true;
}

// �����ǰ�������ڱ��ڵ㣬�򽫵�ǰ���׼��뵽Ǯ����
bool WalletServ::AddToWalletIfMine(const CTransaction& tx, const CBlock* pblock)
{
    if (tx.IsMine() || m_mapWallet.count(tx.GetHash()))
    {
        CWalletTx wtx(tx);
        // Get merkle branch if transaction was found in a block
        if (pblock)
            wtx.SetMerkleBranch(pblock);
        return AddToWallet(wtx);
    }
    return true;
}

// �����״�Ǯ��ӳ�����mapWallet���Ƴ���ͬʱ�����״�CWalletDB���Ƴ�
bool WalletServ::EraseFromWallet(uint256 hash)
{
    if (m_mapWallet.erase(hash))
        DaoServ::getInstance()->EraseTx(hash);
    return true;
}
//////////////////////////////////////////////////////////////////////////////
//
// mapOrphanTransactions
//
// ���ӹ¶�����
void WalletServ::AddOrphanTx(const Transaction& pbTx)
{
    CTransaction *tx = new CTransaction();
    UnSeriaTransaction(pbTx, *tx);

    uint256 hash = tx->GetHash();
    if (m_mapOrphanTransactions.count(hash))
        return;
    m_mapOrphanTransactions[hash] = tx;
    // ��ǰ���׶�Ӧ�������Ӧ�Ľ���hash
    foreach(const CTxIn& txin, tx->m_vTxIn)
        m_mapOrphanTransactionsByPrev.insert(make_pair(txin.m_cPrevOut.m_u256Hash, tx));
}
// ɾ����Ӧ�Ĺ¶�����
void WalletServ::EraseOrphanTx(uint256 hash)
{
    if (!m_mapOrphanTransactions.count(hash))
        return;
    const CTransaction* tx = m_mapOrphanTransactions[hash];

    foreach(const CTxIn& txin, tx->m_vTxIn)
    {
        for (multimap<uint256, CTransaction*>::iterator mi = m_mapOrphanTransactionsByPrev.lower_bound(txin.m_cPrevOut.m_u256Hash);
             mi != m_mapOrphanTransactionsByPrev.upper_bound(txin.m_cPrevOut.m_u256Hash);)
        {
            if ((*mi).second == tx)
                m_mapOrphanTransactionsByPrev.erase(mi++);
            else
                mi++;
        }
    }
    delete tx;
    m_mapOrphanTransactions.erase(hash);
}


void WalletServ::ReacceptWalletTransactions()
{
    foreach(PAIRTYPE(const uint256, CWalletTx)& item, m_mapWallet)
    {
        CWalletTx& wtx = item.second;
        if (!wtx.IsCoinBase() && !DaoServ::getInstance()->ContainsTx(wtx.GetHash()))
            wtx.AcceptWalletTransaction(false);
    }
}

// �������Ľڵ�֮��ת����Щ��ĿǰΪֹ��û�н���block�е�Ǯ������
void WalletServ::RelayWalletTransactions()
{
    static int64 nLastTime;
	// ת��Ǯ������ʱ��ļ����10���ӣ�С��10�����򲻽���ת��
    if (GetTime() - nLastTime < 10 * 60)
        return;
    nLastTime = GetTime();

    // Rebroadcast any of our txes that aren't in a block yet
    printf("RelayWalletTransactions()\n");
    {
		// ����ʱ�䣨����ǰ�ڵ���յ�ʱ�䣩˳���Ǯ���еĽ��׽�������
        // Sort them in chronological order
        multimap<unsigned int, CWalletTx*> mapSorted;// Ĭ���ǰ���unsigned int��Ӧ��ֵ�������У�����Խ��ʱ��Խ��ǰ
        foreach(PAIRTYPE(const uint256, CWalletTx)& item, m_mapWallet)
        {
            CWalletTx& wtx = item.second;
            mapSorted.insert(make_pair(wtx.m_uTimeReceived, &wtx));
        }
        foreach(PAIRTYPE(const unsigned int, CWalletTx*)& item, mapSorted)
        {
            CWalletTx& wtx = *item.second;
			// Ǯ�����׽���ת��
            wtx.RelayWalletTransaction();
        }
    }
}

// Messages
//

// �ж϶�Ӧ��������Ϣ�Ƿ��Ѿ�����
bool WalletServ::AlreadyHave(const CInv& inv)
{
    switch (inv.type)
    {
        case MSG_TX:        return m_mapTransactions.count(inv.hash) || DaoServ::getInstance()->ContainsTx(inv.hash);
    case MSG_BLOCK:     return BlockEngine::getInstance()->getMapBlockIndex().count(inv.hash) || BlockEngine::getInstance()->mapOrphanBlocks.count(inv.hash);
    case MSG_REVIEW:    return true;
    case MSG_PRODUCT:   return mapProducts.count(inv.hash);
    }
    // Don't know what it is, just say we already got one
    return true;
}

//////////////////////////////////////////////////////////////////////////////
//
// Actions
//


int64 WalletServ::GetBalance()
{
    int64 nStart, nEnd;

    int64 nTotal = COIN*100;
    for (map<uint256, CWalletTx>::iterator it = m_mapWallet.begin(); it != m_mapWallet.end(); ++it)
    {
        CWalletTx* pcoin = &(*it).second;
        if (!pcoin->IsFinal() || pcoin->m_bSpent)
            continue;
        nTotal += pcoin->GetCredit();
    }
    printf(" GetBalance() nTotal = %lld\n", nTotal);
    return nTotal;
}


bool WalletServ::SelectCoins(int64 nTargetValue, set<CWalletTx*>& setCoinsRet)
{
    setCoinsRet.clear();

    // List of values less than target
    int64 nLowestLarger = _I64_MAX;
    CWalletTx* pcoinLowestLarger = NULL;
    vector<pair<int64, CWalletTx*> > vValue;
    int64 nTotalLower = 0;
    m_mapWallet.count(18);
    printf("SelectCoins() WalletSize[%d]\n", m_mapWallet.size());
    printf("nTragetValue[%lld]\n", nTargetValue);
    for (map<uint256, CWalletTx>::iterator it = m_mapWallet.begin(); it != m_mapWallet.end(); ++it)
    {
        CWalletTx* pcoin = &(*it).second;
        if (!pcoin->IsFinal() || pcoin->m_bSpent)
            continue;
        int64 n = pcoin->GetCredit();
        printf("SelectCoins---coin Value[%lld], nLowestLarger[%lld]\n", n, nLowestLarger);
        if (n <= 0)
            continue;
        if (n < nTargetValue)
        {
            vValue.push_back(make_pair(n, pcoin));
            nTotalLower += n;
        }
        else if (n == nTargetValue)
        {
            setCoinsRet.insert(pcoin);
            return true;
        }
        else if (n < nLowestLarger)
        {
            printf("SelectCoins---Find coin Value[%lld]\n", n);
            nLowestLarger = n;
            pcoinLowestLarger = pcoin;
        }
    }
    printf("SelectCoins() nTotalLower:[%lld] \n", nTotalLower);
    if (nTotalLower < nTargetValue)
    {
        if (pcoinLowestLarger == NULL)
            return false;
        setCoinsRet.insert(pcoinLowestLarger);
        return true;
    }

    // Solve subset sum by stochastic approximation
    sort(vValue.rbegin(), vValue.rend());
    vector<char> vfIncluded;
    vector<char> vfBest(vValue.size(), true);
    int64 nBest = nTotalLower;

    for (int nRep = 0; nRep < 1000 && nBest != nTargetValue; nRep++)
    {
        vfIncluded.assign(vValue.size(), false);
        int64 nTotal = 0;
        bool fReachedTarget = false;
        for (int nPass = 0; nPass < 2 && !fReachedTarget; nPass++)
        {
            for (int i = 0; i < vValue.size(); i++)
            {
                if (nPass == 0 ? rand() % 2 : !vfIncluded[i])
                {
                    nTotal += vValue[i].first;
                    vfIncluded[i] = true;
                    if (nTotal >= nTargetValue)
                    {
                        fReachedTarget = true;
                        if (nTotal < nBest)
                        {
                            nBest = nTotal;
                            vfBest = vfIncluded;
                        }
                        nTotal -= vValue[i].first;
                        vfIncluded[i] = false;
                    }
                }
            }
        }
    }

    // If the next larger is still closer, return it
    if (pcoinLowestLarger && nLowestLarger - nTargetValue <= nBest - nTargetValue)
        setCoinsRet.insert(pcoinLowestLarger);
    else
    {
        for (int i = 0; i < vValue.size(); i++)
            if (vfBest[i])
                setCoinsRet.insert(vValue[i].second);

        //// debug print
        printf("SelectCoins() best subset: ");
        for (int i = 0; i < vValue.size(); i++)
            if (vfBest[i])
                printf("%s ", FormatMoney(vValue[i].first).c_str());
        printf("total %s\n", FormatMoney(nBest).c_str());
    }
    printf("SelectCoins Return true\n");
    return true;
}


bool WalletServ::CreateTransaction(CScript scriptPubKey, int64 nValue, CWalletTx& wtxNew, int64& nFeeRequiredRet)
{
    nFeeRequiredRet = 0;
    {
        // txdb must be opened before the mapWallet lock
        {
            int64 nFee = m_nTransactionFee;
            loop
            {
                wtxNew.m_vTxIn.clear();
                wtxNew.m_vTxOut.clear();
                if (nValue < 0)
                    return false;
                int64 nValueOut = nValue;
                nValue += nFee;

                // Choose coins to use
                set<CWalletTx*> setCoins;
                if (!SelectCoins(nValue, setCoins)) 
                {
                     printf("CreateTransaction--SelectCoins Fail\n");
                    return false;
                
                }
                printf("CreateTransaction--SelectCoins Ok\n");
                int64 nValueIn = 0;
                foreach(CWalletTx* pcoin, setCoins)
                    nValueIn += pcoin->GetCredit();

                printf("CreateTransaction--nValueOut[%lu]--nValue[%lu]--nValueIn[%lu]\n", nValueOut, nValue, nValueIn);
                printf("CreateTransaction--scriptPubKey[%s]\n", scriptPubKey.ToString().c_str());
                // Fill vout[0] to the payee
                wtxNew.m_vTxOut.push_back(CTxOut(nValueOut, scriptPubKey));

                // Fill vout[1] back to self with any change
                if (nValueIn > nValue)
                {
                    /// todo: for privacy, should randomize the order of outputs,
                    //        would also have to use a new key for the change.
                    // Use the same key as one of the coins
                    vector<unsigned char> vchPubKey;
                    CTransaction& txFirst = *(*setCoins.begin());
                    foreach(const CTxOut& txout, txFirst.m_vTxOut)
                        if (txout.IsMine())
                            if (ExtractPubKey(txout.m_cScriptPubKey, true, vchPubKey))
                                break;
                    if (vchPubKey.empty())
                        return false;

                    // Fill vout[1] to ourself
                    CScript scriptPubKey;
                    scriptPubKey << vchPubKey << OP_CHECKSIG;
                    wtxNew.m_vTxOut.push_back(CTxOut(nValueIn - nValue, scriptPubKey));
                }

                // Fill vin
                foreach(CWalletTx* pcoin, setCoins)
                    for (int nOut = 0; nOut < pcoin->m_vTxOut.size(); nOut++)
                        if (pcoin->m_vTxOut[nOut].IsMine())
                            wtxNew.m_vTxIn.push_back(CTxIn(pcoin->GetHash(), nOut));

                // Sign
                int nIn = 0;
                foreach(CWalletTx* pcoin, setCoins)
                    for (int nOut = 0; nOut < pcoin->m_vTxOut.size(); nOut++)
                        if (pcoin->m_vTxOut[nOut].IsMine())
                            SignSignature(*pcoin, wtxNew, nIn++);
                // Check that enough fee is included
                if (nFee < wtxNew.GetMinFee(true))
                {
                    nFee = nFeeRequiredRet = wtxNew.GetMinFee(true);
                    continue;
                }
                // Fill vtxPrev by copying from previous transactions vtxPrev
                wtxNew.AddSupportingTransactions();
                wtxNew.m_bTimeReceivedIsTxTime = true;

                break;
            }
        }
    }
    return true;
}

// Call after CreateTransaction unless you want to abort
bool WalletServ::CommitTransactionSpent(const CWalletTx& wtxNew)
{
    //// todo: make this transactional, never want to add a transaction
    ////  without marking spent transactions
    printf("CommitTransactionSpent---1\n");
    // Add tx to wallet, because if it has change it's also ours,
    // otherwise just for transaction history.
    AddToWallet(wtxNew);

    // Mark old coins as spent
    set<CWalletTx*> setCoins;
    foreach(const CTxIn& txin, wtxNew.m_vTxIn)
        setCoins.insert(&m_mapWallet[txin.m_cPrevOut.m_u256Hash]);
    foreach(CWalletTx* pcoin, setCoins)
    {
        pcoin->m_bSpent = true;
        pcoin->WriteToDisk();
        m_vWalletUpdated.push_back(make_pair(pcoin->GetHash(), false));
    }
    return true;
}

bool WalletServ::SendMoney(CScript scriptPubKey, int64 nValue, CWalletTx& wtxNew)
{
//CRITICAL_BLOCK(cs_main)
    {
        int64 nFeeRequired;
        if (!CreateTransaction(scriptPubKey, nValue, wtxNew, nFeeRequired))
        {
            string strError;
            if (nValue + nFeeRequired > GetBalance())
                strError = strprintf("Error: This is an oversized transaction that requires a transaction fee of %s  ", FormatMoney(nFeeRequired).c_str());
            else
                strError = "Error: Transaction creation failed  ";
            //wxMessageBox(strError, "Sending...");
            return error("SendMoney() : %s\n", strError.c_str());
        }
        if (!CommitTransactionSpent(wtxNew))
        {
            //wxMessageBox("Error finalizing transaction  ", "Sending...");
            return error("SendMoney() : Error finalizing transaction");
        }

        printf("SendMoney: %s\n", wtxNew.GetHash().ToString().substr(0,6).c_str());

        // Broadcast
        if (!wtxNew.AcceptTransaction())
        {
            // This must not fail. The transaction has already been signed and recorded.
            throw runtime_error("SendMoney() : wtxNew.AcceptTransaction() failed\n");
            //wxMessageBox("Error: Transaction not valid  ", "Sending...");
            return error("SendMoney() : Error: Transaction not valid");
        }
        wtxNew.RelayWalletTransaction();
    }
    //MainFrameRepaint();
    return true;
}

map<uint256, CTransaction>& WalletServ::getMapTransactions()
{
    return m_mapTransactions;
}

map<COutPoint, CInPoint>& WalletServ::getMapNextTx()
{
    return m_mapNextTx;
}
/* EOF */

