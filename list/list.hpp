/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:36:07 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:36:08 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "./iterator.hpp"
#include "./node.hpp"

namespace ft {

    template <class T, class Alloc = std::allocator<T> >
    class list {
        
    public:
        typedef T value_type;
        typedef Node<value_type> *node_pointer;
        typedef Alloc allocator_type;
        typedef typename std::allocator<Node<T> > allocator_node_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        typedef iterator_list<value_type> iterator;
        typedef const_iterator_list<value_type> const_iterator;
        typedef reverse_iterator_list<iterator> reverse_iterator;
        typedef const_reverse_iterator_list<const_iterator> const_reverse_iterator;

        typedef ptrdiff_t defference_type;
        typedef size_t size_type;


    private:
        allocator_node_type     _alloc;
        size_t                  _size;
        node_pointer            _end;

        void add_size(void) {
            this->_size++;
            *reinterpret_cast<int*>(&this->_end->data) += 1;
        }

        void reduce_size(void) {
            this->_size--;
            *reinterpret_cast<int*>(&this->_end->data) -= 1;
        }

        void swap_node(node_pointer one, node_pointer two) {
            node_pointer tmp;

        }

        static bool compare_more(T one, T two) {
            if (one < two) {
                return (true);
            }
            return (false);
        }

        node_pointer create_node(T val) {
            node_pointer node = this->_alloc.allocate(1);

            this->_alloc.construct(node, val);
            node->next = node;
            node->prev = node;
            add_size();
            return (node);
        }

        void delete_node(node_pointer node) {
            this->_alloc.destroy(node);
			this->_alloc.deallocate(node, 1);
            reduce_size();
        }

        node_pointer get_node(iterator position) {
            node_pointer node = this->_end->next;
            iterator it = this->begin();

            while (it++ != position) {
                node = node->next;
            }
            return (node);
        }

        void init_list(const allocator_type& alloc) {
            this->_alloc = alloc;
            this->_size = 0;
            this->_end = this->_alloc.allocate(1);
            this->_alloc.construct(this->_end, T());
            this->_end->next = this->_end;
            this->_end->prev = this->_end;
        }

    public:

        explicit list(const allocator_type& alloc = allocator_type()) {
            this->init_list(alloc);
        }

        explicit list(size_type n, const value_type& val = value_type(),
            const allocator_type& alloc = allocator_type()) {
            this->init_list(alloc);
            this->assign(n, val);
        }

        template <class InputIterator>
        list (InputIterator first, InputIterator last,
            const allocator_type& alloc = allocator_type(), char (*)[sizeof(*first)] = NULL) {
            this->init_list(alloc);
            this->assign(first, last);
        }

        list (const list& x) {
            this->_size = 0;
            *this = x;
        }

        ~list() {
            while (this->_size)
				this->pop_back();
			this->delete_node(this->_end);
        }

        list& operator= (const list& x) {
            this->clear();
            this->init_list(x._alloc);
            this->assign(x.begin(), x.end());
            return (*this);
        }

        iterator begin() {
            iterator it(this->_end->next);
            return (it);
        }

        const_iterator begin() const {
            const_iterator it(this->_end->next);
            return (it);
        }

        iterator end() {
            iterator it(this->_end);
            return (it);
        }

        const_iterator end() const {
            const_iterator it(this->_end);
            return (it);
        }

        reverse_iterator rbegin() {
            reverse_iterator it(this->_end->prev);
            return (it);
        }

        const_reverse_iterator rbegin() const {
            const_reverse_iterator it(this->_end->prev);
            return (it);
        }

        reverse_iterator rend() {
            reverse_iterator it(this->_end);
            return (it);
        }

        const_reverse_iterator rend() const {
            const_reverse_iterator it(this->_end);
            return (it);
        }

        bool empty() const {
            return (this->_size == 0);
        }

        size_type size() const {
            return (this->_size);
        }

        size_type max_size() const {
            return (allocator_node_type().max_size());
        }

        reference front() {
            return (this->_end->next->data);
        }

        const_reference front() const {
            return (this->_end->next->data);
        }

        reference back() {
            return (this->_end->prev->data);
        }

        const_reference back() const {
            return (this->_end->prev->data);
        }

        template <class InputIterator>
        void assign (InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL) {
            clear();
            while (first != last) {
                push_back(*first);
                first++;
            }
        }

        void assign (size_type n, const value_type& val) {
            clear();
            while (n--) {
                push_back(val);
            }
        }

        void push_front (const value_type& val) {
            node_pointer node = create_node(val);

            node->next = this->_end->next;
            this->_end->next->prev = node;
            node->prev = this->_end;
            this->_end->next = node;
        }

        void pop_front () {
            if (this->_size == 0) {
                return ;
            }
            node_pointer tmp = this->_end->next;

            tmp->next->prev = this->_end;
            this->_end->next = tmp->next;
            this->delete_node(tmp);
        }

        void push_back (const value_type& val) {
            node_pointer node = create_node(val);

            node->next = this->_end;
            this->_end->prev->next = node;
            node->prev = this->_end->prev;
            this->_end->prev = node;
        }

        void pop_back() {
            if (this->_size == 0) {
                return ;
            }
            node_pointer tmp = this->_end->prev;

            tmp->prev->next = this->_end;
            this->_end->prev = tmp->prev;
            this->delete_node(tmp);
        }

        iterator insert (iterator position, const value_type& val) {
            node_pointer node = get_node(position);
            node_pointer new_node = create_node(val);

            new_node->prev = node->prev;
            node->prev->next = new_node;

            new_node->next = node;
            node->prev = new_node;
            
            iterator it(new_node);
            return (it);
        }

        void insert (iterator position, size_type n, const value_type& val) {
            while (n--) {
                insert(position, val);
            }
        }

        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL) {
            while (last-- != first) {
                position = insert(position, *last);
            }
        }

        iterator erase (iterator position) {
            node_pointer node = get_node(position);
            iterator it(node->next);

            node->next->prev = node->prev;
            node->prev->next = node->next;
            this->delete_node(node);
            return (it);
        }

        iterator erase (iterator first, iterator last) {
            while (first != last) {
                first = this->erase(first);
            }
            return (first);
        }

        void swap (list& x) {
            Node<T> *tmp_node = x._end;
            allocator_type tmp_alloc = x._alloc;

            x._end = this->_end;
            x._alloc = this->_alloc;
            this->_end = tmp_node;
            this->_alloc = tmp_alloc;
        }

        void resize (size_type n, value_type val = value_type()) {
            while (n > this->_size) {
                push_back(val);
            }
            while (n < this->_size) {
                pop_back();
            }
        }

        void clear() {
            while (this->_size) {
                this->pop_back();
            }
        }

        void splice (iterator position, list& x) {
            splice(position, x, x.begin(), x.end());
        }

        void splice (iterator position, list& x, iterator i) {
            splice(position, x, i, ++i);
        }

        void splice (iterator position, list& x, iterator first, iterator last) {
            node_pointer node_position = position.get_node();
            node_pointer node_first = first.get_node();
            node_pointer node_last = last.get_node();
            node_pointer node_tmp;

            while (node_first != node_last) {
                node_tmp = node_first;
                node_first = node_first->next;

                node_tmp->prev->next = node_tmp->next;
                node_tmp->next->prev = node_tmp->prev;
                x.reduce_size();

                node_tmp->next = node_position;
                node_tmp->prev = node_position->prev;
                node_position->prev->next = node_tmp;
                node_position->prev = node_tmp;
                add_size();
            }
        }

        void remove (const value_type& val) {
            iterator it_start = this->begin();
            iterator it_end = this->end();

            while (it_start != it_end) {
                if (*it_start == val) {
                    it_start = this->erase(it_start);
                } else {
                    it_start++;
                }
            }
        }

        template <class Predicate>
        void remove_if (Predicate pred) {
            iterator it_start = this->begin();
            iterator it_end = this->end();

            while (it_start != it_end) {
                if (pred(*it_start)) {
                    it_start = this->erase(it_start);
                } else {
                    it_start++;
                }
            }
        }

        void unique() {
            if (this->_size <= 1) {
                return ;
            }
            iterator it_start = this->begin();
            iterator it_prev = it_start++;
            iterator it_end = this->end();

            while (it_start != it_end) {
                if (*it_start == *it_prev) {
                    it_start = this->erase(it_start);
                } else {
                    it_prev++;
                    it_start++;
                }
            }
        }

        template <class BinaryPredicate>
        void unique (BinaryPredicate binary_pred) {
            if (this->_size <= 1) {
                return ;
            }
            iterator it_start = this->begin();
            iterator it_prev = it_start++;
            iterator it_end = this->end();

            while (it_start != it_end) {
                if (binary_pred(*it_prev, *it_start)) {
                    it_start = this->erase(it_start);
                } else {
                    it_prev++;
                    it_start++;
                }
            }
        }

        void merge (list& x) {
            this->merge(x, compare_more);
        }

        template <class Compare>
        void merge (list& x, Compare comp) {
            this->splice(this->begin(), x, x.begin(), x.end());
            this->sort(comp);
        }

        void sort() {
            this->sort(compare_more);
        };

        template <class Compare>
        void sort (Compare comp) {
            node_pointer tmp;
            node_pointer begin = this->_end->next;

            for (int i = 0; i < this->_size; i++) {
                begin = this->_end->next;

                while (begin != this->_end) {
                    if (begin->next != this->_end && comp(begin->next->data, begin->data)) {
                        tmp = begin->next;
                        
                        begin->prev->next = tmp;
                        tmp->next->prev = begin;
                        begin->next = tmp->next;
                        tmp->prev = begin->prev;
                        begin->prev = tmp;
                        tmp->next = begin;
                    } else {
                        begin = begin->next;
                    }
                }
            }
        }

        void reverse() {
            node_pointer node_start = this->_end->next;
            node_pointer tmp_start;
            node_pointer tmp_next;

            while (node_start != this->_end) {
                tmp_start = node_start;
                node_start = node_start->next;
                tmp_next = tmp_start->next;
                tmp_start->next = tmp_start->prev;
                tmp_start->prev = tmp_next;
            }
            tmp_next = this->_end->next;
            this->_end->next = this->_end->prev;
            this->_end->prev = tmp_next;
        }
    };

    template <class T, class Alloc>
    bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
        if (lhs.size() != rhs.size()) {
            return (false);
        }
        typename list<T>::const_iterator it_lhs = lhs.begin();
        typename list<T>::const_iterator it_rhs = rhs.begin();
        typename list<T>::const_iterator end_rhs = rhs.end();
        while (it_rhs != end_rhs) {
            if (*it_rhs != *it_lhs) {
                return (false);
            }
            it_rhs++;
            it_lhs++;
        }
        return (true);
    }

    template <class T, class Alloc>
    bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
        return (!(lhs == rhs));
    }

    template <class T, class Alloc>
    bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
        typename list<T>::const_iterator left_begin = lhs.begin();
        typename list<T>::const_iterator left_end = lhs.end();
        typename list<T>::const_iterator right_begin = rhs.begin();
        typename list<T>::const_iterator right_end = rhs.end();

        while (1) {
            if (*left_begin == *left_end && *right_begin != *right_end) {
                return (true);
            } else if (*left_begin != *left_end && *right_begin == *right_end) {
                return (false);
            } else if (*left_begin == *left_end && *right_begin == *right_end) {
                return (false);
            } else if (*left_begin < *right_begin) {
                return (true);
            }
            left_begin++;
            right_begin++;
        }
        return (true);
    }

    template <class T, class Alloc>
    bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
        return ((lhs < rhs) || (lhs == rhs));
    }

    template <class T, class Alloc>
    bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
        return (!(lhs < rhs) && (lhs != rhs));
    }

    template <class T, class Alloc>
    bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
        return ((lhs > rhs) || (lhs == rhs));
    }

    template <class T, class Alloc>
    void swap (list<T,Alloc>& x, list<T,Alloc>& y) {
        x.swap(y);
    }
}

#endif