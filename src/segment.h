#ifndef _SEGMENT_H
#define _SEGMENT_H

#define cimg_debug 0
#include "CImg.h"
#include <iostream>
using namespace cimg_library;
using namespace std;

void connected_component(int **&, int, int, int, int, int, int, bool &);
CImg<unsigned char> clear_border(CImg<unsigned char>);
int get_starty(CImg<unsigned char>);
int get_endy(CImg<unsigned char>);
int get_startx(CImg<unsigned char>);
int get_endx(CImg<unsigned char>);
CImgList<unsigned char> get_images_sorted(int **&, int , int , int , int );
void line_slice(CImg<unsigned char> &, CImgList<unsigned char> &, int);
void vertical_slice(CImg<unsigned char> &, CImgList<unsigned char> &, int );
void get_connected_components(CImg<unsigned char> , CImgList<unsigned char> &);
CImg <unsigned char> get_composite_image(CImgList <unsigned char>);
CImg <unsigned char> get_composite_image_final(CImgList <unsigned char>);

#endif
