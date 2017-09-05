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


keyvi_dictionary *
keyvi_create_dictionary(const char *);

void
keyvi_dictionary_destroy(const keyvi_dictionary *);

void
keyvi_string_destroy(char *str);

char *
keyvi_dictionary_get_statistics(const keyvi_dictionary *);

keyvi_match *
keyvi_dictionary_get(const keyvi_dictionary *, const char *);

unsigned long long
keyvi_dictionary_get_size(const keyvi_dictionary *);

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


#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif //KEYVI_C_API_H
