#include "string_class.h"
#include <stdio.h>

int main()
{
  NEW_EMPTY_STRING(basic);
  printf("basic: %s\n", basic.c_string);
  printf("basic length: %d\n", (int)basic.length);
  NEW_EMPTY_STRING(fill_out_later);
  str_set_string_using_basic_text(&fill_out_later, "New Value");
  printf("%s\n", str_get_c_string(&fill_out_later));

  NEW_STRING(test_new, "Hello world");
  printf("%s\n", str_get_c_string(&test_new));
  // Test str_split
  int number_of_new_strings;
  auto_string_array split_string;
  // Split string basic
  str_split_using_basic_text(&fill_out_later, " ", &split_string);
  for (int ix = 0; ix < split_string.number_of_strings; ix++)
  {
    printf("%s\n", split_string.string_array[ix].c_string);
  }
  // Split string harder
  NEW_STRING(splitter_test, "ThisawkIsawkAawkSplitterawkTestawk");
  auto_string_array split_string_two;
  str_split_using_basic_text(&splitter_test, "awk", &split_string_two);
  for (int ix = 0; ix < split_string_two.number_of_strings; ix++)
  {
    printf("%s\n", split_string_two.string_array[ix].c_string);
  }
  printf("****************************\n");
  printf("**    ends with test      **\n");
  printf("****************************\n");

  NEW_STRING(ends_with_test, "This string ends with hello");
  printf("Ends with test string: %s\n", ends_with_test.c_string);
  if (str_ends_with_using_basic_text(&ends_with_test, "hello"))
  {
    printf("YAY\n");
  }

  return 0;
}