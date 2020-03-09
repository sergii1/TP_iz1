//
// Created by sergiy on 09.03.2020.
//

#ifndef IZ1__LIB_H_
#define IZ1__LIB_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>

typedef struct {
  char *name;
  bool isopening;
  char **atributes;
} Tag;

bool tag_is_open(const char *str);
char *get_tag_name(const char *str);
unsigned amount_atributes_number(const char *str);

extern char **parse_atributes(const char *str, unsigned num, int *status_code);

Tag *initialize_tag(const char *s);
#endif //IZ1__LIB_H_
