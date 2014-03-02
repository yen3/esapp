# -*- coding: utf-8 -*-

#################################################
# esa.pyx
# ESA++
#
# Copyright (c) 2014, Chi-En Wu
# Distributed under The BSD 3-Clause License
#################################################

from libcpp.vector cimport vector
from libcpp.string cimport string

from seg cimport _Segmenter


cdef vector[string] to_string_vector(objs):
    cdef unicode obj
    return [obj.encode('utf-8') for obj in objs]


cdef list from_string_vector(vector[string] &str_vector):
    cdef string str
    return [str.decode('utf-8') for str in str_vector]


cdef class Segmenter(object):
    cdef _Segmenter *_segmenter

    def __cinit__(self, lrv_exp, max_iters=10, max_length=30, smooth=0.0):
        self._segmenter = new _Segmenter(lrv_exp, max_iters, max_length, smooth);

    def __dealloc__(self):
        del self._segmenter

    cpdef list fit_and_segment(self, sequences):
        cdef vector[string] cpp_sequences, words
        cdef string sequence
        cpp_sequences = to_string_vector(sequences)
        self._segmenter.fit(cpp_sequences)

        result = []
        for sequence in cpp_sequences:
            words = self._segmenter.segment(sequence)
            result.append(from_string_vector(words))
        return result

    cpdef fit(self, sequences):
        self._segmenter.fit(to_string_vector(sequences))

    cpdef list segment_all(self, sequences):
        cdef vector[string] words
        cdef unicode sequence

        result = []
        for sequence in sequences:
            words = self._segmenter.segment(sequence.encode('utf-8'))
            result.append(from_string_vector(words))
        return result

    cpdef list segment(self, unicode sequence):
        cdef vector[string] words
        words = self._segmenter.segment(<string>sequence.encode('utf-8'))
        return from_string_vector(words)
