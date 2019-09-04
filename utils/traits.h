#pragma once
#include<iostream>
#include<type_traits>

namespace core
{
    template<typename T>
    using iter_value = typename std::iterator_traits<T>::value_type;

    template<typename T,typename = void >
    struct is_iterator : std::false_type {};

    template< typename T>
    struct is_iterator<T, typename std::enable_if_t<! std::is_same_v< iter_value<T>,void > >> : std::true_type {};
}