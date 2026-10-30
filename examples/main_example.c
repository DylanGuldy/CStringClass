#include "string_class.h"
#include <stdio.h>

int main()
{
  NEW_EMPTY_STRING(basic);
  printf("basic: %s\n", basic.data.c_string);
  printf("basic length: %d\n", (int)basic.data.length);
  NEW_EMPTY_STRING(fill_out_later);
  fill_out_later.functions->set_string_using_basic_text(&fill_out_later, "New Value");
  printf("%s\n", fill_out_later.functions->get_c_string(&fill_out_later));
  return 0;
}