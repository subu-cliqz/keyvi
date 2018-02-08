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
 * dictionary_compiler.h
 *
 *  Created on: Jul 17, 2014
 *      Author: hendrik
 */

#ifndef KEYVI_VECTOR_VECTOR_GENERATOR_H_
#define KEYVI_VECTOR_VECTOR_GENERATOR_H_

#include <string>

#include <boost/property_tree/ptree.hpp>

#include "dictionary/fsa/internal/constants.h"
#include "dictionary/fsa/internal/null_value_store.h"
#include "dictionary/fsa/internal/serialization_utils.h"
#include "dictionary/fsa/generator.h"
#include "util/configuration.h"

#include "dictionary/fsa/internal/memory_map_manager.h"


using namespace keyvi::dictionary;

namespace keyvi {
namespace vector {


template<class ValueStoreT = fsa::internal::NullValueStore>
class VectorGenerator final {

    using OffsetType = uint64_t;

    using compiler_param_t = fsa::internal::IValueStoreWriter::vs_param_t;

public:
    explicit VectorGenerator(const compiler_param_t &params = compiler_param_t())
            : params_(params) {
        params_[TEMPORARY_PATH_KEY] = keyvi::util::mapGetTemporaryPath(params);

        temporary_directory_ = params_[TEMPORARY_PATH_KEY];
        temporary_directory_ /= boost::filesystem::unique_path("keyvi-vector-%%%%-%%%%-%%%%-%%%%");
        boost::filesystem::create_directory(temporary_directory_);

        const size_t external_memory_chunk_size = 100 * 1024 * 1024;

        index_store_.reset(
                new fsa::internal::MemoryMapManager(external_memory_chunk_size, temporary_directory_, "chunk"));

        value_store_.reset(new ValueStoreT(params_));
    }

    ~VectorGenerator() {
        boost::filesystem::remove_all(temporary_directory_);
    }

    VectorGenerator &operator=(VectorGenerator const &) = delete;

    VectorGenerator(const VectorGenerator &) = delete;

    void push_back(typename ValueStoreT::value_t value = ValueStoreT::no_value) {
        fsa::ValueHandle handle = RegisterValue(value);

        index_store_->Append(&handle.value_idx, sizeof(OffsetType));
        ++size_;
    }


    template<typename StringType>
    void write_to_file(StringType filename) {
        std::ofstream out_stream(filename, std::ios::binary);

        boost::property_tree::ptree pt;
        pt.put("size", std::to_string(size_));
        pt.put("index_size", std::to_string(index_store_->GetSize()));
        fsa::internal::SerializationUtils::WriteJsonRecord(out_stream, pt);

        index_store_->Write(out_stream, index_store_->GetSize());
        value_store_->Write(out_stream);
        out_stream.close();
    }

private:
    fsa::internal::IValueStoreWriter::vs_param_t params_;
    boost::filesystem::path temporary_directory_;
    std::unique_ptr<fsa::internal::MemoryMapManager> index_store_;
    std::unique_ptr<ValueStoreT> value_store_;
    size_t count_ = 0;
    size_t size_ = 0;

    fsa::ValueHandle RegisterValue(typename ValueStoreT::value_t value = ValueStoreT::no_value) {
        bool no_minimization = false;
        uint64_t value_idx = value_store_->GetValue(value, &no_minimization);

        fsa::ValueHandle handle = {
                value_idx,                            // offset of value
                count_++,                             // counter(order)
                value_store_->GetWeightValue(value),  // weight
                no_minimization,                      // minimization
                false                                 // deleted flag
        };

        return handle;
    }
};

} /* namespace dictionary */
} /* namespace keyvi */

#endif  // KEYVI_VECTOR_VECTOR_GENERATOR_H_
