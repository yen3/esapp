/************************************************
 *  encoded_multistring.hpp
 *  ESA++
 *
 *  Copyright (c) 2014-2015, Chi-En Wu
 *  Distributed under The BSD 3-Clause License
 ************************************************/

#ifndef ESAPP_ENCODED_MULTISTRING_HPP_
#define ESAPP_ENCODED_MULTISTRING_HPP_

#include <string>
#include <unordered_map>
#include <vector>

namespace esapp
{

namespace impl
{

/************************************************
 * Declaration: class encoded_multistring
 ************************************************/

class encoded_multistring
{
public: // Public Type(s)
    typedef uint32_t char_type;
    typedef uint16_t value_type;
    typedef ::std::vector<char_type> sequence;

    typedef typename ::std::vector<value_type>::const_iterator iterator;
    typedef typename ::std::vector<value_type>::const_iterator const_iterator;

public: // Public Method(s)
    encoded_multistring(void);
    template <typename Generator>
    explicit encoded_multistring(Generator const &g);

    iterator begin(void);
    const_iterator begin(void) const;
    iterator end(void);
    const_iterator end(void) const;

    value_type &operator[](size_t i);
    value_type const &operator[](size_t i) const;

    value_type char_id(char_type c) const;
    size_t offset(size_t i) const;

    size_t size(void) const;
    size_t size(size_t i) const;
    size_t alphabet_count(void) const;
    size_t string_count(void) const;

    void push_back(sequence const &s);
    void clear(void);

private: // Private Type(s)
    typedef ::std::vector<value_type> id_sequence;
    typedef ::std::unordered_map<char_type, value_type> char_id_map;

private: // Private Property(ies)
    char_id_map char_id_map_;
    id_sequence id_sequence_;
    ::std::vector<size_t> offsets_;

    static value_type const BOUNDARY_;
}; // class encoded_multistring

/************************************************
 * Implementation: class encoded_multistring
 ************************************************/

inline encoded_multistring::encoded_multistring(void)
    : char_id_map_({{0, BOUNDARY_}})
{
    // do nothing
}

template <typename Generator>
inline encoded_multistring::encoded_multistring(Generator const &g)
    : encoded_multistring()
{
    for (auto it = g; it; ++it)
    {
        push_back(it);
    }
}

inline encoded_multistring::iterator encoded_multistring::begin(void)
{
    return id_sequence_.begin();
}

inline encoded_multistring::const_iterator encoded_multistring::begin(void) const
{
    return id_sequence_.begin();
}

inline encoded_multistring::iterator encoded_multistring::end(void)
{
    return id_sequence_.end();
}

inline encoded_multistring::const_iterator encoded_multistring::end(void) const
{
    return id_sequence_.end();
}

inline encoded_multistring::value_type &
    encoded_multistring::operator[](size_t i)
{
    return id_sequence_[i];
}

inline encoded_multistring::value_type const &
    encoded_multistring::operator[](size_t i) const
{
    return id_sequence_[i];
}

inline encoded_multistring::value_type
    encoded_multistring::char_id(char_type c) const
{
    return char_id_map_.at(c);
}

inline size_t encoded_multistring::offset(size_t i) const
{
    return offsets_[i];
}

inline size_t encoded_multistring::size(void) const
{
    return id_sequence_.size();
}

inline size_t encoded_multistring::size(size_t i) const
{
    return (i > 0 ? offsets_[i] - offsets_[i - 1] : offsets_[i]) - 1;
}

inline size_t encoded_multistring::alphabet_count(void) const
{
    return char_id_map_.size();
}

inline size_t encoded_multistring::string_count(void) const
{
    return offsets_.size();
}

inline void encoded_multistring::clear(void)
{
    char_id_map_.clear();
    id_sequence_.clear();
    offsets_.clear();
    char_id_map_[0] = BOUNDARY_;
}

} // namespace impl

} // namespace esapp

#endif // ESAPP_ENCODED_MULTISTRING_HPP_
