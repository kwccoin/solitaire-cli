// https://rosettacode.org/wiki/Terminal_control/Unicode_output

/*
Python[edit]
import sys
 
if "UTF-8" in sys.stdout.encoding:
    print("△")
else:
    raise Exception("Terminal can't handle UTF-8")
*/

#include<stdlib.h>
#include<stdio.h>
 
int
main ()
{
  int i;
  char *str = getenv ("LANG");
 
  for (i = 0; str[i + 2] != 00; i++)
    {
      if ((str[i] == 'u' && str[i + 1] == 't' && str[i + 2] == 'f')
          || (str[i] == 'U' && str[i + 1] == 'T' && str[i + 2] == 'F'))
        {
          printf
            ("Unicode is supported on this terminal and U+25B3 is : \u25b3");
          printf
            ("Unicode is supported on this terminal and U+25B3 is : \u2560");
          printf
            ("Unicode is supported on this terminal and U+25B3 is : \u2563");
          printf
            ("Unicode is supported on this terminal and U+25B3 is : \u2565");
          printf
            ("Unicode is supported on this terminal and U+25B3 is : \u2566");
          printf
            ("Unicode is supported on this terminal and U+25B3 is : \u1F08");
          printf
            ("Unicode is supported on this terminal and U+25B3 is : \u1F05");
          i = -1;
          break;
        }
    }

    // card 2660/3/5/6 
 
  if (i != -1)
    printf ("Unicode is not supported on this terminal.");
 
  return 0;
}