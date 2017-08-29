//
// Created by Narek Gharibyan on 8/28/17.
//

#ifndef KEYVI_DICTIONARY_H
#define KEYVI_DICTIONARY_H

#include <memory>
#include <rust_api/rust_match.h>

namespace keyvi {
    namespace dictionary {
        class Dictionary;
    }
}

namespace keyvi {
    namespace rust {
        class RustDictionary {
        public:
            explicit RustDictionary(const std::string &filename);

            ~RustDictionary();

            std::string GetStatistics() const;

            uint64_t GetSize() const;

            bool Contains(const std::string &key) const;

            RustMatch operator[](const std::string &key) const;

        private:
            std::unique_ptr<dictionary::Dictionary> pimpl_;
        };
    }
}


#endif //KEYVI_DICTIONARY_H
