#include <arena.h>
#include <hashtable.h>
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

int main(int argc, char** argv) {

    FILE* current_file;

    current_file = fopen(argv[1], "r");

    if(current_file == NULL) {
      return 1;
    }

    int result = json_scanner(current_file,argv[1]);

    fclose(current_file);


    printf("%i",result);
    return result;
}
