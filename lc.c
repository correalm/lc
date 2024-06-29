#include <limits.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

int is_dir(struct stat *st) {
  if (S_ISDIR(st->st_mode)) return 1;

  return 0;
}

int readfile(FILE *file) {
  const int MAX_LINE_LENGHT = 16384;

  char *line;
  char *token;
  int line_max;
  int counter = 0;

  if (LINE_MAX >= MAX_LINE_LENGHT) {
    line_max = 16384;
  } else {
    long limit = sysconf(_SC_LINE_MAX);
    line_max = (limit < 0 || limit > MAX_LINE_LENGHT) ? MAX_LINE_LENGHT : (int) limit;
  }

  line = malloc(line_max + 1);

  if (line == NULL) return -1;

  while (fgets(line, line_max + 1, file) != NULL) {
    counter++;
  }

  free(line);

  return counter;
}

FILE * openfile(char *path) {
  FILE *file;

  if ((file = fopen(path, "r")) == NULL) {
    perror("cant open file\n");
    printf("ERROR: path[%s]\n", path);
  }

  return file;
}

int explorer(char *path) {
  DIR *dir;
  struct dirent *dp;
  struct stat st;

  char full_path[sizeof(path) + MAX_INPUT + 1];
  int number_of_lines = 0;

  if ((dir = opendir(path)) == NULL) {
    perror("Cannot open the current path\n");
  }

  while ((dp = readdir(dir)) != NULL) {
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
      continue;
    }

    snprintf(full_path, sizeof(full_path), "%s/%s", path, dp->d_name);
    stat(full_path, &st);

    if (is_dir(&st)) {
      number_of_lines += explorer(full_path);
      continue;
    }

    if (st.st_mode & S_IXUSR) {
      printf("This file is an executable [%s]. Next.\n", path);
      continue;
    }

    FILE *file = openfile(full_path);

    int total_lines = readfile(file);
    number_of_lines += total_lines;

    fclose(file);
  }

  closedir(dir);

  return number_of_lines;
}

int main(int argc, char *argv[]) {
  char path[MAX_INPUT] = ".";

  if (argv[1]) {
    strncpy(path, argv[1], sizeof(path) - 1);
  }

  printf("Using the path: %s\n", path);

  printf("-------------------------------------------------\n");
  printf("The total number of lines is: %d\n", explorer(path));
  printf("-------------------------------------------------\n");

  return 0;
}
