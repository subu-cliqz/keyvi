/* * keyvi - A key value store.
 *
 * Copyright 2015, 2016 Narek Gharibyan <narekgharibyan@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * c_api.cpp
 *
 *  Created on: September 4, 2017
 *      Author: Narek Gharibyan <narekgharibyan@gmail.com>
 */

#include <cstring>
#include <iostream>

#include "c_api/c_api.h"
#include "dictionary/completion/multiword_completion.h"
#include "dictionary/completion/prefix_completion.h"
#include "dictionary/dictionary.h"
#include "vector/vector_types.h"

using keyvi::dictionary::Dictionary;
using keyvi::vector::string_vector_t;
using keyvi::vector::StringVector;
using keyvi::vector::json_vector_t;
using keyvi::vector::JsonVector;
using keyvi::dictionary::Match;
using keyvi::dictionary::MatchIterator;
using keyvi::dictionary::completion::MultiWordCompletion;
using keyvi::dictionary::completion::PrefixCompletion;
using keyvi::dictionary::dictionary_t;

namespace {
char* std_2_c_string(const std::string& str) {
  const size_t c_str_length = str.size() + 1;
  auto result = static_cast<char*>(malloc(c_str_length));
  strncpy(result, str.c_str(), c_str_length);
  return result;
}
}  // namespace

struct keyvi_dictionary {
  explicit keyvi_dictionary(const Dictionary& dictionary) : obj_(new Dictionary(dictionary)) {}

  dictionary_t obj_;
};

struct keyvi_string_vector {
    explicit keyvi_string_vector(string_vector_t vector)
        : obj_(vector)  {}

    string_vector_t obj_;
};

struct keyvi_json_vector {
    explicit keyvi_json_vector(json_vector_t vector)
        : obj_(vector)  {}

    json_vector_t obj_;
};

struct keyvi_match {
  explicit keyvi_match(const Match& obj) : obj_(obj) {}

  Match obj_;
};

struct keyvi_match_iterator {
  explicit keyvi_match_iterator(const MatchIterator::MatchIteratorPair& obj) : current_(obj.begin()), end_(obj.end()) {}

  MatchIterator current_;
  const MatchIterator end_;
};

//////////////////////
//// String
//////////////////////

void keyvi_string_destroy(char* str) {
  free(str);
}

//////////////////////
//// Dictionary
//////////////////////

keyvi_dictionary* keyvi_create_dictionary(const char* filename) {
  try {
    return new keyvi_dictionary(Dictionary(filename));
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return nullptr;
  }
}

void keyvi_dictionary_destroy(const keyvi_dictionary* dict) {
  delete dict;
}

size_t keyvi_dictionary_get_size(const keyvi_dictionary* dict) {
  return dict->obj_->GetSize();
}

char* keyvi_dictionary_get_statistics(const keyvi_dictionary* dict) {
  return std_2_c_string(dict->obj_->GetStatistics());
}

keyvi_match* keyvi_dictionary_get(const keyvi_dictionary* dict, const char* key) {
  return new keyvi_match(dict->obj_->operator[](key));
}

keyvi_match_iterator* keyvi_dictionary_get_prefix_completions(const keyvi_dictionary* dict, const char* key,
                                                              size_t cutoff) {
  PrefixCompletion prefixCompletion(dict->obj_);
  return new keyvi_match_iterator(prefixCompletion.GetCompletions(key, cutoff));
}

keyvi_match_iterator* keyvi_dictionary_get_fuzzy(const keyvi_dictionary* dict, const char* key,
                                                 size_t max_edit_distance) {
  return new keyvi_match_iterator(dict->obj_->GetFuzzy(key, max_edit_distance));
}

keyvi_match_iterator* keyvi_dictionary_get_multi_word_completions(const keyvi_dictionary* dict, const char* key,
                                                                  size_t cutoff) {
  MultiWordCompletion multiWordCompletion(dict->obj_);
  return new keyvi_match_iterator(multiWordCompletion.GetCompletions(key, cutoff));
}

//////////////////////
//// String Vector
//////////////////////
keyvi_string_vector* keyvi_create_string_vector(const char* filename) {
    try {
        return new keyvi_string_vector(std::make_shared<StringVector>(filename));
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }

}

void keyvi_string_vector_destroy(const struct keyvi_string_vector* vector) {
    delete vector;
}

char* keyvi_string_vector_get(const struct keyvi_string_vector* vector,  const size_t index) {
    return std_2_c_string(vector->obj_->Get(index));
}

size_t keyvi_string_vector_get_size(const keyvi_string_vector* vector) {
    return vector->obj_->Size();
}

//////////////////////
//// Json Vector
//////////////////////
keyvi_json_vector* keyvi_create_json_vector(const char* filename) {
    try {
        return new keyvi_json_vector(std::make_shared<JsonVector>(filename));
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }

}

void keyvi_json_vector_destroy(const struct keyvi_json_vector* vector) {
    delete vector;
}

char* keyvi_json_vector_get(const struct keyvi_json_vector* vector,  const size_t index) {
    return std_2_c_string(vector->obj_->Get(index));
}

size_t keyvi_json_vector_get_size(const keyvi_json_vector* vector) {
    return vector->obj_->Size();
}

//////////////////////
//// Match
//////////////////////

void keyvi_match_destroy(const keyvi_match* match) {
  delete match;
}

bool keyvi_match_is_empty(const keyvi_match* match) {
  return match->obj_.IsEmpty();
}

double keyvi_match_get_score(const keyvi_match* match) {
  return match->obj_.GetScore();
}

char* keyvi_match_get_value_as_string(const keyvi_match* match) {
  return std_2_c_string(match->obj_.GetValueAsString());
}

char* keyvi_match_get_matched_string(const keyvi_match* match) {
  return std_2_c_string(match->obj_.GetMatchedString());
}

//////////////////////
//// Match Iterator
//////////////////////

void keyvi_match_iterator_destroy(const keyvi_match_iterator* iterator) {
  delete iterator;
}

bool keyvi_match_iterator_empty(const keyvi_match_iterator* iterator) {
  return iterator->current_ == iterator->end_;
}

keyvi_match* keyvi_match_iterator_dereference(const keyvi_match_iterator* iterator) {
  return new keyvi_match(*iterator->current_);
}

void keyvi_match_iterator_increment(keyvi_match_iterator* iterator) {
  iterator->current_.operator++();
}