#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <memory.h>
// remove this later
#include "stdio.h"

#define MAKE_STRING_

struct string;

struct string_array;

typedef struct string string;
typedef struct string_array string_array;

struct string
{
  char *c_string;
  size_t length;
};

struct string_array
{
  string *string_array;
  size_t number_of_strings;
};

typedef enum string_error_code string_error_code;

enum string_error_code
{
  NO_ERROR,
  MALLOC_ERROR,
  NULL_POINTER_ERROR,
  EXECUTION_ERROR
};

// For best practice, use MACROS for RAII

// Define auto clean up macros, users CAN use this but using the
// constructor macros or the below would be easier / more intuitive,
#define priv_auto_cleanup_string_ __attribute__((__cleanup__(str_destroy)))
#define priv_auto_cleanup_string_ptr_ __attribute__((__cleanup__(str_destroy_ptr)))
#define priv_auto_cleanup_string_array_ __attribute__((__cleanup__(str_destroy_array)))

// ONLY if you are okay with manually creating your string.
// For inital creation it's suggested to use the MACROS
// defined below
// NOTE: string_array construction is still manual
#define auto_string priv_auto_cleanup_string_ string
#define auto_string_ptr priv_auto_cleanup_string_ptr_ string *
#define auto_string_array priv_auto_cleanup_string_array_ string_array *

/*
  Must be implemented for auto clean up to work, if you don't this will break
*/
string_error_code str_initialize_string_pointer(string *new, const char *starting_text);
/*
  Deconstructors
*/
void str_destroy(string *self);
void str_destroy_ptr(string **self);
void str_destroy_array(string_array **array);

/*
  Helper, can ignore
*/
#define PRIV_GET_LENGTH_OF_BASIC_STRING(const_char_string) \
  ({                                                       \
  char *priv_string_tracker_ = const_char_string;          \
  while (*priv_string_tracker_ != '\0')                    \
  {                                                        \
    priv_string_tracker_++;                                \
  }                                                        \
  (priv_string_tracker_ - const_char_string); })

/*
  Constructors
*/
#define NEW_EMPTY_STRING(string_variable_name) \
  auto_string string_variable_name =           \
      {                                        \
          .c_string = NULL,                    \
          .length = 0};

#define NEW_STRING(string_variable_name, initial_value)                                  \
  NEW_EMPTY_STRING(string_variable_name)                                                 \
  {                                                                                      \
    string_variable_name.length = PRIV_GET_LENGTH_OF_BASIC_STRING(initial_value);        \
    string_variable_name.c_string = malloc(string_variable_name.length + 1);             \
    if (string_variable_name.c_string)                                                   \
    {                                                                                    \
      memset(string_variable_name.c_string, 0x00, string_variable_name.length + 1);      \
      memcpy(string_variable_name.c_string, initial_value, string_variable_name.length); \
    }                                                                                    \
    else                                                                                 \
    {                                                                                    \
      string_variable_name.length = 0;                                                   \
      string_variable_name.c_string = NULL;                                              \
    }                                                                                    \
  }

#define CLONE_STRING(new_string_variable_name, pointer_to_other_string) \
  NEW_STRING(new_string_variable_name, (pointer_to_other_string)->c_string)

#define NEW_STRING_PTR(string_variable_name)                     \
  auto_string_ptr string_variable_name = malloc(sizeof(string)); \
  if (string_variable_name)                                      \
  {                                                              \
    initialize_string_pointer(string_variable_name, "");         \
  }

/*
  NOTE: I could have used generics, but they are too
  recent to C, so we are doing it the old (not fun) way

  TODO: Maybe have everything return int where possible
  to report pass / fail? I hate that idiom in C but it's
  really the only way to report success / fail

  TODO: We can over malloc / realloc to keep us having having to
  realloc every time a string grows. This will involve having to
  keep track of capacity. This might happen but will be future
  growth, will have to keep track of how often strings grow.
*/

/*
  Create and Destroy
*/
void str_clear(string *self);

/*
  Get and Set
  DO NOT RETURN string_error
*/
size_t str_get_length(const string *self);
const char *str_get_c_string(const string *self);
string_error_code str_set_string(string *self, string *value);
string_error_code str_set_string_using_basic_text(string *self, const char *new_text);
string_error_code *str_get_substring_from_index_a_to_index_b(const string *self, int start_index_a, int end_index_b, string *out);

/*
  Manipulate / modify
*/
string_error_code str_to_upper(string *self);
string_error_code str_to_lower(string *self);
string_error_code str_reverse(string *self);
string_error_code str_replace_first(string *self, const string *find, const string *replacement, bool *replacement_found);
string_error_code str_replace_first_using_basic_text(string *self, const char *find, const char *replacement, bool *replacement_found);
string_error_code str_replace(string *self, const string *find, const string *replacement, int *number_replaced);
string_error_code str_replace_using_basic_text(string *self, const char *find, const char *replacement, int *number_replaced);

/*
  Grow / add
*/
string_error_code str_append(string *self, const string *more_string);
string_error_code str_append_using_basic_text(string *self, const char *using_basic_text);
string_error_code str_join(string *self, const string_array *strings, const string *separation_characters);
string_error_code str_join_using_basic_text(string *self, const string_array *strings, const char *separation_characters);
string_error_code str_pad_left(string *self, char character, size_t count);
string_error_code str_pad_right(string *self, char character, size_t count);

/*
  Insert
*/
string_error_code str_insert(string *self, const string *insertion, size_t index_of_insertion);
string_error_code str_insert_using_basic_text(string *self, const char *insertion, size_t index_of_insertion);

/*
  Remove / shrink
*/
string_error_code str_delete_from_index_a_to_index_b(string *self, size_t start_index_a, int end_index_b);
string_error_code str_delete_first_instance(string *self, const string *text_to_remove);
string_error_code str_delete_first_instance_using_basic_text(string *self, const char *text_to_remove);
string_error_code str_delete_all_instances(string *self, const string *text_to_remove);
string_error_code str_delete_all_instances_using_basic_text(string *self, const char *text_to_remove);
string_error_code str_trim_from_end(string *self, char character_to_remove);
string_error_code str_trim_from_start(string *self, char character_to_remove);

/*
  Find
*/
string_error_code str_find_substring(const string *self, const string *sub_string, size_t *index_out);
string_error_code str_find_substring_using_basic_text(const string *self, const char *using_basic_text, size_t *index_out);
string_error_code str_find_first_char(const string *self, char c, size_t *index_out);
string_error_code str_find_last_char(const string *self, char c);

/*
  Split
*/
// Returns array of strings
string_error_code *str_split(const string *self, const string *splitter, string_array *out);
string_error_code *str_split_using_basic_text(const string *self, const char *splitter_text, string_array *out);

/*
  Compare
  Do not directly return string_error_code, if a failure is detected always returns false
*/
bool str_is_equal(const string *self, const string *other);
bool str_is_null_or_whitespace(const string *self);
bool str_is_alpha(const string *self);
bool str_is_numeric(const string *self);
bool str_is_alphanumeric(const string *self);
bool str_contains(const string *self, const string *text_in_question);
bool str_contains_using_basic_text(const string *self, const char *text_in_question);
bool str_starts_with(const string *self, const string *text_in_question);
bool str_starts_with_using_basic_text(const string *self, const char *text_in_question);
bool str_ends_with(const string *self, const string *text_in_question);
bool str_ends_with_using_basic_text(const string *self, const char *text_in_question);
bool str_is_upper(const string *self);
bool str_is_lower(const string *self);
