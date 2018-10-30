/*
 * =====================================================================================
 *
 *       Filename:  ZMQNode.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/20/2018 07:38:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  enze (), 767201935@qq.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef EN_BT_ZMQ_NODE_H
#define EN_BT_ZMQ_NODE_H
#include <mutex>
#include "ProtocSrc/Message.pb.h"
#include "CRequestTracker.h"
#include "zhelpers.h"
#include "CAddress.h"
#include "CInv.h"

namespace Enze {
class CBlockLocator;
class CTransaction;
class CBlock;

class ZNode 
{
public:
    ZNode(const string& id, void* ctx, const CAddress& addrIn, bool fInboundIn=false);
    ZNode(const string& id, void* ctx, const char* endPoint);
    ~ZNode();
      
    void Disconnect();
    // ׼���ͷ�����
    bool ReadyToDisconnect();
    // ��ȡ��Ӧ��Ӧ�ü���
    int GetRefCount();
    // ���Ӷ�Ӧ��Ӧ�ü���
    void AddRef(int64 nTimeout=0);
    // �ڵ��ͷŶ�Ӧ�����Ӧ��Ӧ�ü�����1
    void Release();
    
    // ���ӿ��
    void AddInventoryKnown(const CInv& inv);

    // ���Ϳ��
    void PushInventory(const CInv& inv);
    
    void AskFor(const CInv& inv);
  
    void SendSelfAddr();
    void SendSelfInv();
    void SendGetDataReq();
    
    void SendVersion();
    void SendAddr(const vector<CAddress>& addr);
    void SendTx(const CTransaction& tx);
    void SendBlock(const CBlock& block);
    void SendGetBlocks(const CBlockLocator& local, const uint256& hash);
    void SendGetAddrRequest();
    void SendInv(const vector<CInv>& vInv, bool bReqInv); 
    bool pingNode();
    const char* getServId()const;
    
    void AddRecvMessage(PB_MessageData* pRecvData);
    bool ProcessMsg();
    void Recv();
    void Send();
   
    inline void setReleaseTime(int64 nTime)
    {
        m_nReleaseTime = nTime;
    }
    
    inline int64 getReleaseTime()const
    {
        return m_nReleaseTime;
    }
   
    inline void setNetworkState(bool bNetworkNode)
    {
        m_bNetworkNode = bNetworkNode;
    }
    
    inline void setConnecState(bool bConnect)
    {
        m_bDisconnect = bConnect;
    }
    
    inline bool isNetworkNode() const
    {
        return m_bNetworkNode;
    }
    
    inline bool isDistconnect()const 
    {
        return m_bDisconnect;
    }
    
    inline const CAddress& getAddr()const 
    {
        return m_cAddr;
    }
    
    inline void* getPeerSock() 
    {
        return m_cP2PSocket;
    
    }
    
    inline int getVesiong()const
    {
        return m_nVersion;
    }
    
    inline bool isExsitAddr(const CAddress& addr)
    {
        return m_setAddrKnown.count(addr);
    }
    
    inline void AddAddr2Send(const CAddress& addr)
    {
        m_vAddrToSend.push_back(addr); 
    }
private:
    void ProcessVerMsg(const Version& cVer);
    void ProcessAddrMsg(const Address& vAddr);
    void ProcessInvMsg(const Inventory& vInv);
    void ProcessGetDataMsg(const Inventory& vInv);
    void ProcessGetBlockMsg(const GetBlocks& cBks);
    void ProcessTxMsg(const Transaction& cTx);
    void ProcessReviewMsg(const Review& cRev);
    void ProcessSubmitOrderMsg(const Order& cOrd, map<unsigned int, vector<unsigned char> >& mapReuseKey);
    void ProcessCheckOrderMsg(const Order& cOrd, map<unsigned int, vector<unsigned char> >& mapReuseKey);
    void ProcessBlockMsg(const Block& cbk);
    void ProcessHashReplyMsg(const string& strReply);
    void ProcessGetAddrMsg(); 
    PB_MessageData* popRecvMsg();
    
private:
        bool m_bInbound;
        bool m_bNetworkNode; // ���ö�Ӧ�Ľڵ�Ϊ����ڵ㣬����Ϊ�Ӷ�Ӧ�ı��ؽڵ��б���û�в�ѯ��
        bool m_bDisconnect; // �˿����ӵı��
        bool m_bClient;// �Ƚ��Ƿ��ǿͻ��ˣ�����ǿͻ�������Ҫ�����ͷ������У��Ϳ�����,����Ҫ�����������������
        int m_nRefCount; // ʹ�ü�����
        int m_nVersion; // �ڵ��Ӧ�İ汾������ڵ�汾Ϊ0������Ϣ���Ͳ���ȥ
        int64 m_nReleaseTime; // �ڵ��ͷŵ�ʱ��
        uint64 m_nServices;
        CAddress m_cAddr;
        string m_Id;
        string m_EndPoint;
        string m_ServId;
        void*  m_cP2PSocket;
        list<PB_MessageData*> m_SendLst; // ���ͻ�����
        list<PB_MessageData*> m_RecvLst; // ���ջ�����
        std::mutex m_cSndMtx;
        std::mutex m_cRcvMtx;

        map<uint256, CRequestTracker> m_mapRequests;

        // flood �鷺����ַ��Ϣ������Ϊaddr
        vector<CAddress> m_vAddrToSend; // ��Ϣ��Ҫ���Ͷ�Ӧ�ĵ�ַ������Ҫ���͵ĵ�ַ������֪��ַ�ļ��Ϲ���֮���ٷ���
        set<CAddress> m_setAddrKnown; // ��֪��ַ�ļ���

        // inventory based relay  ����ת���Ŀ�棺�����Ϣ������Ϊinv
        set<CInv> m_setInventoryKnown; // ��֪���ļ���
        set<CInv> m_setInventoryKnown2;
        vector<CInv> m_vInventoryToSend; //���׼�����͵ļ��ϣ��Կ��׼�����͵ļ��ϸ�����֪���ļ��Ͻ��й���֮���ڷ���
        multimap<int64, CInv> m_mapAskFor; // ��ѯ����ӳ�䣬keyΪʱ�䣨��λ��΢�룩
private:
        ZNode(const ZNode&)= delete;
        ZNode() = delete;
        ZNode operator =(const ZNode&) = delete;
};




} /* End namespace */



#endif /* EN_BT_ZMQ_NODE_H */
/* EOF */
