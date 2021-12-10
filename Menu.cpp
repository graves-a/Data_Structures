//****************************************************************************
// @file Menu.cpp
//
//****************************************************************************

#include "Menu.hpp"
#include <iostream>

//------------------------------------------------------------------------
// Menu use for main
//------------------------------------------------------------------------
void DisplayMainMenu()
{
	std::cout << "\n"
		"Select a data structure\n"
		"1. Vector Sorting\n"
		"2. Linked Lists\n"
		"3. Hash Table\n"
		"4. Binary Search Tree\n"
		"9. Exit\n"
		"Enter your selection\n";
} // end of function DisplayMainMenu()

//------------------------------------------------------------------------
// Used to get user selection
// @return choice
//------------------------------------------------------------------------
unsigned int GetChoice()
{
	unsigned int choice;
	std::cin >> choice;
	while( std::cin.fail() )
	{
		std::cout << "Please enter a valid selection " << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n' );
		std::cin >> choice;
	}
	return choice;
} // end of function GetChoice()

//------------------------------------------------------------------------
// Menu used for Linked List
//------------------------------------------------------------------------
void DisplayLinkedListMenu()
{
	std::cout << "\n"
		"1. Loads bids\n"
		"2. Display all bids\n"
		"3. Find a bid\n"
		"4. Remove a bid\n"
		"5. Prepend a bid\n"
		"9. Exit\n"
		"Enter your selection:\n";
} // end of function DisplayLinkedListMenu()

//------------------------------------------------------------------------
// Menu used for Vector Sorting
//------------------------------------------------------------------------
void DisplayVectorMenu()
{
	std::cout << "\n"
		"1. Loads bid\n"
		"2. Display all bids\n"
		"3. Selection sort all bids\n"
		"4. Quick sort all bids\n"
		"9. Exit\n"
		"Enter your selection:\n";
} // end of function DisplayVectorMenu()

//------------------------------------------------------------------------
// Menu used for Hash Table
//------------------------------------------------------------------------
void DisplayHashTableMenu()
{
	std::cout << "\n"
		"1. Load bids\n"
		"2. Display all bids\n"
		"3. Find a bid\n"
		"4. Remove a bid\n"
		"9. Exit\n"
		"Enter your selection\n";
} // end of function DisplayHashTableMenu()

//------------------------------------------------------------------------
// Menu used for Binary Search Tree
//------------------------------------------------------------------------
void DisplayBSTMenu()
{
	std::cout << "\n"
		"1. Load bids\n"
		"2. Display all bids\n"
		"3. Find a bid\n"
		"4. Remove a bid\n"
		"9. Exit\n"
		"Enter your selection\n";
} // end of function DisplayBSTMenu()

//------------------------------------------------------------------------
// Display the elapsed time to complete action
//------------------------------------------------------------------------
void DisplayElapsedTime(clock_t ticks)
{
	Printers p;
	ticks = clock() - ticks;
	std::string clockTicks = "| time: " + std::to_string(ticks) + " clock ticks";
	p.diff = p.separator.size() - clockTicks.size() - 1;
	p.spaces.append(p.diff, ' ');
	std::cout << p.separator << std::endl;
	std::cout << clockTicks << p.spaces << "|" << std::endl;
	std::cout << p.separator << std::endl;
	float seconds = (ticks * 1.0 / CLOCKS_PER_SEC);
	std::string strSeconds = std::to_string( seconds );
	strSeconds.erase( strSeconds.find_last_not_of('0') + 1, std::string::npos );
	std::string timeSeconds = "| time: " + strSeconds + " seconds";
	p.spaces.clear();
	p.diff = p.separator.size() - timeSeconds.size() - 1;
	p.spaces.append( p.diff, ' ' );
	std::cout << timeSeconds << p.spaces << "|" << std::endl;
	std::cout << p.separator << std::endl;
} // end of function DisplayElapsedTime()

//------------------------------------------------------------------------
// Convert a string to double 
// credit: http://stackoverflow.com/a/24875936
//------------------------------------------------------------------------	
double strToDouble( std::string str, char ch )
{
	str.erase( remove( str.begin(), str.end(), ch ), str.end() );
	return atof( str.c_str() );
} // end of function strToDouble()