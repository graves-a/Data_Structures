//****************************************************************************
// @file LinkedList.cpp : 
//
//****************************************************************************

#include "Bid.hpp"
#include "CSVparser.hpp"
#include "LinkedList.hpp"
#include "Menu.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <time.h>

//----------------------------------------------------------------------------
//! Linked-List class definition
//! Define a class containing data members and methods to implement a 
//! linked-list
//----------------------------------------------------------------------------
class LinkedList
{
private:
	struct Node
	{
		Bid bid;
		Node* next;
		// Default constructor
		Node()
		{
			next = nullptr;
		}
		// Initialize a node with a bid
		Node( Bid aBid )
		{
			bid = aBid;
			next = nullptr;
		}
	};

	Node* head;
	Node* tail;
	int size = 0;

public:
	LinkedList();
	virtual ~LinkedList();
	void Append( Bid bid );
	void Prepend( Bid bid );
	void PrintList();
	void Remove( std::string bidId );
	Bid Search( std::string bidId );
	int Size();
};

//----------------------------------------------------------------------------
//! Default constructor
//----------------------------------------------------------------------------
LinkedList::LinkedList()
{
	head = tail = nullptr;
} // end of function LinkedList::LinkedList()

//----------------------------------------------------------------------------
//! Destructor
//----------------------------------------------------------------------------
LinkedList::~LinkedList() {}

//----------------------------------------------------------------------------
//! Append a new bid to the end of the list
//----------------------------------------------------------------------------
void LinkedList::Append( Bid bid )
{
	Node* node = new Node( bid );

	if( head == nullptr )
	{
		head = node;
	}
	else
	{
		if( tail != nullptr )
		{
			tail->next = node;
		}
	}
	// New node is always the tail
	tail = node;
	size++;
} // end of function LinkedList::Append()

//----------------------------------------------------------------------------
//! Prepend a new bid to the start of the list
//----------------------------------------------------------------------------
void LinkedList::Prepend( Bid bid )
{
	Node* node = new Node( bid );

	if( head != nullptr )
	{
		node->next = head;
	}
	head = node;
	size++;
} // end of function LinkedList::Prepend()

//----------------------------------------------------------------------------
//! Print of list of all bids
//----------------------------------------------------------------------------
void LinkedList::PrintList()
{
	Node* current = head;

	while( current != nullptr )
	{
		std::cout << current->bid.bidID << ": " << current->bid.title << " | "
			<< current->bid.amount << " | " << current->bid.fund << std::endl;
		current = current->next;
	}
} // end of function LinkedList::PrintList()

//----------------------------------------------------------------------------
//! Removes a bid from the linked-list
//----------------------------------------------------------------------------
void LinkedList::Remove( std::string bidId )
{
	if( head != nullptr )
	{
		if( head->bid.bidID.compare( bidId ) == 0 )
		{
			Node* tempNode = head->next;
			delete head;
			head = tempNode;
		}
	}

	Node* current = head;
	// Loop over each node looking for a match
	while( current != nullptr )
	{
		if( current->next->bid.bidID.compare( bidId ) == 0 )
		{
			// Save the next node (one to be removed)
			Node* tempNode = current->next;
			// Make current node point beyond the next one (to be removed)
			current->next = tempNode->next;
			// Delete temp node
			delete tempNode;
			// Reduce count
			size--;
			return;
		}
		current = current->next;
	}
} // end of function LinkedList::Remove()

//----------------------------------------------------------------------------
//! Search the linked-list for a specific bidId
//----------------------------------------------------------------------------
Bid LinkedList::Search( std::string bidId )
{
	Node* current = head;
	while( current != nullptr )
	{
		if( current->bid.bidID.compare( bidId ) == 0 )
		{
			return current->bid;
		}
		else
		{
			current = current->next;
		}
	}	
} // end of function LinkedList::Search()

//----------------------------------------------------------------------------
//! Get the size of the linked-list
//! @return size
//----------------------------------------------------------------------------
int LinkedList::Size()
{
	return size;
} // end of function LinkedList::Size()

//----------------------------------------------------------------------------
//! Display the bid information
//----------------------------------------------------------------------------
void displayLLBid( Bid bid )
{
	std::cout << "  " << bid.bidID << ": " << bid.title << " | " << bid.amount << " | " << bid.fund << std::endl;
	return;
} // end of function displayBid()

//----------------------------------------------------------------------------
//! Prompt the user for bid information
//! @return bid
//----------------------------------------------------------------------------
Bid getBid()
{
	Bid bid;
	std::cout << "Enter ID: ";
	std::cin.ignore();
	std::getline( std::cin, bid.bidID );

	std::cout << "Enter title: ";
	std::getline( std::cin, bid.title );

	std::cout << "Enter fund: ";
	std::getline( std::cin, bid.fund );

	std::cout << "Enter amount: ";
	std::string strAmount;
	std::getline( std::cin, strAmount );
	bid.amount = strToDouble( strAmount, '$' );

	return bid;
} // end of function getBid()

//----------------------------------------------------------------------------
//! Load a CSV file containing bids into a linked-list
//----------------------------------------------------------------------------
void loadBids( std::string csvPath, LinkedList* list )
{
	Printers p;
	std::string loading = "| Loading CSV file " + csvPath;
	p.diff = p.separator.size() - loading.size() - 1;
	p.spaces.append( p.diff, ' ' );
	std::cout << p.separator << std::endl;
	std::cout << loading << p.spaces << "|" << std::endl;
	std::cout << p.separator << std::endl;
	csv::Parser file = csv::Parser( csvPath );

	// Optional
	/*std::vector<std::string> header = file.getHeader();
	for( auto const& c : header )
	{
		std::cout << c << " | ";
	}
	std::cout << "" << std::endl;*/

	try
	{
		// Lop to read rows of a CSV file
		for( unsigned int i = 0; i < file.rowCount(); i++ )
		{
			// Initialize the bid using data from current row (i)
			Bid bid;
			bid.bidID = file[ i ][ 1 ];
			bid.title = file[ i ][ 0 ];
			bid.fund = file[ i ][ 8 ];
			bid.amount = strToDouble( file[ i ][ 4 ], '$' );
			// Add this bid to the end
			list->Append( bid );
		}
	}
	catch( csv::Error& e )
	{
		//std::cerr << e.what() << std::endl;
		std::cout << "error" << std::endl;
	}

	std::string bidsRead = "| " + std::to_string( list->Size() ) + " bids read";
	p.diff = p.separator.size() - bidsRead.size() - 1;
	p.spaces.clear();
	p.spaces.append( p.diff, ' ' );
	std::cout << bidsRead << p.spaces << "|" << std::endl;	
} // end of function loadBids()

//----------------------------------------------------------------------------
//! Launches the linked-list program
//----------------------------------------------------------------------------
void LaunchLinkedList( std::string csvPath )
{
	clock_t tick;
	LinkedList bidList;
	Bid bid;
	int choice = 0;
	std::string searchValue = "81957";

	while( choice != 9 )
	{
		DisplayLinkedListMenu();
		choice = GetChoice();
		std::cout << std::endl;
		switch( choice )
		{
			case 1:
				tick = clock();
				loadBids( csvPath, &bidList );
				DisplayElapsedTime( tick );
				break;
			case 2:
				bidList.PrintList();
				break;
			case 3:
				tick = clock();
				bid = bidList.Search( searchValue );
				DisplayElapsedTime( tick );

				if( !bid.bidID.empty() )
				{
					displayLLBid( bid );
				}
				else
				{
					std::cout << "Bid id " << searchValue << " not found." << std::endl;
				}
				break;
			case 4:
				bidList.Remove( searchValue );
				break;
			case 5:
				bid = getBid();
				bidList.Prepend( bid );
				displayLLBid( bid );
				break;
			case 9:
				break;
		}
	}
} // end of function LaunchLinkedList()