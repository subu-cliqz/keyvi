//
// keyvi - A key value store.
//
// Copyright 2015 Hendrik Muhs<hendrik.muhs@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/*
 * keyvicompiler.cpp
 *
 *  Created on: May 13, 2014
 *      Author: hendrik
 */

#include <iostream>

#include "vector/vector_generator.h"
#include "vector/vector.h"

using namespace keyvi::dictionary;

int main(int argc, char **argv) {

    keyvi::vector::VectorGenerator<fsa::internal::JsonValueStore> keyvi_vector;

    const size_t SIZE = 1025;

    for (size_t i = 0; i < SIZE; ++i) {
        keyvi_vector.push_back("Hello" + std::to_string(i));
    }

    keyvi_vector.write_to_file("/Users/narek/projects/keyvi/vector.kv");

    keyvi::vector::Vector vec("/Users/narek/projects/keyvi/vector.kv");

    for (size_t i = 0; i < SIZE; ++i) {
        std::cout << vec.get(i) << std::endl;
    }

    return 0;
}
