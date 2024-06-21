#include <limits.h>
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
  char *line;
  int line_max;

  if (LINE_MAX >= 16384) {
    line_max = 16384;
  } else {
    long limit = sysconf(_SC_LINE_MAX);
    line_max = (limit < 0 || limit > 16384) ? 16384 : (int) limit;
  }

  line = malloc(line_max + 1);

  if (line == NULL) return -1;

  while (fgets(line, line_max + 1, file) != NULL) {
    printf("Current Line is: %s\n", line);
    printf("READ LINE...\n");
  }

  free(line);

  return 0;
}

FILE * openfile(char *path) {
  FILE *file;

  if ((file = fopen(path, "r")) == NULL) perror("cant open file");

  return file;
}

int main() {
  DIR *dir;
  struct dirent *dp;
  struct stat st;
  char full_path[PATH_MAX];

  if ((dir = opendir(".")) == NULL) {
    perror("Cannot open .");
  }



  while ((dp = readdir(dir)) != NULL) {
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
      continue;
    }

    snprintf(full_path, sizeof(full_path), "%s/%s",".", dp->d_name);
    stat(full_path, &st);

    if (is_dir(&st)) {
      printf("Maybe recursive explorer? (%s)\n", full_path);
      continue;
    }

    FILE *file = openfile(full_path);

    printf("PATH IS: %s\n", full_path);
    readfile(file);

    fclose(file);


    // printf("dp is: %s\n", dp->d_name);

    // if (S_ISDIR(st.st_mode)) {
    //   opendir("./%s", dp->d_name);
    //   printf("%s is a directory\n", dp->d_name);
    // }
  }

  closedir(dir);

  return 0;
}
