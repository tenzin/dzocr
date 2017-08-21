#include <iostream>
#include "preprocess.h"

using namespace std;

int main(int argc, char *argv[])
{
  CImg <unsigned char> image(argv[1]), image1;
  image1 = binarize_by_otsu(image);
  image1.save(argv[2]);
  return 0;
}

