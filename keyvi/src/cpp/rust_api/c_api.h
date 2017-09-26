//
// Created by Narek Gharibyan on 9/4/17.
//

#ifndef KEYVI_C_API_H
#define KEYVI_C_API_H

#ifdef __cplusplus
extern "C" {
#endif

struct keyvi_dictionary;
struct keyvi_match;
struct keyvi_match_iterator;

//////////////////////
//// String
//////////////////////

void
keyvi_string_destroy(char *str);


//////////////////////
//// Dictionary
//////////////////////

keyvi_dictionary *
keyvi_create_dictionary(const char *);

void
keyvi_dictionary_destroy(const keyvi_dictionary *);

unsigned long long
keyvi_dictionary_get_size(const keyvi_dictionary *);

char *
keyvi_dictionary_get_statistics(const keyvi_dictionary *);

keyvi_match *
keyvi_dictionary_get(const keyvi_dictionary *, const char *);

keyvi_match_iterator *
keyvi_dictionary_get_prefix_completions(const keyvi_dictionary *, const char *, int);

keyvi_match_iterator *
keyvi_dictionary_get_multi_word_completions(const keyvi_dictionary *, const char *, int);


//////////////////////
//// Match
//////////////////////

void
keyvi_match_destroy(const keyvi_match *);

bool
keyvi_match_is_empty(const keyvi_match *);

double
keyvi_match_get_score(const keyvi_match *);

char *
keyvi_match_get_value_as_string(const keyvi_match *);

char *
keyvi_match_get_matched_string(const keyvi_match *);


//////////////////////
//// Match Iterator
//////////////////////


void
keyvi_match_iterator_destroy(const keyvi_match_iterator *);

bool
keyvi_match_iterator_empty(const keyvi_match_iterator *);

keyvi_match *
keyvi_match_iterator_dereference(const keyvi_match_iterator *);

void
keyvi_match_iterator_increment(keyvi_match_iterator *);

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif //KEYVI_C_API_H
