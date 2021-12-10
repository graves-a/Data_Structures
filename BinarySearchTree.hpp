//****************************************************************************
//
// HEADER NAME:
//      BinarySearchTree.hpp
//
//****************************************************************************

#ifndef _BinarySearchTree_hpp
#define _BinarySearchTree_hpp

#include "Bid.hpp"
#include <string>
#include <vector>

//----------------------------------------------------------------------------
//! Struct to hold node information
//----------------------------------------------------------------------------
struct BSTNode
{
	Bid bid;
	BSTNode* left;
	BSTNode* right;

	//<! Default constructor
	BSTNode()
	{
		left = nullptr;
		right = nullptr;
	}

	//<! Initialize with a given bid
	BSTNode( Bid const& aBid ) : BSTNode()
	{
		this->bid = aBid;
	}
}; // end of struct Node

//----------------------------------------------------------------------------
//! Binary Search Tree class definition
//----------------------------------------------------------------------------
class BinarySearchTree
{
private:
	BSTNode* root;

	void addNode( BSTNode* node, Bid bid );
	void inOrder( BSTNode* node );
	BSTNode* removeNode( BSTNode* node, std::string bidId );

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
	void Insert( Bid bid );
	void Remove( std::string bidId );
	Bid Search( std::string bidId );
};

//------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------	
void LaunchBinarySearchTree( std::string csvPath );

#endif
