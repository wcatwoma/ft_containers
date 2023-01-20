/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:39:58 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:39:59 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../other/message.hpp"
#include "./../other/generators.hpp"
#include "./queue.hpp"
#include "./../stack/stack.hpp"
#include "./../list/list.hpp"
#include "./../vector/vector.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <unistd.h>

template <class T>
void print_queue(std::string title, T v) {
    std::cout << std::endl;
    std::cout << title << ": ";
    for (int i = 0; i < v.size(); i++) {
        std::cout << v.front() << " ";
        v.pop();
    }
    std::cout << std::endl;
}

template <class T1, class T2>
void check_queue(T1 std_q, T2 ft_q) {

    if (std_q.size() != ft_q.size()) {
        print_error("SIZE", std_q.size(), ft_q.size());
        return ;
    } else if (std_q.empty() != ft_q.empty()) {
        print_error("EMPTY", std_q.empty(), ft_q.empty());
    }
    for (int i = 0; i < std_q.size(); i++) {
        if (std_q.front() != ft_q.front()) {
            print_error("DIFFERENT ELEMENTS FRONT: ", std_q.front(), ft_q.front());
            return ;
        } else if (std_q.back() != ft_q.back()) {
            print_error("DIFFERENT ELEMENTS BACK: ", std_q.back(), ft_q.back());
            return ;
        }
        std_q.pop();
        ft_q.pop();
    }
    print_ok();
}

template <class T>
void test_member_function(std::string title, T (*get_value)(int*)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100);

    // ####################################################################
    // CONSTRUCTOR EMPTY SIZE TOP PUSH POP

    std::queue<T, std::list<T> > std_l_s;
    ft::queue<T, ft::list<T> > ft_l_s;

    int i = 0;
    int k = 100;

    T new_val;

    while (i++ < size) {
        new_val = get_value(&k);

        std_l_s.push(new_val);
        ft_l_s.push(new_val);
    }

    check_queue(std_l_s, ft_l_s);

    // ####################################################################

    std::cout << std::endl << std::endl;
}

template <class T>
void test_nonMember_function_overloads(std::string title, T (*get_value)(int*)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100);

    std::queue<T, std::vector<T> > std_v_s1;
    ft::queue<T, ft::vector<T> > ft_v_s1;
    std::queue<T, std::vector<T> > std_v_s2;
    ft::queue<T, ft::vector<T> > ft_v_s2;

    std::queue<T, std::list<T> > std_l_s1;
    ft::queue<T, ft::list<T> > ft_l_s1;
    std::queue<T, std::list<T> > std_l_s2;
    ft::queue<T, ft::list<T> > ft_l_s2;

    int i = 0;
    int k = 100;

    T new_val;

    while (i++ < size) {
        new_val = get_value(&k);

        std_v_s1.push(new_val);
        std_v_s2.push(new_val);
        ft_v_s1.push(new_val);
        ft_v_s2.push(new_val);

        std_l_s1.push(new_val);
        std_l_s2.push(new_val);
        ft_l_s1.push(new_val);
        ft_l_s2.push(new_val);
    }
    
    // VECTOR
    if ((std_v_s1 == std_v_s2) != (ft_v_s1 == ft_v_s2)) {
        print_error(" == ", (std_v_s1 == std_v_s2), (ft_v_s1 == ft_v_s2));
    } else {
        print_ok();
    }
    if ((std_v_s1 != std_v_s2) != (ft_v_s1 != ft_v_s2)) {
        print_error(" != ", (std_v_s1 != std_v_s2), (ft_v_s1 != ft_v_s2));
    } else {
        print_ok();
    }
    if ((std_v_s1 < std_v_s2) != (ft_v_s1 < ft_v_s2)) {
        print_error(" < ", (std_v_s1 < std_v_s2), (ft_v_s1 < ft_v_s2));
    } else {
        print_ok();
    }
    if ((std_v_s1 > std_v_s2) != (ft_v_s1 > ft_v_s2)) {
        print_error(" > ", (std_v_s1 > std_v_s2), (ft_v_s1 > ft_v_s2));
    } else {
        print_ok();
    }
    if ((std_v_s1 <= std_v_s2) != (ft_v_s1 <= ft_v_s2)) {
        print_error(" <= ", (std_v_s1 <= std_v_s2), (ft_v_s1 <= ft_v_s2));
    } else {
        print_ok();
    }
    if ((std_v_s1 >= std_v_s2) != (ft_v_s1 >= ft_v_s2)) {
        print_error(" >= ", (std_v_s1 >= std_v_s2), (ft_v_s1 >= ft_v_s2));
    } else {
        print_ok();
    }

    // LIST
    if ((std_l_s1 == std_l_s2) != (ft_l_s1 == ft_l_s2)) {
        print_error(" == ", (std_l_s1 == std_l_s2), (ft_l_s1 == ft_l_s2));
    } else {
        print_ok();
    }
    if ((std_l_s1 != std_l_s2) != (ft_l_s1 != ft_l_s2)) {
        print_error(" != ", (std_l_s1 != std_l_s2), (ft_l_s1 != ft_l_s2));
    } else {
        print_ok();
    }
    if ((std_l_s1 < std_l_s2) != (ft_l_s1 < ft_l_s2)) {
        print_error(" < ", (std_l_s1 < std_l_s2), (ft_l_s1 < ft_l_s2));
    } else {
        print_ok();
    }
    if ((std_l_s1 > std_l_s2) != (ft_l_s1 > ft_l_s2)) {
        print_error(" > ", (std_l_s1 > std_l_s2), (ft_l_s1 > ft_l_s2));
    } else {
        print_ok();
    }
    if ((std_l_s1 <= std_l_s2) != (ft_l_s1 <= ft_l_s2)) {
        print_error(" <= ", (std_l_s1 <= std_l_s2), (ft_l_s1 <= ft_l_s2));
    } else {
        print_ok();
    }
    if ((std_l_s1 >= std_l_s2) != (ft_l_s1 >= ft_l_s2)) {
        print_error(" >= ", (std_l_s1 >= std_l_s2), (ft_l_s1 >= ft_l_s2));
    } else {
        print_ok();
    }

    // ####################################################################

    std::cout << std::endl << std::endl;
}

void test(void) {
    // ####################################################################

    print_title("___MEMBER FUNCTIONS___", "\033[33m", true);

    test_member_function("(Unique) INT: ", UniqueNumber);
    test_member_function("(Unique) STRING: ", UniqueString);
    test_member_function("(Unique) DOUBLE: ", UniqueDouble);
    test_member_function("(Unique) CHAR: ", UniqueChar);

    test_member_function("(Random) INT: ", RandomNumber);
    test_member_function("(Random) String: ", RandomString);
    test_member_function("(Random) DOUBLE: ", RandomDouble);
    test_member_function("(Random) CHAR: ", RandomChar);

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
    print_title(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TESTING QUEUE", "\033[36m", true);
    std::cout << std::endl;

    srand(time(NULL));

    test();

    return (0);
}

