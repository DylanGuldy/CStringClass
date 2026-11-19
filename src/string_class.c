#include "string_class.h"

#define RETURN_IF_BAD_MALLOC(new_pointer) \
  if (!new_pointer)                       \
  {                                       \
    return MALLOC_ERROR;                  \
  }

/*
  Private helpers
*/
size_t priv_get_length_of_basic_string(const char *text)
{
  const char *priv_string_tracker_ = text;
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
string_error_code str_split(const string *self, const string *str_split, string_array *out) {}
string_error_code str_split_using_basic_text(const string *self, const char *splitter_text, string_array *out)
{
  if (!self || !out)
  {
    return NULL_POINTER_ERROR;
  }
  // Clear out ay old data
  // This may become a private function
  // if (NULL != out->string_array)
  // {
  //   printf("DEBUG: Freeing\n");
  //   // The last c_string in the array is null and length is 0
  //   for (int ix = 0; ix < out->number_of_strings; ix++)
  //   {
  //     if (out->string_array[ix].c_string)
  //     {
  //       free(out->string_array[ix].c_string);
  //     }
  //     out->number_of_strings = 0;
  //   }
  //   printf("DEBUG: Freeing string array now\n");
  //   free(out->string_array);
  // }
  char *split_indexes[100] = {0};
  size_t new_string_count = 0;

  size_t splitter_size = priv_get_length_of_basic_string(splitter_text);

  // We could also stop once the length of the remaining characters is less than
  // the str_split text but I think the cycles to calculate that and time saved is
  // not any greater than just iterating through
  for (char *main_string_tracker = self->c_string; *main_string_tracker != '\0'; main_string_tracker++)
  {
    size_t same_character_count = 0;

    // Loop through and see if the whole pattern is here
    if (memcmp(main_string_tracker, splitter_text, splitter_size) == 0)
    {
      // Save the location of the start of the match
      split_indexes[new_string_count] = main_string_tracker;
      // Increment for next save, and to keep track of how many matches
      new_string_count++;
      // Fast forward pointer to end of match, account for the +1 about
      // to happen at the top
      main_string_tracker += (splitter_size - 1);
    }
  }

  size_t number_of_result_strings = new_string_count;

  bool ends_with_split = str_ends_with_using_basic_text(self, splitter_text);

  string *result_string_array;
  if (!ends_with_split)
  {
    // +1 for the characters after the last split, +1 for the null terminate at the end of the array
    number_of_result_strings = number_of_result_strings + 2;
  }
  else
  {
    // +1 for the null terminate at the end of the array
    number_of_result_strings = number_of_result_strings + 1;
  }
  result_string_array = malloc(sizeof(string) * (number_of_result_strings));
  RETURN_IF_BAD_MALLOC(result_string_array)
  memset(result_string_array, 0x00, sizeof(string) * (number_of_result_strings));

  char *start_split_string_index = self->c_string;
  for (int ix = 0; ix < new_string_count; ix++)
  {
    size_t size_of_string = split_indexes[ix] - start_split_string_index;
    result_string_array[ix].c_string = malloc(sizeof(size_of_string + 1));
    RETURN_IF_BAD_MALLOC(result_string_array[ix].c_string)
    result_string_array[ix].length = size_of_string;
    memset(result_string_array[ix].c_string, 0x00, size_of_string);
    memcpy(result_string_array[ix].c_string, start_split_string_index, size_of_string);
    start_split_string_index = split_indexes[ix] + splitter_size;
  }

  // If it ends with a split we dont care
  if (!ends_with_split)
  {
    char *last_character_in_string = self->c_string + self->length;
    size_t last_string_length = last_character_in_string - start_split_string_index;
    result_string_array[new_string_count].c_string = malloc(last_string_length + 1);
    RETURN_IF_BAD_MALLOC(result_string_array[new_string_count].c_string);
    result_string_array[new_string_count].length = last_string_length;
    memset(result_string_array[new_string_count].c_string, 0x00, last_string_length);
    memcpy(result_string_array[new_string_count].c_string, start_split_string_index, last_string_length);
  }

  out->string_array = result_string_array;
  out->number_of_strings = number_of_result_strings - 1;
  return NO_ERROR;
}

/*
  Compare
  Do not return string_error_code, if a failure is detected will always return false
*/
bool str_is_equal(const string *self, const string *other)
{
  return str_is_equal_to_basic_text(self, other->c_string);
}
bool str_is_equal_to_basic_text(const string *self, const char *text_in_question)
{
  return memcmp(self->c_string, text_in_question, self->length) == 0;
}
bool str_is_null_or_whitespace(const string *self) {}
bool str_is_alpha(const string *self) {}
bool str_is_numeric(const string *self) {}
bool str_is_alphanumeric(const string *self) {}
bool str_contains(const string *self, const string *text_in_question) {}
bool str_contains_using_basic_text(const string *self, const char *text_in_question) {}
bool str_starts_with(const string *self, const string *text_in_question) {}
bool str_starts_with_using_basic_text(const string *self, const char *text_in_question) {}
bool str_ends_with(const string *self, const string *text_in_question)
{
  return str_ends_with_using_basic_text(self, text_in_question->c_string);
}
bool str_ends_with_using_basic_text(const string *self, const char *text_in_question)
{
  size_t text_size = priv_get_length_of_basic_string(text_in_question);
  if (text_size > self->length)
  {
    return false;
  }
  char *end_of_text = self->c_string;
  end_of_text += self->length;
  // back up the correct amount for mem compare
  end_of_text -= text_size;
  return (memcmp(end_of_text, text_in_question, text_size) == 0);
}
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
    RETURN_IF_BAD_MALLOC(new)
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
    if (NULL != self->c_string)
    {
      free(self->c_string);
    }
    self->length = 0;
  }
}

void str_destroy_ptr(string **self)
{
  printf("DEBUG: I'M KILLING AGAIN.\n");
  if (self && *self)
  {
    if ((*self)->c_string)
    {
      free((*self)->c_string);
    }
    (*self)->length = 0;
    free(*self);
  }
}

void str_destroy_array(string_array *array)
{
  if (array)
  {
    for (int ix = 0; ix < array->number_of_strings; ix++)
    {
      string *string = &((array)->string_array[ix]);
      if ((array)->string_array[ix].c_string)
      {
        free((array)->string_array[ix].c_string);
        (array)->string_array[ix].length = 0;
      }
    }
    free(array->string_array);
  }
}
