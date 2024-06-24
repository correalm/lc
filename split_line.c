#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Word Word;
struct Word {
  char *word;
  Word *previous;
};

Word *new_word(char *word) {
  Word *new_word;

  new_word = (Word *) malloc(sizeof(Word));
  new_word->word = word;
  new_word->previous = NULL;

  return new_word;
}

Word *split_line(char line[]) {
  char *token;
  Word *last_word = NULL;

  token = strtok(line, " ");
  while (token != NULL) {
    Word *created_word = new_word(token);
    created_word->previous = last_word;
    last_word = created_word;

    token = strtok(NULL, " ");
  }

  return last_word;
}

