/* * keyvi - A key value store.
 *
 * Copyright 2018   Narek Gharibyan<narekgharibyan@gmail.com>
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
 *  vector_types.h
 *
 *  Created on: March 17, 2018
 *      Author: Narek Gharibyan <narekgharibyan@gmail.com>
 */

#ifndef KEYVI_VECTOR_VECTOR_TYPES_H_
#define KEYVI_VECTOR_VECTOR_TYPES_H_

#include "vector/types.h"
#include "vector/vector.h"
#include "vector/vector_generator.h"

namespace keyvi {
namespace vector {

using JsonVectorGenerator = VectorGenerator<dictionary::fsa::internal::JsonValueStore>;
using StringVectorGenerator = VectorGenerator<dictionary::fsa::internal::StringValueStore>;

using JsonVector = Vector<value_store_t::JSON_VALUE_STORE>;
using StringVector = Vector<value_store_t::STRING_VALUE_STORE>;

// shared pointer
typedef std::shared_ptr<StringVector> string_vector_t;
typedef std::shared_ptr<JsonVector> json_vector_t;

} /* namespace vector */
} /* namespace keyvi */

#endif  // KEYVI_VECTOR_VECTOR_TYPES_H_