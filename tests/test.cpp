//
// Created by sergiy on 06.03.2020.
//
#include "gtest/gtest.h"
#include "../main.c"

TEST(test_functional_part, Test1) {
  char *s = "<Tag name=\"sergiy\" name=\"sergIy\">";
  Tag *tag = initialize_tag(s);
  unsigned num = amount_atributes_number(s);

  ASSERT_EQ(num, 2);
  ASSERT_EQ(tag->isopening, true);
  ASSERT_STREQ(tag->name, "Tag");
  ASSERT_STREQ(tag->atributes[0], "name=\"sergiy\"");
  ASSERT_STREQ(tag->atributes[1], "name=\"sergIy\"");

  for (int j = 0; j < num; j++) {
    free(tag->atributes[j]);
  }
  free(tag->atributes);
  free(tag->name);
  free(tag);
}

TEST(test_functional_part, Test2){
  char *s = "</Tag name=\"sergiy\" name=\"sergIy\">";
  Tag *tag = initialize_tag(s);
  unsigned num = amount_atributes_number(s);

  ASSERT_EQ(num, 2);
  ASSERT_EQ(tag->isopening, false);
  ASSERT_STREQ(tag->name, "Tag");
  ASSERT_STREQ(tag->atributes[0], "name=\"sergiy\"");
  ASSERT_STREQ(tag->atributes[1], "name=\"sergIy\"");

  for (int j = 0; j < num; j++) {
    free(tag->atributes[j]);
  }
  free(tag->atributes);
  free(tag->name);
  free(tag);
}

TEST(test_functional_part, Test3){
  char *s = "</Tag>";
  Tag *tag = initialize_tag(s);
  unsigned num = amount_atributes_number(s);

  ASSERT_EQ(num, 0);
  ASSERT_EQ(tag->isopening, false);
  ASSERT_STREQ(tag->name, "Tag");

  ASSERT_EQ((tag->atributes==NULL), true);
  std::cout<<"atr null"<<(tag->atributes==NULL);
  for (int j = 0; j < num; j++) {
    free(tag->atributes[j]);
  }
  free(tag->atributes);
  free(tag->name);
  free(tag);
}
