#include <stdio.h>
#include <stdlib.h>
#include <lib.c>
/*Условие ИЗ№1:
Создать структуру для хранения информации об HTML-теге: его имени, признаке «открывающий/закрывающий» и атрибутах тега.
 Составить с ее использованием программу, включающую в себя функцию, принимающую на вход текстовую строку с одним тегом.
 На выход функция должна возвращать указатель на инициализированную структуру.
*/



int main() {

  char ** s = (char**)calloc(1, sizeof(char*));
  size_t * size = (size_t*)calloc(1, sizeof(size_t));
  getline(s,size,stdin);
  (*s)[strlen(*s)-1]='\0';
  Tag *tag = initialize_tag(*s);
  if (!tag) {
    printf("ERr2");
    return 0;
  }
  unsigned num = amount_atributes_number(*s);
  for (int j = 0; j < num; j++) {
    free(tag->atributes[j]);
  }
  free(tag->atributes);
  free(tag->name);
  free(tag);
  free(size);
  free(*s);
  free(s);
}