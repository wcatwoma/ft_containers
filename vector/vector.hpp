/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:40:25 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:40:26 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "./iterator.hpp"

namespace ft {
    template <class T, class Alloc = std::allocator<T> >
    class vector {

    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;

        typedef iterator_vector<value_type> iterator;
        typedef const_iterator_vector<value_type const> const_iterator;
        typedef reverse_iterator_vector<iterator> reverse_iterator;
        typedef const_reverse_iterator_vector<const_iterator> const_reverse_iterator;

        typedef ptrdiff_t defference_type;
        typedef size_t size_type;

    private:
        size_t          _size;
        size_t          _capacity;
        pointer         _pointer;
        allocator_type  _alloc;

    public:

        explicit vector (const allocator_type& alloc = allocator_type()) {
            this->_size = 0;
            this->_capacity = 0;
            this->_pointer = NULL;
            this->_alloc = alloc;
        }

        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
            this->_size = n;
            this->_capacity = n;
            this->_alloc = alloc;
            this->_pointer = this->_alloc.allocate(this->_capacity);
            for (int i = 0; i < this->_size; i++) {
                   _alloc.construct(this->_pointer + i, val);
            }
        }

        template <class InputIterator> 
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), char (*)[sizeof(*first)] = NULL) {
            this->_size = last - first;
            this->_capacity = this->_size;
            this->_alloc = alloc;
            this->_pointer = this->_alloc.allocate(this->_capacity);
            assign(first, last);
            for (int i = 0; i < this->_size; i++) {
                this->_alloc.construct(this->_pointer + i, *first);
                first++;
            }
        }

        vector (const vector& x) {
            *this = x;
        }
        
        ~vector () {
            clear();
            if (this->_capacity) {
                this->_alloc.deallocate(this->_pointer, this->_capacity);
            }
        }

        vector& operator=(vector const &x) {
            this->_capacity = 0;
            this->_size = 0;
            for (size_type i = 0; i < x._size; i++) {
                push_back(x._pointer[i]);
            }
            this->_capacity = this->_size;
            return (*this);
        }

        iterator begin() {
            iterator it(this->_pointer);
            return (it);
        }

        const_iterator begin() const {
            const_iterator it(this->_pointer);
            return (it);
        }

        iterator end() {
            iterator it(this->_pointer + this->_size);
            return (it);
        }

        const_iterator end() const {
            pointer p = this->_pointer + this->_size;
            const_iterator it(p);
            return (it);
        }

        reverse_iterator rbegin() {
            reverse_iterator it(this->_pointer + this->_size - 1);
            return (it);
        }

        const_reverse_iterator rbegin() const {
            const_reverse_iterator it(this->_pointer + this->_size - 1);
            return (it);
        }

        reverse_iterator rend() {
            reverse_iterator it(this->_pointer - 1);
            return (it);
        }

        const_reverse_iterator rend() const {
            const_reverse_iterator it(this->_pointer - 1);
            return (it);
        }

        size_type size() const {
            return (this->_size);
        }

        size_type max_size() const {
            size_type size1 = (size_type) std::numeric_limits<defference_type>::max();
			size_type size2 = std::numeric_limits<size_type>::max() / sizeof(value_type);
            if (size1 < size2) {
                return (size1);
            }
            return (size2);
        }

        void resize (size_type n, value_type val = value_type()) {
            while (n > this->_size) {
                push_back(val);
            }
            while (n < this->_size) {
                pop_back();
            }
        }

        size_type capacity() const {
            return (this->_capacity);
        }

        bool empty() const {
            return (this->_size == 0);
        }

        void reserve (size_type n) {
            if (n > this->_capacity) {
                pointer tmp = this->_alloc.allocate(n);
                for (size_type i = 0; i < this->_size; i++) {
                    tmp[i] = this->_pointer[i];
                }
                this->_alloc.deallocate(this->_pointer, this->_capacity);
                this->_capacity = n;
                this->_pointer = tmp;
            }
        }

        reference operator[] (size_type n) {
            return (this->_pointer[n]);
        }

        const_reference operator[] (size_type n) const {
            return (this->_pointer[n]);
        }

        reference at(size_type n) {
            if (n < 0 || n >= this->_size) {
                throw std::out_of_range("vector");
            }
            return (this->_pointer[n]);
        }

        const_reference at(size_type n) const {
            if (n < 0 || n >= this->_size) {
                throw std::out_of_range("vector");
            }
            reference ref = at(n);
            return (ref);
        }

        reference front() {
            return (this->_pointer[0]);
        }

        const_reference front() const {
            return (this->_pointer[0]);
        }

        reference back() {
            return (this->_pointer[this->_size - 1]);
        }
        
        const_reference back() const {
            return (this->_pointer[this->_size - 1]);
        }

        template <class InputIterator>
        void assign (InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL) {
            int i = 0;
            clear();
            this->_alloc.deallocate(this->_pointer, this->_capacity);
            this->_size = last - first;
            this->_capacity = this->_size * 2;
            this->_pointer = this->_alloc.allocate(this->_capacity);
            while (first != last) {
                this->_alloc.construct(this->_pointer + i, *first);
                first++;
                i++;
            }
        }

        void assign (size_type n, const value_type& val) {
            clear();
            this->_alloc.deallocate(this->_pointer, this->_capacity);
            this->_size = n;
            this->_capacity = n * 2;
            this->_pointer = this->_alloc.allocate(this->_capacity);
            for (size_type i = 0; i < n; i++) {
                this->_alloc.construct(this->_pointer + i, val);
            }
        }

        void push_back(const value_type& val) {
            if (this->_size == 0) {
                this->_capacity = 1;
                this->_pointer = this->_alloc.allocate(this->_capacity);
            } else if (this->_size + 1 >= this->_capacity) {
                size_type new_capacity = (this->_size) * 2;
                pointer tmp = this->_alloc.allocate(new_capacity);
                for (int i = 0; i < this->_size; i++) {
                    this->_alloc.construct(tmp + i, this->_pointer[i]);
                }
                this->_alloc.deallocate(this->_pointer, this->_capacity);
                this->_capacity = new_capacity;
                this->_pointer = tmp;
            }
            this->_alloc.construct(this->_pointer + this->_size++, val);
        }

        void pop_back() {
            if (this->_size == 0) {
                return ;
            }
            this->_alloc.destroy(this->_pointer + this->_size--);
        }

        iterator insert(iterator position, const value_type& val) {
            size_type size = position - begin();

            insert(position, 1, val);
            iterator it(this->_pointer + size);
            return (it);
        }

        void insert (iterator position, size_type n, const value_type& val) {
            size_type old_distance_end = end() - position;

            resize(this->_size + n);

            iterator it_end = end();
        
            int i;
            for (i = 0; i < old_distance_end; i++) {
                pointer p1 = this->_pointer + this->_size - 1 - i;
                pointer p2 = this->_pointer + this->_size - 1 - i - n;
                *p1 = *p2;
            }
            for (int k = 0; k < n; k++) {
                *(this->_pointer + this->_size - ++i) = val;
            }
        }

        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL) {
            size_type old_distance_end = (position - begin()) + (end() - position);
            size_type distance_range = last - first;

            resize(this->_size + distance_range);

            pointer pointer_end = this->_pointer + (old_distance_end + distance_range);

            int i = 0;
            for (; i < old_distance_end; i++) {
                *(pointer_end - i) = *(pointer_end - i - distance_range);
            }
            last--;
            for (int k = 0; k < distance_range; k++) {
                *(pointer_end - i++) = *(last--);
            }
        }

        iterator erase (iterator position) {
            iterator it = position;
            size_type distance_end = end() - position;
            pointer pointer_start = this->_pointer + (position - begin());

            this->_alloc.destroy(pointer_start);
            for (int i = 0; i < distance_end - 1; i++) {
                *(pointer_start) = *(pointer_start + 1);
                pointer_start++;
            }
            this->_size--;
            return it;
        }

        iterator erase (iterator first, iterator last, char (*)[sizeof(*first)] = NULL) {
            iterator it = first;
            size_type distance_end = end() - last;
            size_type size = last - first;
            pointer pointer_start = this->_pointer + (first - begin());

            for (int i = 0; i < distance_end; i++) {
                if (i < size) {
                    this->_alloc.destroy(pointer_start);
                }
                *(pointer_start) = *(pointer_start + size);
                pointer_start++;
            }
            this->_size -= size;
            return (it);
        }

        void swap (vector& x) {
            size_t          tmp_size = x._size;
            size_t          tmp_capacity = x._capacity;
            pointer         tmp_pointer = x._pointer;
            allocator_type  tmp_alloc = x._alloc;
    
            x._size = this->_size;
            x._capacity = this->_capacity;
            x._pointer = this->_pointer;
            x._alloc = this->_alloc;

            this->_size = tmp_size;
            this->_capacity = tmp_capacity;
            this->_pointer = tmp_pointer;
            this->_alloc = tmp_alloc;
        }

        void clear() {
            for (size_type i = 0; i < this->_size; i++) {
                this->_alloc.destroy(this->_pointer + i);
            }
            this->_size = 0;
        }

        allocator_type get_allocator() const {
            return (this->_alloc);
        }
    };

    template <class T>
    bool operator== (vector<T> const &lhs, vector<T> const &rhs) {
        if (lhs.size() != rhs.size()) {
            return (false);
        } else if (lhs.size() == 0) {
            return (true);
        }
        typename vector<T>::const_iterator left_begin = lhs.begin();
        typename vector<T>::const_iterator left_end = lhs.end();
        typename vector<T>::const_iterator right_begin = rhs.begin();
        while (left_begin != left_end) {
            if (*left_begin != *right_begin) {
                return (false);
            }
            left_begin++;
            right_begin++;
        }
        return (true);
    }

    template <class T>
    bool operator!= (vector<T> const &lhs, vector<T> const &rhs) {
        return (!(lhs == rhs));
    }

    template <class T>
    bool operator<(vector<T> const &lhs, vector<T> const &rhs) {
        typename vector<T>::const_iterator left_begin = lhs.begin();
        typename vector<T>::const_iterator left_end = lhs.end();
        typename vector<T>::const_iterator right_begin = rhs.begin();
        typename vector<T>::const_iterator right_end = rhs.end();

        while (1) {
            if (left_begin == left_end && right_begin != right_end) {
                return (true);
            } else if (left_begin != left_end && right_begin == right_end) {
                return (false);
            } else if (left_begin == left_end && right_begin == right_end) {
                return (false);
            } else if (*left_begin < *right_begin) {
                return (true);
            }
            left_begin++;
            right_begin++;
        }
        return (true);
    }

    template <class T>
    bool operator<=(vector<T> const &lhs, vector<T> const &rhs) {
        return ((lhs < rhs) || (lhs == rhs));
    }

    template <class T>
    bool operator>(vector<T> const &lhs, vector<T> const &rhs) {
        return (!(lhs < rhs) && (lhs != rhs));
    }

    template <class T>
    bool operator>=(vector<T> const &lhs, vector<T> const &rhs) {
        return ((lhs > rhs) || (lhs == rhs));
    }

    template <class T>
    void swap (vector<T>& x, vector<T>& y) {
        x.swap(y);
    }
};

#endif