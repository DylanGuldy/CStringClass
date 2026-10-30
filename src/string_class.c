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
string_array *split(const string *self, const string split, int *number_of_result_strings) {}
string_array *split_using_basic_text(const string *self, const char *using_basic_textint, int *number_of_result_strings) {}
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

static const _string_vtable default_string_vtable = {

    .clear = clear,

    /*
      Get and Set
    */
    .get_length = get_length,
    .get_c_string = get_c_string,
    .set_string = set_string,
    .set_string_using_basic_text = set_string_using_basic_text,
    .get_substring_from_index_a_to_index_b = get_substring_from_index_a_to_index_b,
    /*
      Manipulate / modify
    */
    .to_upper = to_upper,
    .to_lower = to_lower,
    .reverse = reverse,
    .replace_first = replace_first,
    .replace_first_using_basic_text = replace_first_using_basic_text,
    .replace = replace,
    .replace_using_basic_text = replace_using_basic_text,
    /*
      Grow / add
    */
    .append = append,
    .append_using_basic_text = append_using_basic_text,
    .join = join,
    .join_using_basic_text = join_using_basic_text,
    .pad_left = pad_left,
    .pad_right = pad_right,
    /*
      Insert
    */
    .insert = insert,
    .insert_using_basic_text = insert_using_basic_text,
    /*
      Remove / shrink
    */
    .delete_from_index_a_to_index_b = delete_from_index_a_to_index_b,
    .delete_first_instace = delete_first_instace,
    .delete_first_instance_using_basic_text = delete_first_instance_using_basic_text,
    .delete_all_instaces = delete_all_instaces,
    .delete_all_instance_using_basic_text = delete_all_instance_using_basic_text,
    .trim_from_end = trim_from_end,
    .trim_from_start = trim_from_start,
    /*
      Find
    */
    .find_substring = find_substring,
    .find_substring_using_basic_text = find_substring_using_basic_text,
    .find_first_char = find_first_char,
    .find_last_char = find_last_char,
    /*
      Split
    */
    .split = split,
    .split_using_basic_text = split_using_basic_text,
    /*
      Compare
    */
    .is_equal = is_equal,
    .is_null_or_whitespace = is_null_or_whitespace,
    .is_alpha = is_alpha,
    .is_numeric = is_numeric,
    .is_alphanumeric = is_alphanumeric,
    .contains = contains,
    .contains_using_basic_text = contains_using_basic_text,
    .starts_with = starts_with,
    .starts_with_using_basic_text = starts_with_using_basic_text,
    .ends_with = ends_with,
    .ends_with_using_basic_text = ends_with_using_basic_text,
    .is_upper = is_upper,
    .is_lower = is_lower};

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
    new->data.length = starting_text_size;
    new->functions = &default_string_vtable;
  }
  else
  {
    // Yeah we could recall this with the now initalized ptr
    // but that feels disingenuous
    new = malloc(sizeof(string));
    if (NULL == new)
    {
      printf("Failed to get memory");
    }
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

const _string_vtable *get_vtable()
{
  return &default_string_vtable;
}