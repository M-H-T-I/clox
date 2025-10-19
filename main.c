#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"


static void repl(){
  char line[1024];

  for(;;){
    printf("> ");


    if(!fgets(line, sizeof(line), stdin)){
      printf("\n");
      break;
    }

    interpret(line);
  }
}

static char* readFile(const char* path){

  FILE* file = fopen(path, "rb");

  // exception handling in case file doesn't open
  if(file == NULL){
    fprintf("Could not open file \"%s\". \n", path);
    exit(74);
  }


  fseek(file, 0L, SEEK_END); // go to the end of the file
  size_t fileSize = ftell(file); // tells us how many bytes we are from the start of the file
  rewind(file); // goes back to the start of the file


  char* buffer = (char*)malloc(fileSize + 1);

  // in case memory is less than file size
  if (buffer ==NULL){
    fprint(stderr, "Not enough memory to read \"%s\". \n", path);
    exit(74);
  }

  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);

  //in case reading fails
  if(bytesRead < fileSize){
    fprintf(stderr, "Could not read file \"%s\". \n", path);
    exit(74);
  }

  buffer[bytesRead] = '\0'; 

  fclose(file);
  return buffer;

}

static void runFile(const char* path){
  char* source = readFile(path);
  InterpretResult result = interpret(source);
  free(source);

  if(result == INTERPRET_COMPILE_ERROR) exit(65);
  if(result == INTERPRET_RUNTIME_ERROR) exit(70);
  
}

int main(int argc, const char* argv[]) {

  initVM();

  if(argc == 1){
    repl();
  }else if(argc == 2){
    runFile(argv[1]);
  }else {
    fprintf(stderr, "Usage: clox [path]\n");
    exit(64);
  }

  freeVM();
  return 0;
}

