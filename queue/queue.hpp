/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:39:52 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:39:53 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <deque>

namespace ft {
    template <class T, class Container = std::deque<T> >
    class queue {
        public:
            typedef T           value_type;
            typedef Container   container_type;
            typedef size_t      size_type;

        private:
            container_type      _container;

        public:
            explicit queue (const container_type& container = container_type()): _container(container) {}

            ~queue() {}

            bool empty() const {
                return (this->_container.empty());
            }

            size_type size() const {
                return (this->_container.size());
            }

            value_type& front() {
                return (this->_container.front());
            }

            const value_type& front() const {
                return (this->_contaier.front());
            }

            value_type& back() {
                return (this->_container.back());
            }

            const value_type& back() const {
                return (this->_container.back());
            }

            void push(const value_type& val) {
                this->_container.push_back(val);
            }

            void pop() {
                this->_container.pop_front();
            }

            friend bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
                return (lhs._container == rhs._container);
            }

            friend bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
                return (lhs._container != rhs._container);
            }

            friend bool operator< (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
                return (lhs._container < rhs._container);
            }

            friend bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
                return (lhs._container <= rhs._container);
            }

            friend bool operator> (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
                return (lhs._container > rhs._container);
            }

            friend bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
                return (lhs._container >= rhs._container);
            }
    };
}

#endif