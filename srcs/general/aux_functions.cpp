/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:33:58 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/12/06 13:38:13 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.hpp"

std::vector<std::string> split_in_vector(std::string str, char c)
{
    std::stringstream 			test(str);
    std::string 				segment;
    std::vector <std::string>	seglist;

    while (std::getline(test,segment,c))
    	seglist.push_back(segment);
    return (seglist);
}