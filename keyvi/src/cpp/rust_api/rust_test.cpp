//
// Created by Narek Gharibyan on 8/29/17.
//

#include "c_api.h"
#include <iostream>


int main() {
    auto dict = keyvi_create_dictionary("/Users/narek/projects/keyvi/test.kv");
    auto stats = keyvi_dictionary_get_statistics(dict);
    auto match = keyvi_dictionary_get(dict, "a");
    auto match_empty = keyvi_dictionary_get(dict, "aasdasd");
    auto value = keyvi_match_get_value_as_string(match);

    std::cout << stats << std::endl;
    std::cout << keyvi_match_get_score(match)<< std::endl;
    std::cout << keyvi_match_is_empty(match)<< std::endl;
    std::cout << keyvi_match_is_empty(match_empty)<< std::endl;
    std::cout << value << std::endl;

    keyvi_string_destroy(value);
    keyvi_match_destroy(match);
    keyvi_string_destroy(stats);
    keyvi_dictionary_destroy(dict);
}
