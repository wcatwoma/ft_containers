/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generators.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcatwoma <wcatwoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:39:43 by wcatwoma          #+#    #+#             */
/*   Updated: 2022/02/09 21:39:44 by wcatwoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include <map>

int UniqueNumber (int *current) { return ++(*current); }

std::string UniqueString (int *current) { return std::to_string(++(*current)); }

double UniqueDouble (int *current) { return static_cast<double>(++(*current)); }

char UniqueChar (int *current) { return static_cast<char>(++(*current)); }

int RandomNumber (int *size_number) {
    if (*size_number == 0) {
        *size_number += 1;
    }
    return (rand() % *size_number); }

std::string RandomString (int *size_number) {
    if (*size_number == 0) {
        *size_number += 1;
    }
    return (std::to_string(rand() % *size_number));
}

double RandomDouble (int *size_number) {
    if (*size_number == 0) {
        *size_number += 1;
    }

    int random = rand() % *size_number;

    return (static_cast<double>(random));
}

char RandomChar (int *size_number) {
    if (*size_number == 0) {
        *size_number += 1;
    }
    return (static_cast<char>(rand() % 125));
}
