//****************************************************************************
// @file DataStructures.cpp : This file includes the main function
//
//****************************************************************************
#include "BinarySearchTree.hpp"
#include "HashTable.hpp"
#include "LinkedList.hpp"
#include "Menu.hpp"
#include "VectorSorting.hpp"
#include <iostream>

std::string csvPath = "eBid_Monthly_Sales.csv";

//------------------------------------------------------------------------
// Main function
//------------------------------------------------------------------------
int main( int argc, char* arvg[] )
{
	unsigned int choice = 0;
	while( choice != 9 )
	{
		DisplayMainMenu();
		choice = GetChoice();
		switch( choice )
		{
			case 1:
				LaunchVectorSort( csvPath );
				break;
			case 2:
				LaunchLinkedList( csvPath );
				break;
			case 3:
				LaunchHashTable( csvPath );
				break;
			case 4:
				LaunchBinarySearchTree( csvPath );
				break;
			case 9:
				std::cout << "Goodbye!\n";
				break;
		}
	}
} // end of function main()
