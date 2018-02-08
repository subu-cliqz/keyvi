from libcpp.string cimport string as libcpp_string
from libcpp.string cimport string as libcpp_utf8_string
from libc.stdint cimport uint32_t
from libcpp cimport bool
from match cimport Match
from match_iterator cimport MatchIteratorPair as _MatchIteratorPair

cdef extern from "vector/vector.h" namespace "keyvi::vector":
    cdef cppclass VectorJson:
        VectorJson (libcpp_utf8_string filename) except +
        libcpp_string get(size_t index)
        size_t size()

cdef extern from "vector/vector.h" namespace "keyvi::vector":
    cdef cppclass VectorString:
        VectorString (libcpp_utf8_string filename) except +
        libcpp_string get(size_t index)
        size_t size()
