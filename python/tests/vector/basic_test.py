# -*- coding: utf-8 -*-
# Usage: py.test tests

import keyvi
import os


def test_basic_json_test():
    generator = keyvi.VectorJsonGenerator()

    size = 10000

    for i in range(size):
        generator.push_back(str(i))

    generator.write_to_file('vector_json_basic_test.kv')

    vector = keyvi.VectorJson('vector_json_basic_test.kv')

    assert size == vector.size()

    for i in range(size):
        assert str(i) == vector.get(i)

    os.remove('vector_json_basic_test.kv')


def test_basic_string_test():
    generator = keyvi.VectorStringGenerator()

    size = 10000

    for i in range(size):
        generator.push_back(str(i))

    generator.write_to_file('vector_string_basic_test.kv')

    vector = keyvi.VectorString('vector_string_basic_test.kv')

    assert size == vector.size()

    for i in range(size):
        assert str(i) == vector.get(i)

    os.remove('vector_string_basic_test.kv')
