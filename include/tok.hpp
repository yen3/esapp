/************************************************
 *  tok.hpp
 *  ESA++
 *
 *  Copyright (c) 2014, Chi-En Wu
 *  Distributed under The BSD 3-Clause License
 ************************************************/

#ifndef ESAPP_TOK_HPP_
#define ESAPP_TOK_HPP_

#include <cwctype>
#include <string>

namespace esapp
{

/************************************************
 * Inline Helper Function(s)
 ************************************************/

inline int ischs(std::wint_t c)
{
    return c >= u'\u4E00' && c <= u'\u9FFF';
}

inline int isfwalnum(std::wint_t c)
{
    return (c >= u'Ａ' && c <= u'Ｚ') ||
           (c >= u'ａ' && c <= u'ｚ') ||
           (c >= u'０' && c <= u'９');
}

/************************************************
 * Declaration: class Tokenizer
 ************************************************/

class Tokenizer
{
public: // Public Type(s)
    typedef std::wstring Sequence;

public: // Public Method(s)
    Tokenizer(Sequence const &sequence);

    Sequence next(void);
    bool has_next(void) const;

private: // Private Method(s)
    template <typename Predicate>
    void skip(Predicate pred);

    template <typename Predicate>
    bool scan(Sequence &token, Predicate pred);

private: // Private Property(ies)
    Sequence const &sequence_;
    Sequence::const_iterator it_;
}; // class Tokenizer

/************************************************
 * Implementation: class Tokenizer
 ************************************************/

inline Tokenizer::Tokenizer(Sequence const &sequence)
    : sequence_(sequence), it_(sequence.begin())
{
    skip(&std::iswspace);
}

inline Tokenizer::Sequence Tokenizer::next(void)
{
    decltype(next()) token;
    if (!scan(token, &ischs) &&
        !scan(token, &isfwalnum) &&
        !scan(token, &std::iswalnum))
    {
        token.assign(1, *it_);
        ++it_;
    }

    skip(&std::iswspace);
    return token;
}

inline bool Tokenizer::has_next(void) const
{
    return it_ != sequence_.end();
}

template <typename Predicate>
inline void Tokenizer::skip(Predicate pred)
{
    for ( ; has_next() && pred(*it_); ++it_) { /* do nothing */ }
}

template <typename Predicate>
inline bool Tokenizer::scan(Sequence &token, Predicate pred)
{
    auto begin = it_;
    skip(pred);

    bool scanned = begin != it_;
    if (scanned) { token.assign(begin, it_); }

    return scanned;
}

} // namespace esa

#endif // ESAPP_TOK_HPP_
