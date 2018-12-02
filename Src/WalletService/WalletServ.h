/*
 * =====================================================================================
 *
 *       Filename:  WalletServ.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/14/2018 03:45:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  enze (), 767201935@qq.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef EZ_BT_WALLET_SERV_H
#define EZ_BT_WALLET_SERV_H
#include <pthread.h>
#include "key.h"
#include "CommonBase/CommDataDef.h"
#include "NetWorkService/CAddress.h"
#include "WalletService/CWalletTx.h"

namespace Enze
{
    class CDataStream;
    class COutPoint;
    class CInPoint;
    class CDiskTxPos;
    class CCoinBase;
    class CBlock;
    class CBlockIndex;
    class CKeyItem;
    class CNode;
    class CScript;
    class CAddress;
    class CTransaction;
    class uint256;
    class uint160;
    class CInv;
    class Transaction;
    class WalletServ
    {
        public:
            static WalletServ* getInstance();
            static void Destory();
            
            void initiation();
            bool AddKey(const CKey& key);
            vector<unsigned char> GenerateNewKey();
            bool AddToWallet(const CWalletTx& wtxIn);
            bool AddToWalletIfMine(const CTransaction& tx, const CBlock* pblock);
            bool EraseFromWallet(uint256 hash);
            void AddOrphanTx(const Transaction& pbTx);
            void EraseOrphanTx(uint256 hash);
            void ReacceptWalletTransactions();
            void RelayWalletTransactions();
            bool AlreadyHave(const CInv& inv);
            int64 GetBalance();
            bool SelectCoins(int64 nTargetValue, set<CWalletTx*>& setCoinsRet);
            bool CreateTransaction(CScript m_cScriptPubKey, int64 nValue, CWalletTx& txNew, int64& nFeeRequiredRet);
            bool CommitTransactionSpent(const CWalletTx& wtxNew);
            bool SendMoney(CScript m_cScriptPubKey, int64 nValue, CWalletTx& wtxNew);    
          
            map<uint256, CTransaction>& getMapTransactions();
            map<COutPoint, CInPoint>& getMapNextTx();
            bool ExsitTransaction(const uint256& hash) const;
            bool ExsitNextTx(COutPoint& outpoint)const;
            
            unsigned int getTransactionsUpdatedTime()const
            {
                return m_nTransactionsUpdated;
            }
            
            void incrTransactionsUpdatedTime()
            {
                ++m_nTransactionsUpdated;
            }
            
            const map<uint256, CWalletTx>& getMapWallet()const
            {
                return m_mapWallet;
            }
           
            void AddToWallet(const uint256& hash, const CWalletTx& tx)
            {
                if (hash == tx.GetHash()) 
                {
                    m_mapWallet[hash] = tx;
                }
                else {
                    printf("error Hash not equal %s---%d\n", __FILE__, __LINE__); 
                }
            }

            const map<vector<unsigned char>, CPrivKey>& getMapKeys()const
            {
                return m_mapKeys;
            }
           
            void AddPrivKey(const vector<unsigned char>&pubKey, const CPrivKey& key)
            {
                m_mapKeys[pubKey] = key;
            }
            
            const map<uint160, vector<unsigned char> > getMapPubKeys()const
            {
                return m_mapPubKeys;
            }
            
            void AddPubKey(const uint160& hash, const vector<unsigned char>& pubKey)
            {
                m_mapPubKeys[hash] = pubKey;
            }
            
            void AddMapAddress(const string& strAddress, const string& strName)
            {
                m_mapAddressBook[strAddress] = strName;
            }
            
            void EraseAddress(const string& strAddr)
            {
                m_mapAddressBook.erase(strAddr);
            }
           
            int64 getTransactionFee()
            {
                return m_nTransactionFee;
            }
            
            void setFee(int64 fee)
            {
                m_nTransactionFee = fee;
            }
            
            CAddress& getAddrIncoming()
            {
                return m_addrIncoming;
            }
            
            multimap<uint256, CTransaction*>& getMapOrphanTransactionsByPrev()
            {
                return m_mapOrphanTransactionsByPrev;
            }
            
        private:
            map<uint256, CTransaction> m_mapTransactions;// ������׶�Ӧ�������Ѿ����������У��򽫴��ڴ���ɾ����Щ���������еĽ��ף�Ҳ����˵�������������û�б�����������н���
            map<COutPoint, CInPoint> m_mapNextTx;// �����Ӧ�������Ѿ����뵽�����У����Ӧ�����齻��Ӧ��Ҫ�ӱ��ڵ㱣��Ľ����ڴ����ɾ��
            map<uint256, CWalletTx> m_mapWallet; // Ǯ�����׶�Ӧ��map������key��Ӧ��Ǯ�����׵�hashֵ��mapWallet������źͱ��ڵ���صĽ���
            vector<pair<uint256, bool> > m_vWalletUpdated;
            map<vector<unsigned char>, CPrivKey> m_mapKeys; // ��Կ��˽Կ��Ӧ��ӳ���ϵ������keyΪ��Կ��valueΪ˽Կ
            map<uint160, vector<unsigned char> > m_mapPubKeys; // ��Կ��hashֵ�͹�Կ�Ĺ�ϵ������keyΪ��Կ��hashֵ��valueΪ��Կ
            CKey m_keyUser; // ��ǰ�û���˽Կ����Ϣ
            CAddress m_addrIncoming;
            map<string, string> m_mapAddressBook; // ��ַ�����Ƶ�ӳ�䣬����keyΪ��ַ��valueΪ����
            map<uint256, CTransaction*> m_mapOrphanTransactions;// �¶����ף�����key��Ӧ�Ľ���hashֵ
            multimap<uint256, CTransaction*> m_mapOrphanTransactionsByPrev; // ����keyΪvalue���׶�Ӧ����Ľ��׵�hashֵ��valueΪ��ǰ����
            int64 m_nTransactionFee = 0;
            unsigned int m_nTransactionsUpdated = 0;
            
        private:
            WalletServ();
            ~WalletServ();
            bool LoadWallet();
        private:
            static WalletServ* m_pInstance;
            static pthread_mutex_t m_mutexLock;
    
    };

}// end namespace

#endif /* EZ_BT_WALLET_SERV_H */
/* EOF */

