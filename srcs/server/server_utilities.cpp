/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utilities.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:37:55 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/12/02 18:57:48 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int server::find_client_nick(std::string str, data_running *run)
{
    // std::cout << "TEST "<< std::endl;
    for (int i = 0;i < run->n_active_fds; i++)
        if (this->clients[i].getnick() == str)
            return (1);
    return (0);
}

int server::find_client_username(std::string str, data_running *run)
{
    // std::cout << "TEST "<< std::endl;
    // std::cout << "Username check "<< std::endl;
    for (int i = 0;i < run->n_active_fds; i++)
        if (this->clients[i].getusername_host() == str)
        {
            return (1);
        }
    return (0);
}

int server::find_client_realname(std::string str, data_running *run)
{
    // std::cout << "Realname check "<< std::endl;
    for (int i = 0;i < run->n_active_fds; i++)
        if (this->clients[i].getrealname_host() == str)
        {
            return (1);
        }
    return (0);
}

int server::check_client_NICK_USER(int i)
{
    if (this->clients[i].getnick() == "")
        return (0);
    if (this->clients[i].getrealname_host() == "")
        return (0);
    if (this->clients[i].getusername_host() == "")
        return (0);
    return (1);
}