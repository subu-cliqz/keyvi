//
// Created by Narek Gharibyan on 8/28/17.
//

#include "rust_match.h"
#include "dictionary/match.h"

namespace keyvi {
    namespace rust {
        RustMatch::RustMatch(const keyvi::dictionary::Match &match)
                : pimpl_(new keyvi::dictionary::Match(match)) {}

        RustMatch::~RustMatch() {}

        const std::string &
        RustMatch::GetMatchedString() const {
            return pimpl_->GetMatchedString();
        }

        double RustMatch::GetScore() const {
            return pimpl_->GetScore();
        }

        bool RustMatch::IsEmpty() const {
            return pimpl_->IsEmpty();
        }

        std::string RustMatch::GetValueAsString() const {
            return pimpl_->GetValueAsString();
        }

        std::string RustMatch::GetRawValueAsString() const {
            return pimpl_->GetRawValueAsString();
        }

    }
}
