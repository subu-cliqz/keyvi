//
// Created by Narek Gharibyan on 8/28/17.
//

#include "rust_dictionary.h"
#include "dictionary/dictionary.h"

namespace keyvi {
    namespace rust {
        RustDictionary::RustDictionary(const std::string &filename)
                : pimpl_(new dictionary::Dictionary(filename)) {}

        RustDictionary::~RustDictionary() {}

        std::string RustDictionary::GetStatistics() const {
            return pimpl_->GetStatistics();
        }

        uint64_t RustDictionary::GetSize() const {
            return pimpl_->GetSize();
        }

        bool RustDictionary::Contains(const std::string &key) const {
            return pimpl_->Contains(key);
        }

        RustMatch RustDictionary::operator[](const std::string &key) const {
            dictionary::Match match = pimpl_->operator[](key);
            return RustMatch(match);
        }
    }
}
