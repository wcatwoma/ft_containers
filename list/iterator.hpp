/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:35:55 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:35:58 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_lIST_HPP
#define ITERATOR_lIST_HPP

#include "./node.hpp"

template <typename T>
class iterator_list : public std::iterator<std::bidirectional_iterator_tag, T> {

public:
    typedef iterator_list       iterator_type;
    typedef T                   value_type;
    typedef Node<value_type>    *node_pointer;
    typedef value_type*         pointer;
    typedef value_type&         reference;
    typedef ptrdiff_t           defference_type;

private:
    node_pointer _node;

public:

    iterator_list(node_pointer value = 0) {
        this->_node = value;
    }

    iterator_list(const iterator_type &temp) {
        *this = temp;
    }

    ~iterator_list() {}

    iterator_type &operator=(const iterator_type &it) {
        this->_node = it._node;
        return (*this);
    }

    bool operator==(iterator_type const &obj) const {
        return (this->_node == obj._node);
    }

    bool operator!=(iterator_type const &obj) const {
        return (this->_node != obj._node);
    }

    reference operator*() const {
        return (this->_node->data);
    }

    pointer operator->() const {
        return (&(this->_node->data));
    }

    iterator_type operator++(int) {
        iterator_type out(*this);
        this->_node = this->_node->next;
        return (out);
    }

    iterator_type &operator++() {
        this->_node = this->_node->next;
        return (*this);
    }

    iterator_type operator--(int) {
        iterator_type out(*this);
        this->_node = this->_node->prev;
        return (out);
    }

    iterator_type &operator--() {
        this->_node = this->_node->prev;
        return (*this);
    }

    node_pointer get_node(void) const {
        return (this->_node);
    }
};

template <typename T>
class const_iterator_list : public std::iterator<std::bidirectional_iterator_tag, T> {

public:
    typedef const_iterator_list iterator_type;
    typedef T                   value_type;
    typedef const Node<value_type>    *node_pointer;
    typedef const value_type*         pointer;
    typedef const value_type&         reference;
    typedef ptrdiff_t           defference_type;

private:
    node_pointer _node;

public:

    const_iterator_list() {
        this->_node = 0;
    }

    const_iterator_list(node_pointer value) {
        this->_node = value;
    }

    const_iterator_list(const iterator_type &temp) {
        *this = temp;
    }

    ~const_iterator_list() {}

    iterator_type &operator=(const iterator_type &it) {
        this->_node = it._node;
        return (*this);
    }

    bool operator==(iterator_type const &obj) const {
        return (this->_node == obj._node);
    }

    bool operator!=(iterator_type const &obj) const {
        return (this->_node != obj._node);
    }

    reference operator*() const {
        return (this->_node->data);
    }

    pointer operator->() const {
        return (&(this->_node->data));
    }

    iterator_type operator++(int) {
        iterator_type out(*this);

        this->_node = this->_node->next;
        return (out);
    }

    iterator_type &operator++(void) {
        this->_node = this->_node->next;
        return (*this);
    }

    iterator_type operator--(int) {
        iterator_type out(*this);
        this->_node = this->_node->prev;
        return (out);
    }

    iterator_type &operator--() {
        this->_node = this->_node->prev;
        return (*this);
    }

    node_pointer get_node(void) const {
        return (this->_node);
    }

};

template <class Iterator>
class reverse_iterator_list {

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

    reverse_iterator_list() {
        this->_iterator = iterator_type();
        this->_base = (++this->_iterator)--;
    }

    explicit reverse_iterator_list (iterator_type it) {
        this->_iterator = it;
        this->_base = (++it)--;
    }

    template <class Iter>
    reverse_iterator_list (const reverse_iterator_list<Iter>& rev_it) {
        this->_iterator = rev_it._iterator;
    }

    ~reverse_iterator_list() {}

    iterator_type base () const {
        return (this->_base);
    }

    reference operator*() const {
        return (*(this->_iterator));
    }

    reverse_iterator_list operator++(int) {
        reverse_iterator_list<Iterator> out(this->_iterator);
        this->_iterator--;
        return (out);
    }

    reverse_iterator_list &operator++() {
        this->_iterator--;
        return (*this);
    }

    reverse_iterator_list operator--(int) {
        reverse_iterator_list out(this->_iterator);
        this->_iterator++;
        return (out);
    }

    reverse_iterator_list &operator--() {
        this->_iterator++;
        return (*this);
    }

    pointer operator->() const {
        return (this->_iterator.operator->());
    }
};

template <class Iterator>
class const_reverse_iterator_list {

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

    const_reverse_iterator_list() {
        this->_iterator = iterator_type();
        this->_base = (--this->_iterator)++;
    }

    explicit const_reverse_iterator_list (iterator_type it) {
        this->_iterator = it;
        this->_base = --it;
    }

    template <class Iter>
    const_reverse_iterator_list (const const_reverse_iterator_list<Iter>& rev_it) {
        this->_iterator = rev_it._iterator;
    }

    ~const_reverse_iterator_list() {}

    iterator_type base () const {
        return (this->_base);
    }

    reference operator*() const {
        return (*(this->_iterator));
    }

    const_reverse_iterator_list operator++(int) {
        const_reverse_iterator_list<Iterator> out(this->_iterator);
        this->_iterator--;
        return (out);
    }

    const_reverse_iterator_list &operator++() {
        this->_iterator--;
        return (*this);
    }

    const_reverse_iterator_list operator--(int) {
        const_reverse_iterator_list out(this->_iterator);
        this->_iterator++;
        return (out);
    }

    const_reverse_iterator_list &operator--() {
        this->_iterator++;
        return (*this);
    }

    pointer operator->() const {
        return (this->_iterator.operator->());
    }

};

#endif
