/* * keyvi - A key value store.
 *
 * Copyright 2015 Hendrik Muhs<hendrik.muhs@gmail.com>
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
 * key_only_dictionary.h
 *
 *  Created on: May 26, 2014
 *      Author: hendrik
 */

#ifndef KEYVI_VECTOR_VECTOR_TYPES_H_
#define KEYVI_VECTOR_VECTOR_TYPES_H_

#include "vector/vector_generator.h"
#include "vector/vector.h"

namespace keyvi {
namespace vector {

using VectorJsonGenerator = keyvi::vector::VectorGenerator<fsa::internal::JsonValueStore>;
using VectorJson = keyvi::vector::Vector;


} /* namespace dictionary */
} /* namespace keyvi */

#endif  // KEYVI_VECTOR_VECTOR_TYPES_H_
