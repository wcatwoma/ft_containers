/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:39:12 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:39:13 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../other/message.hpp"
#include "./../other/generators.hpp"
#include "./list.hpp"
#include <list>
#include <map>
#include <unistd.h>

template <class T, class T2>
void my_generate(T *v, int size, T2 (*func_fill)(int*), int current) {
    for (int i = 0; i < size; i++) {
        func_fill(&current);
        v->push_back(func_fill(&current));
    }
}

template <class T, class T2>
void copy_list(T *src, T2 *dst) {
    typename T::iterator it_begin = src->begin();
    typename T::iterator it_end = src->end();

    while (it_begin != it_end) {
        dst->push_back(*it_begin);
        it_begin++;
    }
}

template <class T>
void print_list(std::string title, T l) {
    std::cout << std::endl;
    std::cout << title << ": ";

    typename T::iterator it_begin = l.begin();
    typename T::iterator it_end = l.end();
    while (it_begin != it_end) {
        std::cout << *it_begin << " ";
        it_begin++;
    }
    std::cout << std::endl;
}

struct predicat_int {
    static bool one_argument (int value) {
        return ((value % 2) == 0);
    }

    static bool two_arguments (int one, int two) {
        return (one >= two);
    }
};

struct predicat_string {
    static bool one_argument (std::string value) {
        return (*reinterpret_cast<int*>(&value) % 2 == 0);
    }

    static bool two_arguments (std::string one, std::string two) {
        return (one >= two);
    }
};

struct predicat_double {
    static bool one_argument (double value) {
        return ((value > 0));
    }

    static bool two_arguments (double one, double two) {
        return (one >= two);
    }
};

struct predicat_char {
    static bool one_argument (char value) {
        return ((value % 2) == 0);
    }

    static bool two_arguments (char one, char two) {
        return (one >= two);
    }
};


template <class T1, class T2>
void check_iterators(T1 std_it, T2 ft_it) {
    if (*std_it != *ft_it) {
        print_error("*ITERATOR", *std_it, *ft_it);
    } else {
        print_ok();
    }
}

template <class T>
void check_lists(std::list<T> std_v, ft::list<T> ft_v) {

     if (std_v.size() != ft_v.size()) {
         print_error("SIZE", std_v.size(), ft_v.size());
         return ;
     } else if (std_v.max_size() != ft_v.max_size()) {
         print_error("MAX_SIZE", std_v.max_size(), ft_v.max_size());
     } else if (std_v.empty() != ft_v.empty()) {
         print_error("EMPTY", std_v.empty(), ft_v.empty());
     }

    
     typename std::list<T>::iterator it_std_b = std_v.begin();
     typename std::list<T>::iterator it_std_e = std_v.end();
     typename ft::list<T>::iterator it_ft_b = ft_v.begin();

     int index = 0;
     while (it_std_b != it_std_e) {
         if (*it_std_b != *it_ft_b) {
             print_error("DIFFERENT ELEMENTS INDEX: " + std::to_string(index), *it_std_b, *it_ft_b);
             return ;
         }
         it_std_b++;
         it_ft_b++;
         index++;
     }
     print_ok();
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

    if (*std_it++ != *ft_it++) {
        print_error("1 *it++", *(std_it), *(ft_it));
    } else {
        print_ok();
    }

    if (*std_it != *ft_it) {
        print_error("*it++", *(std_it), *(ft_it));
    } else {
        print_ok();
    }

    if (*std_it-- != *ft_it--) {
        print_error("1 *it++", *(std_it), *(ft_it));
    } else {
        print_ok();
    }

    if (*std_it != *ft_it) {
        print_error("*it++", *(std_it), *(ft_it));
    } else {
        print_ok();
    }

}

template <class T>
void test_member_function(std::string title, T content) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;

    

    std::list<T>    std_a;
    ft::list<T>     ft_a;

    check_lists(std_a, ft_a);

    

     std::list<T>    std_b(size, content);
     ft::list<T>     ft_b(size, content);

     check_lists(std_b, ft_b);

    

     std::list<T> std_c(std_b.begin(), std_b.end());
     ft::list<T> ft_c(ft_b.begin(), ft_b.end());

     check_lists(std_c, ft_c);

    

     std::list<T> std_d(std_c);
     ft::list<T> ft_d(ft_c);

     check_lists(std_d, ft_d);

    

     std::list<T> std_f = std_d;
     ft::list<T> ft_f = ft_d;

     check_lists(std_f, ft_f);

    std::cout << std::endl << std::endl;
}

template <class T>
void test_iterators(std::string title, T (*func_fill)(int*)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;

    std::list<T> std_l;
    ft::list<T> ft_l;
    my_generate(&std_l, size, func_fill, (rand() % 100));
    copy_list(&std_l, &ft_l);

    {
        typename std::list<T>::iterator std_it = std_l.begin();
        typename ft::list<T>::iterator ft_it = ft_l.begin();

        check_iterators(std_it, ft_it);

        std_it++;
        ft_it++;
        ++std_it;
        ++ft_it;

        check_iterators(std_it, ft_it);
    }

    {
        typename std::list<T>::iterator std_it = std_l.end();
        typename ft::list<T>::iterator ft_it = ft_l.end();

        std_it--;
        ft_it--;
        --std_it;
        --ft_it;

        check_iterators(std_it, ft_it);
    }


    {
        typename std::list<T>::reverse_iterator std_it(std_l.rbegin());
        typename ft::list<T>::reverse_iterator ft_it(ft_l.rbegin());
        typename std::list<T>::iterator std_it2 = std_it.base();
        typename ft::list<T>::iterator ft_it2 = ft_it.base();

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


    {
        typename std::list<T>::reverse_iterator std_it = std_l.rend();
        typename ft::list<T>::reverse_iterator ft_it = ft_l.rend();
        typename std::list<T>::iterator std_it2 = std_it.base();
        typename ft::list<T>::iterator ft_it2 = ft_it.base();

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

    

    {
        typename std::list<T>::iterator std_it = std_l.begin();
        typename ft::list<T>::iterator ft_it = ft_l.begin();

        check_iterators(std_it, ft_it);

        typename std::list<T>::iterator std_it2(std_it);
        typename ft::list<T>::iterator ft_it2(ft_it);

        check_iterators(std_it2, ft_it2);

        typename std::list<T>::iterator std_it3 = std_it;
        typename ft::list<T>::iterator ft_it3 = ft_it;

        check_iterators(std_it2, ft_it2);

    }

     

    {
        typename std::list<T>::iterator std_it = std_l.begin();
        typename ft::list<T>::iterator ft_it = ft_l.begin();
        typename std::list<T>::iterator std_it2 = std_l.begin();
        typename ft::list<T>::iterator ft_it2 = ft_l.begin();

        check_operators_iterator(std_it, std_it2, ft_it, ft_it2);

        std_it2++;
        ft_it2++;
        std_it2++;
        ft_it2++;
        std_it2--;
        ft_it2--;

        check_operators_iterator(std_it, std_it2, ft_it, ft_it2);
    }

    
    {
        typename std::list<T>::reverse_iterator std_it(std_l.rbegin());
        typename ft::list<T>::reverse_iterator ft_it(ft_l.rbegin());
        typename std::list<T>::reverse_iterator std_it2(std_l.rbegin());
        typename ft::list<T>::reverse_iterator ft_it2(ft_l.rbegin());

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

template <class T>
void test_elements_access(std::string title, T (*func_fill)(int *)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;

    std::list<T> std_l;
    ft::list<T> ft_l;
    my_generate(&std_l, size, func_fill, (rand() % 100));
    copy_list(&std_l, &ft_l);
    

    {
        if (std_l.front() != ft_l.front()) {
            print_error("FRONT()", std_l.front(), ft_l.front());
        } else {
            print_ok();
        }
    }

    

    {
        if (std_l.back() != ft_l.back()) {
            print_error("BACK()", std_l.back(), ft_l.back());
        } else {
            print_ok();
        }
    }

    

        std::cout << std::endl << std::endl;
    }




template <class T>
void test_modifiers(std::string title, T (*func_fill)(int*)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;
    T element = func_fill(&size);

    

    {

        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);

        std::list<T> std_l2;
        ft::list<T> ft_l2;
        copy_list(&std_l, &std_l2);
        copy_list(&std_l, &ft_l2);

        std_l.assign(size + 1, element);
        std_l2.assign(size - 1, element);
        ft_l.assign(size + 1, element);
        ft_l2.assign(size - 1, element);

        check_lists(std_l, ft_l);
        check_lists(std_l2, ft_l2);

        std::list<T> random_l;
        my_generate(&random_l, (rand() % 100), func_fill, (rand() % 100));

        ft_l.assign(random_l.begin(), random_l.end());
        ft_l2.assign(random_l.begin(), random_l.end());
        std_l.assign(random_l.begin(), random_l.end());
        std_l2.assign(random_l.begin(), random_l.end());


        check_lists(std_l, ft_l);
        check_lists(std_l2, ft_l2);
    }

    

    {
        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);

        std_l.push_front(element);
        ft_l.push_front(element);

        check_lists(std_l, ft_l);
    }

    

    {
        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, 0);
        copy_list(&std_l, &ft_l);

        std_l.pop_front();
        ft_l.pop_front();

        check_lists(std_l, ft_l);
    }

    

    {
        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);

        std_l.push_back(element);
        ft_l.push_back(element);

        check_lists(std_l, ft_l);
    }

    

    {
        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);

        std_l.pop_back();
        ft_l.pop_back();

        check_lists(std_l, ft_l);
    }

    

    {
        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);
        typename std::list<T>::iterator std_it = ++(std_l.begin());
        typename ft::list<T>::iterator ft_it = ++(ft_l.begin());

        typename std::list<T>::iterator std_it2 = std_l.insert(std_it, element);
        typename ft::list<T>::iterator ft_it2 = ft_l.insert(ft_it, element);

        check_iterators(std_it2, ft_it2);
        check_lists(std_l, ft_l);

        std_it = ++(std_l.begin());
        ft_it = ++(ft_l.begin());
        std_l.insert(std_it, 10, element);
        ft_l.insert(ft_it, 10, element);

        check_lists(std_l, ft_l);

        std::list<T> random_l;
        my_generate(&random_l, (rand() % 100), func_fill, (rand() % 100));

        std_it = ++(std_l.begin());
        ft_it = ++(ft_l.begin());
        std_l.insert(std_it, random_l.begin(), random_l.end());
        ft_l.insert(ft_it, random_l.begin(), random_l.end());

        check_lists(std_l, ft_l);
    }

    

    {
        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, rand() % 100);
        copy_list(&std_l, &ft_l);

        typename std::list<T>::iterator std_it = std_l.begin();
        typename ft::list<T>::iterator ft_it = ft_l.begin();

        std_it = std_l.erase(std_it);
        ft_it = ft_l.erase(ft_it);

        check_iterators(std_it, ft_it);
        check_lists(std_l, ft_l);

        std_it = std_l.erase(++(std_l.begin()), --(std_l.end()));
        ft_it = ft_l.erase(++(ft_l.begin()), --(ft_l.end()));

        check_iterators(std_it, ft_it);
        check_lists(std_l, ft_l);
    }

    

    {
        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);

        std::list<T> std_l2;
        ft::list<T> ft_l2;
        my_generate(&std_l2, size, func_fill, (rand() % 100));
        copy_list(&std_l2, &ft_l2);

        std_l2.swap(std_l);
        ft_l2.swap(ft_l);

        check_lists(std_l, ft_l);
        check_lists(std_l2, ft_l2);
    }

    

    {
        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);

        std::list<T> std_l2 = std_l;
        ft::list<T> ft_l2 = ft_l;

        std_l.resize(size + 1);
        std_l2.resize(size - 1);

        ft_l.resize(size + 1);
        ft_l2.resize(size - 1);

        check_lists(std_l, ft_l);
        check_lists(std_l2, ft_l2);
    }

    

    {
        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);

        std_l.clear();
        ft_l.clear();

        check_lists(std_l, ft_l);
    }

    

    std::cout << std::endl << std::endl;
}

template <class T, class T2>
void test_operations(std::string title, T (*func_fill)(int *), T2 predicat) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;
    T content = func_fill(&size);

    

    {
        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);

        std::list<T> std_l2;
        ft::list<T> ft_l2;
        my_generate(&std_l2, size + 10, func_fill, (rand() % 100));
        copy_list(&std_l2, &ft_l2);

        std_l.splice(++(std_l.begin()), std_l2);
        ft_l.splice(++(ft_l.begin()), ft_l2);

        check_lists(std_l, ft_l);
        check_lists(std_l2, ft_l2);

        my_generate(&std_l2, size + 10, func_fill, (rand() % 100));
        copy_list(&std_l2, &ft_l2);

        std_l.splice(++(std_l.begin()), std_l2, --(std_l2.end()));
        ft_l.splice(++(ft_l.begin()), ft_l2, --(ft_l2.end()));

        check_lists(std_l, ft_l);
        check_lists(std_l2, ft_l2);

        std_l2.clear();
        ft_l2.clear();
        my_generate(&std_l2, size + 10, func_fill, (rand() % 100));
        copy_list(&std_l2, &ft_l2);

        std_l.splice(++(std_l.begin()), std_l2, ++(std_l2.begin()), --(std_l2.end()));
        ft_l.splice(++(ft_l.begin()), ft_l2, ++(ft_l2.begin()), --(ft_l2.end()));

        check_lists(std_l, ft_l);
        check_lists(std_l2, ft_l2);

    }

    

    {
        std::list<T> std_l(5, content);
        ft::list<T> ft_l(5, content);
        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);

        std_l.remove(content);
        ft_l.remove(content);

        check_lists(std_l, ft_l);
    }

    

    {
        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);

        std_l.remove_if(predicat.one_argument);
        ft_l.remove_if(predicat.one_argument);

        check_lists(std_l, ft_l);
    }

    

    {
        std::list<T> std_l(5, content);
        ft::list<T> ft_l;

        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);

        std_l.unique();
        ft_l.unique();

        check_lists(std_l, ft_l);

        std::list<T> std_l2(5, content);
        ft::list<T> ft_l2;
        my_generate(&std_l2, size, func_fill, (rand() % 100));
        copy_list(&std_l2, &ft_l2);

        std_l2.unique(predicat.two_arguments);
        ft_l2.unique(predicat.two_arguments);

        check_lists(std_l2, ft_l2);
    }

    

    {
        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);

        std::list<T> std_l2;
        ft::list<T> ft_l2;
        my_generate(&std_l2, size + 10, func_fill, (rand() % 100));
        copy_list(&std_l2, &ft_l2);

        std_l.sort();   
        std_l2.sort();
        ft_l.sort();
        ft_l2.sort();
        
        std_l.merge(std_l2);
        ft_l.merge(ft_l2);

        check_lists(std_l, ft_l);
        check_lists(std_l2, ft_l2);
    }

    

    {
        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);

        std::list<T> std_l2;
        ft::list<T> ft_l2;
        my_generate(&std_l2, size + 10, func_fill, (rand() % 100));
        copy_list(&std_l2, &ft_l2);

        ft_l.sort();
        std_l.sort();
        ft_l2.sort(predicat.two_arguments);
        std_l2.sort(predicat.two_arguments);

        check_lists(std_l, ft_l);
        check_lists(std_l2, ft_l2);
    }

    

    {
        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);

        std_l.reverse();
        ft_l.reverse();

        check_lists(std_l, ft_l);
    }

    std::cout << std::endl << std::endl;
}

template <class T>
void test_nonMember_function_overloads(std::string title, T (*func_fill)(int *)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100) + 5;

    

    {
        std::list<T> std_l;
        ft::list<T> ft_l;
        my_generate(&std_l, size, func_fill, (rand() % 100));
        copy_list(&std_l, &ft_l);
    
        std::list<T> std_l2;
        ft::list<T> ft_l2;
        copy_list(&std_l, &std_l2);
        copy_list(&std_l, &ft_l2);


        if ((std_l == std_l2) != (ft_l == ft_l2)) {
            print_error(" == ", (std_l == std_l2), (ft_l == ft_l2));
        } else {
            print_ok();
        }
        if ((std_l != std_l2) != (ft_l != ft_l2)) {
            print_error(" != ", (std_l != std_l2), (ft_l != ft_l2));
        } else {
            print_ok();
        }
        if ((std_l < std_l2) != (ft_l < ft_l2)) {
            print_error(" < ", (std_l < std_l2), (ft_l < ft_l2));
        } else {
            print_ok();
        }
        if ((std_l > std_l2) != (ft_l > ft_l2)) {
            print_error(" > ", (std_l > std_l2), (ft_l > ft_l2));
        } else {
            print_ok();
        }
        if ((std_l <= std_l2) != (ft_l <= ft_l2)) {
            print_error(" <= ", (std_l <= std_l2), (ft_l <= ft_l2));
        } else {
            print_ok();
        }
        if ((std_l >= std_l2) != (ft_l >= ft_l2)) {
            print_error(" >= ", (std_l >= std_l2), (ft_l >= ft_l2));
        } else {
            print_ok();
        }
    }

    
    {
    std::list<T> std_l;
    ft::list<T> ft_l;
    my_generate(&std_l, size, func_fill, (rand() % 100));
    copy_list(&std_l, &ft_l);

    std::list<T> std_l2;
    ft::list<T> ft_l2;
    my_generate(&std_l2, size, func_fill, (rand() % 100));
    copy_list(&std_l2, &ft_l2);

    std::swap(std_l, std_l2);
    ft::swap(ft_l, ft_l2);

    check_lists(std_l, ft_l);
    check_lists(std_l2, ft_l2);
    }

    std::cout << std::endl << std::endl;
}

void test(void) {
    

    print_title("___MEMBER FUNCTIONS_AND_CAPACITY___", "\033[33m", true);

    test_member_function("INT: ", 3);
    test_member_function("STRING: ", "HELLO");
    test_member_function("DOUBLE: ", 3.3);
    test_member_function("CHAR: ", 'C');

    

    print_title("___ITERATORS___", "\033[33m", true);

    test_iterators("(Unique) INT: ", UniqueNumber);
    test_iterators("(Unique) STRING: ", UniqueString);
    test_iterators("(Unique) DOUBLE: ", UniqueDouble);
    test_iterators("(Unique) CHAR: ", UniqueChar);

    test_iterators("(Random) INT: ", RandomNumber);
    test_iterators("(Random) String: ", RandomString);
    test_iterators("(Random) DOUBLE: ", RandomDouble);
    test_iterators("(Random) CHAR: ", RandomChar);

    

    print_title("___ELEMENTS ACCESS___", "\033[33m", true);

    test_elements_access("(Unique) INT: ", UniqueNumber);
    test_elements_access("(Unique) STRING: ", UniqueString);
    test_elements_access("(Unique) DOUBLE: ", UniqueDouble);
    test_elements_access("(Unique) CHAR: ", UniqueChar);

    test_elements_access("(Random) INT: ", RandomNumber);
    test_elements_access("(Random) String: ", RandomString);
    test_elements_access("(Random) DOUBLE: ", RandomDouble);
    test_elements_access("(Random) CHAR: ", RandomChar);

    

    print_title("___MODIFIERS___", "\033[33m", true);

    test_modifiers("(Unique) INT: ", UniqueNumber);
    test_modifiers("(Unique) STRING: ", UniqueString);
    test_modifiers("(Unique) DOUBLE: ", UniqueDouble);
    test_modifiers("(Unique) CHAR: ", UniqueChar);

    test_modifiers("(Random) INT: ", RandomNumber);
    test_modifiers("(Random) String: ", RandomString);
    test_modifiers("(Random) DOUBLE: ", RandomDouble);
    test_modifiers("(Random) CHAR: ", RandomChar);

    

    print_title("___OPERATIONS___", "\033[33m", true);

    struct predicat_int     pred_int;
    struct predicat_string  pred_str;
    struct predicat_double  pred_double;
    struct predicat_char    pred_char;

    test_operations("(Unique) INT: ", UniqueNumber, pred_int);
    test_operations("(Unique) STRING: ", UniqueString, pred_str);
    test_operations("(Unique) DOUBLE: ", UniqueDouble, pred_double);
    test_operations("(Unique) CHAR: ", UniqueChar, pred_char);

    test_operations("(Random) INT: ", RandomNumber, pred_int);
    test_operations("(Random) String: ", RandomString, pred_str);
    test_operations("(Random) DOUBLE: ", RandomDouble, pred_double);
    test_operations("(Random) CHAR: ", RandomChar, pred_char);

    

    print_title("___NON-MEMBER_FUNCTION_OVERLOADS___", "\033[33m", true);

    test_nonMember_function_overloads("(Unique) INT: ", UniqueNumber);
    test_nonMember_function_overloads("(Unique) STRING: ", UniqueString);
    test_nonMember_function_overloads("(Unique) DOUBLE: ", UniqueDouble);
    test_nonMember_function_overloads("(Unique) CHAR: ", UniqueChar);

    test_nonMember_function_overloads("(Random) INT: ", RandomNumber);
    test_nonMember_function_overloads("(Random) String: ", RandomString);
    test_nonMember_function_overloads("(Random) DOUBLE: ", RandomDouble);
    test_nonMember_function_overloads("(Random) CHAR: ", RandomChar);

    
}

int main(void) {
    std::cout << std::endl;
    print_title(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TESTING LIST", "\033[36m", true);
    std::cout << std::endl;

    srand(time(NULL));
        
    test();

    return (0);
}
