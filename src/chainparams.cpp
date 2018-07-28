// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2014-2015 Dash Developers
// Copyright (c) 2017-2018 The Bsgcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"
#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "base58.h"
#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;

        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;

        memcpy(&ip, &t, sizeof(ip));

        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

// Hardcoded seeds.
static void getHardcodedSeeds(std::vector<CAddress> &vSeedsOut)
{
    std::vector<std::string> ips;
    ips.push_back("212.237.15.163");
    ips.push_back("80.211.36.93");
    ips.push_back("80.211.165.110");
    ips.push_back("80.211.25.202");
    ips.push_back("80.211.80.158");
    ips.push_back("80.211.144.224");
    ips.push_back("80.211.161.12");
    ips.push_back("80.211.83.233");

    const int64_t oneWeek = 7 * 24 * 60 * 60;
    for (size_t i = 0; i < ips.size(); ++i)
    {
        CAddress addr(CService(ips[i], 36368));
        addr.nTime = GetTime() - GetRand(oneWeek) - oneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xf3;
        pchMessageStart[2] = 0xd8;
        pchMessageStart[3] = 0xdb;
        vAlertPubKey = ParseHex("04d806b72a3d224cc8978e772c607c5135a345f9a8de63bd748f9a80ddeab49b0a362f3609d459be409a1af1278babe2d0d2842b0b7ff3971cc7eea9500c1e3ec6");
        nDefaultPort = 36368;
        nRPCPort = 36369;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16); // starting difficulty is 1 / 2^12

        const char* pszTimestamp = "Startup sues Tesla for USD 2 billion over electric truck design";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();

	// original 1516154401
        CTransaction txNew(1, 1525526688, vin, vout, 0);

        LogPrintf("genesis mainnet transaction:  %s\n", txNew.ToString().c_str());

        genesis.vtx.push_back(txNew);

        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1525526688; // Saturday, 5 May 2018 13:24:48 UTC
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 396366;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x7d72a34c4d766fa69c24b3da6fd039e64c66ac8ba4515e970d69f0f10fde057a"));
        assert(genesis.hashMerkleRoot == uint256("0x3b7a83e1c19d07dc25cf05d168555785a0bcd8c8de618b47bae03a57ff9d07f5"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,26); // B
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,21);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,23);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,41);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x99)(0x75)(0x45)(0xE2).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x99)(0x73)(0x43)(0xE3).convert_to_container<std::vector<unsigned char> >();

	// NOTE: MODIFIED THIS TO 0.0.0.0
        vSeeds.push_back(CDNSSeedData("1",  "212.237.15.163"));
	vSeeds.push_back(CDNSSeedData("2",  "80.211.36.93"));
	vSeeds.push_back(CDNSSeedData("3",  "80.211.165.110"));
	vSeeds.push_back(CDNSSeedData("4",  "80.211.25.202"));
	vSeeds.push_back(CDNSSeedData("5",  "80.211.80.158"));
	vSeeds.push_back(CDNSSeedData("6",  "80.211.144.224"));
	vSeeds.push_back(CDNSSeedData("7",  "80.211.161.12"));
	vSeeds.push_back(CDNSSeedData("8",  "80.211.83.233"));

	convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        getHardcodedSeeds(vFixedSeeds);

        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "Be9UAtaYHEk5cpsvNyg5r5GFtQGXyySf5b";

        nLastPOWBlock = 4000000;
        nPOSStartBlock = 1500;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xc2;
        pchMessageStart[1] = 0xd8;
        pchMessageStart[2] = 0xa9;
        pchMessageStart[3] = 0xb9;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04d806b72a3d224cc8978e772c607c5135a345f9a8de63bd748f9a80ddeab49b0a362f3609d459be409a1af1278babe2d0d2842b0b7ff3971cc7eea9500c1e3ec6");
        nDefaultPort = 59432;
        nRPCPort = 59433;
        strDataDir = "testnet";
        genesis.nTime    = 1525526688;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 396366;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x7d72a34c4d766fa69c24b3da6fd039e64c66ac8ba4515e970d69f0f10fde057a"));
        assert(genesis.hashMerkleRoot == uint256("0x3b7a83e1c19d07dc25cf05d168555785a0bcd8c8de618b47bae03a57ff9d07f5"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,85); // b
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,23);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,25);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,43);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x98)(0x74)(0x44)(0xE1).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x98)(0x72)(0x42)(0xE2).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 4000000;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
