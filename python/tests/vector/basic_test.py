# -*- coding: utf-8 -*-
# Usage: py.test tests

import keyvi
import os


def test_basic_test():
    generator = keyvi.VectorJsonGenerator()

    size = 10000

    for i in range(size):
        generator.push_back(str(i))

    generator.write_to_file('vector_basic_test.kv')

    vector = keyvi.VectorJson('vector_basic_test.kv')

    assert size == vector.size()

    for i in range(size):
        assert str(i) == vector.get(i)

    os.remove('vector_basic_test.kv')
