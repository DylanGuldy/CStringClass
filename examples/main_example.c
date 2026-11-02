#include "string_class.h"
#include <stdio.h>

int main()
{
  NEW_EMPTY_STRING(basic);
  printf("basic: %s\n", basic.data.c_string);
  printf("basic length: %d\n", (int)basic.data.length);
  NEW_EMPTY_STRING(fill_out_later);
  str_set_string_using_basic_text(&fill_out_later, "New Value");
  printf("%s\n", str_get_c_string(&fill_out_later));

  // Test str_split
  int number_of_new_strings;
  // auto_string_array split_string = str_split_using_basic_text(&fill_out_later, " ", &number_of_new_strings);
  // for (int ix = 0; ix < number_of_new_strings; ix++)
  //{
  //   printf(split_string->string_array[ix].data.c_string);
  // }

  return 0;
}