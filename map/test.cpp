/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:39:36 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:39:39 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../other/message.hpp"
#include "./../other/generators.hpp"
#include "./map.hpp"
#include <map>
#include <unistd.h>

template <class T, class K, class V>
void my_generate(T *v, int size, K (*func_fill_key)(int*), V (*func_fill_value)(int*), int current) {
    K key;
    V value;

    for (int i = 0; i < size; i++) {
        key = func_fill_key(&current);
        value = func_fill_value(&current);
        v->operator[](key) = value;
    }
}

template <class T, class T2>
void copy_map(T *src, T2 *dst) {
    typename T::iterator it_b = src->begin();
    typename T::iterator it_e = src->end();

    while (it_b != it_e) {
        dst->operator[]((*it_b).first) = (*it_b).second;
        it_b++;
    }
}

template <class T>
void print_map(std::string title, T m) {
    std::cout << std::endl;
    std::cout << title << ": ";

    typename T::iterator it_begin = m.begin();
    typename T::iterator it_end = m.end();
    while (it_begin != it_end) {
        std::cout << (*it_begin).first << "|" << (*it_begin).second << "# ";
        it_begin++;
    }
    std::cout << std::endl;
}

template <class T1, class T2>
bool is_equal_iterators(T1 std_it, T2 ft_it) {
    if ((*std_it).first != (*ft_it).first || (*std_it).second != (*ft_it).second) {
        return (false);
    }
    return (true);
}

template <class T1, class T2>
void check_iterators(T1 std_it, T2 ft_it) {
    if ((*std_it).first != (*ft_it).first || (*std_it).second != (*ft_it).second) {
        print_error("*ITERATOR", (*std_it).first, (*ft_it).first);
    } else {
        print_ok();
    }
}

template <class T1, class T2>
void check_operators_reverse_iterator(T1 std_it, T1 std_it2, T2 ft_it, T2 ft_it2) {
    if ((*std_it).first != (*ft_it).first || (*std_it).second != (*ft_it).second) {
        print_error("*ITERATOR", (*std_it).first, (*ft_it).first);
    } else {
        print_ok();
    }

    if ((std_it2.operator->() == std_it.operator->()) != (ft_it2.operator->() == ft_it.operator->())) {
        print_error("ITERATOR->", (*(std_it2.operator->())).first, (*(ft_it2.operator->())).first);
    } else {
        print_ok();
    }

}

template <class T1, class T2>
void check_operators_iterator(T1 std_it, T1 std_it2, T2 ft_it, T2 ft_it2) {
    if ((std_it == std_it2) != (ft_it == ft_it2)) {
        print_error("==", (std_it == std_it2), (ft_it == ft_it2));
    } else {
        print_ok();
    }

    if ((std_it != std_it2) != (ft_it != ft_it2)) {
        print_error("!=", (std_it == std_it2), (ft_it == ft_it2));
    } else {
        print_ok();
    }

    if ((*std_it).first != (*ft_it).first || (*std_it).second != (*ft_it).second) {
        print_error("*ITERATOR", (*std_it).first, (*ft_it).first);
    } else {
        print_ok();
    }

    if ((std_it2.operator->() == std_it.operator->()) != (ft_it2.operator->() == ft_it.operator->())) {
        print_error("ITERATOR->", (*(std_it2.operator->())).first, (*(ft_it2.operator->())).first);
    } else {
        print_ok();
    }

    if ((*std_it++).first != (*ft_it++).first || (*std_it).second != (*ft_it).second) {
        print_error("*ITERATOR", (*std_it).first, (*ft_it).first);
    } else {
        print_ok();
    }

    if ((*std_it--).first != (*ft_it--).first || (*std_it).second != (*ft_it).second) {
        print_error("*ITERATOR", (*std_it).first, (*ft_it).first);
    } else {
        print_ok();
    }
}

template <class K, class T>
void check_maps(std::map<K, T> std_m, ft::map<K, T> ft_m) {
    if (std_m.size() != ft_m.size()) {
        print_error("SIZE", std_m.size(), ft_m.size());
        return ;
    } else if (std_m.max_size() != ft_m.max_size()) {
        print_error("MAX_SIZE", std_m.max_size(), ft_m.max_size());
    } else if (std_m.empty() != ft_m.empty()) {
        print_error("EMPTY", std_m.empty(), ft_m.empty());
    }

    typename std::map<K, T>::iterator it_std_b = std_m.begin();
    typename std::map<K, T>::iterator it_std_e = std_m.end();
    typename ft::map<K, T>::iterator it_ft_b = ft_m.begin();

    int index = 0;
    while (it_std_b != it_std_e) {
        if ((*it_std_b).first != (*it_ft_b).first) {
            print_error("DIFFERENT KEY: ", (*it_std_b).first, (*it_ft_b).first);
            return ;
        } else if ((*it_std_b).second != (*it_ft_b).second) {
            print_error("DIFFERENT VALUE: ", (*it_std_b).second, (*it_ft_b).second);
            return ;
        }
        it_std_b++;
        it_ft_b++;
        index++;
    }
    print_ok();
}

template <class K, class T>
void test_member_function(std::string title, K (*func_fill_key)(int*), T (*func_fill_value)(int*)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;

    // ####################################################################

    std::map<K, T>    std_a;
    ft::map<K, T>     ft_a;

    check_maps(std_a, ft_a);

    // ####################################################################

    std::map<K, T>    std_b;
    ft::map<K, T>     ft_b;

    my_generate(&std_b, size, func_fill_key, func_fill_value, (rand() % 100));
    copy_map(&std_b, &ft_b);

    check_maps(std_b, ft_b);

    // ####################################################################

    std::map<K, T> std_c(std_b.begin(), std_b.end());
    ft::map<K, T> ft_c(ft_b.begin(), ft_b.end());

    check_maps(std_c, ft_c);

    // ####################################################################

    std::map<K, T> std_d(std_c);
    ft::map<K, T> ft_d(ft_c);

    check_maps(std_d, ft_d);

    // ####################################################################

    std::map<K, T> std_f = std_d;
    ft::map<K, T> ft_f = ft_d;

    check_maps(std_f, ft_f);

    std::cout << std::endl << std::endl;
}

template <class K, class T>
void test_iterators(std::string title, K (*func_fill_key)(int*), T (*func_fill_value)(int*)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;

    std::map<K, T> std_m;
    ft::map<K, T> ft_m;
    while (std_m.size() < 3) {
        my_generate(&std_m, size, func_fill_key, func_fill_value, (rand() % 100));
    }
    copy_map(&std_m, &ft_m);

    // ####################################################################
    // BEGIN ++it it++

    {
        typename std::map<K, T>::iterator std_it = std_m.begin();
        typename ft::map<K, T>::iterator ft_it = ft_m.begin();

        check_iterators(std_it, ft_it);

        std_it++;
        ft_it++;
        ++std_it;
        ++ft_it;

        check_iterators(std_it, ft_it);
    }

    // ####################################################################
    // END --it it--

    {
        typename std::map<K, T>::iterator std_it = std_m.end();
        typename ft::map<K, T>::iterator ft_it = ft_m.end();

        std_it--;
        ft_it--;
        --std_it;
        --ft_it;

        check_iterators(std_it, ft_it);
    }

    // ####################################################################
    // RBEGIN ++it it++ base()

    {
        typename std::map<K, T>::reverse_iterator std_it(std_m.rbegin());
        typename ft::map<K, T>::reverse_iterator ft_it(ft_m.rbegin());
        typename std::map<K, T>::iterator std_it2 = std_it.base();
        typename ft::map<K, T>::iterator ft_it2 = ft_it.base();

        check_iterators(std_it, ft_it);

        std_it++;
        ft_it++;
        ++std_it;
        ++ft_it;

        check_iterators(std_it, ft_it);

        if ((*--std_it2).first != (*--ft_it2).first || (*std_it2).second != (*ft_it2).second) {
            print_error("base()", (*std_it2).first, (*ft_it2).first);
        } else {
            print_ok();
        }
    }

    // ####################################################################
    // REND --it it-- base()
    
    {
        typename std::map<K, T>::reverse_iterator std_it = std_m.rend();
        typename ft::map<K, T>::reverse_iterator ft_it = ft_m.rend();
        typename std::map<K, T>::iterator std_it2 = std_it.base();
        typename ft::map<K, T>::iterator ft_it2 = ft_it.base();

        std_it--;
        ft_it--;
        --std_it;
        --ft_it;

        check_iterators(std_it, ft_it);

        if ((*std_it2).first != (*ft_it2).first || (*std_it2).second != (*ft_it2).second) {
            print_error("base()", (*std_it2).first, (*ft_it2).first);
        } else {
            print_ok();
        }
    }

    // ####################################################################
    // CONSTRUCT

    {
        typename std::map<K, T>::iterator std_it = std_m.begin();
        typename ft::map<K, T>::iterator ft_it = ft_m.begin();

        check_iterators(std_it, ft_it);

        typename std::map<K, T>::iterator std_it2(std_it);
        typename ft::map<K, T>::iterator ft_it2(ft_it);

        check_iterators(std_it2, ft_it2);

        typename std::map<K, T>::iterator std_it3 = std_it;
        typename ft::map<K, T>::iterator ft_it3 = ft_it;

        check_iterators(std_it2, ft_it2);

    }

    // ####################################################################
    // ITERATOR: == != * -> 

    {
        typename std::map<K, T>::iterator std_it = std_m.begin();
        typename ft::map<K, T>::iterator ft_it = ft_m.begin();
        typename std::map<K, T>::iterator std_it2 = std_m.begin();
        typename ft::map<K, T>::iterator ft_it2 = ft_m.begin();

        check_operators_iterator(std_it, std_it2, ft_it, ft_it2);

        std_it2++;
        ft_it2++;

        std_it2++;
        ft_it2++;

        std_it2--;
        ft_it2--;

        check_operators_iterator(std_it, std_it2, ft_it, ft_it2);
    }

    // ####################################################################
    // REVERSE_ITERATOR: * ++ -- ->
    {
        typename std::map<K, T>::reverse_iterator std_it(std_m.rbegin());
        typename ft::map<K, T>::reverse_iterator ft_it(ft_m.rbegin());
        typename std::map<K, T>::reverse_iterator std_it2(std_m.rbegin());
        typename ft::map<K, T>::reverse_iterator ft_it2(ft_m.rbegin());

        check_operators_reverse_iterator(std_it, std_it2, ft_it, ft_it2);

        std_it2++;
        ft_it2++;
        std_it2++;
        ft_it2++;
        std_it2--;
        ft_it2--;

        check_operators_reverse_iterator(std_it, std_it2, ft_it, ft_it2);
    }

    std::cout << std::endl << std::endl;
}

template <class K, class T>
void test_elements_access(std::string title, K (*func_fill_key)(int *), T (*func_fill_value)(int *)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;

    std::map<K, T> std_m;
    ft::map<K, T> ft_m;
    my_generate(&std_m, size, func_fill_key, func_fill_value, (rand() % 100));
    copy_map(&std_m, &ft_m);

    // ####################################################################
    // OPERATOR

    typename std::map<K, T>::iterator it_b = std_m.begin();
    typename std::map<K, T>::iterator it_e = std_m.end();
    K key;
    T value;

    while (it_b != it_e) {
        key = (*it_b).first;
        value = (*it_b).second;
        ft_m[key] = value;
        it_b++;
    }
    it_b = std_m.begin();
    while (it_b != it_e) {
        if (ft_m[(*it_b).first] != std_m[(*it_b).first]) {
            print_error("operator[], key: ", (*it_b).second, (*it_e).second);
            return ;
        }
        it_b++;
    }

    print_ok();

    // ####################################################################

    std::cout << std::endl << std::endl;
}

template <class K, class T>
void test_modifiers(std::string title, K (*func_fill_key)(int*), T (*func_fill_value)(int*)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 10;

    // ####################################################################
    // INSERT

    {
        typedef typename std::map<K, T>::iterator iterator_std;
        typedef typename ft::map<K, T>::iterator iterator_ft;
        std::map<K, T> std_m;
        ft::map<K, T> ft_m;
         while (std_m.size() < 3) {
            my_generate(&std_m, size, func_fill_key, func_fill_value, (rand() % 100));
        }
        copy_map(&std_m, &ft_m);

        typename std::map<K, T>::value_type std_pair = *(++(std_m.begin()));
        typename ft::map<K, T>::value_type ft_pair = *(++(ft_m.begin()));
        typename std::pair<iterator_std, bool> std_pair2 = std_m.insert(std_pair);
        typename std::pair<iterator_ft, bool> ft_pair2 = ft_m.insert(ft_pair);

        if ((*(std_pair2.first)).first != (*(ft_pair2.first)).first) {
            print_error("INSERT PAIR, ERROR FIRST", (*(std_pair2.first)).first, (*(ft_pair2.first)).first);
        } else if ((*(std_pair2.first)).second != (*(ft_pair2.first)).second) {
            print_error("INSERT PAIR, ERROR SECOND", (*(std_pair2.first)).second, (*(ft_pair2.first)).second);
        } else {
            print_ok();
        }

        check_maps(std_m, ft_m);

        int i = 10;
        typename ft::map<K, T>::value_type new_pair;
        new_pair.first = func_fill_key(&i);
        new_pair.second = func_fill_value(&i);
        typename std::map<K, T>::iterator std_it1 = std_m.insert(std_m.begin(), new_pair);
        typename ft::map<K, T>::iterator ft_it1 = ft_m.insert(ft_m.begin(), new_pair);

        if ((*std_it1).first != (*ft_it1).first) {
            print_error("INSERT PAIR, ERROR FIRST", (*std_it1).first, (*ft_it1).first);
        } else if ((*std_it1).second != (*ft_it1).second) {
            print_error("INSERT PAIR, ERROR SECOND", (*ft_it1).second, (*ft_it1).second);
        } else {
            print_ok();
        }

        check_maps(std_m, ft_m);

        std::map<K, T> random_m;
         while (std_m.size() < 3) {
            my_generate(&random_m, size, func_fill_key, func_fill_value, (rand() % 100));
        }

        std_m.insert(random_m.begin(), random_m.end());
        ft_m.insert(random_m.begin(), random_m.end());

        check_maps(std_m, ft_m);
    }

    // ####################################################################
    // ERASE

    {
        std::map<K, T> std_m;
        ft::map<K, T> ft_m;
        while (std_m.size() < 3) {
            my_generate(&std_m, size, func_fill_key, func_fill_value, (rand() % 100));
        }
        copy_map(&std_m, &ft_m);
        

        typename std::map<K, T>::iterator std_it = std_m.begin();
        typename ft::map<K, T>::iterator ft_it = ft_m.begin();

        std_it++;
        ft_it++;

        std_m.erase(std_it);
        ft_m.erase(ft_it);

        check_maps(std_m, ft_m);

        std_it = ++(std_m.begin());
        ft_it = ++(ft_m.begin());

        int std_s = std_m.erase((*std_it).first);
        int ft_s = ft_m.erase((*ft_it).first);

        if (std_s != ft_s) {
            print_error("ERASE, OUTPUT", std_s, ft_s);
        } else {
            print_ok();
        }

        check_maps(std_m, ft_m);

        std_m.erase(std_m.begin(), std_m.end());
        ft_m.erase(ft_m.begin(), ft_m.end());

        check_maps(std_m, ft_m);
    }

    // ####################################################################
    // SWAP

    {
        std::map<K, T> std_m;
        ft::map<K, T> ft_m;
        while (std_m.size() < 3) {
            my_generate(&std_m, size, func_fill_key, func_fill_value, (rand() % 100));
        }
        copy_map(&std_m, &ft_m);

        std::map<K, T> std_m2;
        ft::map<K, T> ft_m2;
        while (std_m.size() < 3) {
            my_generate(&std_m, size, func_fill_key, func_fill_value, (rand() % 100));
        }
        copy_map(&std_m2, &ft_m2);

        std_m2.swap(std_m);
        ft_m2.swap(ft_m);

        check_maps(std_m, ft_m);
        check_maps(std_m2, ft_m2);
    }

    // ####################################################################
    // CLEAR

    {
        std::map<K, T> std_m;
        ft::map<K, T> ft_m;
        while (std_m.size() < 3) {
            my_generate(&std_m, size, func_fill_key, func_fill_value, (rand() % 100));
        }
        copy_map(&std_m, &ft_m);

        std_m.clear();
        ft_m.clear();

        check_maps(std_m, ft_m);
    }

    // ####################################################################

    std::cout << std::endl << std::endl;
}

template <class K, class T>
void test_observers(std::string title, K (*func_fill_key)(int*), T (*func_fill_value)(int*)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;

    // ####################################################################
    // KEY_COMP

    {
		std::map<K, T> std_m;
		ft::map<K, T> ft_m;
		
		typename std::map<K, T>::key_compare std_comp = std_m.key_comp();
		typename ft::map<K, T>::key_compare ft_comp = ft_m.key_comp();

        int k = 10;
        int p = 10;
        for (int i = 0; i < size; i++) {
            K key1 = func_fill_key(&k);
            K key2 = func_fill_key(&p);
            if (std_comp(key1, key2) != ft_comp(key1, key2)) {
                print_error("KEY_COMP", std_comp(key1, key2), ft_comp(key1, key2));
                return ;
            }
        }
		print_ok();
    }

    // ####################################################################
    // VALUE_COMP

    {
        std::map<K, T> std_m;
        ft::map<K, T> ft_m;
        my_generate(&std_m, size, func_fill_key, func_fill_value, (rand() % 100));
        copy_map(&std_m, &ft_m);

        typename std::map<K, T>::iterator std_begin = std_m.begin();
        std::pair<K, T> std_pair_end = *(std_m.rbegin());
        typename ft::map<K, T>::iterator ft_begin = ft_m.begin();
        std::pair<K, T> ft_pair_end = *(ft_m.rbegin());

        typename std::map<K, T>::value_compare std_comp = std_m.value_comp();
        typename ft::map<K, T>::value_compare ft_comp = ft_m.value_comp();

        while (std_begin != std_m.end()) {
            if (std_comp(*std_begin, std_pair_end) != ft_comp(*ft_begin, ft_pair_end)) {
                print_error("VALUE_COMP", std_comp(*std_begin, std_pair_end), ft_comp(*ft_begin, ft_pair_end));
                return ;
            }
            std_begin++;
            ft_begin++;
        }
        print_ok();
    }

    // ####################################################################

    std::cout << std::endl << std::endl;
}

template <class K, class T>
void test_operations(std::string title, K (*func_fill_key)(int*), T (*func_fill_value)(int*)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;

    std::map<K, T> std_m;
    ft::map<K, T> ft_m;

    while (std_m.size() < 3) {
        my_generate(&std_m, size, func_fill_key, func_fill_value, (rand() % 100));
    }
    copy_map(&std_m, &ft_m);

    int k = 10;
    std::pair<K, T> std_pair;
    std::pair<K, T> ft_pair;

    typename std::map<K, T>::iterator std_it_pair = ++(std_m.begin());
    
    std_pair.first = (*std_it_pair).first;
    std_pair.second = (*std_it_pair).second;
    ft_pair.first = (*std_it_pair).first;
    ft_pair.second = (*std_it_pair).second;

    std_m.insert(std_pair);
    ft_m.insert(ft_pair);

    // ####################################################################
    // FIND

    {
        typename std::map<K, T>::iterator std_it_find = std_m.find(std_pair.first);
        typename ft::map<K, T>::iterator ft_it_find = ft_m.find(ft_pair.first);

        if (is_equal_iterators(std_it_find, ft_it_find) == false) {
            print_error("FIND", (*std_it_find).first, (*ft_it_find).first);
        } else {
            print_ok();
        }
    }

    // ####################################################################
    // COUNT

    {
        size_t std_count = std_m.count(std_pair.first);
        size_t ft_count = ft_m.count(ft_pair.first);

        if (std_count != ft_count) {
            print_error("COUNT", std_m.count(std_pair.first), ft_m.count(std_pair.first));
        } else {
            print_ok();
        }
    }

    // ####################################################################
    // LOWER_BOUND

    {
        typename std::map<K, T>::iterator std_it_lower_bound = std_m.lower_bound(std_pair.first);
        typename ft::map<K, T>::iterator ft_it_lower_bound = ft_m.lower_bound(ft_pair.first);

        if (is_equal_iterators(std_it_lower_bound, ft_it_lower_bound) == false) {
            print_error("LOWER_BOUND", (*std_it_lower_bound).first, (*ft_it_lower_bound).first);
        } else {
            print_ok();
        }
    }

    // ####################################################################
    // UPPER_BOUND

    {
        typename std::map<K, T>::iterator std_it_upper_bound = std_m.upper_bound(std_pair.first);
        typename ft::map<K, T>::iterator ft_it_upper_bound = ft_m.upper_bound(ft_pair.first);

        // print_map("std", std_m);
        // print_map("ft", ft_m);
        if (is_equal_iterators(std_it_upper_bound, ft_it_upper_bound) == false) {
            print_error("UPPER_BOUND", (*std_it_upper_bound).first, (*ft_it_upper_bound).first);
        } else {
            print_ok();
        }
    }

    // ####################################################################
    // EQUAL_RANGE

    {
        std::pair<typename std::map<K, T>::iterator, typename std::map<K, T>::iterator> std_equal_range = std_m.equal_range(std_pair.first);
        std::pair<typename ft::map<K, T>::iterator, typename ft::map<K, T>::iterator> ft_equal_range = ft_m.equal_range(ft_pair.first);

        if (is_equal_iterators(std_equal_range.first, ft_equal_range.first) == false) {
            print_error("1 EQUAL_RANGE", (*(std_equal_range.first)).first, (*(ft_equal_range.first)).first);
        } else {
            print_ok();
        }

        if (is_equal_iterators(std_equal_range.second, ft_equal_range.second) == false) {
            print_error("2 EQUAL_RANGE", (*(std_equal_range.second)).first, (*(ft_equal_range.second)).first);
        } else {
            print_ok();
        }
    }

    // ####################################################################

    std::cout << std::endl << std::endl;
}

void test(void) {
    // ####################################################################

    print_title("___MEMBER FUNCTIONS_AND_CAPACITY___", "\033[33m", true);

    test_member_function("(Unique) INT: ", UniqueNumber, UniqueChar);
    test_member_function("(Unique) STRING: ", UniqueString, UniqueDouble);
    test_member_function("(Unique) DOUBLE: ", UniqueDouble, UniqueString);
    test_member_function("(Unique) CHAR: ", UniqueChar, UniqueNumber);

    test_member_function("(Random) INT: ", RandomNumber, RandomChar);
    test_member_function("(Random) String: ", RandomString, RandomDouble);
    test_member_function("(Random) DOUBLE: ", RandomDouble, RandomString);
    test_member_function("(Random) CHAR: ", RandomChar, RandomNumber);

    // ####################################################################

    print_title("___ITERATORS___", "\033[33m", true);

    test_iterators("(Unique) INT: ", UniqueNumber, UniqueChar);
    test_iterators("(Unique) STRING: ", UniqueString, UniqueDouble);
    test_iterators("(Unique) DOUBLE: ", UniqueDouble, UniqueString);
    test_iterators("(Unique) CHAR: ", UniqueChar, UniqueNumber);

    test_iterators("(Random) INT: ", RandomNumber, RandomChar);
    test_iterators("(Random) String: ", RandomString, RandomDouble);
    test_iterators("(Random) DOUBLE: ", RandomDouble, RandomString);
    test_iterators("(Random) CHAR: ", RandomChar, RandomNumber);

    // ####################################################################

    print_title("___ELEMENTS ACCESS___", "\033[33m", true);

    test_elements_access("(Unique) INT: ", UniqueNumber, UniqueChar);
    test_elements_access("(Unique) STRING: ", UniqueString, UniqueDouble);
    test_elements_access("(Unique) DOUBLE: ", UniqueDouble, UniqueString);
    test_elements_access("(Unique) CHAR: ", UniqueChar, UniqueNumber);

    test_elements_access("(Random) INT: ", RandomNumber, RandomChar);
    test_elements_access("(Random) String: ", RandomString, RandomDouble);
    test_elements_access("(Random) DOUBLE: ", RandomDouble, RandomString);
    test_elements_access("(Random) CHAR: ", RandomChar, RandomNumber);

    // ####################################################################

    print_title("___MODIFIERS___", "\033[33m", true);

    test_modifiers("(Unique) INT: ", UniqueNumber, UniqueChar);
    test_modifiers("(Unique) STRING: ", UniqueString, UniqueDouble);
    test_modifiers("(Unique) DOUBLE: ", UniqueDouble, UniqueString);
    test_modifiers("(Unique) CHAR: ", UniqueChar, UniqueNumber);

    test_modifiers("(Random) INT: ", RandomNumber, RandomChar);
    test_modifiers("(Random) String: ", RandomString, RandomDouble);
    test_modifiers("(Random) DOUBLE: ", RandomDouble, RandomString);
    test_modifiers("(Random) CHAR: ", RandomChar, RandomNumber);

    // ####################################################################

    print_title("___OBSERVERS___", "\033[33m", true);

    test_observers("(Unique) INT: ", UniqueNumber, UniqueChar);
    test_observers("(Unique) STRING: ", UniqueString, UniqueDouble);
    test_observers("(Unique) DOUBLE: ", UniqueDouble, UniqueString);
    test_observers("(Unique) CHAR: ", UniqueChar, UniqueNumber);

    test_observers("(Random) INT: ", RandomNumber, RandomChar);
    test_observers("(Random) String: ", RandomString, RandomDouble);
    test_observers("(Random) DOUBLE: ", RandomDouble, RandomString);
    test_observers("(Random) CHAR: ", RandomChar, RandomNumber);

    // ####################################################################

    print_title("___OPERATIONS___", "\033[33m", true);

    test_operations("(Unique) INT: ", UniqueNumber, UniqueChar);
    test_operations("(Unique) STRING: ", UniqueString, UniqueDouble);
    test_operations("(Unique) DOUBLE: ", UniqueDouble, UniqueString);
    test_operations("(Unique) CHAR: ", UniqueChar, UniqueNumber);

    test_operations("(Random) INT: ", RandomNumber, RandomChar);
    test_operations("(Random) String: ", RandomString, RandomDouble);
    test_operations("(Random) DOUBLE: ", RandomDouble, RandomString);
    test_operations("(Random) CHAR: ", RandomChar, RandomNumber);

    // ####################################################################
}

int main(void) {
    std::cout << std::endl;
    print_title(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TESTING MAP", "\033[36m", true);
    std::cout << std::endl;

    srand(time(NULL));

    test();

    return (0);
}
