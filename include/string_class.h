#pragma once

#include <stdbool.h>
#include <stddef.h>

// remove this later
#include "stdio.h"

#define MAKE_STRING_

struct string;
struct _string_data;

struct string_array;

typedef struct string string;
typedef struct _string_data _string_data;
typedef struct string_array string_array;

// For best practice, use MACROS for RAII

// Define auto clean up macros, users CAN use this but using the
// constructor macros or the below would be easier / more intuitive,
#define _auto_cleanup_string_ __attribute__((__cleanup__(str_destroy)))
#define _auto_cleanup_string_ptr_ __attribute__((__cleanup__(str_destroy_ptr)))
#define _auto_cleanup_string_array_ __attribute__((__cleanup__(str_destroy_array)))

// ONLY if you are okay with manually creating your string.
// For inital creation it's suggested to use the MACROS
// defined below
// NOTE: string_array construction is still manual
#define auto_string _auto_cleanup_string_ string
#define auto_string_ptr _auto_cleanup_string_ptr_ string *
#define auto_string_array _auto_cleanup_string_array_ string_array *

/*
  Must be implemented for auto clean up to work, if you don't this will break
*/
/*
  Deconstructors
*/
void initialize_string_pointer(string *new, const char *starting_text);
void str_destroy(string *self);
void str_destroy_ptr(string **self);
void str_destroy_array(string_array **array);

/*
  Helper, can ignore
*/
#define _GET_LENGTH_OF_BASIC_STRING(const_char_string) \
  while (const char *s != '\0')                        \
  {                                                    \
    s++;                                               \
  }                                                    \
  (s - basic_string)

/*
  Constructors
*/
#define NEW_EMPTY_STRING(string_variable_name) \
  auto_string string_variable_name =           \
      {                                        \
          .data = {                            \
              .c_string = NULL,                \
              .length = 0}};

#define NEW_STRING(string_variable_name, inital_value)                                \
  NEW_EMPTY_STRING(string_variable_name)                                              \
  string_variable_name.data = {                                                       \
      .c_string = malloc(_GET_LENGTH_OF_BASIC_STRING(initial_value) + 1),             \
      .length = _GET_LENGTH_OF_BASIC_STRING(initial_value)};                          \
  if (NULL == string_variable_name.data.c_string)                                     \
  {                                                                                   \
    printf("Failed to get memory for c string\n");                                    \
  }                                                                                   \
  memset(new_string.data.c_string, 0x00, _GET_LENGTH_OF_BASIC_STRING(initial_value)); \
  memcpy(new_string.data.c_string, initial_text, _GET_LENGTH_OF_BASIC_STRING(initial_value));

#define CLONE_STRING(new_string_variable_name, pointer_to_other_string) \
  NEW_STRING(new_string_variable_name, pointer_to_other_string->data.c_string)

#define NEW_STRING_PTR(string_variable_name)                     \
  auto_string_ptr string_variable_name = malloc(sizeof(string)); \
  initialize_string_pointer(string_variable_name);

/*
  NOTE: I could have used generics, but they are too
  recent to C, so we are doing it the old (not fun) way

  TODO: Maybe have everything return int where possible
  to report pass / fail? I hate that idiom in C but it's
  really the only way to report success / fail

*/

/*
  Create and Destroy
*/
void clear(string *self);

/*
  Get and Set
*/
size_t str_get_length(string *self);
const char *str_get_c_string(const string *self);
void str_set_string(string *self, string *string);
void str_set_string_using_basic_text(string *self, const char *new_text);
string *str_get_substring_from_index_a_to_index_b(const string *self, int start_index_a, int end_index_b);

/*
  Manipulate / modify
*/
void str_to_upper(string *self);
void str_to_lower(string *self);
void str_reverse(string *self);
void str_replace_first(string *self, const string replacement, bool *replacement_fount);
void str_replace_first_using_basic_text(string *self, const char *replacement, bool *replacement_fount);
void str_replace(string *self, const string replacement, int *number_replaced);
void str_replace_using_basic_text(string *self, const char *replacement, int *number_replaced);

/*
  Grow / add
*/
void str_append(string *self, const string more_string);
void str_append_using_basic_text(string *self, const char *using_basic_text);
void str_join(string *self, string *strings, const string separation_characters);
void str_join_using_basic_text(string *self, string *strings, const char *separation_characters);
void str_pad_left(string *self, char character, size_t count);
void str_pad_right(string *self, char character, size_t count);

/*
  Insert
*/
void str_insert(string *self, string string, int index_of_insertion);
void str_insert_using_basic_text(string *self, const char *using_basic_text, int index_of_insertion);

/*
  Remove / shrink
*/
void str_delete_from_index_a_to_index_b(string *self, int start_index_a, int end_index_b);
void str_delete_first_instance(string *self, const string text_to_remove);
void str_delete_first_instance_using_basic_text(string *self, const char *text_to_remove);
void str_delete_all_instances(string *self, const string text_to_remove);
void str_delete_all_instance_using_basic_text(string *self, const char *text_to_remove);
void str_trim_from_end(string *self, char character_to_remove);
void str_trim_from_start(string *self, char character_to_remove);

/*
  Find
*/
int str_find_substring(const string *self, const string sub_string);
int str_find_substring_using_basic_text(const string *self, const char *using_basic_text);
int str_find_first_char(const string *self, char c);
int str_find_last_char(const string *self, char c);

/*
  Split
*/
// Returns array of strings
string_array *str_split(const string *self, const string splitter);
string_array *str_split_using_basic_text(const string *self, const char *splitter_text);

/*
  Compare
*/
bool str_is_equal(const string *self, const string other);
bool str_is_null_or_whitespace(const string *self);
bool str_is_alpha(const string *self);
bool str_is_numeric(const string *self);
bool str_is_alphanumeric(const string *self);
bool str_contains(const string *self, const string text_in_question);
bool str_contains_using_basic_text(const string *self, const char *text_in_question);
bool str_starts_with(const string *self, const string text_in_question);
bool str_starts_with_using_basic_text(const string *self, const char *text_in_question);
bool str_ends_with(const string *self, const string text_in_question);
bool str_ends_with_using_basic_text(const string *self, const char *text_in_question);
bool str_is_upper(const string *self);
bool str_is_lower(const string *self);

struct _string_data
{
  char *c_string;
  size_t length;
};

struct string
{
  _string_data data;
};

struct string_array
{
  string *string_array;
  size_t number_of_strings;
};
