#include <iostream>
#include <sstream>
#include <fstream>
#include "segment.h"

using namespace cimg_library;
using namespace std;

int main (int argc, char **argv)
{
  //check for correct command line arguments
  if (argc < 3)
  {
    cout << "Usage Error" << endl << "Usage: "<< argv[0] << " <input_image_name> <output_text_name>" << endl;
    exit (1);
  }
  
  //Load input image
  CImg <unsigned char> image;
  //try
  //{
    image.load(argv[1]);
  //}
  //catch (CImgIOException ex)
  //{
    //cout << "CImg Library Error : " << ex.message << endl;
    //exit (1);
  //}
  ofstream final_text(argv[2]);
  ifstream line_file;
  CImgList <unsigned char> image_list, image_block_list, image_component_list, line_cut, image_cut;
  int no_of_lines = 0, no_of_blocks = 0;
  char *img_filename = NULL;
  char *args = NULL;
  char *line_name;
  char buffer[1024];

  //Process the image
  line_slice (image, image_list, 10);  //Line segmentation
  no_of_lines = image_list.size();
  line_cut.clear();
  image_cut.clear();
  cout << "No of lines: " << no_of_lines << endl;
  for (int i = 0; i < no_of_lines; i++)
  {
    //Create output file names for the images
    //string filename = "out/", temp_name;
    //std::ostringstream fileNum;
    //fileNum << (i + 1);
    //filename += fileNum.str();
    //filename += ".tif";
    //img_filename = &filename[0];
    
    //Get vertical slices for all the lines
    vertical_slice(image_list[i], image_block_list, 3);  //Vertical segmentation
    no_of_blocks = image_block_list.size();
    for (int j = 0; j < no_of_blocks; j++)
    {
      //Get connected components and return new image with the segmented components arranged in a single image
      get_connected_components(image_block_list[j], image_component_list);
      line_cut.insert(get_composite_image(image_component_list));
      image_component_list.clear();
    }
    image_block_list.clear();
    //get_composite_image(line_cut).save(img_filename); //Save the final segmented and arranged image for a line
    image_cut.insert(get_composite_image(line_cut));
    line_cut.clear();
    //Run tesseract on the saved image
    //string string_args = "/usr/local/bin/tesseract " + filename + " " + filename + " -l dzo";
    //args = &string_args[0];
    //system (args);
    //temp_name = filename + ".txt";
    //line_name = &temp_name[0];
    //line_file.open(line_name);
    //if(!line_file)
    //{
      //cout << "Error opening text line File" << endl;
      //exit(1);
    //}
    //while (line_file.getline(buffer, 1024))
    //{
    //  final_text << buffer;
    //}
    //final_text << endl;
    //line_file.close();
  }
  image_list.clear();
  //final_text.close();
  cout << "calling " << endl;
  //Get composite image as well as individual lines
  get_composite_image_final(image_cut).save("out/out.png");
  for (int i = 0; i < image_cut.size(); i++)
  {
    string filename = "out/";
    std::ostringstream fileNum;
    fileNum << (i + 1);
    filename += fileNum.str();
    filename += ".tif";
    img_filename = &filename[0];
    image_cut[i].save(img_filename);
  }
  return 0;
}
