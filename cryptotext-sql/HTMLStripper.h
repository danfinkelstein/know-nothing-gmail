// 
// File:   HTMLStripper.hh
//
// $Id: HTMLStripper.h 27 2010-08-22 02:45:42Z df2417 $
//
//

#include <cassert>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include "ReplaceAll.h"
#include "require.h"

using namespace std;

#ifndef HTMLSTRIPPER_HH
#define	HTMLSTRIPPER_HH

string& stripHTMLTags(string &s);

#endif	/* HTMLSTRIPPER_HH */

