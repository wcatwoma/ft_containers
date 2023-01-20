/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:39:17 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:39:20 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP

#include "./node.hpp"

template <class K, class V>
class iterator_map : public std::iterator<std::bidirectional_iterator_tag, V> {

public:
    typedef iterator_map        iterator_type;
    typedef std::pair<K, V>     value_type;
    typedef node_map<K, V>      node_type;
    typedef value_type*         pointer;
    typedef value_type&         reference;
    typedef ptrdiff_t           defference_type;

private:
    node_type *_node;

public:

    iterator_map() {
        this->_node = NULL;
    }

    iterator_map(node_type *value) {
        this->_node = value;
    }

    iterator_map(const iterator_type &temp) {
        *this = temp;
    }

    ~iterator_map() {}

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
        operator++();
        return (out);
    }

    iterator_type &operator++() {
        node_type *tmp = this->_node;
    
        if (this->_node->right) {
            this->_node = this->_node->right;
            while (this->_node->left && this->_node->left != tmp) {
                this->_node = this->_node->left;
            }
        } else if (this->_node->parrent) {
            K key_node = this->_node->data.first;
            while (key_node >= this->_node->data.first) {
                this->_node = this->_node->parrent;
            }
        }
        return (*this);
    }

    iterator_type operator--(int) {
        iterator_type out(*this);
        operator--();
        return (out);
    }

    iterator_type &operator--() {
        node_type *tmp = this->_node;

        if (this->_node->left) {
            this->_node = this->_node->left;
            while (this->_node->right && this->_node->right != tmp) {
                this->_node = this->_node->right;
            }
        } else if (this->_node->parrent) {
            K key_node = this->_node->data.first;
            while (this->_node->parrent && key_node <= this->_node->data.first) {
                this->_node = this->_node->parrent;
            }
        }
        return (*this);
    }
};

template <class K, class V>
class const_iterator_map : public std::iterator<std::bidirectional_iterator_tag, V> {

public:
    typedef const_iterator_map      iterator_type;
    typedef std::pair<K, V>         value_type;
    typedef const node_map<K, V>    node_type;
    typedef const value_type*       pointer;
    typedef const value_type&       reference;
    typedef ptrdiff_t               defference_type;

private:
    node_type *_node;

public:

    const_iterator_map() {
        this->_node = NULL;
    }

    const_iterator_map(node_type *value) {
        this->_node = value;
    }

    const_iterator_map(const iterator_type &temp) {
        *this = temp;
    }

    ~const_iterator_map() {}

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
        operator++();
        return (out);
    }

    iterator_type &operator++() {
        node_type *tmp = this->_node;
    
        if (this->_node->right) {
            this->_node = this->_node->right;
            while (this->_node->left && this->_node->left != tmp) {
                this->_node = this->_node->left;
            }
        } else if (this->_node->parrent) {
            K key_node = this->_node->data.first;
            while (key_node >= this->_node->data.first) {
                this->_node = this->_node->parrent;
            }
        }
        return (*this);
    }

    iterator_type operator--(int) {
        iterator_type out(*this);
        operator--();
        return (out);
    }

    iterator_type &operator--() {
        node_type *tmp = this->_node;
    
        if (this->_node->left) {
            this->_node = this->_node->left;
            while (this->_node->right && this->_node->right != tmp) {
                this->_node = this->_node->right;
            }
        } else if (this->_node->parrent) {
            K key_node = this->_node->data.first;
            while (this->_node->parrent && key_node <= this->_node->data.first) {
                this->_node = this->_node->parrent;
            }
        }
        return (*this);
    }
};

template <typename Iterator>
class reverse_iterator_map {

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

    reverse_iterator_map() {
        this->_iterator = iterator_type();
        this->_base = (++this->_iterator)--;
    }

    explicit reverse_iterator_map (iterator_type it) {
        this->_iterator = it;
        this->_base = (++it)--;
    }

    template <class Iter>
    reverse_iterator_map (const reverse_iterator_map<Iter>& rev_it) {
        this->_iterator = rev_it._iterator;
    }

    ~reverse_iterator_map() {}

    iterator_type base () const {
        return (this->_base);
    }

    reference operator*() const {
        return (*(this->_iterator));
    }

    reverse_iterator_map operator++(int) {
        reverse_iterator_map<Iterator> out(this->_iterator);
        this->_iterator--;
        return (out);
    }

    reverse_iterator_map &operator++() {
        this->_iterator--;
        return (*this);
    }

    reverse_iterator_map operator--(int) {
        reverse_iterator_map out(this->_iterator);
        this->_iterator++;
        return (out);
    }

    reverse_iterator_map &operator--() {
        this->_iterator++;
        return (*this);
    }

    pointer operator->() const {
        return (this->_iterator.operator->());
    }
};

template <class Iterator>
class const_reverse_iterator_map {

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

    const_reverse_iterator_map() {
        this->_iterator = iterator_type();
        this->_base = (--this->_iterator)++;
    }

    explicit const_reverse_iterator_map (iterator_type it) {
        this->_iterator = it;
        this->_base = --it;
    }

    template <class Iter>
    const_reverse_iterator_map (const const_reverse_iterator_map<Iter>& rev_it) {
        this->_iterator = rev_it._iterator;
    }

    ~const_reverse_iterator_map() {}

    iterator_type base () const {
        return (this->_base);
    }

    reference operator*() const {
        return (*(this->_iterator));
    }

    const_reverse_iterator_map operator++(int) {
        const_reverse_iterator_map<Iterator> out(this->_iterator);
        this->_iterator--;
        return (out);
    }

    const_reverse_iterator_map &operator++() {
        this->_iterator--;
        return (*this);
    }

    const_reverse_iterator_map operator--(int) {
        const_reverse_iterator_map out(this->_iterator);
        this->_iterator++;
        return (out);
    }

    const_reverse_iterator_map &operator--() {
        this->_iterator++;
        return (*this);
    }

    pointer operator->() const {
        return (this->_iterator.operator->());
    }

};

#endif
