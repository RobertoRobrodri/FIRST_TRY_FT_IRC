/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:15:25 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/11/09 13:34:23 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <unistd.h>
#include <string>
#include <vector>
#include <sstream>

server::server( void ) :  host(""), network_pass (""), network_port(""), port(""), password(""), status(true), current_size(0)
{

  std::cout << "Default constructor called" << std::endl;

}

server::server( std::string network , std::string prt , std::string pass ) : host(""), network_pass(""), network_port (""), port(""), password(""), status(true), current_size(0)
{
    std::stringstream test(network);
    std::string segment;
    std::vector <std::string>seglist;

    while (std::getline(test,segment,':'))
      seglist.push_back(segment);

    if (seglist.size() == 3)
    {
		this->host          = seglist[0];
		this->network_port  = seglist[1];
		this->network_pass  = seglist[2];
    }
    this->port          = prt;
	this->password      = pass;
  std::cout << "Parameter constructor called" << std::endl;

}

server::server( const server & var )
{
	(void) var;
	std::cout << "Copy constructor called" << std::endl;
}

server::~server( void ) 
{
	std::cout << "Destructor constructor called" << std::endl;
}

server & server::operator=(const server &tmp)
{
	(void) tmp;
	std::cout << "Operator equalizer called" << std::endl;
	return *this;
}

std::ostream &operator<<(std::ostream& os, const server &tmp)
{
	os << "Operator output called" << std::endl;
	os << "host           |     " << tmp.get_host() << std::endl;
	os << "network pass   |     " << tmp.get_network_pass() << std::endl;
	os << "network port   |     " << tmp.get_network_port() << std::endl;
	os << "password       |     " << tmp.get_password() << std::endl;
	os << "port           |     " << tmp.get_port() << std::endl;
	return (os);
}

bool	server::is_good_host(std::string host) const
{
  	std::stringstream test(host);
    std::string segment;
    std::vector <int>seglist;

    while (std::getline(test,segment,'.'))
    {
      if (segment.c_str() != std::to_string(atoi(segment.c_str())))
        seglist.push_back(-1);
      else
        seglist.push_back(atoi(segment.c_str()));
    }
    if (seglist.size() != 4)
      return (0);
    for (int i = 0; i < 4; i++)
      if (seglist[i] < 0 || seglist[i] > 255)
        return (0);
    
    return (1);
}

bool	server::is_good_port(std::string port) const
{
  int port_i;

  port_i = atoi(port.c_str());
  if (port != std::to_string(port_i))
    return(0);
  if (port_i < 6000 /*|| port_i > 7000*/) // What about 80 and 8080 port????????
    return (0);
  return (1);
}

bool	server::check_data_correct(void) const
{
  if (this->host == "" || !this->is_good_host(this->host))
    return (0);
  if (this->network_pass == "")
    return (0);
  if (this->network_port == "" || !this->is_good_port(this->network_port))
    return (0);
  if (this->password == "")
    return (0);
  if (this->port == "" || !this->is_good_port(this->port))
    return (0);
  return (1);
}

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

	if ((this->host_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return 0;
	// No sé que opciones tendremos que habilitar pero vamos a tener que usarlo
	if (setsockopt(this->host_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		perror("Bad socket ");
		return 0;
	}
	addr = init_socket_struct(this->network_port, this->host);
	// Asigna un nombre al socket; Asigna la info de address al socket
	if (bind(this->host_socket, (const sock_addr*)&addr, sizeof(addr)) == -1)
	{
		perror("Error binding ");
		return 0;
	}
	// Tenemos que definir un max_size para la cola
	if (listen(this->host_socket, N_CLIENTS) == -1)
	{
		perror("Can't hear you");
		return 0;
	}
	std::cout << "Server listening" << std::endl;
	return 1;
}

void	server::wait_for_msg(void)
{
	sock_in 	client;
	socklen_t	cli_size;
	char 		buff[4096];
	int 		bytes_recieved;
	
	
	std::cout << "Espera a que llegue un cliente" << std::endl;
	cli_size = sizeof(client);
	if (accept(this->host_socket, (sock_addr *) &client, &cli_size) == -1)
		std::cout << "Problem with client: "<< std::endl;
	else
	{
		std::cout << "Una vez tiene el cliente escucha que quiere decir" << std::endl;
		while (true)
		{
			memset(buff,0,4096);
			bytes_recieved = recv(this->host_socket,buff,4096,0);
			if ( bytes_recieved != -1)
				std::cout << "Server : " << std::string(buff,bytes_recieved) << std::endl;
		}
	}
}

void fds_search_data(int size, pollfd *data)
{
	std::cout << "POLLIN VALUE IS = "<< POLL_IN << std::endl;
	for (int i = 0;i < size ; i++)
		std::cout << "fds[" << i <<"]fd = "<< data[i].fd <<" events = "<< data[i].events << " revents = "<< data[i].revents << std::endl;
}

int	server::start(void)
{
	int		poll_result;
	int		new_sd;
	bool	close_connection;
	bool	compress_array;
	char 	buff[4096];
	int		bytes_recieved;
	int		n_active_fds;

	this->fds[0].fd 	= this->host_socket;
  	this->fds[0].events = POLLIN;
	compress_array 		= false;
	n_active_fds = 1;
	this->status = true;
	std::cout << "El server empieza este infierno que llamo proyecto status ->(" << this->status<< ")"<< std::endl;
	do
	{
		poll_result = poll(this->fds, n_active_fds, TIMEOUT_MS);
		std::cout << "poll is  : " << poll_result << std::endl;
		if (poll_result < 1) 	//Poll failed
			break;
		if 	(poll_result == 0) //Poll no result
			break;
		current_size = n_active_fds;
		for (int i = 0; i < current_size;i++)
		{
			if (this->fds[i].revents == 0)
				continue;
			if(fds[i].revents != POLLIN)
			{
				std::cout << "Error revent is  : " << fds[i].revents << std::endl;
				this->status = false;
				break;
			}
			if (fds[i].fd == this->host_socket)
      		{
				if (n_active_fds >= N_CLIENTS)
				{
					std::cout << "Connection rejected ... al fds are taken " << std::endl;
					break;
				}

				new_sd = accept(this->host_socket, NULL, NULL);
				if (new_sd < 0)
				{
					if (errno != EWOULDBLOCK)
					{
						std::cout << "Error accept failed " << std::endl;
						this->status = false;
					}
					break;
				}
				fds[n_active_fds].fd = new_sd;
				fds[n_active_fds].events = POLLIN;
				std::cout << "Tenemos un nuevo cliente connectado ... en el slot "<< n_active_fds << "new_sd = "<< new_sd<< std::endl;
				n_active_fds++;
				fds_search_data(N_CLIENTS,this->fds);
			}
			else
			{
				close_connection = false;
				bytes_recieved = recv(fds[i].fd, buff, sizeof(buff), 0);
				
				if (bytes_recieved < 0)
				{
					if (errno != EWOULDBLOCK)
					{
						std::cout << "Error recv() failed " << std::endl;
						close_connection = true;
					}
					break;
				}
				if (bytes_recieved == 0)
				{
					std::cout << "Connection closed "<< std::endl;
					close_connection = true;
					break;
				}
				std::cout << "MSG["<< bytes_recieved<<"] : "<< std::string(buff,bytes_recieved) << std::endl;
				this->fds[i].events = 0 ;

				if (close_connection == true)
				{
					close(this->fds[i].fd);
					this->fds[i].fd = -1;
          			compress_array = true;
				}
			}
			
			
		}
		// std::cout << "Damos una vuelta ... status -> "<< this->status << std::endl;
	}
	while (this->status);
	return (0);
}




// if (compress_array == true)
// 			{
// 				compress_array = false;
// 				for (int x = 0; x < n_active_fds; x++)
// 				{
// 					if (fds[x].fd == -1)
// 					{
// 					for(int j = x; j < n_active_fds; j++)
// 					{
// 						fds[j].fd = fds[j+1].fd;
// 					}
// 					x--;
// 					n_active_fds--;
// 					}
// 				}
// 			}


// for (int i = 0; i < n_active_fds; i++)
// 	{
// 		if(fds[i].fd >= 0)
// 		close(fds[i].fd);
// 	}