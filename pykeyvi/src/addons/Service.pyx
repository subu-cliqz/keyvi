
from cython.parallel import parallel, prange
cdef _Match* _get (_Dictionary* dict,  libcpp_string key, default = None) nogil:
    return new _Match(deref(dict)[(key)])

cdef libcpp_vector[libcpp_string] batch_get(libcpp_vector[_Dictionary*] dicts, libcpp_vector[libcpp_string] keys, default= None):
    cdef int count = dicts.size()
    cdef int i
    cdef libcpp_vector[libcpp_string] result
    result.resize(keys.size())

    with nogil, parallel(num_threads=10):
        for i in prange(count, schedule="guided"):
            result[i] = _get(dicts[i], keys[i], default).GetValueAsString()


    return result

def batch_get_py (dicts_with_keys, default = None):
    cdef int n = len(dicts_with_keys)
    cdef libcpp_vector[libcpp_string] _keys
    _keys.resize(n)
    cdef libcpp_vector[_Dictionary*] _dicts
    _dicts.resize(n)
    cdef int i
    cdef Dictionary dict
    for i, item  in enumerate(dicts_with_keys):
        dict, key = item
        if isinstance(key, unicode):
            _keys[i] = <libcpp_string>(key.encode("utf-8"))
        else:
            _keys[i] = <libcpp_string>(key)

        _dicts[i] = dict.inst.get()

    cdef libcpp_vector[libcpp_string] result = batch_get(_dicts, _keys,default)


    py_result = []
    for r in result:
        py_result.append(r)

    return py_result
