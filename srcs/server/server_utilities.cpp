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
    for (int i = 0;i < run->n_active_fds; i++)
        if (this->clients[i].getnick() == str)
            return (1);
    return (0);
}

int server::find_client_username(std::string str, data_running *run)
{
    for (int i = 0;i < run->n_active_fds; i++)
        if (this->clients[i].getusername_host() == str)
            return (1);
    return (0);
}

int server::find_client_realname(std::string str, data_running *run)
{
    for (int i = 0;i < run->n_active_fds; i++)
        if (this->clients[i].getrealname_host() == str)
            return (1);
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

int server::recv_message(int fd , std::string &str)
{
    char 		buff[4096];
    int bytes;
    
    bytes = recv(fd, buff, sizeof(buff), 0);
    // std::cout << "Bytes recieved -> " << this->get_bytes_recieved() << std::endl;
    if (bytes < 0)
	{
		std::cout << "Error recv() failed " << std::endl;
		return (0);
	}
	if (bytes == 0)
	{
		std::cout << "Connection closed "<< std::endl;
		return (0);;
	}
    str = std::string(buff,bytes);
    return (1);
}

int server::send_message(int fd, std::string str)
{
    int result;

	result = send(fd, str.c_str(), str.size(), 0);
	if (result < 0)
	{
		std::cout << "Error send() failed " << std::endl;
		return (0);
	}
  return (1);
}