// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

//#include <windows.h>

/// .........................
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <memory>
#include <unordered_map>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <boost/variant.hpp>

#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

//temp, for now.............
#ifdef __linux__ 

//linux code goes here
#elif _WIN32

#ifndef _WINDOWS_
typedef struct tagRECT
{
	uint32_t    left;
	uint32_t    top;
	uint32_t    right;
	uint32_t    bottom;
} RECT, *PRECT,*LPRECT;

#endif

#endif

//TODO virtual links..................
//#include "C:\cpp\boost_geometry\Geometry.h"


// TODO: reference additional headers your program requires here
