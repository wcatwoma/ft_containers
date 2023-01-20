/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:39:32 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:39:33 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

template <typename K, typename V>
class node_map
{
    public:
        node_map        *left;
        node_map        *right;
        node_map        *parrent;
        size_t          height;
        std::pair<K, V> data;

        node_map() {
            data.first = K();
            data.second = V();
            this->left = NULL;
            this->right = NULL;
            this->parrent = NULL;
        }

        node_map(K key, V value) {
            this->data.first = key;
            this->data.second = value;
            this->left = NULL;
            this->right = NULL;
            this->parrent = NULL;
        }

        ~node_map() {}
};

#endif