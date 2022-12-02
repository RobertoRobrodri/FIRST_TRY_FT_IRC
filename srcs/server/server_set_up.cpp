/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_set_up.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:37:55 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/12/02 18:57:48 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

sock_in	init_socket_struct(std::string port, std::string host)
{
	sock_in	addr;
// Init struct that the socket needs

//  IPV4 addresses
	addr.sin_family				= AF_INET;
//  Convert our port to a network address (host to network)
	addr.sin_port				= htons(atoi(port.c_str()));
//  Our address as integer
	addr.sin_addr.s_addr		= inet_addr(host.c_str());
	return addr;
}

int		server::server_listening(void)
{
	sock_in	addr;
	int		opt = 1;

	if ((this->listening_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return 0;
	// No sé que opciones tendremos que habilitar pero vamos a tener que usarlo
	if (setsockopt(this->listening_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		perror("Bad socket ");
		return 0;
	}
	addr = init_socket_struct(this->serv_data.network_port, this->serv_data.host);
	// Asigna un nombre al socket; Asigna la info de address al socket
	if (bind(this->listening_socket, (const sock_addr*)&addr, sizeof(addr)) == -1)
	{
		perror("Error binding ");
		return 0;
	}
	// Tenemos que definir un max_size para la cola
	if (listen(this->listening_socket, N_CLIENTS) == -1)
	{
		perror("Can't hear you");
		return 0;
	}
	std::cout << "Server listening" << std::endl;
	return 1;
}