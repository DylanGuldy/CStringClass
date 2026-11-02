#include "string_class.h"
#include <stdlib.h>
#include <memory.h>
/*
  Private helpers
*/
size_t _get_length_of_basic_string(const char *basic_string)
{
  const char *s = basic_string;
  while (*s != '\0')
  {
    s++;
  }
  return (s - basic_string);
}

/*
  Class definitions
*/
void clear(string *self) {}

/*
  Get and Set
*/
size_t str_get_length(string *self) {}
const char *str_get_c_string(const string *self)
{
  return self->c_string;
}
void str_set_string(string *self, string *string) {}
void str_set_string_using_basic_text(string *self, const char *new_text)
{
  if (self)
  {
    size_t length = _get_length_of_basic_string(new_text);
    if (length > self->length)
    {
      if (self->c_string)
      {
        printf("Resizing\n");
        self->c_string = realloc(self->c_string, length + 1);
        if (NULL == self->c_string)
        {
          printf("Failed to get realloc of c string\n");
        }
      }
      else
      {
        printf("Creating new string\n");
        self->c_string = malloc(length + 1);
        if (NULL == self->c_string)
        {
          printf("Failed to malloc for c string\n");
        }
      }
    }
    memcpy((void *)self->c_string, (void *)new_text, length + 1);
    self->length = length;

    printf("New string is: %s\n", self->c_string);
  }
}
string *str_get_substring_from_index_a_to_index_b(const string *self, int start_index_a, int end_index_b) {}

/*
  Manipulate / modify
*/
void str_to_upper(string *self) {}
void str_to_lower(string *self) {}
void str_reverse(string *self) {}
void str_replace_first(string *self, const string *replacement, bool *replacement_found) {}
void str_replace_first_using_basic_text(string *self, const char *replacement, bool *replacement_found) {}
void str_replace(string *self, const string *replacement, int *number_replaced) {}
void str_replace_using_basic_text(string *self, const char *replacement, int *number_replaced) {}

/*
  Grow / add
*/
void str_append(string *self, const string *more_string) {}
void str_append_using_basic_text(string *self, const char *using_basic_text) {}
void str_join(string *self, const string_array *strings, const string *separation_characters) {}
void str_join_using_basic_text(string *self, const string_array *strings, const char *separation_characters) {}
void str_pad_left(string *self, char character, size_t count) {}
void str_pad_right(string *self, char character, size_t count) {}

/*
  Insert
*/
void str_insert(string *self, const string *string, int index_of_insertion) {}
void str_insert_using_basic_text(string *self, const char *using_basic_text, int index_of_insertion) {}

/*
  Remove / shrink
*/
void str_delete_from_index_a_to_index_b(string *self, int start_index_a, int end_index_b) {}
void str_delete_first_instance(string *self, const string *text_to_remove) {}
void str_delete_first_instance_using_basic_text(string *self, const char *text_to_remove) {}
void str_delete_all_instances(string *self, const string *text_to_remove) {}
void str_delete_all_instance_using_basic_text(string *self, const char *text_to_remove) {}
void str_trim_from_end(string *self, char character_to_remove) {}
void str_trim_from_start(string *self, char character_to_remove) {}

/*
  Find
*/
int str_find_substring(const string *self, const string *sub_string) {}
int str_find_substring_using_basic_text(const string *self, const char *using_basic_text) {}
int str_find_first_char(const string *self, char c) {}
int str_find_last_char(const string *self, char c) {}

/*
  Split
*/
// Returns array of strings
string_array *str_split(const string *self, const string *str_split) {}
string_array *str_split_using_basic_text(const string *self, const char *splitter_text)
{
  // const char *string_to_split = *self->c_string;
  // // Sliding window
  // char *main_string_tracker = string_to_split;
  // char *splitter_tracker = splitter_text;

  // size_t splitter_size = _get_length_of_basic_string(splitter_text);

  // // We could also stop once the length of the remaining characters is less than
  // // the str_split text but I think the cycles to calculate that and time saved is
  // // not any greater than just iterating through
  // for (*main_string_tracker; *main_string_tracker != '\0'; main_string_tracker++)
  // {
  //   size_t same_character_count = 0;
  //   while (*main_string_tracker == *splitter_tracker)
  //   {
  //     same_character_count++;
  //     if (same_character_count == splitter_size)
  //     {
  //     }
  //   }
  // }
}

/*
  Compare
*/
bool str_is_equal(const string *self, const string *other) {}
bool str_is_null_or_whitespace(const string *self) {}
bool str_is_alpha(const string *self) {}
bool str_is_numeric(const string *self) {}
bool str_is_alphanumeric(const string *self) {}
bool str_contains(const string *self, const string *text_in_question) {}
bool str_contains_using_basic_text(const string *self, const char *text_in_question) {}
bool str_starts_with(const string *self, const string *text_in_question) {}
bool str_starts_with_using_basic_text(const string *self, const char *text_in_question) {}
bool str_ends_with(const string *self, const string *text_in_question) {}
bool str_ends_with_using_basic_text(const string *self, const char *text_in_question) {}
bool str_is_upper(const string *self) {}
bool str_is_lower(const string *self) {}

/*
  Required functions
*/
void initialize_string_pointer(string *new, const char *starting_text)
{
  size_t starting_text_size = _get_length_of_basic_string(starting_text);
  // This looks a lot like our set_string_using_basic_text
  // with the catch that we are untrusting of the new data
  // maybe we reuse
  if (new)
  {
    size_t current_pointer_string_size = _get_length_of_basic_string(new->c_string);

    // if for some reason the supposed new ptr has a valid ptr
    if (new->c_string &&
        starting_text_size > current_pointer_string_size)
    {
      new->c_string = realloc(new->c_string, starting_text_size + 1);
      if (NULL == new->c_string)
      {
        printf("Failed to get reallocation for c string\n");
      }
    }
    if (NULL == new->c_string)
    {
      new->c_string = malloc(starting_text_size + 1);
      if (NULL == new->c_string)
      {
        printf("Failed to get memory for c string\n.");
      }
    }
  }
  else
  {
    // Yeah we could recall this with the now initalized ptr
    // but that feels disingenuous
    new = malloc(sizeof(string));
    if (NULL == new)
    {
      printf("Failed to get memory");
      return;
    }
    initialize_string_pointer(new, starting_text);
  }
}

/*
  Deconstructors
*/
void str_destroy(string *self)
{
  printf("I'm killing!\n");
  if (self)
  {
    if (NULL != (self)->c_string)
    {
      free((self)->c_string);
    }
    (self)->length = 0;
  }
}

void str_destroy_ptr(string **self)
{
  printf("DEBUG: I'M KILLING AGAIN.\n");
  if (self && *self)
  {
    if (NULL != (*self)->c_string)
    {
      free((*self)->c_string);
    }
    (*self)->length = 0;
    free(self);
  }
}

void str_destroy_array(string_array **array)
{
  if (array && *array)
  {
    for (int ix = 0; ix < (*array)->number_of_strings; ix++)
    {
      string *string = &(*array)->string_array[ix];
      if (string)
      {
        str_destroy_ptr(&string);
      }
    }
  }
}
