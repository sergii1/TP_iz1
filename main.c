#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>
/*Условие ИЗ№1:
Создать структуру для хранения информации об HTML-теге: его имени, признаке «открывающий/закрывающий» и атрибутах тега.
 Составить с ее использованием программу, включающую в себя функцию, принимающую на вход текстовую строку с одним тегом.
 На выход функция должна возвращать указатель на инициализированную структуру.
*/


typedef struct {
  char *name;
  bool isopening;
  char **atributes;
} Tag;

bool tag_is_open(const char *str) {

  return str[1] != '/' ? true : false;
}

char *get_tag_name(char *str) {
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

unsigned amount_atributes_number(char *str) {
  unsigned res = 0;
  for (unsigned i = 0; i < strlen(str); ++i) {
    if (str[i] == '=')
      res += 1;
  }
  return res;
}

char **parse_atributes(char *str, unsigned num, int *status_code) {

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
  for (unsigned i = 0; i < strlen(str) - 1; ++i) {

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

Tag *initialize_tag(char *s) {
  int *error;
  Tag *tag = (Tag *) calloc(1, sizeof(*tag));
  if (!tag) {
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
    return NULL;
  }

  return tag;
}

//int main() {
//  char *s = "</Tag>";
//  Tag *tag = initialize_tag(s);
//  if (!tag) {
//    printf("ERr2");
//    return 0;
//  }
//  unsigned num = amount_atributes_number(s);
//  for (int j = 0; j < num; j++) {
//    free(tag->atributes[j]);
//  }
//  free(tag->atributes);
//  free(tag->name);
//  free(tag);
//}