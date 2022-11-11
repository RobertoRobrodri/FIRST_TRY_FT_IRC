/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:00:57 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/11/11 13:19:49 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "server/server.hpp"

int exit_msg(std::string msg)
{
	std::cout << msg << std::endl;
	return (0);
}

int main(int argc, char **argv)
{
	// int sock;
	(void)argc;
	(void)argv;
	server *serv;
	if (argc != 4)
		return (exit_msg("Unexact number of argvs"));
	serv = new server(argv[1], argv[2], argv[3]);
	if (serv->check_data_correct())
		std::cout << "GOOD CHECK "<< std::endl << *serv <<std::endl;
	else
		return (exit_msg("Bad Check"));
	// sock = socket( 0,SOCK_STREAM,PF_INET6);
	return (0);

}