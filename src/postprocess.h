#ifndef _POSTPROCESS_H
#define _POSTPROCESS_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
using namespace std;

//Character classes
const char CONSONANT[30][4] = {"ཀ", "ཁ", "ག", "ང", "ཅ", "ཆ", "ཇ", "ཉ", "ཏ", "ཐ", \
                                                                "ད", "ན", "པ", "ཕ", "བ", "མ", "ཙ", "ཚ", "ཛ", "ཝ", \
                                                                "ཞ", "ཟ", "འ", "ཡ", "ར", "ལ", "ཤ", "ས", "ཧ", "ཨ"};

const char LOWER_CONSONANT[30][4] = {"ྐ", "ྑ", "ྒ", "ྔ", "ྕ", "ྖ", "ྗ", "ྙ", "ྟ", "ྠ", \
                                                                                "ྡ", "ྣ", "ྤ", "ྥ", "ྦ", "ྨ", "ྩ", "ྪ", "ྫ", "ྭ", \
                                                                                "ྮ", "ྯ", "ཱ", "ྱ", "ྲ", "ླ", "ྴ", "ྶ", "ྷ", "ྸ"};

const char CACC1[10][4] = {"ག", "ང", "ད", "ན", "བ", "མ", "འ", "ར", "ལ", "ཤ"};

const char CACC2[2][4] = {"ད", "ས"};

const char UPPER_VOWEL[3][4] = {"ི", "ེ", "ོ"};

const char LOWER_VOWEL[4] = "ུ";

const char TSA_TSHA_ZA[3][4] = {"ཙ", "ཚ", "ཛ"};

const char RA_LA_SA[3][4] = {"ར", "ལ", "ས"};

const char NYA_TA_DA_HA[4][4] = {"ཉ", "ཏ", "ད", "ཧ"};

const char NYA_TA_DA_HA_LOWER[4][4] = {"ྙ", "ྟ", "ྡ", "ྷ"};

const char PUNCTUATION[2][4] = {"་", "།"};

//---End Character Classes ---
//Function prototypes 
void get_characters(char *, char **&, int);
void process_text(char **&, int, ofstream &);
void clear(char **&, int length);
#endif
