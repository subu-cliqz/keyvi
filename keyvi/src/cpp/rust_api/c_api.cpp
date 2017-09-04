//
// Created by Narek Gharibyan on 9/4/17.
//

#include "rust_api/c_api.h"
#include "dictionary/dictionary.h"


Keyvi_Dictionary
keyvi_create_dictionary(const char* filename) {
    keyvi::dictionary::Dictionary* cpp_dict = new keyvi::dictionary::Dictionary(filename);
    return Keyvi_Dictionary {cpp_dict};
}

void
keyvi_destroy_dictionary(Keyvi_Dictionary dict) {
    delete dict.ptr_;
}

const char *
keyvi_get_dictionary_stats(Keyvi_Dictionary dict) {
    const std::string stats = dict.ptr_->GetStatistics();
    auto ret = static_cast<char *>(malloc(stats.size() + 1));
    strcpy(ret, stats.c_str());
    return ret;
}
