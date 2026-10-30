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
#define _auto_cleanup_string_ __attribute__((__cleanup__(destroy)))
#define _auto_cleanup_string_ptr_ __attribute__((__cleanup__(destroy_ptr)))
#define _auto_cleanup_string_array_ __attribute__((__cleanup__(destroy_array)))

// ONLY if you are okay with manually creating your string.
// For inital creation it's suggested to use the MACROS
// defined below
// NOTE: string_array construction is still manual
#define auto_string _auto_cleanup_string_ string
#define auto_string_ptr _auto_cleanup_string_ptr_ string *
#define auto_string_array _auto_cleanup_string_ptr_ string_array *

/*
  Must be implemented for auto clean up to work, if you don't this will break
*/
/*
  Deconstructors
*/
void initialize_string_pointer(string *new, const char *starting_text);
void destroy(string *self);
void destroy_ptr(string **self);
void destroy_array(string_array **array);

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

  TODO: Maybe have everhthing return int where possible
  to report pass / fail? I hate that idiom in C but it's
  really the only way to report success / fail

  TODO: Right now I have all non cons strings that are
  NOT self copied in, I.E. not using a pointer. I may
  want to review that. My justification is extra safety
  and in general we are copying in a struct with a pointer
  and an interger, that's not a lot of data
*/

/*
  Create and Destroy
*/
void clear(string *self);

/*
  Get and Set
*/
size_t get_length(string *self);
const char *get_c_string(const string *self);
void set_string(string *self, string *string);
void set_string_using_basic_text(string *self, const char *new_text);
string *get_substring_from_index_a_to_index_b(const string *self, int start_index_a, int end_index_b);

/*
  Manipulate / modify
*/
void to_upper(string *self);
void to_lower(string *self);
void reverse(string *self);
void replace_first(string *self, const string replacement, bool *replacment_found);
void replace_first_using_basic_text(string *self, const char *replacment, bool *replacment_found);
void replace(string *self, const string replacement, int *number_replaced);
void replace_using_basic_text(string *self, const char *replacment, int *number_replaced);

/*
  Grow / add
*/
void append(string *self, const string more_string);
void append_using_basic_text(string *self, const char *using_basic_text);
void join(string *self, string *strings, const string sparation_characters);
void join_using_basic_text(string *self, string *strings, const char *sparation_characters);
void pad_left(string *self, char character, size_t count);
void pad_right(string *self, char character, size_t count);

/*
  Insert
*/
void insert(string *self, string string, int index_of_insertion);
void insert_using_basic_text(string *self, const char *using_basic_text, int index_of_insertion);

/*
  Remove / shrink
*/
void delete_from_index_a_to_index_b(string *self, int start_index_a, int end_index_b);
void delete_first_instace(string *self, const string text_to_remove);
void delete_first_instance_using_basic_text(string *self, const char *text_to_remove);
void delete_all_instaces(string *self, const string text_to_remove);
void delete_all_instance_using_basic_text(string *self, const char *text_to_remove);
void trim_from_end(string *self, char character_to_remove);
void trim_from_start(string *self, char character_to_remove);

/*
  Find
*/
int find_substring(const string *self, const string sub_string);
int find_substring_using_basic_text(const string *self, const char *using_basic_text);
int find_first_char(const string *self, char c);
int find_last_char(const string *self, char c);

/*
  Split
*/
// Returns array of strings
string_array *split(const string *self, const string split, int *number_of_result_strings);
string_array *split_using_basic_text(const string *self, const char *using_basic_textint, int *number_of_result_strings);

/*
  Compare
*/
bool is_equal(const string *self, const string other);
bool is_null_or_whitespace(const string *self);
bool is_alpha(const string *self);
bool is_numeric(const string *self);
bool is_alphanumeric(const string *self);
bool contains(const string *self, const string text_in_question);
bool contains_using_basic_text(const string *self, const char *text_in_question);
bool starts_with(const string *self, const string text_in_question);
bool starts_with_using_basic_text(const string *self, const char *text_in_question);
bool ends_with(const string *self, const string text_in_question);
bool ends_with_using_basic_text(const string *self, const char *text_in_question);
bool is_upper(const string *self);
bool is_lower(const string *self);

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
