#include <iostream>
#include <sstream>
#include "segment.h"

using namespace std;

int main(int argc, char *argv[])
{
  CImg <unsigned char> image(argv[1]);
  CImgList <unsigned char> image_list;
  vertical_slice(image, image_list, 3);
  string filename;
  char *img_filename = NULL;
  for (int i = 0; i < image_list.size(); i++)
  {
    std::ostringstream fileNum;
    fileNum << (i + 1);
    filename = fileNum.str();
    filename += ".jpg";
    img_filename = &filename[0];
    image_list[i].save(img_filename);
  }
  return 0;
}
