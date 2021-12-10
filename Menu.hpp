//****************************************************************************
//
// HEADER NAME:
//      Menu.hpp
//
//****************************************************************************

#ifndef _Menu_hpp
#define _Menu_hpp

#include <time.h>
#include <string>

//------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------
void DisplayMainMenu();

unsigned int GetChoice();

void DisplayLinkedListMenu();

void DisplayHashTableMenu();

void DisplayVectorMenu();

void DisplayBSTMenu();

void DisplayElapsedTime( clock_t ticks );

double strToDouble( std::string str, char ch );

struct Printers
{
	std::string separator = "|-----------------------------------------|";
	std::string spaces;
	int diff;
};

#endif
