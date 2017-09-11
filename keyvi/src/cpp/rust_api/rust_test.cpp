//
// Created by Narek Gharibyan on 8/29/17.
//

#include "c_api.h"
#include <iostream>


int main() {
    auto dict = keyvi_create_dictionary("/Users/narek/projects/keyvi/rskeyvi/test.kv");


    {
        auto stats = keyvi_dictionary_get_statistics(dict);
        std::cout << stats << std::endl;
        keyvi_string_destroy(stats);
    }

    {
        std::cout << keyvi_dictionary_get_size(dict) << std::endl;
    }

    {
        auto match = keyvi_dictionary_get(dict, "c");
        {
            auto matched_string = keyvi_match_get_matched_string(match);

            std::cout << matched_string << std::endl;
            keyvi_string_destroy(matched_string);
        }
        {
            auto value = keyvi_match_get_value_as_string(match);
            std::cout << value << std::endl;
            keyvi_string_destroy(value);

        }
        {
            std::cout << keyvi_match_get_score(match) << std::endl;
            std::cout << keyvi_match_is_empty(match) << std::endl;
        }
        keyvi_match_destroy(match);
    }

    {
        auto match_empty = keyvi_dictionary_get(dict, "aasdasd");
        std::cout << keyvi_match_is_empty(match_empty) << std::endl;
        keyvi_match_destroy(match_empty);
    }

    {
        auto mit = keyvi_dictionary_get_prefix_completions(dict, "a");

        for (; !keyvi_match_iterator_empty(mit); keyvi_match_iterator_increment(mit)) {
            auto m = keyvi_match_iterator_dereference(mit);
            auto matched_string = keyvi_match_get_matched_string(m);
            auto value = keyvi_match_get_value_as_string(m);
            std::cout << matched_string << " -> " << value << std::endl;
            keyvi_string_destroy(value);
            keyvi_string_destroy(matched_string);
            keyvi_match_destroy(m);
        }

        keyvi_match_iterator_destroy(mit);
    }


    keyvi_dictionary_destroy(dict);
}
