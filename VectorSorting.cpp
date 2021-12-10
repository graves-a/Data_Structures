//****************************************************************************
// @file VectorSorting.cpp
//
//****************************************************************************

#include "Bid.hpp"
#include "CSVparser.hpp"
#include "Menu.hpp"
#include "VectorSorting.hpp"
#include <algorithm>
#include <iostream>
#include <time.h>
#include <cstring>

//----------------------------------------------------------------------------
//! Prints out bid information in Bid
//----------------------------------------------------------------------------
void displayVectorBid( Bid aBid )
{
	std::cout << aBid.bidID << " : " << aBid.title << " | "
		<< aBid.amount << " | " << aBid.fund << std::endl;
	return;
} // end of function displayBid()

//----------------------------------------------------------------------------
//! Iterates through the file assigning Bid values.
//! @return std::vector<Bid> vectorBids
//----------------------------------------------------------------------------
std::vector<Bid> loadVectorBids( std::string csvPath )
{
	Printers p;
	std::string loading = "| Loading CSV file " + csvPath;
	p.diff = p.separator.size() - loading.size() - 1;
	p.spaces.append( p.diff, ' ' );
	std::cout << p.separator << std::endl;
	std::cout << loading << p.spaces << "|" << std::endl;
	std::cout << p.separator << std::endl;
	std::vector<Bid> vectorBids;
	csv::Parser file = csv::Parser( csvPath );

	// Optional - read the header row
	/*std::vector<std::string> header = file.getHeader();
	for( auto const& c : header )
	{
		std::cout << c << " | ";
	}
	std::cout << "" << std::endl;*/

	try
	{

		for( int i = 0; i < file.rowCount(); i++ )
		{
			Bid aBid;
			aBid.bidID = file[ i ][ 1 ];
			aBid.title = file[ i ][ 0 ];
			aBid.fund = file[ i ][ 8 ];
			aBid.amount = strToDouble( file[ i ][ 4 ], '$' );
			vectorBids.push_back( aBid );
		}
	}
	catch( csv::Error& e )
	{
		std::cerr << e.what() << std::endl;
	}

	std::string bidsRead = "| " + std::to_string( vectorBids.size() ) + " bids read";
	p.diff = p.separator.size() - bidsRead.size() - 1;
	p.spaces.clear();
	p.spaces.append( p.diff, ' ' );
	std::cout << bidsRead << p.spaces << "|" << std::endl;
	return vectorBids;
} // end of function loadVectorBids()

//----------------------------------------------------------------------------
//! Perform a selection sort on bid title
//! Average performance: O(n^2))
//! Worse case performance: O(n^2))
//----------------------------------------------------------------------------
void selectionSort( std::vector<Bid>& bids )
{
	int min;
	for( unsigned pos = 0; pos < bids.size(); pos++ )
	{
		min = pos;
		for( unsigned j = pos + 1; j < bids.size(); j++ )
		{
			if( bids.at( j ).title.compare( bids.at( min ).title ) < 0 )
			{
				min = j;
			}
		}
		if( min != pos )
		{
			std::swap( bids.at( pos ), bids.at( min ) );
		}
	}
} // end of function selectionSort()

//----------------------------------------------------------------------------
//! Partition the vector of bids into two parts, low and high
//! @return high point
//----------------------------------------------------------------------------
int partition( std::vector<Bid>& bids, int begin, int end )
{
	int low = begin;
	int high = end;

	// Pick the middle as the pivot point
	int pivot = begin + ( end - begin ) / 2;

	bool done = false;
	while( !done )
	{
		// Keep incrementing low as it's less than pivot
		while( bids.at( low ).title.compare( bids.at( pivot ).title ) < 0 )
		{
			++low;
		}
		// Keep decremeting high as long as it's less than pivot
		while( bids.at( pivot ).title.compare( bids.at( high ).title ) < 0 )
		{
			--high;
		}

		if( low >= high )
		{
			done = true;
		}
		else
		{
			// Swap the low and high bids using built-in vector method
			// and move the end points closer
			std::swap( bids.at( low ), bids.at( high ) );
			++low;
			--high;
		}
	}
	return high;
} // end of function partition()

//----------------------------------------------------------------------------
//! Perform a quick sort on bid title
//! Average performance: O(n log(n))
//! Worse case performance: O(n^2)) 
//----------------------------------------------------------------------------
void quickSort( std::vector<Bid>& bids, int begin, int end )
{
	int mid = 0;
	// If zero or one bids to sort, then done
	if( begin >= end )
	{
		return;
	}
	// Partition bids into low and high parts
	mid = partition( bids, begin, end );
	// Recursively call quicksort using midpoint value (begin to mid)
	quickSort( bids, begin, mid );
	// Recursively call quicksort using midpoint value (mid + 1 to end)
	quickSort( bids, mid + 1, end );
} // end of function quickSort()

//----------------------------------------------------------------------------
//! Launches the vector sort program
//----------------------------------------------------------------------------
void LaunchVectorSort( std::string csvPath )
{
	std::vector<Bid> vectorBids;
	int choice = 0;
	clock_t ticks;

	while( choice != 9 )
	{
		DisplayVectorMenu();
		choice = GetChoice();
		std::cout << std::endl;
		switch( choice )
		{
			case 1:
				ticks = clock();
				vectorBids = loadVectorBids( csvPath );
				DisplayElapsedTime( ticks );
				break;
			case 2:
				for( int i = 0; i < vectorBids.size(); i++ )
				{
					displayVectorBid( vectorBids[ i ] );
				}
				break;
			case 3:
				ticks = clock();
				selectionSort( vectorBids );
				DisplayElapsedTime( ticks );
				break;
			case 4:
				ticks = clock();
				quickSort( vectorBids, 0, vectorBids.size() - 1 );
				DisplayElapsedTime( ticks );
				break;

			case 9:
				break;
		}
	}
} // end of function LaunchVectorSort()