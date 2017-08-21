//Post Processing Functions

#include "postprocess.h"

//Function to get a dzongkha text line and store individual unicode strings in 2-d array for later processing
void get_characters(char *text_line, char **&char_list, int length)
{
  char text[4];
  //Allocate space for char_list
  char_list = new char*[length];
  for (int i = 0; i < length; i++)
    char_list[i] = new char[4];

  //Copy each character in the character array
  int tracker = 0;
  for (int i = 0; i < length; i++)
  {
      for (int j = 0; j < 3; j++)
      {
        if (text_line[tracker + j] == ' ') //unwanted space in the text - ignore it and go to next char.
        {
          j = j - 1;
          tracker = tracker + 1;
        }
        else
          text[j] = text_line[tracker + j];
      }
      text[3] = '\0';
      strcpy(char_list[i], text);
      tracker = tracker + 3;
  }
}
//------End----

//function to clear the char_list structure after its use

void clear(char **&char_list, int length)
{
  for (int i = 0; i < length; i++)
    delete [] char_list[i];
  delete [] char_list;
}
//--End chear---

//Functions to check the group in which unicode char falls
bool is_consonant(char *text)
{
  for (int i = 0; i < 30; i++)
  {
    if (strcmp(text, CONSONANT[i]) == 0) //is consonant
      return true;
  }
  return false;
}

bool is_lower_consonant(char *text)
{
  for (int i = 0; i < 30; i++)
  {
    if(strcmp(text, LOWER_CONSONANT[i]) == 0) //is lower consonant
      return true;
  }
  return false;
}

bool is_cacc1(char *text)
{
  for (int i = 0; i < 10; i++)
  {
    if(strcmp(text, CACC1[i]) == 0) //is CACC1
      return true;
  }
  return false;
}

bool is_cacc2(char *text)
{
  for (int i = 0; i < 2; i++)
  {
    if(strcmp(text, CACC2[i]) == 0) //is CACC2
      return true;
  }
  return false;
}

bool is_upper_vowel(char *text)
{
  for (int i = 0; i < 3; i++)
  {
    if(strcmp(text, UPPER_VOWEL[i]) == 0) //is upper vowel
      return true;
  }
  return false;
}

bool is_lower_vowel(char *text)
{
  if(strcmp(text, LOWER_VOWEL) == 0) //is lower vowel
    return true;
  else
    return false;
}

bool is_punctuation(char *text)
{
  for (int i = 0; i < 2; i++)
  {
    if(strcmp(text, PUNCTUATION[i]) == 0) //is upper vowel
      return true;
  }
  return false;
}

bool is_tsa_tsha_za(char *text)
{
  for (int i = 0; i < 3; i++)
  {
    if (strcmp(text, TSA_TSHA_ZA[i]) == 0) //is Tsa or Tsha or Za
      return true;
  }
  return false;
}

bool is_ra_la_sa(char *text)
{
  for (int i = 0; i < 3; i++)
  {
    if(strcmp(text, RA_LA_SA[i]) == 0) //is ra || la || sa
      return true;
  }
  return false;
}

int is_nya_ta_da_ha(char *text)
{
  for (int i = 0; i < 4; i++)
  {
    if(strcmp(text, NYA_TA_DA_HA[i]) == 0) //is ra || la || sa
      return i; //return index here. not boolean
  }
  return -1;
}
//---End check ---------

//Main processing function
void process_text(char **&char_list, int length, ofstream &outfile)
{
  for (int i = 0; i < length; i++)
  {
    if (is_consonant(char_list[i])) //start consonant check
    {
      if (is_tsa_tsha_za(char_list[i]) && is_upper_vowel(char_list[i + 1]))  // checking for tsa, tsha, za + upper vowel ordering 
      {
        outfile << char_list[i];
        outfile << char_list[i + 1];
        i = i +1;
      }
      else if(is_ra_la_sa(char_list[i]) && (is_nya_ta_da_ha(char_list[i + 1]) != -1))  //Checking ra, la sa + nya, ta, ha without upper vowel
      {
        int index = is_nya_ta_da_ha(char_list[i + 1]);
        outfile << char_list[i] << NYA_TA_DA_HA_LOWER[index];
        i = i + 1;
      }
      else
        outfile << char_list[i];
    }
    //-- End consonant ordering
    
    else if (is_lower_consonant(char_list[i]))
    {
      outfile << char_list[i];
    }
    else if (is_upper_vowel(char_list[i])) // start upper vowel - things need to correct here - according to our segmentation output
    {
      if (is_punctuation(char_list[i + 1])) //if tsheg or shed follow upper vowel, we need no ordering .
      {
        outfile << char_list[i] << char_list[i + 1];
        i = i + 1;
      }
      else if (is_ra_la_sa(char_list[i + 1]) && (is_nya_ta_da_ha(char_list[i + 2]) != -1)) //checking for nya, ta and ha with superscrib ra, la and sa
      {
        int index1 = is_nya_ta_da_ha(char_list[i + 2]);
        outfile << char_list[i + 1] << NYA_TA_DA_HA_LOWER[index1] << char_list[i];
        i = i + 2;
      }
      else //generic upper vowel ordering
      {
        char temp[4];
        strcpy(temp, char_list[i]);
        for (int count = 1; ; count ++)
        {
          if (is_consonant(char_list[i + count]))
          {
            outfile << char_list[i + count];
            if (!is_lower_consonant(char_list[i + count +1]))
            {
              i = i + count;
              break;
            }
          }
          if (is_lower_consonant(char_list[i + count]))
          {
            outfile << char_list[i + count];
            if (!is_lower_consonant(char_list[i + count +1]))
            {
              i = i + count;
              break;
            }
          }
        }
        outfile << temp;
      }
    }
    //--End upper vowel ordering
    else if (is_lower_vowel(char_list[i]))
    {
      outfile << char_list[i];
    }
    else
    {
      outfile << char_list[i];
    }
  }
  outfile << endl;
}
//---End----
