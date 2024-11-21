#pragma once

#include <string>

using namespace std;

string GetResourceDir()
{
#ifdef NDEBUG // release build
	return "assets/";
#else // debug
	return "C:/Users/Reece/Documents/GitHub/FeralAscent/FeralAscentGame/assets/";
#endif

}
