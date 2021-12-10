//****************************************************************************
// @file BinarySearchTree.cpp
//
//****************************************************************************
#include "Bid.hpp"
#include "BinarySearchTree.hpp"
#include "CSVparser.hpp"
#include "Menu.hpp"
#include <iostream>
#include <time.h>

//----------------------------------------------------------------------------
//! Default constructor
//----------------------------------------------------------------------------
BinarySearchTree::BinarySearchTree()
{
	root = nullptr;
} // end of function BinarySearchTree::BinarySearchTree()

//----------------------------------------------------------------------------
//! Destructor
//----------------------------------------------------------------------------
BinarySearchTree::~BinarySearchTree() {}

//----------------------------------------------------------------------------
//! Traverse the tree in order
//----------------------------------------------------------------------------
void BinarySearchTree::InOrder()
{
	this->inOrder( root );
} // end of function BinarySearchTree::InOrder()

void BinarySearchTree::inOrder( BSTNode* node )
{
	if( node != nullptr )
	{
		inOrder( node->left );
		std::cout << node->bid.bidID << ": " << node->bid.title << " | "
			<< node->bid.amount << " | " << node->bid.fund << std::endl;
		inOrder( node->right );
	}
} // end of function BinarySearchTree::inOrder()

//----------------------------------------------------------------------------
//! Insert a bid into the tree
//----------------------------------------------------------------------------
void BinarySearchTree::Insert( Bid bid )
{
	if( root == nullptr )
	{
		root = new BSTNode( bid );
	}
	else
	{
		this->addNode( root, bid );
	}
} // end of function BinarySearchTree::Insert()

//----------------------------------------------------------------------------
//! Remove a given bid from the tree
//----------------------------------------------------------------------------
void BinarySearchTree::Remove( std::string bidId )
{
	this->removeNode( root, bidId );
} // end of function BinarySearchTree::Remove()

BSTNode* BinarySearchTree::removeNode( BSTNode* node, std::string bidId )
{
	// If this node is null then return (avoid crashing)
	if( node == nullptr )
	{
		return node;
	}

	// Recurse down left subtree
	if( bidId.compare( node->bid.bidID ) < 0 )
	{
		node->left = removeNode( node->left, bidId );
	}
	else if( bidId.compare( node->bid.bidID ) > 0 )
	{
		node->right = removeNode( node->right, bidId );
	}
	else
	{
		// No children so this is a leaf node
		if( node->left == nullptr && node->right == nullptr )
		{
			delete node;
			node = nullptr;
		}
		// One child to the left
		else if( node->left != nullptr && node->right == nullptr )
		{
			BSTNode* temp = node;
			node = node->left;
			delete temp;
		}
		// One child to the right
		else if( node->right != nullptr && node->left == nullptr )
		{
			BSTNode* temp = node;
			node = node->right;
			delete temp;
		}
		// Two children
		else
		{
			BSTNode* temp = node->right;
			while( temp->left != nullptr )
			{
				temp = temp->left;
			}
			node->bid = temp->bid;
			node->right = removeNode( node->right, temp->bid.bidID );
		}
	}
	return node;
} // end of function BinarySearchTree::removeNode

//----------------------------------------------------------------------------
//! Search the tree given a bid
//! @return bid
//----------------------------------------------------------------------------
Bid BinarySearchTree::Search( std::string bidId )
{
	// Start searching from the root
	BSTNode* current = root;

	// Keep looping downwards until bottom is reached or bid is found
	while( current != nullptr )
	{
		// If current node matches, return it
		if( current->bid.bidID.compare( bidId ) == 0 )
		{
			return current->bid;
		}
		// If bid is smaller than current node, traverse left
		if( current->bid.bidID.compare( bidId ) > 0 )
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}
	Bid bid;
	return bid;
} // end of function BinarySearchTree::Search()

//----------------------------------------------------------------------------
//! Add a bid to some node (recursive)
//----------------------------------------------------------------------------
void BinarySearchTree::addNode( BSTNode* node, Bid bid )
{
	// If node is larger than the bid, add to the left subtree
	if( node->bid.bidID.compare( bid.bidID ) > 0 )
	{
		if( node->left == nullptr )
		{
			node->left = new BSTNode( bid );
		}
		else
		{
			this->addNode( node->left, bid );
		}
	}
	// If node is smaller than the bid, add to the right subtree
	else
	{
		if( node->right == nullptr )
		{
			node->right = new BSTNode( bid );
		}
		else
		{
			this->addNode( node->right, bid );
		}
	}
} // end of function BinarySearchTree::addNode()

//----------------------------------------------------------------------------
//! Display the bid information to the console
//----------------------------------------------------------------------------
void displayBid( Bid bid )
{
	std::cout << "  " << bid.bidID << ": " << bid.title << " | " << bid.amount << " | " << bid.fund << std::endl;
	return;
} // end of function displayBid()

//----------------------------------------------------------------------------
//! Load a CSV file containing bids into a container
//----------------------------------------------------------------------------
void loadBid( std::string csvPath, BinarySearchTree* bst )
{
	//std::string separator = "|-----------------------------------------|";
	Printers p;
	std::string loading = "| Loading CSV file " + csvPath;
	p.diff = p.separator.size() - loading.size() - 1;
	p.spaces.append(p.diff, ' ');
	std::cout << p.separator << std::endl;
	std::cout << loading << p.spaces << "|" << std::endl;
	std::cout << p.separator << std::endl;
	csv::Parser file = csv::Parser( csvPath );
	int count = 0;

	// Optional - read the header row
	/*std::vector<std::string> header = file.getHeader();
	for( auto const& c : header )
	{
		std::cout << c << " | ";
	}
	std::cout << "" << std::endl;*/

	try
	{
		// Loop to read rows of a CSV file
		for( unsigned int i = 0; i < file.rowCount(); i++ )
		{
			// Create a data structure and add to the collection of bids
			Bid bid;
			bid.bidID = file[ i ][ 1 ];
			bid.title = file[ i ][ 0 ];
			bid.fund = file[ i ][ 8 ];
			bid.amount = strToDouble( file[ i ][ 4 ], '$' );
			bst->Insert( bid );
			count++;
		}
	}
	catch( csv::Error& e )
	{
		std::cerr << e.what() << std::endl;
	}
	std::string bidsRead = "| " + std::to_string(count) + " bids read";
	p.diff = p.separator.size() - bidsRead.size() - 1;
	p.spaces.clear();
	p.spaces.append(p.diff, ' ');
	std::cout << bidsRead << p.spaces << "|" << std::endl;
} // end of function loadBid()

//----------------------------------------------------------------------------
//! Launches the Binary Search Tree program
//----------------------------------------------------------------------------
void LaunchBinarySearchTree( std::string csvPath )
{
	Bid bid;
	clock_t ticks;
	int choice = 0;
	std::string bidKey = "81957";
	BinarySearchTree* bst = new BinarySearchTree();

	while( choice != 9 )
	{
		DisplayBSTMenu();
		choice = GetChoice();
		std::cout << std::endl;
		switch( choice )
		{
			case 1:
				ticks = clock();
				loadBid( csvPath, bst );
				DisplayElapsedTime( ticks );
				break;
			case 2:
				bst->InOrder();
				break;
			case 3:
				ticks = clock();
				bid = bst->Search( bidKey );
				DisplayElapsedTime( ticks );

				if( !bid.bidID.empty() )
				{
					displayBid( bid );
				}
				else
				{
					std::cout << "Bid id " << bidKey << " not found." << std::endl;
				}
				break;
			case 4:
				bst->Remove( bidKey );
				break;
		}
	}
} // end of function LaunchBinarySearchTree()
