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


cdef vector[string] to_string_vector(list objs):
    cdef unicode obj
    return [obj.encode('utf-8') for obj in objs]


cdef list from_string_vector(vector[string] str_vector):
    cdef string str
    return [str.decode('utf-8') for str in str_vector]


cdef class Segmenter(object):
    cdef _Segmenter *_segmenter

    def __cinit__(self, lrv_exp, max_iters=10, max_length=30, smooth=0.0):
        self._segmenter = new _Segmenter(lrv_exp, max_iters, max_length, smooth);

    def __dealloc__(self):
        del self._segmenter

    cpdef list fit_and_segment(self, list sequences):
        cdef vector[vector[string]] words_list
        cdef vector[string] words
        words_list = self._segmenter.fit_and_segment(to_string_vector(sequences))
        return [from_string_vector(words) for words in words_list]

    cpdef fit(self, list sequences):
        self._segmenter.fit(to_string_vector(sequences))

    cpdef list segment_all(self, list sequences):
        cdef vector[vector[string]] words_list
        cdef vector[string] words
        words_list = self._segmenter.segment(to_string_vector(sequences))
        return [from_string_vector(words) for words in words_list]

    cpdef list segment(self, unicode sequence):
        cdef vector[string] words
        words = self._segmenter.segment(<string>sequence.encode('utf-8'))
        return from_string_vector(words)
