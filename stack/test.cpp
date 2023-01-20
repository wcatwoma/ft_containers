/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:40:05 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:40:08 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./stack.hpp"
#include "./../list/list.hpp"
#include "./../vector/vector.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <unistd.h>
#include "./../other/message.hpp"
#include "./../other/generators.hpp"

template <class T>
void print_stack(std::string title, T v) {
    std::cout << std::endl;
    std::cout << title << ": ";
    int size = v.size();
    for (int i = 0; i < size; i++) {
        std::cout << v.top() << " ";
        v.pop();
    }
    std::cout << std::endl;
}

template <class T1, class T2>
void check_stack(T1 std_s, T2 ft_s) {

    if (std_s.size() != ft_s.size()) {
        print_error("SIZE", std_s.size(), ft_s.size());
        return ;
    } else if (std_s.empty() != ft_s.empty()) {
        print_error("EMPTY", std_s.empty(), ft_s.empty());
    }
    for (int i = 0; i < std_s.size(); i++) {
        if (std_s.top() != ft_s.top()) {
            print_error("DIFFERENT ELEMENTS INDEX: " + std::to_string(std_s.size() - 1 - i), std_s.top(), ft_s.top());
            return ;
        }
        std_s.pop();
        ft_s.pop();
    }
    print_ok();
}

template <class T>
void test_member_function(std::string title, T (*get_value)(int*)) {
    print_title(title, "\033[34m", false);

    int size = rand() % 100;

    // ####################################################################
    // CONSTRUCTOR EMPTY SIZE TOP PUSH POP

    std::stack<T, std::vector<T> > std_v_s;
    ft::stack<T, std::vector<T> > ft_v_s;
    std::stack<T, std::list<T> > std_l_s;
    ft::stack<T, ft::list<T> > ft_l_s;

    for (int i = 1; i < size; i++) {
        T new_val = get_value(&i);

        std_v_s.push(new_val);
        ft_v_s.push(new_val);
        std_l_s.push(new_val);
        ft_l_s.push(new_val);
    }

    check_stack(std_v_s, ft_v_s);
    check_stack(std_l_s, ft_l_s);

    // ####################################################################

    std::cout << std::endl << std::endl;
}

template <class T>
void test_nonMember_function_overloads(std::string title, T (*get_value)(int*)) {
    print_title(title, "\033[34m", false);

    int size = (rand() % 100);

    // ####################################################################
    // RELATIONAL_OPERATOR

    std::stack<T, std::vector<T> > std_v_s1;
    ft::stack<T, ft::vector<T> > ft_v_s1;
    std::stack<T, std::vector<T> > std_v_s2;
    ft::stack<T, ft::vector<T> > ft_v_s2;

    std::stack<T, std::list<T> > std_l_s1;
    ft::stack<T, ft::list<T> > ft_l_s1;
    std::stack<T, std::list<T> > std_l_s2;
    ft::stack<T, ft::list<T> > ft_l_s2;

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

    // // ####################################################################

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
    print_title(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TESTING STACK", "\033[36m", true);
    std::cout << std::endl;

    srand(time(NULL));

    test();
    
    return (0);
}

