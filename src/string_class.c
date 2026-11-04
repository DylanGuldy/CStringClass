#include "string_class.h"

/*
  Private helpers
*/
size_t priv_get_length_of_basic_string(const char *text)
{
  char *priv_string_tracker_ = text;
  while (*priv_string_tracker_ != '\0')
  {
    priv_string_tracker_++;
  }
  return (size_t)(priv_string_tracker_ - text);
}

/*
  Class definitions
*/
void clear(string *self) {}

/*
  Get and Set
  DO NOT RETURN  string_error
*/
size_t str_get_length(const string *self) {}
const char *str_get_c_string(const string *self)
{
  return self->c_string;
}

string_error_code str_set_string(string *self, string *value) {}

string_error_code str_set_string_using_basic_text(string *self, const char *new_text)
{
  if (self)
  {
    size_t length = priv_get_length_of_basic_string(new_text);
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
string_error_code *str_get_substring_from_index_a_to_index_b(const string *self, int start_index_a, int end_index_b, string *out) {}

/*
  Manipulate / modify
*/
string_error_code str_to_upper(string *self) {}
string_error_code str_to_lower(string *self) {}
string_error_code str_reverse(string *self) {}
string_error_code str_replace_first(string *self, const string *find, const string *replacement, bool *replacement_found) {}
string_error_code str_replace_first_using_basic_text(string *self, const char *find, const char *replacement, bool *replacement_found) {}
string_error_code str_replace(string *self, const string *find, const string *replacement, int *number_replaced) {}
string_error_code str_replace_using_basic_text(string *self, const char *find, const char *replacement, int *number_replaced) {}

/*
  Grow / add
*/
string_error_code str_append(string *self, const string *more_string) {}
string_error_code str_append_using_basic_text(string *self, const char *using_basic_text) {}
string_error_code str_join(string *self, const string_array *strings, const string *separation_characters) {}
string_error_code str_join_using_basic_text(string *self, const string_array *strings, const char *separation_characters) {}
string_error_code str_pad_left(string *self, char character, size_t count) {}
string_error_code str_pad_right(string *self, char character, size_t count) {}

/*
  Insert
*/
string_error_code str_insert(string *self, const string *insertion, size_t index_of_insertion) {}
string_error_code str_insert_using_basic_text(string *self, const char *insertion, size_t index_of_insertion) {}

/*
  Remove / shrink
*/
string_error_code str_delete_from_index_a_to_index_b(string *self, size_t start_index_a, int end_index_b) {}
string_error_code str_delete_first_instance(string *self, const string *text_to_remove) {}
string_error_code str_delete_first_instance_using_basic_text(string *self, const char *text_to_remove) {}
string_error_code str_delete_all_instances(string *self, const string *text_to_remove) {}
string_error_code str_delete_all_instances_using_basic_text(string *self, const char *text_to_remove) {}
string_error_code str_trim_from_end(string *self, char character_to_remove) {}
string_error_code str_trim_from_start(string *self, char character_to_remove) {}

/*
  Find
*/
string_error_code str_find_substring(const string *self, const string *sub_string, size_t *index_out) {}
string_error_code str_find_substring_using_basic_text(const string *self, const char *using_basic_text, size_t *index_out) {}
string_error_code str_find_first_char(const string *self, char c, size_t *index_out) {}
string_error_code str_find_last_char(const string *self, char c) {}

/*
  Split
*/
// Returns array of strings
string_error_code *str_split(const string *self, const string *str_split, string_array *out) {}
string_error_code *str_split_using_basic_text(const string *self, const char *splitter_text, string_array *out)
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
  Do not return string_error_code, if a failure is detected will always return false
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
string_error_code str_initialize_string_pointer(string *new, const char *starting_text)
{
  size_t starting_text_size = priv_get_length_of_basic_string(starting_text);
  // This looks a lot like our set_string_using_basic_text
  // with the catch that we are untrusting of the new data
  // maybe we reuse
  if (new)
  {
    size_t current_pointer_string_size = priv_get_length_of_basic_string(new->c_string);

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
      return MALLOC_ERROR;
    }
    string_error_code error = str_initialize_string_pointer(new, starting_text);
    if (error)
    {
      return error;
    }
  }
  return NO_ERROR;
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
