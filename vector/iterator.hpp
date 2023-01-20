/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:40:15 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:40:16 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_VECTOR_HPP
#define ITERATOR_VECTOR_HPP

#include <iostream>

template <typename T>
class iterator_vector : public std::iterator<std::random_access_iterator_tag, T> {

public:
    typedef iterator_vector iterator_type;
    typedef T               value_type;
    typedef value_type*     pointer;
    typedef value_type&     reference;
    typedef ptrdiff_t       defference_type;

private:
    pointer _pointer;

public:

    iterator_vector(pointer value = 0) {
        this->_pointer = value;
    }

    iterator_vector(const iterator_vector &temp) {
        *this = temp;
    }

    ~iterator_vector() {}

    iterator_type &operator=(const iterator_type &it) {
        this->_pointer = it._pointer;
        return (*this);
    }

    bool operator==(iterator_type const &obj) const {
        return (this->_pointer == obj._pointer);
    }

    bool operator!=(iterator_type const &obj) const {
        return (this->_pointer != obj._pointer);
    }

    reference operator*() const {
        return (*(this->_pointer));
    }

    pointer operator->() const {
        return (this->_pointer);
    }

    iterator_type operator++(int) {
        iterator_type out(*this);
        this->_pointer++;
        return (out);
    }

    iterator_type &operator++() {
        this->_pointer++;
        return (*this);
    }

    iterator_type operator--(int) {
        iterator_type out(*this);
        this->_pointer--;
        return (out);
    }

    iterator_type &operator--() {
        this->_pointer--;
        return (*this);
    }

    iterator_type operator+(int i) {
        iterator_type it(this->_pointer + i);
        return (it);
    }

    iterator_type operator-(int i) {
        iterator_type it(this->_pointer - i);
        return (it);
    }

    defference_type operator-(iterator_type const &it) {
        return (this->_pointer - it._pointer);
    }

    bool operator<(iterator_type const &obj) const {
        return (this->_pointer < obj._pointer);
    }

    bool operator>(iterator_type const &obj) const {
        return (this->_pointer > obj._pointer);
    }

    bool operator<=(iterator_type const &obj) const {
        return (this->_pointer <= obj._pointer);
    }

    bool operator>=(iterator_type const &obj) const {
        return (this->_pointer >= obj._pointer);
    }

    iterator_type operator+=(int value) {
        this->_pointer += value;
        return (*this);
    }

    iterator_type operator-=(int value) {
        this->_pointer -= value;
        return (*this);
    }

    reference operator[](size_t index) {
        return (this->_pointer[index]);
    }
};

template <typename T>
class const_iterator_vector : public std::iterator<std::random_access_iterator_tag, T> {

public:
    typedef const_iterator_vector   iterator_type;
    typedef T                       value_type;
    typedef value_type*             pointer;
    typedef value_type&             reference;
    typedef ptrdiff_t               defference_type;

private:
    pointer _pointer;

public:

    const_iterator_vector(pointer value = 0) {
        this->_pointer = value;
    }

    const_iterator_vector(const iterator_type &temp) {
        *this = temp;
    }

    ~const_iterator_vector() {}

    iterator_type &operator=(const iterator_type &it) {
        this->_pointer = it._pointer;
        return (*this);
    }

    bool operator==(iterator_type const &obj) const {
        return (this->_pointer == obj._pointer);
    }

    bool operator!=(iterator_type const &obj) const {
        return (this->_pointer != obj._pointer);
    }

    reference operator*() const {
        return (*(this->_pointer));
    }

    pointer operator->() const {
        return (this->_pointer);
    }

    iterator_type operator++(int) {
        iterator_type out(*this);
        this->_pointer++;
        return (out);
    }

    iterator_type &operator++() {
        this->_pointer++;
        return (*this);
    }

    iterator_type operator--(int) {
        iterator_type out(*this);
        this->_pointer--;
        return (out);
    }

    iterator_type &operator--() {
        this->_pointer--;
        return (*this);
    }

    iterator_type operator+(int i) {
        iterator_type it(this->_pointer + i);
        return (it);
    }

    iterator_type &operator-(int i) {
        iterator_type it(this->_pointer - i);
        return (it);
    }

    defference_type operator-(iterator_type const &it) {
        return (this->_pointer - it._pointer);
    }
    
    bool operator<(iterator_type const &obj) const {
        return (this->_pointer < obj._pointer);
    }

    bool operator>(iterator_type const &obj) const {
        return (this->_pointer > obj._pointer);
    }

    bool operator<=(iterator_type const &obj) const {
        return (this->_pointer <= obj._pointer);
    }

    bool operator>=(iterator_type const &obj) const {
        return (this->_pointer >= obj._pointer);
    }

    iterator_type operator+=(int value) {
        this->_pointer += value;
        return (*this);
    }

    iterator_type operator-=(int value) {
        this->_pointer -= value;
        return (*this);
    }

    reference operator[](size_t index) {
        return (this->_pointer[index]);
    }

};

template <typename Iterator>
class reverse_iterator_vector {

public:
    typedef Iterator                            iterator_type;
    typedef typename Iterator::value_type       value_type;
    typedef typename Iterator::pointer          pointer;
    typedef typename Iterator::reference        reference;
    typedef typename Iterator::defference_type  defference_type;

private:
    iterator_type _iterator;
    iterator_type _base;

public:

    reverse_iterator_vector() {
        this->_iterator = iterator_type();
        this->_base = this->_iterator + 1;
    }

    explicit reverse_iterator_vector (iterator_type it) {
        this->_iterator = it;
        this->_base = it + 1;
    }

    template <class T>
    reverse_iterator_vector (const reverse_iterator_vector<T>& rev_it) {
        this->_iterator = rev_it._iterator;
        this->_base = rev_it.base();
    }

    ~reverse_iterator_vector() {}

    iterator_type base () const {
        return (this->_base);
    }

    reference operator*() const {
        return (*(this->_iterator));
    }

    reverse_iterator_vector operator+(int i) {
        reverse_iterator_vector<Iterator> it(this->_iterator - i);
        return (it);
    }

    reverse_iterator_vector operator++(int) {
        reverse_iterator_vector out(this->_iterator);
        this->_iterator--;
        return (out);
    }

    reverse_iterator_vector &operator++() {
        this->_iterator--;
        return (*this);
    }

    reverse_iterator_vector operator+=(int value) {
        this->_iterator -= value;
        this->_base -= value;
        return (*this);
    }

    reverse_iterator_vector operator-(int i) {
        reverse_iterator_vector<Iterator> it(this->_iterator + i);
        return (it);
    }

    reverse_iterator_vector operator--(int) {
        reverse_iterator_vector out(this->_iterator);
        this->_iterator++;
        return (out);
    }

    reverse_iterator_vector &operator--() {
        this->_iterator++;
        return (*this);
    }

    reverse_iterator_vector operator-=(int value) {
        this->_iterator += value;
        this->_base += value;
        return (*this);
    }

    pointer operator->() const {
        return (this->_iterator.operator->());
    }

    reference operator[](size_t index) {
        return (*(this->_iterator - index));
    }

};

template <typename Iterator>
class const_reverse_iterator_vector {

public:
    typedef Iterator                            iterator_type;
    typedef typename Iterator::value_type       value_type;
    typedef typename Iterator::pointer          pointer;
    typedef typename Iterator::reference        reference;
    typedef typename Iterator::defference_type  defference_type;

private:
    iterator_type _iterator;
    iterator_type _base;

public:

    const_reverse_iterator_vector() {
        this->_iterator = iterator_type();
        this->_base = this->_iterator + 1;
    }

    explicit const_reverse_iterator_vector (iterator_type it) {
        this->_iterator = it;
        this->_base = it + 1;
    }

    template <class T>
    const_reverse_iterator_vector (const const_reverse_iterator_vector<T>& rev_it) {
        this->_iterator = rev_it._iterator;
        this->_base = rev_it.base();
    }

    ~const_reverse_iterator_vector() {}

    iterator_type base () const {
        return (this->_base);
    }

    reference operator*() const {
        return (*(this->_iterator));
    }

    const_reverse_iterator_vector operator+(int i) {
        const_reverse_iterator_vector<Iterator> it(this->_iterator - i);
        return (it);
    }

    const_reverse_iterator_vector operator++(int) {
        const_reverse_iterator_vector out(this->_iterator);
        this->_iterator--;
        return (out);
    }

    const_reverse_iterator_vector &operator++() {
        this->_iterator--;
        return (*this);
    }

    const_reverse_iterator_vector operator+=(int value) {
        this->_iterator -= value;
        this->_base -= value;
        return (*this);
    }

    const_reverse_iterator_vector operator-(int i) {
        const_reverse_iterator_vector<Iterator> it(this->_iterator + i);
        return (it);
    }

    const_reverse_iterator_vector operator--(int) {
        const_reverse_iterator_vector out(this->_iterator);
        this->_iterator++;
        return (out);
    }

    const_reverse_iterator_vector &operator--() {
        this->_iterator++;
        return (*this);
    }

    const_reverse_iterator_vector operator-=(int value) {
        this->_iterator += value;
        this->_base += value;
        return (*this);
    }

    pointer operator->() const {
        return (this->_iterator.operator->());
    }

    reference operator[](size_t index) {
        return (*(this->_iterator - index));
    }

};

#endif