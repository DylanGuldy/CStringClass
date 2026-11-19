#include "string_class.h"
#include <stdio.h>

int main()
{
  printf("****************************\n");
  printf("**    Creation Tests      **\n");
  printf("****************************\n");

  printf("** New Empty Macro Test **\n");
  NEW_EMPTY_STRING(basic);
  printf("basic: %s\n", basic.c_string);
  printf("basic length: %d\n", (int)basic.length);
  printf("~~ New Empty Macro Test ~~\n");

  printf("** Set String Test **\n");
  NEW_EMPTY_STRING(fill_out_later);
  str_set_string_using_basic_text(&fill_out_later, "New Value");
  printf("%s\n", str_get_c_string(&fill_out_later));
  printf("~~ Set String Test ~~\n");

  printf("** New String Macro Test **\n");
  NEW_STRING(test_new, "Hello world");
  printf("%s\n", str_get_c_string(&test_new));
  printf("~~ New String Macro Test ~~\n");

  printf("****************************\n");
  printf("**  String Split Tests    **\n");
  printf("****************************\n");

  printf("** Simple Split Test **\n");
  NEW_EMPTY_STRING_ARRAY(split_string);
  // Split string basic
  str_split_using_basic_text(&fill_out_later, " ", &split_string);
  for (int ix = 0; ix < split_string.number_of_strings; ix++)
  {
    printf("%s\n", split_string.string_array[ix].c_string);
  }
  printf("~~ Simple Split Test ~~\n");

  printf("** More Complicated Split Test **\n");
  // Split string harder
  NEW_STRING(splitter_test, "ThisawkIsawkAawkSplitterawkTestawk");
  auto_string_array split_string_two = {0};
  str_split_using_basic_text(&splitter_test, "awk", &split_string_two);
  int ix = 0;
  while (split_string_two.string_array[ix].c_string != NULL)
  {
    printf("%s\n", split_string_two.string_array[ix].c_string);
    ix++;
  }
  printf("~~ More Complicated Split Test ~~\n");

  printf("****************************\n");
  printf("**      Find Tests        **\n");
  printf("****************************\n");

  printf("** Find last character **\n");
  NEW_STRING(find_last_char_test, "The last A in this at index 9");
  size_t last_A_location;
  str_find_last_char(&find_last_char_test, 'A', &last_A_location);
  printf("Last A char is at %d\n", (int)last_A_location);
  printf("Here it is using the index %c\n", find_last_char_test.c_string[last_A_location]);
  printf("~~ Find last character ~~\n");

  printf("** Ends With Basic Text Test **\n");
  NEW_STRING(ends_with_test, "This string ends with hello");
  printf("Ends with test string: %s\n", ends_with_test.c_string);
  if (str_ends_with_using_basic_text(&ends_with_test, "hello"))
  {
    printf("YAY\n");
  }
  printf("~~ Ends With Basic Text Test ~~\n");

  return 0;
}