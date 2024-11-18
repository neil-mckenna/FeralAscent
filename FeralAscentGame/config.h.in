#pragma once

#include <string>

using namespace std;

string GetResourceDir()
{
#ifdef NDEBUG // release build
	return "@RESOURCE_FOLDER_NAME@/";
#else // debug
	return "@RESOURCE_SRC_DIR@/";
#endif

}