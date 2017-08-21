#include "postprocess.h"

int main(int argc, char **argv)
{
  ifstream infile(argv[1]);
  ofstream outfile("dzo.out");
  char text_line[1024], **char_list = NULL;
  int length;
  if(!infile)
  {
    cout << "Error opening input File" << endl;
    exit(1);
  }
  if(!outfile)
  {
    cout << "Error opening output file" << endl;
    exit(1);
  }
  while (infile.getline(text_line, 1024))
  {
    length = strlen(text_line) / 3;
    get_characters(text_line, char_list, length);
    for (int i = 0; i < length; i++)
      cout << char_list[i] << "   ";
    cout << endl << "length = " << length << endl;
    process_text(char_list, length, outfile);
    clear(char_list, length);
  }
  return 0;
}
