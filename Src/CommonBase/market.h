// Copyright (c) 2009 Satoshi Nakamoto
// Distributed under the MIT/X11 software license, see the accompanying
// file license.txt or http://www.opensource.org/licenses/mit-license.php.
#ifndef EZ_BT_MARKET_H
#define EZ_BT_MARKET_H

#include "CommonBase/uint256.h"
#include "NetWorkService/CAddress.h"
#include "util.h"

namespace Enze
{


class CUser;
class CReview;
class CProduct;
class CAddress;
static const unsigned int nFlowthroughRate = 2;




bool AdvertInsert(const CProduct& product);
void AdvertErase(const CProduct& product);
bool AddAtomsAndPropagate(uint256 hashUserStart, const vector<unsigned short>& vAtoms, bool fOrigin);








class CUser
{
public:
    vector<unsigned short> vAtomsIn;
    vector<unsigned short> vAtomsNew;
    vector<unsigned short> vAtomsOut;
    vector<uint256> vLinksOut;

    CUser()
    {
    }


    void SetNull()
    {
        vAtomsIn.clear();
        vAtomsNew.clear();
        vAtomsOut.clear();
        vLinksOut.clear();
    }

    uint256 GetHash() const { return SerializeHash(*this); }


    int GetAtomCount() const
    {
        return (vAtomsIn.size() + vAtomsNew.size());
    }

    void AddAtom(unsigned short nAtom, bool fOrigin);
};







class CReview
{
public:
    int nVersion;
    uint256 hashTo;
    map<string, string> mapValue;
    vector<unsigned char> vchPubKeyFrom;
    vector<unsigned char> vchSig;

    // memory only
    unsigned int nTime;
    int nAtoms;


    CReview()
    {
        nVersion = 1;
        hashTo = 0;
        nTime = 0;
        nAtoms = 0;
    }

    uint256 GetHash() const { return SerializeHash(*this); }
    uint256 GetSigHash() const { return SerializeHash(*this, SER_GETHASH|SER_SKIPSIG); }
    uint256 GetUserHash() const { return Hash(vchPubKeyFrom.begin(), vchPubKeyFrom.end()); }


    bool AcceptReview();
};







class CProduct
{
public:
    int nVersion;
    CAddress addr;
    map<string, string> mapValue;
    map<string, string> mapDetails;
    vector<pair<string, string> > vOrderForm;
    unsigned int nSequence;
    vector<unsigned char> vchPubKeyFrom;
    vector<unsigned char> vchSig;

    // disk only
    int nAtoms;

    // memory only
    set<unsigned int> setSources;

    CProduct()
    {
        nVersion = 1;
        nAtoms = 0;
        nSequence = 0;
    }


    uint256 GetHash() const { return SerializeHash(*this); }
    uint256 GetSigHash() const { return SerializeHash(*this, SER_GETHASH|SER_SKIPSIG); }
    uint256 GetUserHash() const { return Hash(vchPubKeyFrom.begin(), vchPubKeyFrom.end()); }


    bool CheckSignature();
    bool CheckProduct();
};


extern map<uint256, CProduct> mapProducts;
//extern CCriticalSection cs_mapProducts;
extern map<uint256, CProduct> mapMyProducts;

} //end namespace

#endif /* EZ_BT_MARKET_H */
/* EOF */
