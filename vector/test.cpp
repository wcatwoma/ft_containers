/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:40:21 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:40:56 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./vector.hpp"
#include <iostream>
#include <vector>
#include "./../other/message.hpp"
#include "./../other/generators.hpp"
#include <unistd.h>

template <class T, class T2>
void my_generate(T *v, int size, T2 (*func_fill)(int*), int current) {
    for (int i = 0; i < size; i++) {
        v->push_back(func_fill(&current));
    }
}

template <class T, class T2>
void copy_vector(T *src, T2 *dst) {
    for (int i = 0; i < src->size(); i++) {
        dst->push_back(src->at(i));
    }
}

template <class T>
void print_vector(std::string title, T v) {
    std::cout << std::endl;
    std::cout << title << ": ";
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

template <class T1, class T2>
void check_iterators(T1 std_it, T2 ft_it) {
    if (*std_it != *ft_it) {
        print_error("*ITERATOR", *std_it, *ft_it);
    } else {
        print_ok();
    }
    
}

template <class T1, class T2>
void check_operators_reverse_iterator(T1 std_it, T1 std_it2, T2 ft_it, T2 ft_it2) {
    if (*std_it2 != *ft_it2) {
        print_error("*ITERATOR", *std_it2, *ft_it2);
    } else {
        print_ok();
    }

    if ((std_it2.operator->() == std_it.operator->()) != (ft_it2.operator->() == ft_it.operator->())) {
        print_error("ITERATOR->", std_it2.operator->(), ft_it2.operator->());
    } else {
        print_ok();
    }

    if ((std_it[2] == std_it2[2]) != (ft_it[2] == ft_it2[2])) {
        print_error("it[n]", std_it[2], ft_it[2]);
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

    if (*std_it2 != *ft_it2) {
        print_error("*ITERATOR", *std_it2, *ft_it2);
    } else {
        print_ok();
    }

    if ((std_it2.operator->() == std_it.operator->()) != (ft_it2.operator->() == ft_it.operator->())) {
        print_error("ITERATOR->", std_it2.operator->(), ft_it2.operator->());
    } else {
        print_ok();
    }

    if ((std_it < std_it2) != (ft_it < ft_it2)) {
        print_error("<", (std_it < std_it2), (ft_it < ft_it2));
    } else {
        print_ok();
    }

    if ((std_it > std_it2) != (ft_it > ft_it2)) {
        print_error(">", (std_it > std_it2), (ft_it > ft_it2));
    } else {
        print_ok();
    }

    if ((std_it >= std_it2) != (ft_it >= ft_it2)) {
        print_error(">=", (std_it >= std_it2), (ft_it >= ft_it2));
    } else {
        print_ok();
    }

    if ((std_it <= std_it2) != (ft_it <= ft_it2)) {
        print_error("<=", (std_it <= std_it2), (ft_it <= ft_it2));
    } else {
        print_ok();
    }

    if ((std_it[2] == std_it2[2]) != (ft_it[2] == ft_it2[2])) {
        print_error("it[n]", std_it[2], ft_it[2]);
    } else {
        print_ok();
    }

    if ((std_it + 1 == std_it2 + 1) != (ft_it + 2 == ft_it2 + 2)) {
        print_error("it + 2", *(std_it + 2), *(ft_it2 + 2));
    } else {
        print_ok();
    }

    if ((std_it - 1 == std_it2 - 1) != (ft_it - 1 == ft_it2 - 1)) {
        print_error("it - 1", 1, 1);
    } else {
        print_ok();
    }

    if ((std_it2 - std_it) != (ft_it2 - ft_it)) {
        print_error("it2 - it", (std_it2 - std_it), (ft_it2 - ft_it));
    } else {
        print_ok();
    }

    if (*std_it++ != *ft_it++) {
        print_error("*it++", *(std_it - 1), *(ft_it - 1));
    } else {
        print_ok();
    }

    if (*std_it != *ft_it) {
        print_error("*it++", *(std_it - 1), *(ft_it - 1));
    } else {
        print_ok();
    }

}

template <class T>
void check_vectors(std::vector<T> std_v, ft::vector<T> ft_v) {
    if (std_v.size() != ft_v.size()) {
        print_error("SIZE", std_v.size(), ft_v.size());
        return ;
    } else if (std_v.max_size() != ft_v.max_size()) {
        print_error("MAX_SIZE", std_v.max_size(), ft_v.max_size());
        return ;
    } else if (std_v.capacity() != ft_v.capacity()) {
        print_error("CAPACITY", std_v.capacity(), ft_v.capacity());
        return ;
    } else if (std_v.empty() != ft_v.empty()) {
        print_error("EMPTY", std_v.empty(), ft_v.empty());
    }
    for (int i = 0; i < std_v.size(); i++) {
        if (std_v[i] != ft_v[i]) {
            print_error("DIFFERENT ELEMENTS INDEX: " + std::to_string(i), std_v[i], ft_v[i]);
            return ;
        }
    }
    print_ok();
}

template <class T>
void test_member_function(std::string title, T val) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;

    // ####################################################################

    std::vector<T>    std_a;
    ft::vector<T>     ft_a;

    check_vectors(std_a, ft_a);

    // ####################################################################

    std::vector<T>    std_b(size, val);
    ft::vector<T>     ft_b(size, val);

    check_vectors(std_b, ft_b);

    // ####################################################################

    std::vector<T> std_c(std_b.begin(), std_b.end());
    ft::vector<T> ft_c(ft_b.begin(), ft_b.end());

    check_vectors(std_c, ft_c);

    // ####################################################################

    std::vector<T> std_d(std_c);
    ft::vector<T> ft_d(ft_c);

    check_vectors(std_d, ft_d);

    // ####################################################################

    std::vector<T> std_f = std_d;
    ft::vector<T> ft_f = ft_d;

    check_vectors(std_f, ft_f);

    std::cout << std::endl << std::endl;
}

template <class T>
void test_iterators(std::string title, T (*func_fill)(int*)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 10;

    std::vector<T> std_v;
    ft::vector<T> ft_v;
    my_generate(&std_v, size, func_fill, (rand() % 100));
    copy_vector(&std_v, &ft_v);

    // ####################################################################
    // BEGIN ++it it++

    {
        typename std::vector<T>::iterator std_it = std_v.begin();
        typename ft::vector<T>::iterator ft_it = ft_v.begin();

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
        typename std::vector<T>::iterator std_it = std_v.end();
        typename ft::vector<T>::iterator ft_it = ft_v.end();

        std_it--;
        ft_it--;
        --std_it;
        --ft_it;

        check_iterators(std_it, ft_it);

    }

    // ####################################################################
    // RBEGIN ++it it++ base()

    {
        typename std::vector<T>::reverse_iterator std_it(std_v.rbegin());
        typename ft::vector<T>::reverse_iterator ft_it(ft_v.rbegin());
        typename std::vector<T>::iterator std_it2 = std_it.base();
        typename ft::vector<T>::iterator ft_it2 = ft_it.base();

        check_iterators(std_it, ft_it);

        std_it++;
        ft_it++;
        ++std_it;
        ++ft_it;

        check_iterators(std_it, ft_it);

        if (*(--std_it2) != *(--ft_it2)) {
            print_error("base()", *(std_it2), *(ft_it2));
        } else {
            print_ok();
        }

    }

    // ####################################################################
    // REND --it it-- base()

    {
        typename std::vector<T>::reverse_iterator std_it = std_v.rend();
        typename ft::vector<T>::reverse_iterator ft_it = ft_v.rend();
        typename std::vector<T>::iterator std_it2 = std_it.base();
        typename ft::vector<T>::iterator ft_it2 = ft_it.base();

        std_it--;
        ft_it--;
        --std_it;
        --ft_it;

        check_iterators(std_it, ft_it);

        if (*(std_it2) != *(ft_it2)) {
            print_error("base()", *(std_it2), *(ft_it2));
        } else {
            print_ok();
        }
    }

    // ####################################################################
    // CONSTRUCT

    {
        typename std::vector<T>::iterator std_it = std_v.begin();
        typename ft::vector<T>::iterator ft_it = ft_v.begin();

        check_iterators(std_it, ft_it);

        typename std::vector<T>::iterator std_it2(std_it);
        typename ft::vector<T>::iterator ft_it2(ft_it);

        check_iterators(std_it2, ft_it2);

        typename std::vector<T>::iterator std_it3 = std_it;
        typename ft::vector<T>::iterator ft_it3 = ft_it;

        check_iterators(std_it2, ft_it2);

    }

    // ####################################################################
    // ITERATOR: == != * -> < > <= >= it[n] (it += n) (it -= n) (it + 2) (it - 2) (2 + it) (it - it2)

    {
        typename std::vector<T>::iterator std_it = std_v.begin();
        typename ft::vector<T>::iterator ft_it = ft_v.begin();
        typename std::vector<T>::iterator std_it2 = std_v.begin();
        typename ft::vector<T>::iterator ft_it2 = ft_v.begin();

        check_operators_iterator(std_it, std_it2, ft_it, ft_it2);

        std_it2++;
        ft_it2++;
        std_it2++;
        ft_it2++;
        std_it2--;
        ft_it2--;
        std_it2 += 2;
        ft_it2 += 2;
        std_it2 -= 1;
        ft_it2 -= 1;

        check_operators_iterator(std_it, std_it2, ft_it, ft_it2);
    }

    // ####################################################################
    // REVERSE_ITERATOR: * + ++ += - -- -= -> it[n]
    {
        typename std::vector<T>::reverse_iterator std_it(std_v.rbegin());
        typename ft::vector<T>::reverse_iterator ft_it(ft_v.rbegin());
        typename std::vector<T>::reverse_iterator std_it2(std_v.rbegin());
        typename ft::vector<T>::reverse_iterator ft_it2(ft_v.rbegin());

        check_operators_reverse_iterator(std_it, std_it2, ft_it, ft_it2);

        std_it2++;
        ft_it2++;
        std_it2++;
        ft_it2++;
        std_it2--;
        ft_it2--;
        std_it2 += 5;
        ft_it2 += 5;
        std_it2 -= 3;
        ft_it2 -= 3;
        ft_it2 = ft_it2 + 2;
        std_it2 = std_it2 + 2;
        ft_it2 = ft_it2 - 1;
        std_it2 = std_it2 - 1;

        check_operators_reverse_iterator(std_it, std_it2, ft_it, ft_it2);
    }

    std::cout << std::endl << std::endl;
}

template <class T>
void test_capacity(std::string title, T val) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;

    std::vector<T> std_in(size, val);
    ft::vector<T> ft_in(size, val);

    // ####################################################################
    // SIZE
    // EMPTY
    // MAX_SIZE

    {
        std::vector<T> std_v;
        std::vector<T> std_v2 = std_in;
        ft::vector<T> ft_v;
        ft::vector<T> ft_v2 = ft_in;

        check_vectors(std_v, ft_v);
        check_vectors(std_v2, ft_v2);
    }

    // ####################################################################
    // RESIZE

    {
        std::vector<T> std_v = std_in;
        std::vector<T> std_v2 = std_in;
        ft::vector<T> ft_v = ft_in;
        ft::vector<T> ft_v2 = ft_in;

        std_v.resize(size + 1);
        std_v2.resize(size - 1);

        ft_v.resize(size + 1);
        ft_v2.resize(size - 1);

        check_vectors(std_v, ft_v);
        check_vectors(std_v2, ft_v2);
    }

    // ####################################################################
    // RESERVE

    {
        std::vector<T> std_v = std_in;
        std::vector<T> std_v2 = std_in;
        ft::vector<T> ft_v = ft_in;
        ft::vector<T> ft_v2 = ft_in;

        std_v.reserve(size + 1);
        std_v2.reserve(size - 1);

        ft_v.reserve(size + 1);
        ft_v2.reserve(size - 1);

        check_vectors(std_v, ft_v);
        check_vectors(std_v2, ft_v2);
    }

    // ####################################################################

    std::cout << std::endl << std::endl;
}

template <class T>
void test_elements_access(std::string title, T (*func_fill)(int *)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;

    std::vector<T> std_v;
    ft::vector<T> ft_v;
    my_generate(&std_v, size, func_fill, (rand() % 100));
    copy_vector(&std_v, &ft_v);

    // ####################################################################
    // OPERATOR[]

    {
        int error = 0;

        for (int i = 0; i < std_v.size(); i++) {
            if (std_v[i] != ft_v[i]) {
                print_error("OPERATOR[" + std::to_string(i) + "]", std_v[i], ft_v[i]);
                error = 1;
                break ;
            }
        }
        if (!error) {
            print_ok();
        }
    }

    // ####################################################################
    // AT

    {
        int error = 0;

        for (int i = 0; i < std_v.size(); i++) {
            try {
                if (std_v.at(i) != ft_v.at(i)) {
                    print_error("AT(" + std::to_string(i) + ")", std_v.at(i), ft_v.at(i));
                    error = 1;
                    break ;
                }
            } catch (std::exception &x) {

            }
        }

        try {
            ft_v.at(-1);
            error++;
        } catch (std::exception &x) {}

        if (!error) {
            print_ok();
        }
    }

    // ####################################################################
    // FRONT

    {
        if (std_v.front() != ft_v.front()) {
            print_error("FRONT()", std_v.front(), ft_v.front());
        } else {
            print_ok();
        }
    }

    // ####################################################################
    // BACK

    {
        if (std_v.back() != ft_v.back()) {
            print_error("BACK()", std_v.back(), ft_v.back());
        } else {
            print_ok();
        }
    }

    // ####################################################################

    std::cout << std::endl << std::endl;
}

template <class T>
void test_modifiers(std::string title, T (*func_fill)(int*)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;
    T element = func_fill(&size);

    // ####################################################################
    // ASSIGN

    {
        std::vector<T> std_v;
        ft::vector<T> ft_v;
        my_generate(&std_v, size, func_fill, (rand() % 100));
        copy_vector(&std_v, &ft_v);

        std::vector<T> std_v2;
        ft::vector<T> ft_v2;
        copy_vector(&std_v, &std_v2);
        copy_vector(&std_v, &ft_v2);

        std_v.assign(size + 1, element);
        std_v2.assign(size - 1, element);
        ft_v.assign(size + 1, element);
        ft_v2.assign(size - 1, element);

        check_vectors(std_v, ft_v);
        check_vectors(std_v2, ft_v2);

        std::vector<T> random_v;
        my_generate(&random_v, (rand() % 100), func_fill, (rand() % 100));

        ft_v.assign(random_v.begin(), random_v.end());
        ft_v2.assign(random_v.begin(), random_v.end());
        std_v.assign(random_v.begin(), random_v.end());
        std_v2.assign(random_v.begin(), random_v.end());

        check_vectors(std_v, ft_v);
        check_vectors(std_v2, ft_v2);
    }

    // ####################################################################
    // PUSH_BACK

    {
        std::vector<T> std_v;
        ft::vector<T> ft_v;
        my_generate(&std_v, size, func_fill, (rand() % 100));
        copy_vector(&std_v, &ft_v);

        std_v.push_back(element);
        ft_v.push_back(element);

        check_vectors(std_v, ft_v);
    }

    // ####################################################################
    // POP_BACK

    {
        std::vector<T> std_v;
        ft::vector<T> ft_v;
        my_generate(&std_v, size, func_fill, (rand() % 100));
        copy_vector(&std_v, &ft_v);

        std_v.pop_back();
        ft_v.pop_back();

        check_vectors(std_v, ft_v);
    }

    // ####################################################################
    // INSERT

    {
        std::vector<T> std_v;
        ft::vector<T> ft_v;
        my_generate(&std_v, size, func_fill, (rand() % 100));
        copy_vector(&std_v, &ft_v);
        typename std::vector<T>::iterator std_it = ++(std_v.begin());
        typename ft::vector<T>::iterator ft_it = ++(ft_v.begin());

        typename std::vector<T>::iterator std_it2 = std_v.insert(std_it, element);
        typename ft::vector<T>::iterator ft_it2 = ft_v.insert(ft_it, element);

        check_iterators(std_it2, ft_it2);
        check_vectors(std_v, ft_v);

        std_it = ++(std_v.begin());
        ft_it = ++(ft_v.begin());
        std_v.insert(std_it, 10, element);
        ft_v.insert(ft_it, 10, element);

        check_vectors(std_v, ft_v);

        std::vector<T> random_v;
        my_generate(&random_v, (rand() % 100), func_fill, (rand() % 100));

        std_it = ++(std_v.begin());
        ft_it = ++(ft_v.begin());
        std_v.insert(std_it, random_v.begin(), random_v.end());
        ft_v.insert(ft_it, random_v.begin(), random_v.end());

        check_vectors(std_v, ft_v);
    }

    // ####################################################################
    // ERASE

    {
        std::vector<T> std_v;
        ft::vector<T> ft_v;
        my_generate(&std_v, size, func_fill, (rand() % 100));
        copy_vector(&std_v, &ft_v);

        typename std::vector<T>::iterator std_it = std_v.begin();
        typename ft::vector<T>::iterator ft_it = ft_v.begin();

        std_it = std_v.erase(std_it);
        ft_it = ft_v.erase(ft_it);
        
        check_iterators(std_it, ft_it);
        check_vectors(std_v, ft_v);

        std_it = std_v.erase(++(std_v.begin()), --(std_v.end()));
        ft_it = ft_v.erase(++(ft_v.begin()), --(ft_v.end()));

        check_iterators(std_it, ft_it);
        check_vectors(std_v, ft_v);
    }

    // ####################################################################
    // SWAP

    {
        std::vector<T> std_v;
        ft::vector<T> ft_v;
        my_generate(&std_v, size, func_fill, (rand() % 100));
        copy_vector(&std_v, &ft_v);

        std::vector<T> std_v2;
        ft::vector<T> ft_v2;
        my_generate(&std_v2, size + 50, func_fill, (rand() % 100));
        copy_vector(&std_v2, &ft_v2);

        std_v2.swap(std_v);
        ft_v2.swap(ft_v);

        check_vectors(std_v, ft_v);
        check_vectors(std_v2, ft_v2);
    }

    // ####################################################################
    // CLEAR

    {
        std::vector<T> std_v;
        ft::vector<T> ft_v;
        my_generate(&std_v, size, func_fill, (rand() % 100));
        copy_vector(&std_v, &ft_v);

        std_v.clear();
        ft_v.clear();

        check_vectors(std_v, ft_v);
    }

    // ####################################################################

    std::cout << std::endl << std::endl;
}

template <class T>
void test_nonMember_function_overloads(std::string title, T (*func_fill)(int *)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;
    size = 0;

    // ####################################################################
    // RELATIONAL_OPERATOR

    {
        std::vector<T> std_v;
        ft::vector<T> ft_v;
        my_generate(&std_v, size, func_fill, (rand() % 100));
        copy_vector(&std_v, &ft_v);
        
        std::vector<T> std_v2;
        ft::vector<T> ft_v2;
        copy_vector(&std_v, &std_v2);
        copy_vector(&std_v, &ft_v2);

 
        if ((std_v == std_v2) != (ft_v == ft_v2)) {
            print_error(" == ", (std_v == std_v2), (ft_v == ft_v2));
        } else {
            print_ok();
        }
        if ((std_v != std_v2) != (ft_v != ft_v2)) {
            print_error(" != ", (std_v != std_v2), (ft_v != ft_v2));
        } else {
            print_ok();
        }
        if ((std_v < std_v2) != (ft_v < ft_v2)) {
            print_error(" < ", (std_v < std_v2), (ft_v < ft_v2));
        } else {
            print_ok();
        }
        if ((std_v > std_v2) != (ft_v > ft_v2)) {
            print_error(" > ", (std_v > std_v2), (ft_v > ft_v2));
        } else {
            print_ok();
        }
        if ((std_v <= std_v2) != (ft_v <= ft_v2)) {
            print_error(" <= ", (std_v <= std_v2), (ft_v <= ft_v2));
        } else {
            print_ok();
        }
        if ((std_v >= std_v2) != (ft_v >= ft_v2)) {
            print_error(" >= ", (std_v >= std_v2), (ft_v >= ft_v2));
        } else {
            print_ok();
        }
    }

    // ####################################################################
    // SWAP
    {
        std::vector<T> std_v;
        ft::vector<T> ft_v;
        my_generate(&std_v, size, func_fill, (rand() % 100));
        copy_vector(&std_v, &ft_v);
        
        std::vector<T> std_v2;
        ft::vector<T> ft_v2;
        my_generate(&std_v2, size, func_fill, (rand() % 100));
        copy_vector(&std_v2, &ft_v2);

        std::swap(std_v, std_v2);
        ft::swap(ft_v, ft_v2);

        check_vectors(std_v, ft_v);
        check_vectors(std_v2, ft_v2);
    }


    std::cout << std::endl << std::endl;
}

void test(void) {
    // ####################################################################

    print_title("___MEMBER FUNCTIONS___", "\033[33m", true);

    test_member_function("INT: ", 3);
    test_member_function("STRING: ", "HELLO");
    test_member_function("DOUBLE: ", 5.3);
    test_member_function("CHAR: ", 'D');

    // ####################################################################

    print_title("___ITERATORS___", "\033[33m", true);

    test_iterators("(Unique) INT: ", UniqueNumber);
    test_iterators("(Unique) STRING: ", UniqueString);
    test_iterators("(Unique) DOUBLE: ", UniqueDouble);
    test_iterators("(Unique) CHAR: ", UniqueChar);

    test_iterators("(Random) INT: ", RandomNumber);
    test_iterators("(Random) String: ", RandomString);
    test_iterators("(Random) DOUBLE: ", RandomDouble);
    test_iterators("(Random) CHAR: ", RandomChar);

    // ####################################################################

    print_title("___CAPACITY___", "\033[33m", true);

    test_capacity("(Unique) INT: ", UniqueNumber);
    test_capacity("(Unique) STRING: ", UniqueString);
    test_capacity("(Unique) DOUBLE: ", UniqueDouble);
    test_capacity("(Unique) CHAR: ", UniqueChar);

    test_capacity("(Random) INT: ", RandomNumber);
    test_capacity("(Random) String: ", RandomString);
    test_capacity("(Random) DOUBLE: ", RandomDouble);
    test_capacity("(Random) CHAR: ", RandomChar);

    // ####################################################################

    print_title("___ELEMENTS ACCESS___", "\033[33m", true);

    test_elements_access("(Unique) INT: ", UniqueNumber);
    test_elements_access("(Unique) STRING: ", UniqueString);
    test_elements_access("(Unique) DOUBLE: ", UniqueDouble);
    test_elements_access("(Unique) CHAR: ", UniqueChar);

    test_elements_access("(Random) INT: ", RandomNumber);
    test_elements_access("(Random) String: ", RandomString);
    test_elements_access("(Random) DOUBLE: ", RandomDouble);
    test_elements_access("(Random) CHAR: ", RandomChar);

    // ####################################################################

    print_title("___MODIFIERS___", "\033[33m", true);

    test_modifiers("(Unique) INT: ", UniqueNumber);
    test_modifiers("(Unique) STRING: ", UniqueString);
    test_modifiers("(Unique) DOUBLE: ", UniqueDouble);
    test_modifiers("(Unique) CHAR: ", UniqueChar);

    test_modifiers("(Random) INT: ", RandomNumber);
    test_modifiers("(Random) String: ", RandomString);
    test_modifiers("(Random) DOUBLE: ", RandomDouble);
    test_modifiers("(Random) CHAR: ", RandomChar);

    // ####################################################################

    print_title("___NON-MEMBER_FUNCTION_OVERLOADS___", "\033[33m", true);

    test_nonMember_function_overloads("(Unique) INT: ", UniqueNumber);
    test_nonMember_function_overloads("(Unique) STRING: ", UniqueString);
    test_nonMember_function_overloads("(Unique) DOUBLE: ", UniqueDouble);
    test_nonMember_function_overloads("(Unique) CHAR: ", UniqueChar);

    test_nonMember_function_overloads("(Random) INT: ", RandomNumber);
    test_nonMember_function_overloads("(Random) String: ", RandomString);
    test_nonMember_function_overloads("(Random) DOUBLE: ", RandomDouble);
    test_nonMember_function_overloads("(Random) CHAR: ", RandomChar);

    // ####################################################################
}

int main(void) {
    std::cout << std::endl;
    print_title(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TESTING VECTOR", "\033[36m", true);
    std::cout << std::endl;

    srand(time(NULL));

    test();

    return (0);
}