//
// Created by Narek Gharibyan on 8/28/17.
//

#ifndef KEYVI_RUSTMATCH_H
#define KEYVI_RUSTMATCH_H

#include <memory>

namespace keyvi {
    namespace dictionary {
        class Match;
    }
}

namespace keyvi {
    namespace rust {
        class RustMatch {
        public:
            explicit RustMatch(const dictionary::Match &match);

            ~RustMatch();

            const std::string &GetMatchedString() const;

            double GetScore() const;

            bool IsEmpty() const;

            std::string GetValueAsString() const;

            std::string GetRawValueAsString() const;

        private:
            std::shared_ptr<keyvi::dictionary::Match> pimpl_;
        };
    }
}


#endif //KEYVI_RUSTMATCH_H
