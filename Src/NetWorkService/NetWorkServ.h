/*
 * =====================================================================================
 *
 *       Filename:  NetWorkServ.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/06/2018 10:35:31 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  enze (), 767201935@qq.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef EZ_BT_NWS_H
#define EZ_BT_NWS_H
#include <mutex>
#include "CAddress.h"
#include "PeerNode.h"
#include "zhelpers.h"
#include "CommonBase/ThreadGuard.h"
namespace Enze
{
    class ServMsg;
    class CInv;
    class NetWorkServ
    {
        public:
            static NetWorkServ* getInstance();
            static void Destory();
            
            void initiation();
            bool ConnectSocket(const CAddress& addrConnect, SOCKET& hSocketRet);
            PeerNode* FindNode(unsigned int ip);
            PeerNode* FindNode(const CAddress& addr);
            PeerNode* ConnectNode(const CAddress& addrConnect, int64 nTimeout=0);
            bool StartNode();
            bool StopNode();
    
            bool ProcessMessages(PeerNode* pfrom);
            bool SendMessages(PeerNode* pto);
            
            void CheckForShutdown(int n);
            void AbandonRequests(/*void (*fn)(void*, CDataStream&), void* param1*/);
            bool AnySubscribed(unsigned int nChannel);
            void MessageHandler();
            void SocketHandler();
            void PeerNodeManagerThread();
            void AddrManagerThread();
            void RelayInventory(const CInv& inv);
            void RelayMessage(const CInv& inv, const CTransaction& tx);
            
            inline map<string, CAddress>& getMapAddr()
            {
                return m_cMapAddresses; 
            }
            
            inline vector<PeerNode*>& getNodeList()
            {
                return m_cPeerNodeLst;
            }
            
            inline bool AlreadyHaveNode()
            {
                return !m_cPeerNodeLst.empty();
            }

            inline const CAddress& getLocakAddr()
            {
                return m_cAddrLocalHost;
            }
            
            inline map<CInv, int64>& getMapAlreadyAskedFor()
            {
                return m_mapAlreadyAskedFor;
            }
            
            inline void removeAlreadyAskedFor(const CInv& inv)
            {
                m_mapAlreadyAskedFor.erase(inv);
            }

            const map<CInv, CTransaction>& getMapRelay()const
            {
                return m_mapRelay;
            }
        private:
            NetWorkServ();
            ~NetWorkServ();
            bool LoadAddresses();
            bool AddUserProviedAddress();
            void AddNewAddrByEndPoint(const char* endPoint);
            bool GetMyExternalIP(unsigned int& ipRet);
            bool GetMyExternalIP2(const CAddress& addrConnect, 
                                    const char* pszGet, const char* pszKeyword, unsigned int& ipRet);
        
            void AddAddress(const ServMsg& cMsg);
        
            map<unsigned int, vector<CAddress> > selectIp(unsigned int ipC);
            vector<unsigned int> getIPCList();
            void AddrConvertPeerNode();
            void DealPeerNodeMsg(void* zmqSock);
            void UpdatePeerNodeStatu();
        private:
            
            int nDropMessagesTest = 0; // 消息采集的频率，即是多个少消息采集一次进行处理
            int m_iSocketFd = 0;
            bool m_bClient = false;
            uint64 m_nLocalServices = (m_bClient ? 0 : NODE_NETWORK);
            CAddress m_cAddrLocalHost;// = new CAddress(0, DEFAULT_PORT, m_nLocalServices);// 本地主机地址
            PeerNode* m_pcNodeLocalHost;// = new PeerNode(INVALID_SOCKET, CAddress("127.0.0.1", m_nLocalServices)); // 本地节点
            
            vector<PeerNode*> m_cPeerNodeLst; //value is node
            map<string, CAddress> m_cMapAddresses;
            CAddress addrProxy;

            list<ThreadGuard*> m_ThreadList;
            std::mutex m_cAddrMutex;
            map<CInv, CTransaction> m_mapRelay; // 重新转播的内容
            deque<pair<int64, CInv> > m_vRelayExpiration;
            map<CInv, int64> m_mapAlreadyAskedFor;
            void* m_cZmqCtx; 
            string m_strIdentity;
            static NetWorkServ* m_pInstance;
            static pthread_mutex_t m_NWSLock;
        
    };

}


#endif /* EZ_BT_NWS_H */
/* EOF */

