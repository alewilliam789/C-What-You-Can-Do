#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

int main(int argc, char** argv) {

    FILE* current_file;

    current_file = fopen(argv[1], "r");

    if(current_file == NULL) {
      return 1;
    }

    int result = json_lexer(current_file);

    

    fclose(current_file);
    return result;
}
