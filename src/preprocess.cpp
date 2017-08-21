// Preprocessing Functions for Dzongkha OCR

#include "preprocess.h"

// Function to Binarize the input image using Otsu Method
// Function takes  CImg object of grayimage and returns CImg object of the corresponding binary image

CImg <unsigned char> binarize_by_otsu(CImg <unsigned char> gray_image)
{
  int hist[GRAYLEVEL];
  double prob[GRAYLEVEL], omega[GRAYLEVEL]; //Probabilities of graylevels
  double myu[GRAYLEVEL]; //mean value for separation
  double max_sigma, sigma[GRAYLEVEL]; // inter-class variance
  int threshold; //Threshold for binarization
  int width = gray_image.width();
  int height = gray_image.height();
  CImg <unsigned char> binary_image(width, height);
  
  //Initialize histogram
  for (int i = 0; i < GRAYLEVEL; i++)
    hist[i] = 0;
  cimg_forY(gray_image, y)
  {
    cimg_forX(gray_image, x)
      hist[int(gray_image(x, y))]++;
  }
 
  // calculation of probability density 
  for (int i = 0; i < GRAYLEVEL; i ++ )
  {
    prob[i] = (double)hist[i] / (width * height);
  }

  //omega & myu generation
  omega[0] = prob[0];
  myu[0] = 0.0;       //0.0 times prob[0] equals zero
  for (int i = 1; i < GRAYLEVEL; i++)
  {
    omega[i] = omega[i-1] + prob[i];
    myu[i] = myu[i-1] + i*prob[i];
  }
  
  // sigma maximization
  // sigma stands for inter-class variance 
  // and determines optimal threshold value
  threshold = 0;
  max_sigma = 0.0;
  for (int i = 0; i < GRAYLEVEL-1; i++)
  {
    if (omega[i] != 0.0 && omega[i] != 1.0)
      sigma[i] = pow(myu[GRAYLEVEL-1]*omega[i] - myu[i], 2) / (omega[i]*(1.0 - omega[i]));
    else
      sigma[i] = 0.0;
    if (sigma[i] > max_sigma)
    {
      max_sigma = sigma[i];
      threshold = i;
    }
  }
  //cout << "Threshold is = " << threshold << endl;

  //Create the binary image using threslhold
  cimg_forY(gray_image, y)
  {
    cimg_forX(gray_image, x)
    {
      if (int(gray_image(x, y)) > threshold)
        binary_image(x, y) = 255;
      else binary_image(x, y) = 0;
    }
  }
  return binary_image;
}
// End binarize_by_otsu
