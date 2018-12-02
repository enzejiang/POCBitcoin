/*
 * =====================================================================================
 *
 *       Filename:  CWalletTx.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/02/2018 07:21:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  enze (), 767201935@qq.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "WalletService/WalletServ.h"
#include "BlockEngine/BlockEngine.h"
#include "BlockEngine/CBlockIndex.h"
#include "WalletService/CWalletTx.h"
#include "NetWorkService/CInv.h"
#include "NetWorkService/NetWorkServ.h"
#include "DAO/DaoServ.h"

using namespace Enze;
extern bool fClient ;
// ��ȡ����ʱ��
int64 CWalletTx::GetTxTime() const
{
    const map<uint256, CBlockIndex*>& mapBlockIndex = BlockEngine::getInstance()->getMapBlockIndex();
    if (!m_bTimeReceivedIsTxTime && m_hashBlock != 0)
    {
        // If we did not receive the transaction directly, we rely on the block's
        // time to figure out when it happened.  We use the median over a range
        // of blocks to try to filter out inaccurate block times.
        map<uint256, CBlockIndex*>::const_iterator mi = mapBlockIndex.find(m_hashBlock);
        if (mi != mapBlockIndex.end())
        {
            CBlockIndex* pindex = (*mi).second;
            if (pindex)
                return pindex->GetMedianTime();
        }
    }
    return m_uTimeReceived;
}



// ����֧�ֵĽ���
void CWalletTx::AddSupportingTransactions()
{
    m_vPrevTx.clear();

    const int COPY_DEPTH = 3;
	// �����ǰ�������ڵ�block�����ĩβ֮���block����С��3
    if (SetMerkleBranch() < COPY_DEPTH)
    {
        vector<uint256> vWorkQueue;// ��Ӧ��ǰ���������Ӧ�Ľ��׵�hashֵ
        foreach(const CTxIn& txin, m_vTxIn)
            vWorkQueue.push_back(txin.m_cPrevOut.m_u256Hash);

        // This critsect is OK because txdb is already open
        const map<uint256, CWalletTx>& mapWallet = WalletServ::getInstance()->getMapWallet();
        map<uint256, const CMerkleTx*> mapWalletPrev;
        set<uint256> setAlreadyDone;
        for (int i = 0; i < vWorkQueue.size(); i++)
        {
            uint256 hash = vWorkQueue[i];
            if (setAlreadyDone.count(hash))
                continue;
            setAlreadyDone.insert(hash);

            CMerkleTx tx;
            if (mapWallet.count(hash))
            {
                tx = mapWallet.at(hash);
                foreach(const CMerkleTx& txWalletPrev, mapWallet.at(hash).m_vPrevTx)
                    mapWalletPrev[txWalletPrev.GetHash()] = &txWalletPrev;
            }
            else if (mapWalletPrev.count(hash))
            {
                tx = *mapWalletPrev[hash];
            }
            else if (!fClient && DaoServ::getInstance()->ReadDiskTx(hash, tx))
            {
                ;
            }
            else
            {
                printf("ERROR: AddSupportingTransactions() : unsupported transaction\n");
                continue;
            }

            int nDepth = tx.SetMerkleBranch();
            m_vPrevTx.push_back(tx);

            if (nDepth < COPY_DEPTH)
                foreach(const CTxIn& txin, tx.m_vTxIn)
                    vWorkQueue.push_back(txin.m_cPrevOut.m_u256Hash);
        }
    }

    reverse(m_vPrevTx.begin(), m_vPrevTx.end());
}

// Ǯ�����׽���ת��
void CWalletTx::RelayWalletTransaction()
{
    // ������Щ��������block�������block֮��ľ���С��3����Ҫ����Щ���׽���ת��
    foreach(const CMerkleTx& tx, m_vPrevTx)
    {
        if (!tx.IsCoinBase())
        {
            uint256 hash = tx.GetHash();
            if (!DaoServ::getInstance()->ContainsTx(hash))
                Enze::NetWorkServ::getInstance()->RelayMessage(CInv(MSG_TX, hash), (CTransaction)tx);
        }
    }
    if (!IsCoinBase())
    {
        uint256 hash = GetHash();
        if (!DaoServ::getInstance()->ContainsTx(hash))
        {
            printf("Relaying wtx %s\n", hash.ToString().substr(0,6).c_str());
            Enze::NetWorkServ::getInstance()->RelayMessage(CInv(MSG_TX, hash), (CTransaction)*this);
        }
    }
}

// �жϵ�ǰ�����Ƿ��ܹ�������
bool CWalletTx::AcceptWalletTransaction(bool fCheckInputs)
{
    const map<uint256, CTransaction>& mapTransactions = WalletServ::getInstance()->getMapTransactions();
    foreach(CMerkleTx& tx, m_vPrevTx)
    {
        if (!tx.IsCoinBase())
        {
            uint256 hash = tx.GetHash();
            if (!mapTransactions.count(hash) && !DaoServ::getInstance()->ContainsTx(hash))
                tx.AcceptTransaction(fCheckInputs);
        }
    }
    if (!IsCoinBase())
        return AcceptTransaction(fCheckInputs);
    return true;
}



bool CWalletTx::WriteToDisk()
{
    return DaoServ::getInstance()->WriteTx(GetHash(), *this);
}
/* EOF */

