#ifndef _PREPROCESS_H
#define _PREPROCESS_H

#include <iostream>
#include "CImg.h"
using namespace std;
using namespace cimg_library;
#define GRAYLEVEL 256 //No of Gray level

CImg <unsigned char> binarize_by_otsu(CImg <unsigned char>);

#endif
