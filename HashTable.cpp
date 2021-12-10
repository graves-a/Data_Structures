//****************************************************************************
// @file BinarySearchTree.cpp
//
//****************************************************************************

#include "CSVparser.hpp"
#include "HashTable.hpp"
#include "Menu.hpp"
#include <algorithm>
#include <iostream>
#include <string>

//------------------------------------------------------------------------
// Default constructor
//------------------------------------------------------------------------
HashTable::HashTable()
{
	nodes.resize( tableSize );
} // end of function HashTable::HashTable()

//------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------
HashTable::HashTable( unsigned size )
{
	this->tableSize = size;
	nodes.resize( tableSize );
}// end of function HashTable::HashTable()

//------------------------------------------------------------------------
// Desctructor
//------------------------------------------------------------------------
HashTable::~HashTable()
{
	nodes.erase( nodes.begin() );
} // end of function HashTable::~HashTable()

//------------------------------------------------------------------------
// Calculate the has value of a given key
// @return calculated hash
//------------------------------------------------------------------------
unsigned int HashTable::hash( int key )
{
	return key % tableSize;
} // end of function HashTable::hash()

//------------------------------------------------------------------------
// Insert a bid
//------------------------------------------------------------------------
void HashTable::Insert( Bid bid )
{
	// Calculate the key for this bid
	unsigned key = hash( atoi( bid.bidID.c_str() ) );
	HTNode* oldNode = &( nodes.at( key ) );

	// If no entry found for this key
	if( oldNode == nullptr )
	{
		HTNode* newNode = new HTNode( bid, key );
		nodes.insert( nodes.begin() + key, ( *newNode ) );
	}
	else
	{
		// Node found
		if( oldNode->key == UINT_MAX )
		{
			oldNode->key = key;
			oldNode->bid = bid;
			oldNode->next = nullptr;
		}
		else
		{
			// Find the next open node
			while( oldNode->next != nullptr )
			{
				oldNode = oldNode->next;
			}
			oldNode->next = new HTNode( bid, key );
		}
	}
} // end of function HashTable::Insert()

//------------------------------------------------------------------------
// Search for a specific bid
//------------------------------------------------------------------------
Bid HashTable::Search( std::string bidId )
{
	Bid bid;
	unsigned key = hash( atoi( bidId.c_str() ) );
	HTNode* node = &( nodes.at( key ) );
	
	// If no entry found
	if( node == nullptr || node->key == UINT_MAX )
	{
		return bid;
	}

	// If node found that matches key
	if( node != nullptr && node->key != UINT_MAX && node->bid.bidID.compare( bidId ) == 0 )
	{
		return node->bid;
	}
	
	// Walk the linked list to find the match
	while( node != nullptr )
	{
		if( node->key != UINT_MAX && node->bid.bidID.compare( bidId ) == 0 )
		{
			return node->bid;
		}
		node = node->next;
	}
	return bid;
} // end of function HashTable::Search()

//------------------------------------------------------------------------
// Remove a specific bid
//------------------------------------------------------------------------
void HashTable::Remove( std::string bidId )
{
	unsigned key = hash( atoi( bidId.c_str() ) );
	nodes.erase( nodes.begin() + key );
} //end of function HashTable::Remove()

//------------------------------------------------------------------------
// Print all the bids
//------------------------------------------------------------------------
void HashTable::PrintAll()
{
	for( auto i = nodes.begin(); i != nodes.end(); i++ )
	{
		if( i->key != UINT_MAX )
		{
			std::cout << "Key " << i->key << ":" << i->bid.bidID << " | "
				<< i->bid.title << " | " << i->bid.amount << " | "
				<< i->bid.fund << std::endl;
			HTNode* node = i->next;
			while( node != nullptr )
			{
				std::cout << "    " << node->key << ":" << node->bid.bidID
					<< " | " << node->bid.title << " | " << node->bid.amount
					<< " | " << node->bid.fund << std::endl;
				node = node->next;
			}
		}
	}
} // end of function HashTable::PrintAll()

//------------------------------------------------------------------------
// Display the bid information to the console
//------------------------------------------------------------------------
void displayHTBid( Bid bid )
{
	std::cout << "  " << bid.bidID << ": " << bid.title << " | " << bid.amount << " | " << bid.fund << std::endl;
	return;
} // end of function displayHTBid()

//------------------------------------------------------------------------
// Load a CSV file containing bids into a container
// @return a container holding all the bids read
//------------------------------------------------------------------------
void loadBids( std::string csvPath, HashTable* hashTable )
{
	//std::cout << "Loading CSV file" << csvPath << std::endl;
	Printers p;
	std::string loading = "| Loading CSV file " + csvPath;
	p.diff = p.separator.size() - loading.size() - 1;
	p.spaces.append( p.diff, ' ' );
	std::cout << p.separator << std::endl;
	std::cout << loading << p.spaces << "|" << std::endl;
	std::cout << p.separator << std::endl;
	csv::Parser file = csv::Parser( csvPath );
	int count = 0;

	// Optional
	/*std::vector<std::string> header = file.getHeader();
	for( auto const& c : header )
	{
		std::cout << c << " | ";
	}
	std::cout << "" << std::endl;*/

	try
	{
		for( unsigned int i = 0; i < file.rowCount(); i++ )
		{
			Bid bid;
			bid.bidID = file[ i ][ 1 ];
			bid.title = file[ i ][ 0 ];
			bid.fund = file[ i ][ 8 ];
			bid.amount = strToDouble( file[ i ][ 4 ], '$' );
			hashTable->Insert( bid );
			count++;
		}
	}
	catch( csv::Error& e )
	{
		std::cerr << e.what() << std::endl;
	}
	std::string bidsRead = "| " + std::to_string( count ) + " bids read";
	p.diff = p.separator.size() - bidsRead.size() - 1;
	p.spaces.clear();
	p.spaces.append( p.diff, ' ' );
	std::cout << bidsRead << p.spaces << "|" << std::endl;
} // end of function loadBids()

//------------------------------------------------------------------------
// Launches the hashtable program
//------------------------------------------------------------------------
void LaunchHashTable( std::string csvPath )
{
	HashTable* bidTable = new HashTable();
	Bid bid;
	int choice = 0;
	clock_t ticks;

	std::string searchValue = "81957";

	while( choice != 9 )
	{
		DisplayHashTableMenu();
		choice = GetChoice();
		std::cout << std::endl;
		switch( choice )
		{
			case 1:
				ticks = clock();
				loadBids( csvPath, bidTable );
				DisplayElapsedTime( ticks );
				break;
			case 2:
				bidTable->PrintAll();
				break;
			case 3:
				ticks = clock();
				bid = bidTable->Search( searchValue );
				DisplayElapsedTime( ticks );

				if( !bid.bidID.empty() )
				{
					displayHTBid( bid );
				}
				else
				{
					std::cout << "Bid Id " << searchValue << " not found." << std::endl;
				}
				break;
			case 4:
				bidTable->Remove( searchValue );
				break;
			case 9:
				break;

		}
	}
} // end of function LaunchHashTable()