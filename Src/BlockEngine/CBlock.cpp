/*
 * =====================================================================================
 *
 *       Filename:  CBlock.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/02/2018 07:24:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  enze (), 767201935@qq.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "BlockEngine.h"
#include "BlockEngine/CBlock.h"
#include "BlockEngine/CBlockIndex.h"
#include "BlockEngine/CDiskBlockIndex.h"
#include "BlockEngine/CDiskTxPos.h"
#include "NetWorkService/NetWorkServ.h"
#include "NetWorkService/CInv.h"
#include "WalletService/CTxIndex.h"
#include "WalletService/WalletServ.h"
#include "DAO/DaoServ.h"
#include "CommonBase/ProtocSerialize.h"
#include "ProtocSrc/Block.pb.h"
using namespace Enze;

// �������ӣ�ÿһ���������ӣ����ӵ�������������
bool CBlock::ConnectBlock(CBlockIndex* pindex)
{
    //// issue here: it doesn't know the version
    printf("error %s_%d\n", __FILE__, __LINE__);
    unsigned int nTxPos = pindex->m_nBlockPos;// + ::GetSerializeSize(CBlock(), SER_DISK) - 1 + GetSizeOfCompactSize(m_vTrans.size());

    map<uint256, CTxIndex> mapUnused;
    int64 nFees = 0;
    foreach(CTransaction& tx, m_vTrans)
    {
        CDiskTxPos posThisTx(pindex->m_nFile, pindex->m_nBlockPos, nTxPos);
        printf("%s---%d\n", __FILE__, __LINE__); 
        //nTxPos += ::GetSerializeSize(tx, SER_DISK);
		// ��ÿһ�����׽������������ж�
        if (!tx.ConnectInputs(mapUnused, posThisTx, pindex->m_nCurHeight, nFees, true, false))
            return false;
    }
	// �һ������ж�Ӧ��������ܴ���������Ӧ�Ľ���+����������
    if (m_vTrans[0].GetValueOut() > GetBlockValue(nFees))
        return false;

    // Update block index on disk without changing it in memory.
    // The memory index structure will be changed after the db commits.
    if (pindex->m_pPrevBlkIndex)
    {
		// ����ǰ�������� ���� ǰһ����������֮��
        CDiskBlockIndex blockindexPrev(pindex->m_pPrevBlkIndex);
        blockindexPrev.m_NextHash = pindex->GetBlockHash();
        DaoServ::getInstance()->WriteBlockIndex(blockindexPrev);
    }

	// ������block����Щ
    // Watch for transactions paying to me
    foreach(CTransaction& tx, m_vTrans)
        WalletServ::getInstance()->AddToWalletIfMine(tx, this);
    return true;
}

//////////////////////////////////////////////////////////////////////////////
//
// CBlock and CBlockIndex
//
// �����������������ݿ��ļ��ж�ȡ��Ӧ��������Ϣ
bool CBlock::ReadFromDisk(const CBlockIndex* pblockindex, bool fReadTransactions)
{
    return ReadFromDisk(pblockindex->m_nFile, pblockindex->m_nBlockPos, fReadTransactions);
}

// ��ȡ��������Ӧ�ļ�ֵ������+���������ѣ�
int64 CBlock::GetBlockValue(int64 nFees) const
{
    int nBestHeight = BlockEngine::getInstance()->getBestHeight();
	// ����;��������ʼ������50�����ر�
    int64 nSubsidy = 50 * COIN;

	// ������ÿ4���һ�룬������2100��
	// nBestHeight �����������ÿ����210000��block���Ӧ�Ľ������룬������һ��block��Ҫ10����
	// �����210000��block��Ҫ��ʱ���� 210000*10/(60*24*360)=4.0509...���꣩ ������ÿ4���һ��
    // Subsidy is cut in half every 4 years
    nSubsidy >>= (nBestHeight / 210000);

    return nSubsidy + nFees;
}

// ��һ������block�Ͽ����ӣ������ͷ������Ӧ����Ϣ��ͬʱ�ͷ������Ӧ������������
bool CBlock::DisconnectBlock(CBlockIndex* pindex)
{
	// �����ͷŽ��׵�����
    // Disconnect in reverse order
    for (int i = m_vTrans.size()-1; i >= 0; i--)
        if (!m_vTrans[i].DisconnectInputs())
            return false;

	// ������������
    // Update block index on disk without changing it in memory.
    // The memory index structure will be changed after the db commits.
    if (pindex->m_pPrevBlkIndex)
    {
		// ����ǰ����������Ӧ��ǰһ������������hashNextֵΪ0����ʾ����ǰ����������ǰһ����������������ȥ��
        CDiskBlockIndex blockindexPrev(pindex->m_pPrevBlkIndex);
        blockindexPrev.m_NextHash = 0;
        DaoServ::getInstance()->WriteBlockIndex(blockindexPrev);
    }

    return true;
}

// ����ǰ�������ӵ���Ӧ��������������mapBlockIndex
bool CBlock::AddToBlockIndex(unsigned int nFile, unsigned int nBlockPos)
{
    printf("CBlock::AddToBlockIndex--- serail--nFile[%d]\n", nFile);
    const map<uint256, CBlockIndex*>& mapBlockIndex = BlockEngine::getInstance()->getMapBlockIndex();
    // Check for duplicate
    uint256 hash = GetHash();
    if (mapBlockIndex.count(hash))
        return error("AddToBlockIndex() : %s already exists", hash.ToString().substr(0,14).c_str());
    printf("CBlock::AddToBlockIndex--- serail----111\n");
    // Construct new block index object
    CBlockIndex* pindexNew = new CBlockIndex(nFile, nBlockPos, *this);
    if (!pindexNew)
        return error("AddToBlockIndex() : new CBlockIndex failed");
    //map<uint256, CBlockIndex*>::iterator mi = mapBlockIndex.insert(make_pair(hash, pindexNew)).first;
    map<uint256, CBlockIndex*>::iterator mi = BlockEngine::getInstance()->insertBlockIndex(make_pair(hash, pindexNew));
    pindexNew->m_pHashBlock = &((*mi).first);
    map<uint256, CBlockIndex*>::const_iterator miPrev = mapBlockIndex.find(m_hashPrevBlock);
      printf("CBlock::AddToBlockIndex--- serail----222\n");
    if (miPrev != mapBlockIndex.end())
    {
        pindexNew->m_pPrevBlkIndex = (*miPrev).second;
		// ����ǰһ������������Ӧ�ĸ߶�
        pindexNew->m_nCurHeight = pindexNew->m_pPrevBlkIndex->m_nCurHeight + 1;
    }
      printf("CBlock::AddToBlockIndex--- serail----333\n");
    DaoServ::getInstance()->WriteBlockIndex(CDiskBlockIndex(pindexNew));

	// ���������Ӧ��ָ��
    // New best
	// �����ĸ߶��Ѿ����������ˣ�������������������ĳ��� ���� ���ڵ���Ϊ���������������ĳ���
    const int nBestHeight = BlockEngine::getInstance()->getBestHeight();
    const uint256& hashGenesisBlock = BlockEngine::getInstance()->getGenesisHash();
    const CBlockIndex* pindexGenesisBlock = BlockEngine::getInstance()->getGenesisBlock();
    const uint256& hashBestChain = BlockEngine::getInstance()->getHashBestChain();
    const CBlockIndex* pindexBest = BlockEngine::getInstance()->getBestIndex();
      printf("CBlock::AddToBlockIndex--- serail----444--CurHeight[%d]---nBestHeight[%d]\n",pindexNew->m_nCurHeight, nBestHeight);
    if (pindexNew->m_nCurHeight > nBestHeight)
    {
		// �ж��Ƿ��Ǵ�������
        if (pindexGenesisBlock == NULL && hash == hashGenesisBlock)
        {
            printf("CBlock::AddToBlockIndex--- serail----no pindexGenesisBlock\n");
            pindexGenesisBlock = pindexNew;
            DaoServ::getInstance()->WriteHashBestChain(hash);
        }
        else if (m_hashPrevBlock == hashBestChain)
        {
			// �����ǰ���Ӧ��ǰһ�����������
            // Adding to current best branch
            if (!ConnectBlock(pindexNew) || !DaoServ::getInstance()->WriteHashBestChain(hash))
            {
                pindexNew->EraseBlockFromDisk();
                BlockEngine::getInstance()->eraseBlockIndex(pindexNew->GetBlockHash());
                delete pindexNew;
                return error("AddToBlockIndex() : ConnectBlock failed");
            }
			// ���������У������ö�Ӧ����������m_pNextBlkIndex�ֶΣ�����ǰ��������������ǰһ�����������ĺ���
            pindexNew->m_pPrevBlkIndex->m_pNextBlkIndex = pindexNew;

			// �����Ӧ�������Ѿ����뵽�����У����Ӧ�����齻��Ӧ��Ҫ�ӱ��ڵ㱣��Ľ����ڴ����ɾ��
            // Delete redundant memory transactions
            foreach(CTransaction& tx, m_vTrans)
                tx.RemoveFromMemoryPool();
        }
        else
        {
			// ��ǰ����Ȳ��Ǵ������飬�ҵ�ǰ�����Ӧ��ǰһ������Ҳ����������ϵ����
			// �ټ����������������ĳ��ȴ��ڱ��ڵ���Ϊ�����ĳ��ȣ����н����зֲ洦��
            // New best branch
            if (!BlockEngine::getInstance()->Reorganize(pindexNew))
            {
                return error("AddToBlockIndex() : Reorganize failed");
            }
        }

        printf("CBlock::AddToBlockIndex--- serail----888888\n");
        // New best link
        BlockEngine::getInstance()->setBestChain(hash);
        printf("CBlock::AddToBlockIndex--- serail----888--1111\n");
        BlockEngine::getInstance()->setBestIndex(pindexNew);
        printf("CBlock::AddToBlockIndex--- serail----8888--222\n");
        BlockEngine::getInstance()->setBestHeight(pindexNew->m_nCurHeight);
        printf("CBlock::AddToBlockIndex--- serail----888-333\n");
        WalletServ::getInstance()->incrTransactionsUpdatedTime();
        printf("AddToBlockIndex: new best=%s  height=%d\n", hashBestChain.ToString().substr(0,14).c_str(), BlockEngine::getInstance()->getBestHeight());
    }

      printf("CBlock::AddToBlockIndex--- serail----99999999\n");
	// ת����Щ��ĿǰΪֹ��û�н���block�е�Ǯ������
    // Relay wallet transactions that haven't gotten in yet
    if (pindexNew == pindexBest)
        WalletServ::getInstance()->RelayWalletTransactions();// �ڽڵ�֮�����ת��
     printf("CBlock::AddToBlockIndex--- serail----9999999910\n");
  //  MainFrameRepaint();
    return true;
}



// ����У��
bool CBlock::CheckBlock() const
{
    // These are checks that are independent of context
    // that can be verified before saving an orphan �¶� block.

    printf("error %s_%d\n", __FILE__, __LINE__);
    // Size limits
    //if (m_vTrans.empty() || m_vTrans.size() > MAX_SIZE || ::GetSerializeSize(*this, SER_DISK) > MAX_SIZE)
    //    return error("CheckBlock() : size limits failed");

	// block�Ĵ���ʱ�� ����ڵ�ǰʱ�� ����2��Сʱ
    // Check timestamp
    if (m_uTime > GetAdjustedTime() + 2 * 60 * 60)
        return error("CheckBlock() : block timestamp too far in the future");

	// �ڿ��бһ�����һ��Ҫ���ڣ����ҽ���ֻ�ܴ���һ��
    // First transaction must be coinbase, the rest must not be
    if (m_vTrans.empty() || !m_vTrans[0].IsCoinBase())
        return error("CheckBlock() : first tx is not coinbase");
    for (int i = 1; i < m_vTrans.size(); i++)
        if (m_vTrans[i].IsCoinBase())
            return error("CheckBlock() : more than one coinbase");

	// �Կ��еĽ��׽���У��
    // Check transactions
    foreach(const CTransaction& tx, m_vTrans)
        if (!tx.CheckTransaction())
            return error("CheckBlock() : CheckTransaction failed");

	// �Թ������Ѷ�ָ�����У��
    // Check proof of work matches claimed amount
    if (CBigNum().SetCompact(m_uBits) > bnProofOfWorkLimit)
        return error("CheckBlock() : m_uBits below minimum work");
	// ���㵱ǰ���hash�Ƿ������Ӧ�������Ѷ�ָ��
    if (GetHash() > CBigNum().SetCompact(m_uBits).getuint256())
        return error("CheckBlock() : hash doesn't match m_uBits");

	// ��Ĭ�˶�����Ӧ�ĸ�����У��
    // Check merkleroot
    if (m_hashMerkleRoot != BuildMerkleTree())
        return error("CheckBlock() : hashMerkleRoot mismatch");

    return true;
}
// �жϵ�ǰ�����ܹ�������
bool CBlock::AcceptBlock()
{
    const map<uint256, CBlockIndex*>& mapBlockIndex = BlockEngine::getInstance()->getMapBlockIndex();
    // Check for duplicate
    uint256 hash = GetHash();
    if (mapBlockIndex.count(hash)) 
        return error("AcceptBlock() : block already in mapBlockIndex");

    // Get prev block index
    map<uint256, CBlockIndex*>::const_iterator mi = mapBlockIndex.find(m_hashPrevBlock);
    if (mi == mapBlockIndex.end())
        return error("AcceptBlock() : prev block not found");
    CBlockIndex* pindexPrev = (*mi).second;

	// ��ǰ�鴴����ʱ��Ҫ����ǰһ�����Ӧ����λ��ʱ��
    // Check timestamp against prev
    if (m_uTime <= pindexPrev->GetMedianTimePast())
        return error("AcceptBlock() : block's timestamp is too early");

	//������֤��У�飺ÿһ���ڵ��Լ������Ӧ�Ĺ������Ѷ�
    // Check proof of work
    if (m_uBits != BlockEngine::getInstance()->GetNextWorkRequired(pindexPrev))
        return error("AcceptBlock() : incorrect proof of work");

    printf("error %s_%d\n", __FILE__, __LINE__);
    // Write block to history file
    //if (!BlockEngine::getInstance()->CheckDiskSpace(::GetSerializeSize(*this, SER_DISK)))
    //    return error("AcceptBlock() : out of disk space");
    unsigned int nFile;
    unsigned int nBlockPos;
	// ������Ϣд���ļ���
    bool fClient = false; 
    if (!WriteToDisk(!fClient, nFile, nBlockPos))
        return error("AcceptBlock() : WriteToDisk failed");
	// ���ӿ��Ӧ�Ŀ�������Ϣ
    if (!AddToBlockIndex(nFile, nBlockPos))
        return error("AcceptBlock() : AddToBlockIndex failed");

    if (BlockEngine::getInstance()->getHashBestChain() == hash)
        Enze::NetWorkServ::getInstance()->RelayInventory(CInv(MSG_BLOCK, hash));

    // // Add atoms to user reviews for coins created
    // vector<unsigned char> vchPubKey;
    // if (ExtractPubKey(vtx[0].vout[0].m_cScriptPubKey, false, vchPubKey))
    // {
    //     unsigned short nAtom = GetRand(USHRT_MAX - 100) + 100;
    //     vector<unsigned short> vAtoms(1, nAtom);
    //     AddAtomsAndPropagate(Hash(vchPubKey.begin(), vchPubKey.end()), vAtoms, true);
    // }

    return true;
}

// ���ݽ��׹�����Ӧ��Ĭ�˶���
uint256 CBlock::BuildMerkleTree() const
{
    m_vMerkleTree.clear();
    foreach(const CTransaction& tx, m_vTrans)
        m_vMerkleTree.push_back(tx.GetHash());
    int j = 0;
    for (int nSize = m_vTrans.size(); nSize > 1; nSize = (nSize + 1) / 2)
    {
        for (int i = 0; i < nSize; i += 2)
        {
            int i2 = min(i+1, nSize-1);
            m_vMerkleTree.push_back(Hash(BEGIN(m_vMerkleTree[j+i]),  END(m_vMerkleTree[j+i]),
                                       BEGIN(m_vMerkleTree[j+i2]), END(m_vMerkleTree[j+i2])));
        }
        j += nSize;
    }
    foreach(auto it ,m_vMerkleTree) {
        printf("CBlock::BuildMerkleTree---[%s]\n", it.ToString().c_str());
    }

    return (m_vMerkleTree.empty() ? 0 : m_vMerkleTree.back());
}
// ���ݽ��׶�Ӧ��������ý��׶�Ӧ��Ĭ�˶���֧
vector<uint256> CBlock::GetMerkleBranch(int nIndex) const
{
    if (m_vMerkleTree.empty())
        BuildMerkleTree();
    vector<uint256> vMerkleBranch;
    int j = 0;
    for (int nSize = m_vTrans.size(); nSize > 1; nSize = (nSize + 1) / 2)
    {
        int i = min(nIndex^1, nSize-1);
        vMerkleBranch.push_back(m_vMerkleTree[j+i]);
        nIndex >>= 1;
        j += nSize;
    }
    return vMerkleBranch;
}
// �жϵ�ǰ��Ӧ�Ľ���hash��Ĭ�˶���֧����֤��Ӧ�Ľ����Ƿ��ڶ�Ӧ��blcok��
uint256 CBlock::CheckMerkleBranch(uint256 hash, const vector<uint256>& vMerkleBranch, int nIndex)
{
    if (nIndex == -1)
        return 0;
    foreach(const uint256& otherside, vMerkleBranch)
    {
        if (nIndex & 1)
            hash = Hash(BEGIN(otherside), END(otherside), BEGIN(hash), END(hash));
        else
            hash = Hash(BEGIN(hash), END(hash), BEGIN(otherside), END(otherside));
        nIndex >>= 1;
    }
    return hash;
}

// ��blockд�뵽�ļ���
bool CBlock::WriteToDisk(bool fWriteTransactions, unsigned int& nFileRet, unsigned int& nBlockPosRet)
{
    // Open history file to append
    CAutoFile fileout = BlockEngine::getInstance()->AppendBlockFile(nFileRet);
    if (!fileout)
        return error("CBlock::WriteToDisk() : AppendBlockFile failed");
    if (!fWriteTransactions)
        fileout.nType |= SER_BLOCKHEADERONLY;

    Block cProtocData;
    printf("CBlock::WriteToDisk---start serail, hasmerkel [%s]\n", m_hashMerkleRoot.ToString().c_str());
    if (!SeriaBlock(*this, cProtocData))
    {
         printf("CBlock::WriteToDisk---fault serail\n");
        return false;
    }
    printf("CBlock::WriteToDisk---end serail\n");
    string strSerial;
    cProtocData.SerializePartialToString(&strSerial);

    // Write index header
    unsigned int nSize = strSerial.length();//fileout.GetSerializeSize(*this);
    printf("CBlock::WriteToDisk--- serail--Len[%d]\n", nSize);
    nBlockPosRet = ftell(fileout);

    if (nBlockPosRet == -1)
        return error("CBlock::WriteToDisk() : ftell failed");
    // ������Ϣͷ�Ͷ�Ӧ��Ĵ�Сֵ
    fileout.write((const char*)&nSize, sizeof(nSize));
     printf("CBlock::WriteToDisk--startPost[%d]- serail--Len[%d]---2\n", nBlockPosRet, nSize);
    // Write block
    // ��block������д�뵽�ļ���
    fileout.write(strSerial.c_str(), nSize);
    printf("CBlock::WriteToDisk--- serail--Len[%d]--3\n", nSize);
    return true;
}

// ���ļ��ж�ȡ����Ϣ
bool CBlock::ReadFromDisk(unsigned int nFile, unsigned int nBlockPos, bool fReadTransactions)
{
    SetNull();
    printf("CBlock::ReadFromDisk-----nBlockPos[%d]--1\n", nBlockPos);
    // Open history file to read
    CAutoFile filein = BlockEngine::getInstance()->OpenBlockFile(nFile, nBlockPos, "rb");
    if (!filein)
        return error("CBlock::ReadFromDisk() : OpenBlockFile failed");
    if (!fReadTransactions)
        filein.nType |= SER_BLOCKHEADERONLY;

    // Read block ���ļ��е����ݶ�ȡ������
    unsigned int nSize = 0;
    filein.read((char*)&nSize, sizeof(nSize));
    if (-1 == nSize)
        return error("CBlock::ReadFromDisk, Get Block Size");
    printf("CBlock::ReadFromDisk-----Size[%d]--2\n", nSize);
    char *buf = (char*)malloc(nSize);
    filein.read(buf, nSize);
    Block cProtoc;
 //   cProtoc.ParsePartialFromString(buf);
    cProtoc.ParsePartialFromArray(buf, nSize);
    UnSeriaBlock(cProtoc, *this);
  //  filein >> *this;

    // Check the header 1. ������֤���ѶȱȽ� 2. �����hashֵҪС�ڶ�Ӧ�Ĺ������Ѷ�
    if (CBigNum().SetCompact(m_uBits) > bnProofOfWorkLimit)
        return error("CBlock::ReadFromDisk() : m_uBits errors in block header");
    if (GetHash() > CBigNum().SetCompact(m_uBits).getuint256())
        return error("CBlock::ReadFromDisk() : GetHash() errors in block header");

    return true;
}


/* EOF */

