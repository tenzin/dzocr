// Segmentation functions for Dzongkha OCR

#include "segment.h"

// Connected component using the intrinsic stack based recursive implementation
void connected_component(int **&image_map, int width, int height, int posx, int posy, int original_color, int replacement_color, bool &increase_color)
{
  if(image_map[posx][posy] != original_color)
    return;
  if(image_map[posx][posy] == replacement_color)
    return;
  image_map[posx][posy] = replacement_color;
  increase_color = true;
  if(posx != 0) //Going West - Check posx is not a pixel in first col
  {
    connected_component(image_map, width, height, (posx - 1), posy, original_color, replacement_color, increase_color);
    //check North-West
    if(posy != 0)
      connected_component(image_map, width, height, (posx - 1), (posy - 1), original_color, replacement_color, increase_color);
    //check South-West
    if(posy != (height - 1))
      connected_component(image_map, width, height, (posx - 1), (posy + 1), original_color, replacement_color, increase_color);
  }
  if(posy != 0) //Going North - Check posy is not a pixel in the first row
    connected_component(image_map, width, height, posx, (posy - 1), original_color, replacement_color, increase_color);
  if(posx != (width - 1)) //Going East - Check posx is not a pixel in last col
  {
    connected_component(image_map, width, height, (posx + 1), posy, original_color, replacement_color, increase_color);
    //check North-East
    if(posy != 0)
      connected_component(image_map, width, height, (posx + 1), (posy - 1), original_color, replacement_color, increase_color);
    //check South-East
    if(posy != (height - 1))
      connected_component(image_map, width, height, (posx + 1), (posy + 1), original_color, replacement_color, increase_color);
  }
  if(posy != (height - 1)) //Going South - Check posy is not pixel in last row
    connected_component(image_map, width, height, posx, (posy + 1), original_color, replacement_color, increase_color); 
}
// ************************* End of connected_components() ********************************

// Function to clear borde of image by 1 pixel
CImg<unsigned char> clear_border(CImg<unsigned char> image)
{
  int width = image.width();
  int height = image.height();
  for(int i = 0; i < width; i++)
  {
    image(i, 0) = 255;
    image(i, (height - 1)) = 255;
  }
	
  for(int j = 0; j < height; j++)
  {
    image(0, j) = 255;
    image((width - 1), j) = 255;
  }
  return image;
}
// ************************** Endo of clear_border() *********************

// Functions to get the position of the first pixel from top, bottom, left, right , of the given image
int get_starty(CImg<unsigned char> image)
{
  cimg_forY(image, y)
  {
    cimg_forX(image, x)
    {
      if (int(image(x, y)) == 0)
        return y;
    }
  }
  return 0;
}
// ********** End of get_starty() ****************

int get_endy(CImg<unsigned char> image)
{
  int height = image.height();
  cimg_forY(image, y)
  {
    cimg_forX(image, x)
    {
      if (int(image(x, (height -1) - y)) == 0)
        return ((height -1) - y);
    }
  }
  return 0;
}
// ******************** End of get_endy() ***********

int get_startx(CImg<unsigned char> image)
{
  cimg_forX(image, x)
  {
    cimg_forY(image, y)
    {
      if (int(image(x, y)) == 0)
        return x;
    }
  }
  return 0;
}
// ******************** End of get_startx() ***********

int get_endx(CImg<unsigned char> image)
{
  int width = image.width();
  cimg_forX(image, x)
  {
    cimg_forY(image, y)
    {
      if (int(image((width -1 ) - x, y)) == 0)
        return ((width -1 ) - x);
    }
  }
	return 0;
}
// **************************** End of get_endx() ***********

// Function to return an image list consisting of all the images extracted by flood fill. The returned image list is in 
// "Left to Right, Top to Bottom" sorted.
CImgList<unsigned char> get_images_sorted(int **&image_map, int width, int height, int no_of_components, int color)
{
  CImg<unsigned char> image(width, height);
  CImgList<unsigned char> unordered_image_list, ordered_image_list, image_list;
  int startx[no_of_components], endx[no_of_components], starty[no_of_components], endy[no_of_components];

  for(int i = 0; i < no_of_components; i++)
  {
    cimg_forY(image, y)
    {
      cimg_forX(image, x)
      {
        if(image_map[x][y] == color)
          image(x, y) = 0;
        else
          image(x, y) = 255;
      }
    }
    unordered_image_list.insert(image);
    color = color + 1;
  }
	
  // Order the unordered_image_list
  while(unordered_image_list.size() > 0)
  {
    if(unordered_image_list.size() >= 2)  //more than or equal to two imagess yet to process
    {
      if(get_endx(unordered_image_list[0]) - get_startx(unordered_image_list[1]) > 4) // they are overlapping vertically
			{
        //cout << "2 images overlapping" << endl;
        //if(get_endy(unordered_image_list[0]) <= get_starty(unordered_image_list[1])) // 0 is probably upper vovel
        if(get_starty(unordered_image_list[0]) <= get_starty(unordered_image_list[1]))
        {
          //cout << "first image is vovel" << endl;
          ordered_image_list.insert(unordered_image_list[0]);
          ordered_image_list.insert(unordered_image_list[1]);
          unordered_image_list.pop_front();
          unordered_image_list.pop_front();
        }
        else //(get_endy(unordered_image_list[1]) <= get_starty(unordered_image_list[0]))  1 is probably upper vovel or something else
        {
          ordered_image_list.insert(unordered_image_list[1]);
          ordered_image_list.insert(unordered_image_list[0]);
          unordered_image_list.pop_front();
          unordered_image_list.pop_front();
        }
      }
      else //Not overlapping vertically - just insert the first image
      {
        ordered_image_list.insert(unordered_image_list[0]);
        unordered_image_list.pop_front();
      }
    }
    else //only one image left
    {
      ordered_image_list.insert(unordered_image_list[0]);
      unordered_image_list.pop_front();			
    }
  }
	
  // Now clean the images, get border and send them back
  for(int i = 0; i < ordered_image_list.size(); i++)
  {
    //-1 and +1 to have one pixel border around the output image. and clear_border function ensures the one pixel border to be white/255
    int startx = get_startx(ordered_image_list[i]);
    int starty = get_starty(ordered_image_list[i]);
    int endx = get_endx(ordered_image_list[i]);
    int endy = get_endy(ordered_image_list[i]);
    //check if the image is noise or not
    if((endx - startx) > 2 && (endy - starty) > 2) //Not noise
      image_list.insert(clear_border(ordered_image_list[i].crop(startx - 1 , starty - 1, endx + 1, endy +1)));
  }
  return image_list;
}
// **************************** End of get_image_sorted() ***************************************

//Function to cut the image passed as the first argument horizontally (line segmentation/slicing) and place the segments in a CImgList object
void line_slice(CImg<unsigned char> &image, CImgList<unsigned char> &image_list, int threshold)
{
	CImg<unsigned char> temp;
	int width, height, no_of_lines, start_line[150], end_line[150], *horizontal_pixel_count;
	bool inside_pix = false;
	width = image.width();
	height = image.height();
	no_of_lines = 0;
	horizontal_pixel_count = new int[height];

	//Initialize arrays that keep track of the line beginning and line end. Need to implement these trackers better
	for(int i = 0; i < 150; i++)
	{
		start_line[i] = 0;
		end_line[i] = height - 1; //So that if a line extends to the end of image height, it wont get a segfault.
	}
	
	//Initialize array containing line wise pixel counts to zeros
	for(int i = 0; i < height; i++)
		horizontal_pixel_count[i] = 0;
	
	//Horizontal Scanning to get the no of pixels in each row of the image
	cimg_forY(image, y)
	{
		cimg_forX(image, x)
		{
			if (int(image(x,y)) == 0)
				horizontal_pixel_count[y] = horizontal_pixel_count[y] + 1;
		}
	}
	
	//compute start and end of line	
	for(int i = 0; i < height; i++)
	{
		if(horizontal_pixel_count[i] != 0 && !inside_pix) 
		{
		 	//start of a new text line
			inside_pix = true;
			start_line[no_of_lines] = i;
		}
		else 
		{
			if(horizontal_pixel_count[i] == 0 && inside_pix) 
			{
				//end of text line
				inside_pix = false;
				end_line[no_of_lines] = i;

				//Check if the text line found is really a text line or noise by comparing height to a threshold
				if((end_line[no_of_lines] - start_line[no_of_lines]) >= threshold)
				{
					//It is indeed a line \0/, Now we go on to check for the next line
					no_of_lines = no_of_lines + 1;
				}
			}
		}
	}
	
	//Check to see if some lines are cut into 2 because of the upper vowels not touching the consonants
	//Checks whether the width b/t start of one line and end of next line is greater than a threshold or not
	for(int i = 0; i < no_of_lines; i++)
	{
		if((i + 1) < no_of_lines)  //check to see if we have reached the last line or not. If its the last line, then theres nothing to check
		{
			//check for threshold
			if((start_line[i+1] - end_line[i]) <= 2 && (end_line[i] - start_line[i] < 20)) //gap is too small + previous line is too thin to be a line in itself.. probably part of line - we may need to get threshold dynamically
			{
				//join lines i and i+1 and shift the whole arrays one step forward and decrease the no_of_lines
				end_line[i] = end_line[i + 1];
				for(int j = i + 1; j < (no_of_lines - 1); j++)
				{
					start_line[j] = start_line[j+1];
					end_line[j] = end_line[j+1];
				}
				no_of_lines = no_of_lines - 1;
			}
		}
	}
	
	//save all the horizontal line segments into the image_list CImgList object
	for(int i = 0; i < no_of_lines; i++)
	{
		temp = image.get_crop(0, start_line[i], (width - 1), (end_line[i] - 1));
		image_list.insert(temp);
	}
	
	//Cleanup
	delete horizontal_pixel_count;
}
//************************ End Line Slice******************************

//Function to cut the image passed as the first argument vertically (vertical slicing) and place the segments in a CImgList object
void vertical_slice(CImg<unsigned char> &image, CImgList<unsigned char> &image_list, int threshold)
{
	CImg<unsigned char> temp;
	int width, height, no_of_blocks, start_block[150], end_block[150], *vertical_pixel_count;
	bool inside_pix = false;
	width = image.width();
	height = image.height();
	no_of_blocks = 0;
	vertical_pixel_count = new int[width];
	
	//Initialize arrays that keep track of beginning and end of vertical blocks
	for(int i = 0; i < 150; i++)
	{
		start_block[i] = 0;
		end_block[i] = width - 1; //so that we dont segfault on some images
	}
	//Initialize the vertical pixel count array to zeros
	for(int i = 0; i < width; i++)
		vertical_pixel_count[i] = 0;
	
	//Vertical scanning to get no. of pixels in each column of the present line image
	cimg_forX(image, x)
	{
		cimg_forY(image, y)
		{
			if (int(image(x,y)) == 0)
				vertical_pixel_count[x] = vertical_pixel_count[x] + 1;
		}
	}
	
	//compute start and end of vertical block 
	for(int i = 0; i < width; i++)
	{
		if(vertical_pixel_count[i] != 0 && !inside_pix) 
		{
	 		//start of a new vertical block
			inside_pix = true;
			start_block[no_of_blocks] = i;
		}
		else 
		{
			if(vertical_pixel_count[i] == 0 && inside_pix) 
			{
				//end of text line
				inside_pix = false;
				end_block[no_of_blocks] = i;
						
				//Check if the text line found is really a text line or noise by comparing height to a threshold
				if((end_block[no_of_blocks] - start_block[no_of_blocks]) >= threshold)
				{
					//It is indeed a line \0/, Now we go on to check for the next line
					no_of_blocks = no_of_blocks + 1;
				}
			}
		}
	}
	
	//save all the horizontal line segments into the image_list CImgList object
	for(int i = 0; i < no_of_blocks; i++)
	{
		temp = image.get_crop(start_block[i], 0, (end_block[i] - 1), (height - 1));
		//slice the temp image horizontally , i.e. the block height is not same as the parent line
		//image_list.insert(temp.get_crop(0, get_firstpix_top(temp), (temp.dimx() - 1), (temp.dimy() - 1)));
		image_list.insert(temp);
	}
	
	//Cleanup
	delete vertical_pixel_count;
}
//*********************End Vertical Slice***********************************************

//Function to get all the connected components from the input image, determine their order of writing and store in image list
void get_connected_components(CImg<unsigned char> image, CImgList<unsigned char> &image_list)
{
	CImg<unsigned char> temp_image;
	int **image_map, width, height;  //Image map will have 0 for black pixels and 1 for background/white pixels
	int replacement_color = 2, no_of_components = 0; //replacement color begins from 2 and will increase for every conn. component
	width = image.width();
	height = image.height();
	image_map = new int* [width];
	bool increase_color = false; //To keep track of the replacement color increment
	
	//Get image data into image_map
	cimg_forX(image, x)
	{
		image_map[x] = new int[height];
		cimg_forY(image, y)
		{
			if (int(image(x,y)) == 0)
				image_map[x][y] = 0; //Black 
			else
				image_map[x][y] = 1; //White
		}
	}
	
	//Call Flood Fill :-)
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			if(image_map[i][j] == 0)
				connected_component(image_map, width, height, i, j, 0, replacement_color, increase_color);
			if(increase_color)
			{
				replacement_color = replacement_color + 1;
				no_of_components = no_of_components + 1;
				increase_color = false;
			}

		}
	}

	//Get the connected components marked with different colors as individual images keeping the writing order intact :-(
	int begin_color = 2; //the start color of the components
	image_list = get_images_sorted(image_map, width, height, no_of_components, begin_color);

	//Cleanup
	for (int i = 0; i < width; i++)
		delete [] image_map[i];
	delete [] image_map;
}
//************************** End Get Connected Components *********************************

//************************ Get Composite Image - Horizontal (Line) ***************************
CImg <unsigned char> get_composite_image(CImgList <unsigned char> image_list)
{
  int no_of_images = image_list.size();
  int width = 0, height = 0, temp = 0;
  int width_tracker = 5;
  
  //Get the greatest height and addition of all widths;
  for (int i =0; i < no_of_images; i++)
  {
    width = width + image_list[i].width();
    if (image_list[i].height() > height)
      height = image_list[i].height();
  }
  width = width + (5 * no_of_images) + 5;
  height = height + 1;
  CImg <unsigned char> image(width, height);
  image.fill(255); //Fill with white/background color
  for (int i =0; i < no_of_images; i++)
  {
    int w = image_list[i].width();
    int h = image_list[i].height();
    for (int x = 0; x < w; x++)
    {
      for (int y = 0; y < h; y++)
      {
         image(x + width_tracker, y + (height - h)) = image_list[i](x,y);
      }
    }
    width_tracker = width_tracker + w + 5;
  }
  return image;
}
//******************** End Composite Image - Line ************************

//******************** Get composite image - Final *************************
CImg <unsigned char> get_composite_image_final(CImgList <unsigned char> image_list)
{
  int no_of_images = image_list.size();
  cout << "no of images " << no_of_images << endl;
  int width = 0, height = 0, height_tracker = 5;
  
  // Find the greatest width among all the images in list. Get the addition of all heights
  for (int i = 0; i < no_of_images; i++)
  {
    height = height + image_list[i].height();
    if (image_list[i].width() > width)
      width = image_list[i].width();
  }
  
  height = height + (5 * no_of_images) + 5;
  width = width + 10;
  cout << "width and height found" << endl;
  // Create new image, draw all the images in image_list on this new image.
  CImg <unsigned char> image(width, height);
  image.fill(255); //Fill with white/background color
  for (int i = 0; i < no_of_images; i ++)
  {
    int w = image_list[i].width();
    int h = image_list[i].height();
    for (int x = 0; x < w; x++)
    {
      for (int y = 0; y < h; y++)
        image(x + 5, y + height_tracker) = image_list[i](x, y);
    }
    height_tracker = height_tracker + h + 5;
    cout << "done with image " << i + 1 << endl;
  }
  return image;
}
//******************** End Composite Image - Final ************************
