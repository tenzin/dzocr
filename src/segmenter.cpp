/**
 Program to Segment an input image of Dzongkha text into respective lines and then lines into vertical blocks.
 (Basically Looks for whitespace between the lines and vertical blocks - Horizontal and Vertical Histograms)
**/

#include <iostream>
#include<fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "segment.h"
using namespace std;

int main()
{
	CImgList<unsigned char> image_line_list, image_block_list, image_component_list;
	int no_of_images;
	ifstream info_file("Info.txt");
	info_file >> no_of_images;
	while(no_of_images > 0)
	{
		char inp = ' ';
		char output_file_name[64], system_args[256];
		info_file >> inp;
		char main_dir_name[2] = {inp, '\0'};
		char sub_dir_name[64];
		char image_file_name[6] = {inp, '.', 'p', 'n', 'g', '\0'};
		CImg<unsigned char> image(image_file_name);
		int no_of_lines = 0, no_of_blocks = 0, no_of_components = 0;
		
		line_slice(image, image_line_list, 10); //Call the line slicing function
		mkdir(main_dir_name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); //Create main directory of the particular test image
		
		no_of_lines = image_line_list.size();
		for(int i = 0; i < no_of_lines; i++)
		{
			char temp1[10];
			//create sub directories
			strcpy(sub_dir_name, main_dir_name);
			strcat(sub_dir_name, "/");
			sprintf(temp1, "%d", (i+1));
			strcat(sub_dir_name, temp1);
			vertical_slice(image_line_list[i], image_block_list, 3);
			mkdir(sub_dir_name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);  //Create sub directory for ith line
			no_of_blocks = image_block_list.size();
			for(int j = 0; j < no_of_blocks; j++)
			{
				get_connected_components(image_block_list[j], image_component_list);
				no_of_components = image_component_list.size();
				for(int k = 0; k < no_of_components; k++)
				{
					char temp[10], component_name[2] = {char(97+k), '\0'};
					strcpy(output_file_name, sub_dir_name);
					strcat(output_file_name, "/");
					sprintf(temp, "%d", (j+1));
					strcat(output_file_name, temp);
					strcat(output_file_name, component_name);
					strcat(output_file_name, ".tif");
					image_component_list[k].save(output_file_name);
					//Calling Tesseract
					/**strcpy(system_args, "/usr/local/bin/tesseract ");
					strcat(system_args, output_file_name);
					strcat(system_args, " ");
					strcat(system_args, output_file_name);
					strcat(system_args, " -l dzo");
					system(system_args);**/
					//End of calling tesseract
				}
				image_component_list.clear();
			}
			image_block_list.clear();
		}
		image_line_list.clear();
		no_of_images = no_of_images - 1;
	}
	return 0;
}
