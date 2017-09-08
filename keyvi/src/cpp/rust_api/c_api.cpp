//
// Created by Narek Gharibyan on 9/4/17.
//

#include "rust_api/c_api.h"
#include "dictionary/dictionary.h"

namespace {
    char *
    std_2_c_string(const std::string &str) {
        auto result = static_cast<char *>(malloc(str.size() + 1));
        strcpy(result, str.c_str());
        return result;
    }
}

struct keyvi_dictionary {
    using Type=keyvi::dictionary::Dictionary;

    explicit keyvi_dictionary(const Type &obj)
            : obj_(obj) {}

    Type obj_;
};


struct keyvi_match {
    using Type=keyvi::dictionary::Match;

    explicit keyvi_match(const Type &obj)
            : obj_(obj) {}

    Type obj_;
};

//////////////////////
//// String
//////////////////////

void
keyvi_string_destroy(char *str) {
    free(str);
}


//////////////////////
//// Dictionary
//////////////////////

keyvi_dictionary *
keyvi_create_dictionary(const char *filename) {
    return new keyvi_dictionary(keyvi_dictionary::Type(filename));
}

void
keyvi_dictionary_destroy(const keyvi_dictionary *dict) {
    delete dict;
}

unsigned long long
keyvi_dictionary_get_size(const keyvi_dictionary *dict) {
    return dict->obj_.GetSize();
}

char *
keyvi_dictionary_get_statistics(const keyvi_dictionary *dict) {
    return std_2_c_string(dict->obj_.GetStatistics());
}

keyvi_match *
keyvi_dictionary_get(const keyvi_dictionary *dict, const char *key) {
    return new keyvi_match(dict->obj_[key]);
}


//////////////////////
//// Match
//////////////////////

void
keyvi_match_destroy(const keyvi_match *match) {
    delete match;
}

bool
keyvi_match_is_empty(const keyvi_match *match) {
    return match->obj_.IsEmpty();
}

double
keyvi_match_get_score(const keyvi_match *match) {
    return match->obj_.GetScore();
}

char *
keyvi_match_get_value_as_string(const keyvi_match *match) {
    return std_2_c_string(match->obj_.GetValueAsString());
}

char *
keyvi_match_get_matched_string(const keyvi_match *match) {
    return std_2_c_string(match->obj_.GetMatchedString());
}

