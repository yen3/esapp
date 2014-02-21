/************************************************
 *  example.cpp
 *  ESA++
 *
 *  Copyright (c) 2014, Chi-En Wu
 *  Distributed under The BSD 3-Clause License
 ************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "seg.hpp"

using namespace std;
using namespace esapp;

int main (void)
{
    cout.imbue(locale("zh_tw.UTF-8"));

    vector<string> sequences = {
        u8"這是一隻可愛的小花貓",
        u8"一隻貓",
        u8"真可愛的貓",
        u8"這是一隻花貓",
        u8"小貓真可愛"
    };

    Segmenter segmenter(2.0, 10, 30, 3);

    /*
    segmenter.fit(sequences);
    for (auto const &sequence : sequences)
    {
        auto words = segmenter.segment(sequence);
        copy(words.begin(), words.end(), ostream_iterator<string>(cout, " "));
        cout << endl;
    }
    //*/

    auto words_list = segmenter.fit_and_segment(sequences);
    for (auto const &words : words_list)
    {
        copy(words.begin(), words.end(), ostream_iterator<string>(cout, " "));
        cout << endl;
    }

    return EXIT_SUCCESS;
}
