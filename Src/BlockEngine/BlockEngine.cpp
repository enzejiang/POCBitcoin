/*
 * =====================================================================================
 *
 *       Filename:  BlockEngine.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/05/2018 11:44:35 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  enze (), 767201935@qq.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "BlockEngine.h"
#include "headers.h"
#include "sha.h"
#include "market.h"
#include "util.h"
#include "CommonBase/CommDataDef.h"
#include "CommonBase/bignum.h"
#include "CommonBase/uint256.h"
#include "CommonBase/base58.h"
#include "NetWorkService/NetWorkServ.h"
#include "NetWorkService/PeerNode.h"
#include "BlockEngine/CBlock.h"
#include "BlockEngine/CBlockIndex.h"
#include "BlockEngine/CBlockLocator.h"
#include "DAO/DaoServ.h"
#include "WalletService/WalletServ.h"
#include "WalletService/CTxIndex.h"
using namespace Enze;

BlockEngine* BlockEngine::m_pInstance = NULL;
pthread_mutex_t BlockEngine::m_mutexLock;

BlockEngine* BlockEngine::getInstance()
{
    if (NULL == m_pInstance)
    {
        pthread_mutex_lock(&m_mutexLock); 
        
        if (NULL == m_pInstance) 
        {
            m_pInstance = new BlockEngine();
        }
        
        pthread_mutex_unlock(&m_mutexLock); 
    
    }
    
    return m_pInstance;
}

void BlockEngine::Destory()
{
    pthread_mutex_lock(&m_mutexLock); 
    if (NULL != m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
    pthread_mutex_unlock(&m_mutexLock); 

}

BlockEngine::BlockEngine()
: hashGenesisBlock("0xf510d86af37ae70980806706913a812d0b30350572dda9c748de079f3805dd76")
{

    pindexGenesisBlock = NULL; // �������Ӧ��������Ҳ���Ǵ��������Ӧ������
    nBestHeight = -1; // �����Ӧ������������Ӵ������鵽��ǰ�������һ�����飬�м���˶��ٸ�����
    hashBestChain = 0; // ������һ�������Ӧ��hash
    pindexBest = NULL; // ��¼��ǰ���������Ӧ����������ָ��


    // Settings
    fGenerateBitcoins = 1; // �Ƿ��ڿ󣬲������ر�
    mapBlockIndex.clear();
}

BlockEngine::~BlockEngine()
{

}

void BlockEngine::initiation()
{
    //
    // Load data files
    //
    string strErrors;
    int64 nStart, nEnd;
    printf("Loading block index...\n");
    if (!LoadBlockIndex())
        strErrors += "Error loading blkindex.dat      \n";
    printf(" block index %20I64d\n", nEnd - nStart);

    if (!strErrors.empty())
    {
        printf("Initiation Error\n");
        exit(-1);
    }

}

// ��ȡ�¶����Ӧ�ĸ�
uint256 BlockEngine::GetOrphanRoot(const CBlock* pblock)
{
    // Work back to the first block in the orphan chain
    while (mapOrphanBlocks.count(pblock->m_hashPrevBlock))
        pblock = mapOrphanBlocks[pblock->m_hashPrevBlock];
    return pblock->GetHash();
}


// ����ǰһ��block��Ӧ�Ĺ�������ȡ��һ��block��ȡ��Ҫ�Ĺ�����
unsigned int BlockEngine::GetNextWorkRequired(const CBlockIndex* pindexLast)
{
    const unsigned int nTargetTimespan = 14 * 24 * 60 * 60; // two weeks
    const unsigned int nTargetSpacing = 10 * 60; // 10���Ӳ���һ��block
	// ÿ��2016�����Ӧ�Ĺ������ѶȾ���Ҫ���¼���һ��
    const unsigned int nInterval = nTargetTimespan / nTargetSpacing; // �м���˶��ٸ�block 2016����
 //   printf("GetNextWorkRequired---bnProofOfWorkLimit[%0x]\n", bnProofOfWorkLimit.GetCompact());
	// ˵����ǰ����һ���������飬��Ϊ��ǰ���Ӧ��ǰһ������Ϊ��
    // Genesis block
    if (pindexLast == NULL)
        return bnProofOfWorkLimit.GetCompact();

	// ���������0�����й������Ѷȸı�
    // Only change once per interval
    if ((pindexLast->m_nCurHeight+1) % nInterval != 0)
        return pindexLast->m_uBits;

	// ��ǰ��2016������
    // Go back by what we want to be 14 days worth of blocks
    const CBlockIndex* pindexFirst = pindexLast;
    for (int i = 0; pindexFirst && i < nInterval-1; i++)
        pindexFirst = pindexFirst->m_pPrevBlkIndex;
    assert(pindexFirst);

	// ��ǰ�����ǰһ�����鴴��ʱ�� ��ȥ �ӵ�ǰ������ǰ��2016������õ����鴴��ʱ��
    // Limit adjustment step
    unsigned int nActualTimespan = pindexLast->m_uTime - pindexFirst->m_uTime;
    printf("  nActualTimespan = %d  before bounds\n", nActualTimespan);
    // ����Ŀ���Ѷȵ����Ŀ�Ȳ���̫��
	if (nActualTimespan < nTargetTimespan/4)
        nActualTimespan = nTargetTimespan/4;
    if (nActualTimespan > nTargetTimespan*4)
        nActualTimespan = nTargetTimespan*4;

	// ����Ŀ������Ѷȣ���ǰ�����Ӧ��ǰһ�������Ӧ��Ŀ���Ѷ� * ʵ��2016�����Ӧ�Ĵ���ʱ���� / Ŀ��ʱ����14��
    // Retarget
    CBigNum bnNew;
    bnNew.SetCompact(pindexLast->m_uBits);
    bnNew *= nActualTimespan;
    bnNew /= nTargetTimespan;

	// �������Ĺ������Ѷȣ�ֵԽ���Ӧ�Ĺ����Ѷ�ԽС��С�ڵ�ǰ��Ӧ�Ĺ������Ѷ�
    if (bnNew > bnProofOfWorkLimit)
        bnNew = bnProofOfWorkLimit;

    /// debug print
    printf("\n\n\nGetNextWorkRequired RETARGET *****\n");
    printf("nTargetTimespan = %d    nActualTimespan = %d\n", nTargetTimespan, nActualTimespan);
    printf("Before: %08x  %s\n", pindexLast->m_uBits, CBigNum().SetCompact(pindexLast->m_uBits).getuint256().ToString().c_str());
    printf("After:  %08x  %s\n", bnNew.GetCompact(), bnNew.getuint256().ToString().c_str());

    return bnNew.GetCompact();
}





// ������֯�������������Ϊ��ʱ�Ѿ������������ֲ�
bool BlockEngine::Reorganize(CBlockIndex* pindexNew)
{
    printf("*** REORGANIZE ***\n");

	// �ҵ�����ֲ��
    // Find the fork
    CBlockIndex* pfork = pindexBest;
    CBlockIndex* plonger = pindexNew;
	// �ҵ������ͷֲ�����Ӧ�Ľ����
    while (pfork != plonger)
    {
        if (!(pfork = pfork->m_pPrevBlkIndex))
            return error("Reorganize() : pfork->m_pPrevBlkIndex is null");
        while (plonger->m_nCurHeight > pfork->m_nCurHeight)
            if (!(plonger = plonger->m_pPrevBlkIndex))
                return error("Reorganize() : plonger->m_pPrevBlkIndex is null");
    }

	// �оٳ���ǰ�ڵ���Ϊ������У��ӵ�ǰ���������㣩ʧȥ���ӵĿ�
    // List of what to disconnect
    vector<CBlockIndex*> vDisconnect;
    for (CBlockIndex* pindex = pindexBest; pindex != pfork; pindex = pindex->m_pPrevBlkIndex)
        vDisconnect.push_back(pindex);

	// ��ȡ��Ҫ���ӵĿ飬��Ϊ�Լ���Ϊ�����ʵ���ϲ������
    // List of what to connect
    vector<CBlockIndex*> vConnect;
    for (CBlockIndex* pindex = pindexNew; pindex != pfork; pindex = pindex->m_pPrevBlkIndex)
        vConnect.push_back(pindex);
	// ��Ϊ��������ʱ���ǵ��ŷŵģ����������ڽ�������򣬵õ������
    reverse(vConnect.begin(), vConnect.end());

	// �ͷŶ����������ͷŶ�Ӧ��block������Ӧ��block��������û���ͷţ�
    // Disconnect shorter branch
    vector<CTransaction> vResurrect;
    foreach(CBlockIndex* pindex, vDisconnect)
    {
        CBlock block;
        if (!block.ReadFromDisk(pindex->m_nFile, pindex->m_nBlockPos, true))
            return error("Reorganize() : ReadFromDisk for disconnect failed");
        if (!block.DisconnectBlock(pindex))
            return error("Reorganize() : DisconnectBlock failed");

		// ���ͷſ��еĽ��׷���vResurrect���ȴ�����
        // Queue memory transactions to resurrect
        foreach(const CTransaction& tx, block.m_vTrans)
            if (!tx.IsCoinBase())
                vResurrect.push_back(tx);
    }

	// ������ķ�֧
    // Connect longer branch
    vector<CTransaction> vDelete;
    for (int i = 0; i < vConnect.size(); i++)
    {
        CBlockIndex* pindex = vConnect[i];
        CBlock block;
        if (!block.ReadFromDisk(pindex->m_nFile, pindex->m_nBlockPos, true))
            return error("Reorganize() : ReadFromDisk for connect failed");
        if (!block.ConnectBlock(pindex))
        {
			// ���block����ʧ��֮��˵�����block��Ч����ɾ�����֮��ķ�֧
            // Invalid block, delete the rest of this branch
            for (int j = i; j < vConnect.size(); j++)
            {
                CBlockIndex* pindex = vConnect[j];
                pindex->EraseBlockFromDisk();
                DaoServ::getInstance()->EraseBlockIndex(pindex->GetBlockHash());
                mapBlockIndex.erase(pindex->GetBlockHash());
                delete pindex;
            }
            return error("Reorganize() : ConnectBlock failed");
        }
		// �������������Ŀ��еĽ��״Ӷ�Ӧ���ڴ���ɾ��
        // Queue memory transactions to delete
        foreach(const CTransaction& tx, block.m_vTrans)
            vDelete.push_back(tx);
    }
	// д�����
    if (!DaoServ::getInstance()->WriteHashBestChain(pindexNew->GetBlockHash()))
        return error("Reorganize() : WriteHashBestChain failed");


	// �ͷŶ�Ӧ�Ŀ�������
    // Disconnect shorter branch
    foreach(CBlockIndex* pindex, vDisconnect)
        if (pindex->m_pPrevBlkIndex)
            pindex->m_pPrevBlkIndex->m_pNextBlkIndex = NULL; // ��ʾ��Щ��û����������

	// �γ�һ�������Ŀ�������
    // Connect longer branch
    foreach(CBlockIndex* pindex, vConnect)
        if (pindex->m_pPrevBlkIndex)
            pindex->m_pPrevBlkIndex->m_pNextBlkIndex = pindex;

	// ���ͷ����ӵķ�֧�л�ȡ��Ӧ�Ľ��ף�����Щ���׷����Ӧ��ȫ�ֱ����еõ�����
    // Resurrect memory transactions that were in the disconnected branch
    foreach(CTransaction& tx, vResurrect)
        tx.AcceptTransaction(false);

	// ��ȫ�ֱ�����ɾ����Щ�Ѿ��������еĽ���
    // Delete redundant memory transactions that are in the connected branch
    foreach(CTransaction& tx, vDelete)
        tx.RemoveFromMemoryPool();

    return true;
}

// �������飬�����ǽ��յ��Ļ����Լ��ڿ�õ���
bool BlockEngine::ProcessBlock(PeerNode* pfrom, CBlock* pblock)
{
    // Check for duplicate
    uint256 hash = pblock->GetHash();
    if (mapBlockIndex.count(hash))
        return error("ProcessBlock() : already have block %d %s", mapBlockIndex[hash]->m_nCurHeight, hash.ToString().substr(0,14).c_str());
    if (mapOrphanBlocks.count(hash))
        return error("ProcessBlock() : already have block (orphan) %s", hash.ToString().substr(0,14).c_str());

    // Preliminary checks ��������
    if (!pblock->CheckBlock())
    {
        delete pblock;
        return error("ProcessBlock() : CheckBlock FAILED");
    }

    // If don't already have its previous block, shunt it off to holding area until we get it
    if (!mapBlockIndex.count(pblock->m_hashPrevBlock))
    {
        printf("ProcessBlock: ORPHAN BLOCK, prev=%s\n", pblock->m_hashPrevBlock.ToString().substr(0,14).c_str());
        mapOrphanBlocks.insert(make_pair(hash, pblock));
        mapOrphanBlocksByPrev.insert(make_pair(pblock->m_hashPrevBlock, pblock));

        // Ask this guy to fill in what we're missing
        if (pfrom)
            pfrom->SendGetBlocks(CBlockLocator(pindexBest), GetOrphanRoot(pblock));
        return true;
    }

    // Store to disk
    if (!pblock->AcceptBlock())
    {
        delete pblock;
        return error("ProcessBlock() : AcceptBlock FAILED");
    }
    delete pblock;

    // Recursively process any orphan blocks that depended on this one
    vector<uint256> vWorkQueue;
    vWorkQueue.push_back(hash);
    for (int i = 0; i < vWorkQueue.size(); i++)
    {
        uint256 hashPrev = vWorkQueue[i];
        for (multimap<uint256, CBlock*>::iterator mi = mapOrphanBlocksByPrev.lower_bound(hashPrev);
             mi != mapOrphanBlocksByPrev.upper_bound(hashPrev);
             ++mi)
        {
            CBlock* pblockOrphan = (*mi).second;
            if (pblockOrphan->AcceptBlock())
                vWorkQueue.push_back(pblockOrphan->GetHash());
            mapOrphanBlocks.erase(pblockOrphan->GetHash());
            delete pblockOrphan;
        }
        mapOrphanBlocksByPrev.erase(hashPrev);
    }

    printf("ProcessBlock: ACCEPTED\n");
    return true;
}








template<typename Stream>
bool ScanMessageStart(Stream& s)
{
    // Scan ahead to the next pchMessageStart, which should normally be immediately
    // at the file pointer.  Leaves file pointer at end of pchMessageStart.
    s.clear(0);
    short prevmask = s.exceptions(0);
    const char* p = BEGIN(pchMessageStart);
    try
    {
        loop
        {
            char c;
            s.read(&c, 1);
            if (s.fail())
            {
                s.clear(0);
                s.exceptions(prevmask);
                return false;
            }
            if (*p != c)
                p = BEGIN(pchMessageStart);
            if (*p == c)
            {
                if (++p == END(pchMessageStart))
                {
                    s.clear(0);
                    s.exceptions(prevmask);
                    return true;
                }
            }
        }
    }
    catch (...)
    {
        s.clear(0);
        s.exceptions(prevmask);
        return false;
    }
}

string BlockEngine::GetAppDir()
{
    string strDir;
    if (!strSetDataDir.empty())
    {
        strDir = strSetDataDir;
    }
    else if (getenv("APPDATA"))
    {
        //strDir = strprintf("%s\\Bitcoin", getenv("APPDATA"));
		strDir = strprintf("%s\\Bitcoin-debug", getenv("APPDATA"));
    }
    else if (getenv("USERPROFILE"))
    {
        string strAppData = strprintf("%s\\Application Data", getenv("USERPROFILE"));
        static bool fMkdirDone;
        if (!fMkdirDone)
        {
            fMkdirDone = true;
            mkdir(strAppData.c_str(), 775);
        }
       // strDir = strprintf("%s\\Bitcoin", strAppData.c_str());
		strDir = strprintf("%s\\Bitcoin-debug", strAppData.c_str());
    }
    else
    {
        return ".";
    }
    static bool fMkdirDone;
    if (!fMkdirDone)
    {
        fMkdirDone = true;
        mkdir(strDir.c_str(), 775);
    }
    return strDir;
}

bool BlockEngine::CheckDiskSpace(int64 nAdditionalBytes)
{
#if 0
    uint64 nFreeBytesAvailable = 0;     // bytes available to caller
    uint64 nTotalNumberOfBytes = 0;     // bytes on disk
    uint64 nTotalNumberOfFreeBytes = 0; // free bytes on disk

    if (!GetDiskFreeSpaceEx(GetAppDir().c_str(),
            (PULARGE_INTEGER)&nFreeBytesAvailable,
            (PULARGE_INTEGER)&nTotalNumberOfBytes,
            (PULARGE_INTEGER)&nTotalNumberOfFreeBytes))
    {
        printf("ERROR: GetDiskFreeSpaceEx() failed\n");
        return true;
    }

    // Check for 15MB because database could create another 10MB log file at any time
    if ((int64)nFreeBytesAvailable < 15000000 + nAdditionalBytes)
    {
        fShutdown = true;
        //wxMessageBox("Warning: Your disk space is low  ", "Bitcoin", wxICON_EXCLAMATION);
        _beginthread(Shutdown, 0, NULL);
        return false;
    }
#endif
    return true;
}

// �򿪿��ļ�
// ֪�����ļ���ӦnFileֵ�Ϳ���֪�����Ӧ���ļ�����blk${nFile}.dat
FILE* BlockEngine::OpenBlockFile(unsigned int nFile, unsigned int nBlockPos, const char* pszMode)
{
    if (nFile == -1)
        return NULL;
    FILE* file = fopen(strprintf("%s\/blk%04d.dat", GetAppDir().c_str(), nFile).c_str(), pszMode);
    if (!file)
        return NULL;
    if (nBlockPos != 0 && !strchr(pszMode, 'a') && !strchr(pszMode, 'w'))
    {
		// ���ļ��и��ݿ��ƫ�ƽ��ж�λ�ļ�ָ��
        if (fseek(file, nBlockPos, SEEK_SET) != 0)
        {
            fclose(file);
            return NULL;
        }
    }
    return file;
}

// ȫ�־�̬���������ƶ�Ӧ�ĵ�ǰblock��Ӧ���ļ���ţ�Ҳ�����ļ�����
// ÿһ��block��Ӧһ���������ļ�
static unsigned int nCurrentBlockFile = 1;

// ���ص�ǰblockӦ���ڵ��ļ�ָ��
FILE* BlockEngine::AppendBlockFile(unsigned int& nFileRet)
{
    nFileRet = 0;
    loop
    {
        FILE* file = OpenBlockFile(nCurrentBlockFile, 0, "ab");
        if (!file)
            return NULL;
        if (fseek(file, 0, SEEK_END) != 0)
            return NULL;
        // FAT32 filesize max 4GB, fseek and ftell max 2GB, so we must stay under 2GB
        if (ftell(file) < 0x7F000000 - MAX_SIZE)
        {
            nFileRet = nCurrentBlockFile;
            return file;
        }
        fclose(file);
        nCurrentBlockFile++;
    }
}

bool BlockEngine::LoadBlockIndex(bool fAllowNew)
{
    mapBlockIndex.clear();
    //
    // Load block index
    //
    if (!DaoServ::getInstance()->LoadBlockIndex())
        return false;

    //
    // Init with genesis block
    //
    printf("---------------------------------\n");
    printf("---------mapBlockIndex [%d]--------------\n", mapBlockIndex.size());

    printf("---------------------------------\n");

    if (mapBlockIndex.empty())
    {
        if (!fAllowNew)
            return false;
        // Genesis block
        char* pszTimestamp = "The Times 03/Jan/2009 Chancellor on brink of second bailout for banks";
        CTransaction txNew;
        txNew.m_vTxIn.resize(1);
        txNew.m_vTxOut.resize(1);
        txNew.m_vTxIn[0].m_cScriptSig     = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((unsigned char*)pszTimestamp, (unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.m_vTxOut[0].m_nValue       = 50 * COIN;
        txNew.m_vTxOut[0].m_cScriptPubKey = CScript() << CBigNum("0x5F1DF16B2B704C8A578D0BBAF74D385CDE12C11EE50455F3C438EF4C3FBCF649B6DE611FEAE06279A60939E028A8D65C10B73071A6F16719274855FEB0FD8A6704") << OP_CHECKSIG;
        CBlock block;
        block.m_vTrans.push_back(txNew);
        block.m_hashPrevBlock = 0;
        block.m_hashMerkleRoot = block.BuildMerkleTree();
        block.m_nCurVersion = 1;
        block.m_uTime    = 1231006505;
        block.m_uBits    = bnProofOfWorkLimit.GetCompact();//0x1d00ffff;
        block.m_uNonce   = 2083236893;

        //// debug print, delete this later
        printf("BlockEngine::LoadBlockIndex, Hash[%s]\n", block.GetHash().ToString().c_str());
        printf("BlockEngine::LoadBlockIndex, merkelRoot[%s]\n", block.m_hashMerkleRoot.ToString().c_str());
       // printf("%s\n", hashGenesisBlock.ToString().c_str());
       // txNew.m_vTxOut[0].m_cScriptPubKey.print();
        //block.print();
        //assert(block.m_hashMerkleRoot == uint256("0x4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b"));
        assert(block.m_hashMerkleRoot == uint256("0x0e5ce7366413c7c0dc91923b90a7a9cf1575ece3b492baf74e02cc6b67c52845"));

        assert(block.GetHash() == hashGenesisBlock);

        // Start new block file
        unsigned int nFile;
        unsigned int nBlockPos;
        bool fClient = false;
        printf("BlockEngine::LoadBlockInde--start write to disk\n");
        if (!block.WriteToDisk(!fClient, nFile, nBlockPos))
            return error("LoadBlockIndex() : writing genesis block to disk failed");
        if (!block.AddToBlockIndex(nFile, nBlockPos))
            return error("LoadBlockIndex() : genesis block not accepted");
    }

    return true;
}



void BlockEngine::PrintBlockTree()
{
    // precompute tree structure
    map<CBlockIndex*, vector<CBlockIndex*> > mapNext;
    for (map<uint256, CBlockIndex*>::iterator mi = mapBlockIndex.begin(); mi != mapBlockIndex.end(); ++mi)
    {
        CBlockIndex* pindex = (*mi).second;
        mapNext[pindex->m_pPrevBlkIndex].push_back(pindex);
        // test
        //while (rand() % 3 == 0)
        //    mapNext[pindex->m_pPrevBlkIndex].push_back(pindex);
    }

    vector<pair<int, CBlockIndex*> > vStack;
    vStack.push_back(make_pair(0, pindexGenesisBlock));

    int nPrevCol = 0;
    while (!vStack.empty())
    {
        int nCol = vStack.back().first;
        CBlockIndex* pindex = vStack.back().second;
        vStack.pop_back();

        // print split or gap
        if (nCol > nPrevCol)
        {
            for (int i = 0; i < nCol-1; i++)
                printf("| ");
            printf("|\\\n");
        }
        else if (nCol < nPrevCol)
        {
            for (int i = 0; i < nCol; i++)
                printf("| ");
            printf("|\n");
        }
        nPrevCol = nCol;

        // print columns
        for (int i = 0; i < nCol; i++)
            printf("| ");

        // print item
        CBlock block;
        block.ReadFromDisk(pindex, true);
#if 0
        printf("%d (%u,%u) %s  %s  tx %d",
            pindex->m_nCurHeight,
            pindex->nFile,
            pindex->nBlockPos,
            block.GetHash().ToString().substr(0,14).c_str(),
            DateTimeStr(block.m_uTime).c_str(),
            block.m_vTrans.size());
        //CRITICAL_BLOCK(cs_mapWallet)
        {
            if (mapWallet.count(block.m_vTrans[0].GetHash()))
            {
                CWalletTx& wtx = mapWallet[block.m_vTrans[0].GetHash()];
                printf("    mine:  %d  %d  %d", wtx.GetDepthInMainChain(), wtx.GetBlocksToMaturity(), wtx.GetCredit());
            }
        }
        printf("\n");


        // put the main timechain first
        vector<CBlockIndex*>& vNext = mapNext[pindex];
        for (int i = 0; i < vNext.size(); i++)
        {
            if (vNext[i]->m_pNextBlkIndex)
            {
                printf("error %s_%d\n", __FILE__, __LINE__);
                //swap(vNext[0], vNext[i]);
                break;
            }
        }

        // iterate children
        for (int i = 0; i < vNext.size(); i++)
            vStack.push_back(make_pair(nCol+i, vNext[i]));
#endif

    }
}






int BlockEngine::FormatHashBlocks(void* pbuffer, unsigned int len)
{
    unsigned char* pdata = (unsigned char*)pbuffer;
    unsigned int blocks = 1 + ((len + 8) / 64);
    unsigned char* pend = pdata + 64 * blocks;
    memset(pdata + len, 0, 64 * blocks - len);
    pdata[len] = 0x80;
    unsigned int bits = len * 8;
    pend[-1] = (bits >> 0) & 0xff;
    pend[-2] = (bits >> 8) & 0xff;
    pend[-3] = (bits >> 16) & 0xff;
    pend[-4] = (bits >> 24) & 0xff;
    return blocks;
}

using CryptoPP::ByteReverse;
static int detectlittleendian = 1;

// ����hash
void BlockEngine::BlockSHA256(const void* pin, unsigned int nBlocks, void* pout)
{
    unsigned int* pinput = (unsigned int*)pin;
    unsigned int* pstate = (unsigned int*)pout;

    CryptoPP::SHA256::InitState(pstate);

    // ����Ǵ�˻���С��
    if (*(char*)&detectlittleendian != 0)
    {
        for (int n = 0; n < nBlocks; n++)
        {
            unsigned int pbuf[16];
            // ��С�˵����⽫�ֽڷ�ת
            for (int i = 0; i < 16; i++)
                pbuf[i] = ByteReverse(pinput[n * 16 + i]);
            CryptoPP::SHA256::Transform(pstate, pbuf);
        }
        for (int i = 0; i < 8; i++)
            pstate[i] = ByteReverse(pstate[i]);
    }
    else
    {
        for (int n = 0; n < nBlocks; n++)
            CryptoPP::SHA256::Transform(pstate, pinput + n * 16);
    }
}

// �ڵ��ڿ�
bool BlockEngine::BitcoinMiner()
{
    printf("BitcoinMiner started\n");
    ////SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_LOWEST);

    CKey key;
    key.MakeNewKey(); // ʹ����Բ�����㷨���һ�Թ�Կ��˽Կ
	// �������0��ʼ
    CBigNum bnExtraNonce = 0;
    while (fGenerateBitcoins)
    {
        sleep(10*3);

        while (!NetWorkServ::getInstance()->AlreadyHaveNode())
        {
            printf("**************************\nBitcoinMiner ---Do not Have Node\n*************************\n");
            sleep(30);
        }

        unsigned int nTransactionsUpdatedLast = WalletServ::getInstance()->getTransactionsUpdatedTime();
        CBlockIndex* pindexPrev = pindexBest;
        if (NULL == pindexPrev) {
            printf("**************************\nBitcoinMiner---pindexPrev == NULL\n*************************\n");
        }
		// ��ȡ�ڿ��Ѷ�
        unsigned int m_uBits = GetNextWorkRequired(pindexPrev);
       // printf("BitcoinMiner---[%0x]--prev Hash [%s]\n", m_uBits, pindexPrev->GetBlockHash().ToString().c_str());

        // �����һ�����
        // Create coinbase tx
        //
        CTransaction txNew;
        txNew.m_vTxIn.resize(1);
        txNew.m_vTxIn[0].m_cPrevOut.SetNull();
        txNew.m_vTxIn[0].m_cScriptSig << m_uBits << ++bnExtraNonce;
        txNew.m_vTxOut.resize(1);
        txNew.m_vTxOut[0].m_cScriptPubKey << key.GetPubKey() << OP_CHECKSIG;


        // �����µ�����
        // Create new block
        //
        auto_ptr<CBlock> pblock(new CBlock());
        if (!pblock.get())
            return false;

		// ���ӱһ�������������ĵ�һ������
        // Add our coinbase tx as first transaction
        pblock->m_vTrans.push_back(txNew);

		// �ռ����µĽ��׷���������
        // Collect the latest transactions into the block
        int64 nFees = 0;
        //CRITICAL_BLOCK(cs_main)
        //CRITICAL_BLOCK(cs_mapTransactions)
        map<uint256, CTransaction>& mapTransactions = WalletServ::getInstance()->getMapTransactions();
        {
            map<uint256, CTxIndex> mapTestPool;
            vector<char> vfAlreadyAdded(mapTransactions.size());
            bool fFoundSomething = true;
            unsigned int nBlockSize = 0;
            // ���ѭ������Ϊ�Ƕ��̣߳����ܸտ�ʼ��Ӧ�Ľ���û����ô�࣬���ڵȴ����ף����д����ֻ�ȴ�һ�֣����mapTransactions�кཻܶ����һ����
            while (fFoundSomething && nBlockSize < MAX_SIZE/2)
            {
                fFoundSomething = false;
                unsigned int n = 0;
                for (map<uint256, CTransaction>::iterator mi = mapTransactions.begin(); mi != mapTransactions.end(); ++mi, ++n)
                {
                    if (vfAlreadyAdded[n])
                        continue;
                    CTransaction& tx = (*mi).second;
                    if (tx.IsCoinBase() || !tx.IsFinal())
                        continue;

                    // Transaction fee requirements, mainly only needed for flood control
                    // Under 10K (about 80 inputs) is free for first 100 transactions
                    // Base rate is 0.01 per KB
                    // ���ݷ������ж�ÿһ��������Ҫ�����ٷ���
                    int64 nMinFee = tx.GetMinFee(pblock->m_vTrans.size() < 100);

                    map<uint256, CTxIndex> mapTestPoolTmp(mapTestPool);
                    // �жϵ�ǰ�����Ƿ������Ӧ����ͷ���Ҫ�󣬶�Ӧ��nFees��ConnectInputs�ǽ����ۼӵ�
                    if (!tx.ConnectInputs(mapTestPoolTmp, CDiskTxPos(1,1,1), 0, nFees, false, true, nMinFee))
                        continue;
                    swap(mapTestPool, mapTestPoolTmp);

                    pblock->m_vTrans.push_back(tx);
                    printf("error %s--%d\n", __FILE__, __LINE__);
                    //nBlockSize += ::GetSerializeSize(tx, SER_NETWORK); // ����ǰ�����Ľ��״�С�����Ӧ�Ŀ��С��
                    vfAlreadyAdded[n] = true;
                    fFoundSomething = true;
                }
            }
        }
        pblock->m_uBits = m_uBits; // ���ö�Ӧ���ڿ��Ѷ�ֵ
        pblock->m_vTrans[0].m_vTxOut[0].m_nValue = pblock->GetBlockValue(nFees); // ���ö�Ӧ�Ŀ��һ�����׶�Ӧ�������Ӧ��ֵ=���� + ���׷���
        printf("\n\nRunning BitcoinMiner with %d transactions in block, uBit[%0x]\n", pblock->m_vTrans.size(), m_uBits);


        //
        // Prebuild hash buffer
        //
        struct unnamed1
        {
            struct unnamed2
            {
                int nVersion;
                uint256 hashPrevBlock;
                uint256 hashMerkleRoot;
                unsigned int m_uTime;
                unsigned int m_uBits;
                unsigned int m_uNonce;
            }
            block;
            unsigned char pchPadding0[64];
            uint256 hash1;
            unsigned char pchPadding1[64];
        }
        tmp;

        tmp.block.nVersion       = pblock->m_nCurVersion;
        tmp.block.hashPrevBlock  = pblock->m_hashPrevBlock  = (pindexPrev ? pindexPrev->GetBlockHash() : 0);
        tmp.block.hashMerkleRoot = pblock->m_hashMerkleRoot = pblock->BuildMerkleTree();
        // ȡǰ11�������Ӧ�Ĵ���ʱ���Ӧ����λ��
        tmp.block.m_uTime          = pblock->m_uTime          = max((pindexPrev ? pindexPrev->GetMedianTimePast()+1 : 0), GetAdjustedTime());
        tmp.block.m_uBits          = pblock->m_uBits          = m_uBits;
        tmp.block.m_uNonce         = pblock->m_uNonce         = 1; // �������1��ʼ

        unsigned int nBlocks0 = FormatHashBlocks(&tmp.block, sizeof(tmp.block));
        unsigned int nBlocks1 = FormatHashBlocks(&tmp.hash1, sizeof(tmp.hash1));


        //
        // Search
        //
        unsigned int nStart = GetTime();
        uint256 hashTarget = CBigNum().SetCompact(pblock->m_uBits).getuint256(); // �����Ѷ�ϵ��ֵ��ȡ��Ӧ��hashĿ��ֵ
        printf("BitcoinMiner: hashTarget[%s]--nBlocks0[%u]--nBlocks1[%u]\n", hashTarget.ToString().c_str(), nBlocks0, nBlocks1);
        uint256 hash;
        loop
        {
            BlockSHA256(&tmp.block, nBlocks0, &tmp.hash1);
            BlockSHA256(&tmp.hash1, nBlocks1, &hash);


            // �ڿ�ɹ�
            if (hash <= hashTarget)
            {
                pblock->m_uNonce = tmp.block.m_uNonce;
                assert(hash == pblock->GetHash());

                //// debug print
                printf("BitcoinMiner:\n");
                printf("proof-of-work found  \n  hash: %s  \ntarget: %s\n", hash.GetHex().c_str(), hashTarget.GetHex().c_str());
                pblock->print();

                // Save key
                if (!WalletServ::getInstance()->AddKey(key))
                    return false;
                key.MakeNewKey();

                // Process this block the same as if we had received it from another node
                if (!ProcessBlock(NULL, pblock.release()))
                    printf("ERROR in BitcoinMiner, ProcessBlock, block not accepted\n");

                sleep(5);
                break;
            }

            // �������鴴��ʱ�䣬���������ڿ�
            // Update m_uTime every few seconds
            if ((++tmp.block.m_uNonce & 0x3ffff) == 0)
            {
                if (tmp.block.m_uNonce == 0)
                    break;
                if (pindexPrev != pindexBest)
                    break;
                if (WalletServ::getInstance()->getTransactionsUpdatedTime() != nTransactionsUpdatedLast && GetTime() - nStart > 60)
                    break;
                if (!fGenerateBitcoins)
                    break;
                tmp.block.m_uTime = pblock->m_uTime = max(pindexPrev->GetMedianTimePast()+1, GetAdjustedTime());
            }
        }
    }

    return true;
}





/* EOF */

