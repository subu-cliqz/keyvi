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
 * dictionary.h
 *
 *  Created on: Jun 3, 2014
 *      Author: hendrik
 */

#ifndef KEYVI_VECTOR_VECTOR_H_
#define KEYVI_VECTOR_VECTOR_H_

#include <string>

#include "dictionary/fsa/internal/memory_map_flags.h"

#include "dictionary/fsa/internal/value_store_factory.h"

using namespace keyvi::dictionary;

namespace keyvi {
namespace vector {

template <fsa::internal::value_store_t value_store_type>
class Vector final {
public:
    explicit Vector(const std::string &filename) {
        loading_strategy_types loading_strategy = loading_strategy_types::lazy_no_readahead;

        std::ifstream file_stream(filename, std::ios::binary);
        if (!file_stream.good()) {
            throw std::invalid_argument("file not found");
        }

        properties_ = fsa::internal::SerializationUtils::ReadJsonRecord(file_stream);

        size_ = boost::lexical_cast<size_t>(properties_.get<std::string>("size"));
        const auto index_size = boost::lexical_cast<size_t>(properties_.get<std::string>("index_size"));

        file_mapping_ = boost::interprocess::file_mapping(filename.c_str(), boost::interprocess::read_only);

//        int flags = 0;
//
//        flags |= MAP_SHARED;
//
//#ifdef MAP_NOSYNC
//        flags |= MAP_NOSYNC
//#endif

        const boost::interprocess::map_options_t map_options =
                fsa::internal::MemoryMapFlags::FSAGetMemoryMapOptions(loading_strategy);

        index_region_ = boost::interprocess::mapped_region(file_mapping_, boost::interprocess::read_only,
                                                           file_stream.tellg(), index_size, 0, map_options);

        index_region_.advise(boost::interprocess::mapped_region::advice_types::advice_random);

        index_ptr_ = static_cast<uint64_t *>(index_region_.get_address());

        file_stream.seekg(size_t(file_stream.tellg()) + index_size);

        value_store_reader_.reset(
                fsa::internal::ValueStoreFactory::MakeReader(value_store_type, file_stream,
                                                             &file_mapping_, loading_strategy));
    }

    std::string get(const size_t index) const {
        assert(index < size_);
        return value_store_reader_->GetValueAsString(index_ptr_[index]);
    }

    size_t size() const {
        return size_;
    }

private:
    boost::property_tree::ptree properties_;
    std::unique_ptr<fsa::internal::IValueStoreReader> value_store_reader_;
    boost::interprocess::file_mapping file_mapping_;
    boost::interprocess::mapped_region index_region_;

    uint64_t *index_ptr_;

    size_t size_;

};

} /* namespace dictionary */
} /* namespace keyvi */

#endif  //  KEYVI_VECTOR_VECTOR_H_
