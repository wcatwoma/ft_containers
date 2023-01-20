/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:40:02 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:40:03 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <deque>

namespace ft {

    template <class T, class Container = std::deque<T> >
    class stack {
        public:
            typedef T           value_type;
            typedef Container   container_type;
            typedef size_t      size_type;
            container_type _container;

        private:
            

        public:

            explicit stack (const container_type& container = container_type()): _container(container) {}

            ~stack() {}

            bool empty() const {
                return (this->_container.empty());
            }

            size_type size() const {
                return (this->_container.size());
            }

            value_type &top() {
                return (this->_container.back());
            }

            void push (const value_type &val) {
                this->_container.push_back(val);
            }

            void pop() {
                this->_container.pop_back();
            }

            friend bool operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return (lhs._container == rhs._container);
            }

            friend bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return (lhs._container != rhs._container);
            }

            friend bool operator< (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return (lhs._container < rhs._container);
            }

            friend bool operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return (lhs._container <= rhs._container);
            }

            friend bool operator> (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return (lhs._container > rhs._container);
            }

            friend bool operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
                return (lhs._container >= rhs._container);
            }
    };
}

#endif