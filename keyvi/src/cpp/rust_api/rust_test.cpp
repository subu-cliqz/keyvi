//
// Created by Narek Gharibyan on 8/29/17.
//

#include "rust_dictionary.h"
#include <iostream>

using namespace keyvi::rust;

int main() {
    RustDictionary dict("/Users/narek/projects/keyvi/test.kv");
    std::cout << dict.GetStatistics() << std::endl;
    std::cout << dict["a"].GetValueAsString() << std::endl;
}
