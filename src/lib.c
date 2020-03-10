//
// Created by sergiy on 09.03.2020.
//

#include "lib.h"

bool tag_is_open(const char *str) {
  if(strlen(str)<2)
    return true;
  return str[1] != '/';
}

char *get_tag_name(const char *str) {
  char *name = (char *) calloc(strlen(str), sizeof(char));
  if (!name) {
    return NULL;
  }
  unsigned j = 0, i = 0;
  for (i = 0; i < strlen(str) && !isalpha(str[i]); i++) {}
  for (; i < strlen(str) && isalpha(str[i]); i++) {
    name[j++] = str[i];
  }
  return name;
}

unsigned amount_atributes_number(const char *str) {
  unsigned res = 0;
  for (unsigned i = 0; i < strlen(str); ++i) {
    if (str[i] == '=')
      res += 1;
  }
  return res;
}

char **parse_atributes(const char *str, unsigned num, int *status_code) {

  if (num == 0)
    return NULL;
  str = strchr(str, ' ');

  char **res = (char **) calloc(num, sizeof(char *));
  if (!res) {
    *status_code = 1;
    return NULL;
  }

  for (int j = 0; j < num; j++) {
    res[j] = (char *) calloc(strlen(str), sizeof(char));
    if (!res[j]) {
      *status_code = 1;
      return res;
    }
  }

  unsigned j = 0;
  unsigned k = 0;
  char c;
  bool in_quote = false;
  unsigned len = strlen(str);
  for (unsigned i = 0; i < len - 1 ; ++i) {

    c = str[i];
    if (c != ' ' || in_quote) {
      res[j][k++] = c;
    }

    if (c == '\"' && in_quote) {
      in_quote = false;
      j++;
      k = 0;
    } else {
      if (c == '\"' && !in_quote) {
        in_quote = true;
      }
    }

  }

  return res;
}

Tag *initialize_tag(const char *s) {
  int *error;
  Tag *tag = (Tag *) calloc(1, sizeof(*tag));
  if (!tag) {
    return NULL;
  }

  if(!strchr(s, '<') || !strchr(s,'>'))
  {
    free(tag);
    return NULL;
  }

  unsigned num = amount_atributes_number(s);


  tag->isopening = tag_is_open(s);
  tag->name = get_tag_name(s);

  int *status_code = (int *) calloc(1, sizeof(int));

  tag->atributes = parse_atributes(s, num, status_code);

  if (*status_code == 1) {
    for (int j = 0; j < num; j++) {
      free(tag->atributes[j]);
    }
    free(tag->atributes);
    free(tag->name);
    free(tag);
    free(status_code);
    return NULL;
  }
  free(status_code);
  return tag;
}
