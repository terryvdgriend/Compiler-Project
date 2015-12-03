// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma once

#include "targetver.h"

// For the Apple (OSX) users
#ifdef _WIN32
#include <crtdbg.h>
#include <tchar.h>
#endif

// Std libraries
#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional> 
#include <iostream>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <regex>
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Own libraries
#include "ErrorHandler.h"