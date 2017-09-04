//
// Created by Narek Gharibyan on 9/4/17.
//

#ifndef KEYVI_C_API_H
#define KEYVI_C_API_H

#ifdef __cplusplus
extern "C" {
#endif

namespace keyvi {
    namespace dictionary {
        class Dictionary;

        class Match;
    }
}

struct Keyvi_Dictionary {
    keyvi::dictionary::Dictionary *ptr_;
};

struct Keyvi_Match {
    keyvi::dictionary::Match *ptr_;
};

Keyvi_Dictionary
keyvi_create_dictionary(const char *filename);

void
keyvi_destroy_dictionary(Keyvi_Dictionary);

const char *
keyvi_get_dictionary_stats(Keyvi_Dictionary);


#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif //KEYVI_C_API_H
