#pragma once

#include <string>

using namespace std;

string GetResourceDir()
{
#ifdef NDEBUG // release build
	return "assets/";
#else // debug
	return "C:/Users/jakes/source/repos/FeralAscent/FeralAscentGame/assets/";
#endif

}
