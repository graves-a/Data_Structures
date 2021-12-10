//****************************************************************************
//
// HEADER NAME:
//      Bid.hpp
//
//****************************************************************************

#ifndef _Bid_hpp
#define _Bid_hpp

#include <string>

//------------------------------------------------------------------------
// Structure to hold bid information
//------------------------------------------------------------------------	
struct Bid
{
	std::string bidID;
	std::string title;
	std::string fund;
	double	    amount;

	Bid()
	{
		amount = 0.0;
	}
};

#endif
