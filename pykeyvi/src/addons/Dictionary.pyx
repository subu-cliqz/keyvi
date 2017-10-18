
from cython.parallel import parallel, prange



    cdef _Match* _get (self, libcpp_string key, default = None) nogil:
        return new _Match(deref(self.inst.get())[(key)])


    def get (self, key, default = None):
        if isinstance(key, unicode):
            key = key.encode('utf-8')
        assert isinstance(key, bytes), 'arg in_0 wrong type'
        cdef shared_ptr[_Match] _r = shared_ptr[_Match](self._get(key, default))
        if _r.get().IsEmpty():
            return default
        cdef Match result = Match.__new__(Match)
        result.inst = _r
        return result
    
    cdef libcpp_vector[_Match*] _batch_get (self, libcpp_vector[libcpp_string] keys, default = None):
        cdef int i
        cdef libcpp_vector[_Match*] result
        result.resize(keys.size())
        with nogil, parallel(num_threads=10):
            for i in prange(keys.size(), schedule="guided"):
                result[i] = self._get(keys[i], default)

        return result 
    
    def batch_get (self, keys, default = None):
        cdef int n = len(keys)
        cdef libcpp_vector[libcpp_string] _keys =libcpp_vector[libcpp_string](n)
        for i, k in enumerate(keys):
            if isinstance(k, unicode):
                _keys[i] = <libcpp_string>(keys[i].encode("utf-8"))
            else:
                _keys[i] = <libcpp_string>(keys[i])

        cdef libcpp_vector[_Match*] result = self._batch_get(_keys,default)
        py_result = []
        cdef shared_ptr[_Match] _r 
        cdef Match m
        cdef _Match* r
        for r in result:
            m = Match.__new__(Match)
            m.inst = shared_ptr[_Match](r)      
            py_result.append(m)

        return py_result
  
    def __contains__(self, key):
        if isinstance(key, unicode):
            key = key.encode('utf-8')

        assert isinstance(key, bytes), 'arg in_0 wrong type'

        return self.inst.get().Contains(key)

    def __len__(self):
        return self.inst.get().GetSize()

    def __getitem__ (self, key):
        if isinstance(key, unicode):
            key = key.encode('utf-8')

        assert isinstance(key, bytes), 'arg in_0 wrong type'
    
        cdef shared_ptr[_Match] _r = shared_ptr[_Match](new _Match(deref(self.inst.get())[(<libcpp_string>key)]))

        if _r.get().IsEmpty():
            raise KeyError(key)
        cdef Match py_result = Match.__new__(Match)
        py_result.inst = _r
        return py_result

    def _key_iterator_wrapper(self, iterator):
        for m in iterator:
            yield m.GetMatchedString()

    def _value_iterator_wrapper(self, iterator):
        for m in iterator:
            yield m.GetValue()

    def _item_iterator_wrapper(self, iterator):
        for m in iterator:
            yield (m.GetMatchedString(), m.GetValue())

    def GetAllKeys(self):
        cdef _MatchIteratorPair _r = self.inst.get().GetAllItems()
        cdef MatchIterator py_result = MatchIterator.__new__(MatchIterator)
        py_result.it = _r.begin()
        py_result.end = _r.end()
        return self._key_iterator_wrapper(py_result)

    def GetAllValues(self):
        cdef _MatchIteratorPair _r = self.inst.get().GetAllItems()
        cdef MatchIterator py_result = MatchIterator.__new__(MatchIterator)
        py_result.it = _r.begin()
        py_result.end = _r.end()
        return self._value_iterator_wrapper(py_result)

    def GetAllItems(self):
        cdef _MatchIteratorPair _r = self.inst.get().GetAllItems()
        cdef MatchIterator py_result = MatchIterator.__new__(MatchIterator)
        py_result.it = _r.begin()
        py_result.end = _r.end()
        return self._item_iterator_wrapper(py_result)

    def GetManifest(self):
        cdef libcpp_string _r = self.inst.get().GetManifestAsString()
        cdef bytes py_result = _r
        py_result_unicode = _r.decode('utf-8')

        return json.loads(py_result_unicode)

    def GetStatistics(self):
        cdef libcpp_string _r = self.inst.get().GetStatistics()
        cdef bytes py_result = _r
        py_result_unicode = _r.decode('utf-8')

        return {k: json.loads(v) for k, v in filter(
            lambda kv: kv and isinstance(kv, list) and len(kv) > 1 and kv[1],
            [s.rstrip().split("\n") for s in py_result_unicode.split("\n\n")]
        )}
