/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:39:29 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:39:30 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "./iterator.hpp"
#include "./node.hpp"

namespace ft {

    template < class K, class V, class Compare = std::less<K>, class Alloc = std::allocator<std::pair<K, V> > >
    class map {

    public:
        typedef K												key_type;
		typedef V												mapped_type;
		typedef typename std::pair<key_type,mapped_type>	    value_type;
		typedef Compare											key_compare;
        class value_compare
        {
            friend class map;
            protected:
                Compare comp;
                value_compare (Compare c) : comp(c) {}
            public:
                typedef bool result_type;
                typedef value_type first_argument_type;
                typedef value_type second_argument_type;
                bool operator() (const value_type& x, const value_type& y) const
                {
                    return comp(x.first, y.first);
                }
        };

        typedef Alloc allocator_type;
        typedef typename std::allocator<node_map<K, V> > allocator_node_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        typedef iterator_map<key_type, mapped_type> iterator;
        typedef const_iterator_map<key_type, mapped_type> const_iterator;
        typedef reverse_iterator_map<iterator> reverse_iterator;
        typedef const_reverse_iterator_map<const_iterator> const_reverse_iterator;

        typedef ptrdiff_t defference_type;
        typedef size_t size_type;

        typedef node_map<K, V> node_type;

    private:
        allocator_node_type _alloc;
        node_type           *_begin;
        node_type           *_end;
        size_type           _size;
        key_compare         _comp;

        bool is_end_node(node_type *node) {
            if (node == NULL) {
                return (true);
            } else if (node == this->_begin) {
                return (true);
            } else if (node == this->_end) {
                return (true);
            }
            return (false);
        }

        void add_chain_parrent_child(node_type *parrent, node_type *child, node_type *node) {
            if (node == NULL) {
                return ;
            }
            node->parrent = parrent;
            if (parrent == NULL) {
                return ;
            }
            if (parrent->left == child) {
                parrent->left = node;
            } else if (parrent->right == child) {
                parrent->right = node;
            }
        }

        void delete_chain(node_type *parrent, node_type *child) {
            if (parrent == NULL || child == NULL) {
                return ;
            }
            child->parrent = NULL;
            if (parrent->left == child) {
                parrent->left = NULL;
            } else if (parrent->right == child) {
                parrent->right = NULL;
            }
        }

        node_type *get_parrent_node(node_type *node) {
            if (!node) {
                return (NULL);
            }
            return (node->parrent);
        }

        size_type get_height_node(node_type *node) {
            if (!node || node == this->_begin || node == this->_end) {
                return (0);
            }
            return (node->height);
        }

        int get_factor_balance(node_type *node) {
            return (get_height_node(node->right) - get_height_node(node->left));
        }

        size_type get_update_height(node_type *node) {
            size_type size_left = get_height_node(node->right);
            size_type size_right = get_height_node(node->left);

            if (size_left > size_right) {
                return (size_left + 1);
            } else {
                return (size_right + 1);
            }
        }

        node_type *get_root() const {
            node_type *node = this->_begin->right;
            if (node == NULL || node == this->_end) {
                return (NULL);
            }
            while (node->parrent) {
                node = node->parrent;
            }
            return (node);
        }

        node_type *rotate_left(node_type *node) {
            node_type *parrent = get_parrent_node(node);
            node_type *child_right = node->right;
            node->right = child_right->left;
            child_right->left = node;
            node->parrent = child_right;
            add_chain_parrent_child(parrent, node, child_right);
            node->height = get_update_height(node);
            child_right->height = get_update_height(child_right);
            child_right->left->height = get_update_height(child_right->left);
            return (child_right);
        }

        node_type *rotate_right(node_type *node) {
            node_type *parrent = get_parrent_node(node);
            node_type *child_left = node->left;
            node->left = child_left->right;
            child_left->right = node;
            node->parrent = child_left;
            add_chain_parrent_child(parrent, node, child_left);
            node->height = get_update_height(node);
            child_left->height = get_update_height(child_left);
            child_left->right->height = get_update_height(child_left->right);
            return (child_left);
        }

        node_type *balance(node_type *node) {
            if (is_end_node(node)) {
                return (NULL);
            }
            node->height = get_update_height(node);
            int factor_balance = get_factor_balance(node);

            if (factor_balance == 2) {
                if (get_factor_balance(node->right) < 0) {
                    node->right = rotate_right(node->right);
                }
                return (rotate_left(node));
            } else if (factor_balance == -2) {
                if (get_factor_balance(node->left) > 0) {
                    node->left = rotate_left(node->left);
                }
                return (rotate_right(node));
            }
            return (node);
        }

        node_type *insert_key(node_type *parrent, key_type key) {
            if (parrent == this->_begin || parrent == this->_end) {
                return (NULL);
            }
            if (key < parrent->data.first) {
                if (parrent->left && parrent->left != this->_begin) {
                    parrent->left = insert_key(parrent->left, key);
                } else {
                    parrent->left = create_node(key);
                    parrent->left->parrent = parrent;
                }
            } else if (key > parrent->data.first) {
                if (parrent->right && parrent->right != this->_end) {
                    parrent->right = insert_key(parrent->right, key);
                } else {
                    parrent->right = create_node(key);
                    parrent->right->parrent = parrent;
                }
            }
            return (balance(parrent));
        }

        node_type *search_key(node_type *parrent, key_type key) const {
            if (parrent == NULL ||
                parrent == this->_begin ||
                parrent == this->_end) {
                return (NULL);
            }
            if (key < parrent->data.first) {
                return (search_key(parrent->left, key));
            } else if (key > parrent->data.first) {
                return (search_key(parrent->right, key));
            } else if (key == parrent->data.first) {
                return (parrent);
            }
            return (NULL);
        }

        node_type *find_min(node_type *parrent) {
            if (parrent->left && 
                parrent->left != this->_begin && 
                parrent->right != this->_end) {
                return (find_min(parrent->left));
            }
            return (parrent);
        }

        node_type *remove_node_from_map(node_type *node, key_type key) {
            if (is_end_node(node)) {
                return (NULL);
            }
            if (key < node->data.first) {
                node->left = remove_node_from_map(node->left, key);
            } else if (key > node->data.first) {
                node->right = remove_node_from_map(node->right, key);
            } else {
                node = remove_node(node);
                if (is_end_node(node)) {
                    return (node);
                }
                return (balance(node));
            }
            return (balance(node));
        }

        

        node_type *remove_node(node_type *node) {
            node_type *result = NULL;
            node_type *min_node = NULL;
            node_type *left_node = node->left;
            node_type *right_node = node->right;
            node_type *parrent_node = node->parrent;

            if (is_end_node(left_node) && is_end_node(right_node)) {
                delete_chain(parrent_node, node);
                if (this->_size == 1) {
                    this->_begin->right = this->_end;
                    this->_end->left = this->_begin;
                    result = NULL;
                } else if (node->left == this->_begin) {
                    this->_begin->right = parrent_node;
                    result = this->_begin;
                } else if (node->right == this->_end) {
                    this->_end->left = parrent_node;
                    result = this->_end;
                }
            } else if (is_end_node(right_node)) {
                add_chain_parrent_child(parrent_node, node, left_node);
                if (node->right == this->_end) {
                    this->_end->left = left_node;
                    left_node->right = this->_end;
                }
                result = left_node;
            } else if (is_end_node(left_node)) {
                add_chain_parrent_child(parrent_node, node, right_node);
                if (node->left == this->_begin) {
                    this->_begin->right = right_node;
                    right_node->left = this->_begin;
                }
                result = right_node;
            } else if (is_end_node(right_node->left)) {
                right_node->left = node->left;
                node->left->parrent = right_node;
                add_chain_parrent_child(parrent_node, node, right_node);
                result = right_node;
            } else if (is_end_node((min_node = find_min(right_node))->right)) {
                delete_chain(min_node->parrent, min_node);
                add_chain_parrent_child(parrent_node, node, min_node);
                min_node->left = left_node;
                min_node->right = right_node;
                left_node->parrent = min_node;
                right_node->parrent = min_node;
                result = min_node;
            } else {
                min_node->parrent->left = min_node->right;
                min_node->right->parrent = min_node->parrent;
                add_chain_parrent_child(parrent_node, node, min_node);
                min_node->left = left_node;
                min_node->right = right_node;
                left_node->parrent = min_node;
                right_node->parrent = min_node;
                result = min_node;
            }
            this->delete_node(node);
            return (result);
        }

        template <class I, class B>
		std::pair<I, B> create_pair(I first, B second)
		{
			std::pair<I, B> pair(first, second);
			return (pair);
		}

        void update_begin_end() {
            if (this->_begin->right == this->_end) {
                return ;
            }
            if (this->_begin->right->left != this->_begin) {
                this->_begin->right = this->_begin->right->left;
                this->_begin->right->left = this->_begin;
            } 
            if (this->_end->left->right != this->_end) {
                this->_end->left = this->_end->left->right;
                this->_end->left->right = this->_end;
            }
        }

        node_type *create_node(key_type key) {
            node_type *node = this->_alloc.allocate(1);
            this->_alloc.construct(node, key_type(), mapped_type());
            node->parrent = NULL;
            node->left = NULL;
            node->right = NULL;
            node->height = 1;
            node->data.first = key;
            this->_size++;
            return (node);
        }

        void delete_node(node_type *node) {
            this->_alloc.destroy(node);
			this->_alloc.deallocate(node, 1);
            this->_size--;
        }

        void init_map(const key_compare &comp, const allocator_type &alloc) {
            this->_comp = comp;
            this->_alloc = alloc;
            this->_size = 0;
            this->_begin = this->_alloc.allocate(1);
            this->_alloc.construct(this->_begin, key_type(), mapped_type());
            this->_end = this->_alloc.allocate(1);
            this->_alloc.construct(this->_end, key_type(), mapped_type());
            this->_begin->right = this->_end;
            this->_end->left = this->_begin;
        }

    public:
        explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
            this->init_map(comp, alloc);
        }

        template <class InputIterator>
        map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type(), char (*)[sizeof(*first)] = NULL) {
            this->init_map(comp, alloc);
            this->insert(first, last);
        }

        map (const map& x) {
            this->_size = 0;
            *this = x;
        }

        ~map() {
            if (this->_size > 0) {
                this->clear();
            }
            this->delete_node(this->_begin);
            this->delete_node(this->_end);
        }

        map& operator=(const map& x) {
            if (this->_size > 0) {
                this->clear();
            }
            this->init_map(x._comp, x._alloc);
            if (x.size() > 0) {
                this->insert(x.begin(), x.end());
            }
            return (*this);
        }

        iterator begin() {
            iterator it(this->_begin->right);
            return (it);
        }

        const_iterator begin() const {
            const_iterator it(this->_begin->right);
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
            reverse_iterator it(this->_end->left);
            return (it);
        }

        const_reverse_iterator rbegin() const {
            const_reverse_iterator it(this->_end->left);
            return (it);
        }

        reverse_iterator rend() {
            reverse_iterator it(this->_begin);
            return (it);
        }

        const_reverse_iterator rend() const {
            const_reverse_iterator it(this->_begin);
            return (it);
        }

        bool empty() const {
            return (this->_size == 0);
        }

        size_type size() const {
            return (this->_size);
        }

        size_type max_size() const {
            return (this->_alloc.max_size());
        }

        mapped_type& operator[] (const key_type& key) {
            node_type *node_root = this->get_root();
            node_type *node = NULL;

            if (this->_begin->right == this->_end) {
                node = this->create_node(key);

                this->_begin->right = node;
                this->_end->left = node;
                node->left = this->_begin;
                node->right = this->_end;
                return (node->data.second);
            }
            if ((node = search_key(node_root, key))) {
                return (node->data.second);
            }
            node_root = this->insert_key(node_root, key);
            this->update_begin_end();
            node = search_key(node_root, key);
            return (node->data.second);
        }

        std::pair<iterator,bool> insert(const value_type& data) {
            node_type *node_root = this->get_root();
            node_type *node = NULL;

            if (this->_begin->right == this->_end) {
                node = this->create_node(data.first);

                this->_begin->right = node;
                this->_end->left = node;
                node->left = this->_begin;
                node->right = this->_end;
                node->data.second = data.second;
                return (create_pair<iterator, bool>(iterator(node), true));
            }
            if ((node = search_key(node_root, data.first))) {
                return (create_pair<iterator, bool>(iterator(node), false));
            }
            node_root = this->insert_key(node_root, data.first);
            this->update_begin_end();
            node = search_key(node_root, data.first);
            node->data.second = data.second;
            return (create_pair<iterator, bool>(iterator(node), true));
        }

        iterator insert(iterator position, const value_type& val) {
            (void)position;
            return (this->insert(val).first);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last, char (*)[sizeof(*first)] = NULL) {
            while (first != last) {
                this->insert(*first);
                first++;
            }
        }

        void erase(iterator position) {
            this->erase((*position).first);
        }

        size_type erase(const key_type& key) {
            if (this->_begin->right == this->_end) {
                return (0);
            }

            node_type *node_root = this->get_root();
            if (this->search_key(node_root, key)) {
                this->remove_node_from_map(node_root, key);
                return (1);
            }
            return (0);
        }

        void erase(iterator first, iterator last, char (*)[sizeof(*first)] = NULL) {
            while (first != last) {
                this->erase(first++);
            }
        }

        void swap (map& x) {
            allocator_type  tmp_alloc;
            node_type       *tmp_begin;
            node_type       *tmp_end;
            size_type       tmp_size;
            key_compare     tmp_comp;

            tmp_alloc = x._alloc;
            tmp_begin = x._begin;
            tmp_end = x._end;
            tmp_size = x._size;
            tmp_comp = x._comp;

            x._alloc = this->_alloc;
            x._begin = this->_begin;
            x._end = this->_end;
            x._size = this->_size;
            x._comp = this->_comp;

            this->_alloc = tmp_alloc;
            this->_begin = tmp_begin;
            this->_end = tmp_end;
            this->_size = tmp_size;
            this->_comp = tmp_comp;
        }

        void clear() {
            this->erase(this->begin(), this->end());

        }

        key_compare key_comp() const {
            return (this->_comp);
        }

        value_compare value_comp() const {
            value_compare v_comp(this->_comp);
            return (v_comp);
        }

        iterator find(const key_type& key) {
            if (this->_begin->right == NULL) {
                return (NULL);
            }

            node_type *node_root = this->get_root();
            node_type *node = search_key(node_root, key);
            if (!node) {
                return (NULL);
            }
            return (iterator(node));
        }

        const_iterator find(const key_type& key) const {
            if (this->_begin->right == NULL) {
                return (NULL);
            }

            node_type *node_root = this->get_root();
            node_type *node = search_key(node_root, key);
            if (!node) {
                return (NULL);
            }
            return (const_iterator(node));
        }

        size_type count(const key_type& key) const {
            if (this->_begin->right == NULL) {
                return (0);
            }

            node_type *node_root = this->get_root();
            node_type *node = search_key(node_root, key);
            if (!node) {
                return (0);
            }
            return (1);
        }

        iterator lower_bound(const key_type& key) {
            if (this->_begin->right == NULL) {
                return (NULL);
            }

            iterator it_b = this->begin();
            iterator it_e = this->end();

            while (it_b != it_e) {
                if (it_b->first == key) {
                    return (it_b);
                } else if (this->_comp(it_b->first, key) == false) {
                    return (it_b);
                }
                it_b++;
            }
            return (it_b);
        }

        const_iterator lower_bound(const key_type& key) const {
            if (this->_begin->right == NULL) {
                return (NULL);
            }

            const_iterator it_b = this->begin();
            const_iterator it_e = this->end();

            while (it_b != it_e) {
                if (it_b->first == key) {
                    return (it_b);
                } else if (this->_comp(it_b->first, key) == false) {
                    return (it_b);
                }
                it_b++;
            }
            return (it_b);
        }

        iterator upper_bound(const key_type& key) {
            if (this->_begin->right == NULL) {
                return (NULL);
            }

            iterator it_b = this->begin();
            iterator it_e = this->end();

            while (it_b != it_e) {
                if (this->_comp(it_b->first, key) == false) {
                    return (++it_b);
                }
                it_b++;
            }
            return (it_b);
        }

        const_iterator upper_bound(const key_type& key) const {
            if (this->_begin->right == NULL) {
                return (NULL);
            }

            const_iterator it_b = this->begin();
            const_iterator it_e = this->end();

            while (it_b != it_e) {
                if (this->_comp(it_b->first, key) == false) {
                    return (++it_b);
                }
                it_b++;
            }
            return (it_b);
        }

        std::pair<const_iterator,const_iterator> equal_range(const key_type& key) const {
            std::pair<const_iterator, const_iterator> pair;
            pair.first = (const_iterator) lower_bound(key);
            pair.second = (const_iterator) upper_bound(key);
            return (pair);
        }

        std::pair<iterator,iterator>             equal_range(const key_type& key) {
            std::pair<iterator, iterator> pair;
            pair.first = (iterator) lower_bound(key);
            pair.second = (iterator) upper_bound(key);
            return (pair);
        }
    };
}

#endif