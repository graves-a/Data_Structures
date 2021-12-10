//****************************************************************************
//
// HEADER NAME:
//      HashTable.hpp
//
//****************************************************************************

#ifndef _HashTable_hpp
#define _HashTable_hpp

#include <vector>
#include "Bid.hpp"
#include <string>

const unsigned int DEFAULT_SIZE = 179;

//----------------------------------------------------------------------------
//! Struct to hold node information
//----------------------------------------------------------------------------
struct HTNode
{
	Bid bid;
	unsigned key;
	HTNode* next;

	// default constructor
	HTNode()
	{
		key = UINT_MAX;
		next = nullptr;
	}

	// initialize with a bid
	HTNode( Bid aBid ) : HTNode()
	{
		bid = aBid;
	}

	// initialize with a bid and a key
	HTNode( Bid aBid, unsigned aKey ) : HTNode( aBid )
	{
		key = aKey;
	}
};

//----------------------------------------------------------------------------
//! Hash Table class definition
//----------------------------------------------------------------------------
class HashTable
{
private:


	std::vector<HTNode> nodes;

	unsigned tableSize = DEFAULT_SIZE;

	unsigned int hash( int key );

public:
	HashTable();
	HashTable( unsigned size );
	virtual ~HashTable();
	void Insert( Bid bid );
	void PrintAll();
	void Remove( std::string bidId );
	Bid Search( std::string bidId );
};

//------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------	
void LaunchHashTable( std::string csvPath );

#endif
