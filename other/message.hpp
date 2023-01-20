/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:39:48 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:39:49 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

void print_ok() {
    std::cout << "\033[32;4;24m OK \033[0m";
}

void print_title(std::string title, std::string color, bool isEndl) {
    std::cout << color << title << "\033[0m";
    if (isEndl) {
        std::cout << std::endl;
    }
}

template <class T>
void print_error(std::string type, T std_result, T ft_result) {
    std::cout << "\033[31;1;4m KO " << type << " ";
    std::cout << "(std: " << std_result;
    std::cout << ", ft: " << ft_result;
    std::cout << ")\033[0m ";
}
