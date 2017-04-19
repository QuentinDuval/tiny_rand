//
// Created by Duval Quentin on 19/04/2017.
//

#ifndef TINYRANDOM_TEST_UTILS_H
#define TINYRANDOM_TEST_UTILS_H

#include <algorithm>

template <typename Container>
bool all_equal_to(Container const& cont, typename Container::value_type const& seeked)
{
   return std::all_of(cont.begin(), cont.end(), [&](auto const& val) { return val == seeked; });
}

template <typename Container, typename Predicate>
bool all_of(Container const& c, Predicate p)
{
   return std::all_of(c.begin(), c.end(), p);
};

template <typename Container>
bool contains(Container const& cont, typename Container::value_type const& seeked)
{
   return cont.end() != std::find(cont.begin(), cont.end(), seeked);
}

#endif //TINYRANDOM_TEST_UTILS_H
