//
// Created by Narek Gharibyan on 8/29/17.
//

#include "c_api.h"
#include <iostream>


int main() {
    Keyvi_Dictionary dict = keyvi_create_dictionary("/Users/narek/projects/keyvi/test.kv");

    std::cout << keyvi_get_dictionary_stats(dict) << std::endl;

    keyvi_destroy_dictionary(dict);
}
