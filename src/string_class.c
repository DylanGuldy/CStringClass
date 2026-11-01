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
size_t get_length(string *self) {}
const char *get_c_string(const string *self)
{
  return self->data.c_string;
}
void set_string(string *self, string *string) {}
void set_string_using_basic_text(string *self, const char *new_text)
{
  if (self)
  {
    size_t length = _get_length_of_basic_string(new_text);
    if (length > self->data.length)
    {
      if (self->data.c_string)
      {
        printf("Resizing\n");
        self->data.c_string = realloc(self->data.c_string, length + 1);
        if (NULL == self->data.c_string)
        {
          printf("Failed to get realloc of c string\n");
        }
      }
      else
      {
        printf("Creating new string\n");
        self->data.c_string = malloc(length + 1);
        if (NULL == self->data.c_string)
        {
          printf("Failed to malloc for c string\n");
        }
      }
    }
    memccpy((void *)self->data.c_string, (void *)new_text, (char)0x00, length + 1);
    self->data.length = length;

    printf("New string is: %s\n", self->data.c_string);
  }
}
string *get_substring_from_index_a_to_index_b(const string *self, int start_index_a, int end_index_b) {}

/*
  Manipulate / modify
*/
void to_upper(string *self) {}
void to_lower(string *self) {}
void reverse(string *self) {}
void replace_first(string *self, const string replacement, bool *replacment_found) {}
void replace_first_using_basic_text(string *self, const char *replacment, bool *replacment_found) {}
void replace(string *self, const string replacement, int *number_replaced) {}
void replace_using_basic_text(string *self, const char *replacment, int *number_replaced) {}

/*
  Grow / add
*/
void append(string *self, const string more_string) {}
void append_using_basic_text(string *self, const char *using_basic_text) {}
void join(string *self, string strings[], const string sparation_characters) {}
void join_using_basic_text(string *self, string strings[], const char *sparation_characters) {}
void pad_left(string *self, char character, size_t count) {}
void pad_right(string *self, char character, size_t count) {}

/*
  Insert
*/
void insert(string *self, string string, int index_of_insertion) {}
void insert_using_basic_text(string *self, const char *using_basic_text, int index_of_insertion) {}

/*
  Remove / shrink
*/
void delete_from_index_a_to_index_b(string *self, int start_index_a, int end_index_b) {}
void delete_first_instace(string *self, const string text_to_remove) {}
void delete_first_instance_using_basic_text(string *self, const char *text_to_remove) {}
void delete_all_instaces(string *self, const string text_to_remove) {}
void delete_all_instance_using_basic_text(string *self, const char *text_to_remove) {}
void trim_from_end(string *self, char character_to_remove) {}
void trim_from_start(string *self, char character_to_remove) {}

/*
  Find
*/
int find_substring(const string *self, const string sub_string) {}
int find_substring_using_basic_text(const string *self, const char *using_basic_text) {}
int find_first_char(const string *self, char c) {}
int find_last_char(const string *self, char c) {}

/*
  Split
*/
// Returns array of strings
string_array *split(const string *self, const string split) {}
string_array *split_using_basic_text(const string *self, const char *splitter_text)
{
  // const char *string_to_split = *self->data.c_string;
  // // Sliding window
  // char *main_string_tracker = string_to_split;
  // char *splitter_tracker = splitter_text;

  // size_t splitter_size = _get_length_of_basic_string(splitter_text);

  // // We could also stop once the length of the remaining characters is less than
  // // the split text but I think the cycles to calculate that and time saved is
  // // not any greather than just itterating through
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
bool is_equal(const string *self, const string other) {}
bool is_null_or_whitespace(const string *self) {}
bool is_alpha(const string *self) {}
bool is_numeric(const string *self) {}
bool is_alphanumeric(const string *self) {}
bool contains(const string *self, const string text_in_question) {}
bool contains_using_basic_text(const string *self, const char *text_in_question) {}
bool starts_with(const string *self, const string text_in_question) {}
bool starts_with_using_basic_text(const string *self, const char *text_in_question) {}
bool ends_with(const string *self, const string text_in_question) {}
bool ends_with_using_basic_text(const string *self, const char *text_in_question) {}
bool is_upper(const string *self) {}
bool is_lower(const string *self) {}

/*
  Requred functions
*/
void initialize_string_pointer(string *new, const char *starting_text)
{
  size_t starting_text_size = _get_length_of_basic_string(starting_text);
  // This looks a lot like our set_string_using_basic_text
  // with the catch that we are untrusting of the new data
  // maybe we reuse
  if (new)
  {
    size_t current_pointer_string_size = _get_length_of_basic_string(new->data.c_string);

    // if for some reasoon the supposed new ptr has a valid ptr
    if (new->data.c_string &&
        starting_text_size > current_pointer_string_size)
    {
      new->data.c_string = realloc(new->data.c_string, starting_text_size + 1);
      if (NULL == new->data.c_string)
      {
        printf("Failed to get reallocation for c string\n");
      }
    }
    if (NULL == new->data.c_string)
    {
      new->data.c_string = malloc(starting_text_size + 1);
      if (NULL == new->data.c_string)
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
void destroy(string *self)
{
  printf("I'm killing!\n");
  if (self)
  {
    if (NULL != (self)->data.c_string)
    {
      free((self)->data.c_string);
    }
    (self)->data.length = 0;
  }
}

void destroy_ptr(string **self)
{
  printf("DEBUG: I'M KILLING AGAIN.\n");
  if (self && *self)
  {
    if (NULL != (*self)->data.c_string)
    {
      free((*self)->data.c_string);
    }
    (*self)->data.length = 0;
    free(self);
  }
}

void destroy_array(string_array **array)
{
  if (array && *array)
  {
    for (int ix = 0; ix < (*array)->number_of_strings; ix++)
    {
      string *string = &(*array)->string_array[ix];
      if (string)
      {
        destroy_ptr(&string);
      }
    }
  }
}
