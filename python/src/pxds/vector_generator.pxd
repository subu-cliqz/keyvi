from libcpp.string cimport string as libcpp_string
from libcpp.string  cimport string as libcpp_utf8_string
from libcpp.map cimport map as libcpp_map

cdef extern from "vector/vector_types.h" namespace "keyvi::vector":
    cdef cppclass VectorJsonGenerator:
        VectorJsonGenerator() except +
        VectorJsonGenerator(libcpp_map[libcpp_utf8_string, libcpp_utf8_string] value_store_params) except +
        void push_back(libcpp_utf8_string) nogil
        void write_to_file(libcpp_utf8_string) except +
