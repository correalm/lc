#include <linux/limits.h>
#include <stdio.h>
#include <string.h>

#include "explorer.h"

void print_result(int count) {
  printf("-------------------------------------------------\n");
  printf("The total number of lines is: %d\n", count);
  printf("-------------------------------------------------\n");
}

int main(int argc, char *argv[]) {
  char path[MAX_INPUT] = ".";

  if (argv[1]) {
    strncpy(path, argv[1], sizeof(path) - 1);
  }

  printf("Using the path: %s\n", path);

  print_result(explorer(path));

  return 0;
}
