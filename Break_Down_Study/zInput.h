#ifndef zINPUT
#define zINPUT

typedef struct parsed_input {
  char source;
  char destination;
  int source_index;
  int destination_index;
  int source_amount;
  int success;
} parsed_input;


parsed_input parse_input(char *command);


#endif