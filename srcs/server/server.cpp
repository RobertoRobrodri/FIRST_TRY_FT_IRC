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

server::server( void )
{
  return ;
}

server::server( std::string network , std::string prt , std::string pass )
{
    std::stringstream test(network);
    std::string segment;
    std::vector <std::string>seglist;

    while (std::getline(test,segment,':'))
      seglist.push_back(segment);

    if (seglist.size() == 3)
    {
		this->serv_data.host          = seglist[0];
		this->serv_data.network_port  = seglist[1];
		this->serv_data.network_pass  = seglist[2];
    }
	else
	{
		this->serv_data.network_port  = "";
		this->serv_data.network_pass  = "";
		this->serv_data.host          = "";
	}
    this->serv_data.port          = prt;
	this->serv_data.password      = pass;
  return ;
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
	std::cout << "Parameter Server called - "<< &tmp << std::endl;
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
	bool base[5] = { (this->serv_data.host == "" || !this->is_good_host(this->serv_data.host)) 					\
					,(this->serv_data.network_pass == "")														\
					,(this->serv_data.network_port == "" || !this->is_good_port(this->serv_data.network_port)) 	\
					,(this->serv_data.password == "")															\
					,(this->serv_data.port == "" || !this->is_good_port(this->serv_data.port))};
	for (int i = 0; i < 5; i++)
		if (base[i] == true)
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

void server::fds_search_data(void) const
{
	for (int i = 0;i < N_CLIENTS ; i++)
		std::cout << "fds[" << i <<"]fd = "<< this->fds[i].fd <<" events = "<< this->fds[i].events << " revents = "<< this->fds[i].revents << std::endl;
}

int server::recieve_msg(Data_Running *run, int i)
{
	run->close_connection = false;
	run->bytes_recieved = recv(fds[i].fd, run->buff, sizeof(run->buff), 0);
	
	if (run->bytes_recieved < 0)
	{
		std::cout << "Error recv() failed " << std::endl;
		run->close_connection = true;
		return (0);
	}
	if (run->bytes_recieved == 0)
	{
		std::cout << "Connection closed "<< std::endl;
		run->close_connection = true;
		return (0);;
	}
	run->len = run->bytes_recieved;
	// std::cout << "MSG["<< i <<"] : "<< std::string(run->buff,run->bytes_recieved) << std::endl;
	// bytes_recieved = send(fds[i].fd, buff, len, 0);
	run->bytes_recieved = send(fds[i].fd,   "127.0.0.1 : Pegame un tiro por dios", 27, 0);
	run->bytes_recieved = send(fds[i].fd, run->buff, run->len, 0);
	if (run->bytes_recieved < 0)
	{
		std::cout << "Error send() failed " << std::endl;
		run->close_connection = true;
		return (0);;
	}
	if (run->close_connection == true)
	{
		close(this->fds[i].fd);
		this->fds[i].fd = -1;
    		run->compress_array = true;
	}
	if (run->compress_array == true)
	{
		run->compress_array = false;
		for (int x = 0; x < run->n_active_fds; x++)
		{
			if (fds[x].fd == -1)
			{
				for(int j = x; j < run->n_active_fds; j++)
					fds[j].fd = fds[j+1].fd;
				x--;
				run->n_active_fds--;
			}
		}
	}
	return (1);
}

int	server::accept_client(Data_Running *run)
{
	run->new_sd = accept(this->listening_socket, NULL, NULL);
	if (run->new_sd < 0)
	{
		std::cout << "Error accept failed " << std::endl;
		run->status = false;
		return (0);
	}
	if (run->n_active_fds >= N_CLIENTS)
	{
		std::cout << "Error to many clients " << std::endl;
		run->bytes_recieved = recv(run->new_sd, run->buff, sizeof(run->buff), 0);
		run->len = run->bytes_recieved;
		std::cout << "CLIENT REJECTED : "<< std::endl << std::string(run->buff,run->bytes_recieved) << std::endl;

	}
	else
	{
		fds[run->n_active_fds].fd = this->listening_socket;
		fds[run->n_active_fds].events = POLL_IN;
		fds[run->n_active_fds - 1].fd = run->new_sd;
		fds[run->n_active_fds - 1].events = POLLIN;
		std::cout << "Tenemos un nuevo cliente connectado ... en el slot "<< run->n_active_fds << "new_sd = "<< run->new_sd<< std::endl;
		run->n_active_fds++;
		fds_search_data();
	}
	return (1);
}

void	server::search_fds(Data_Running *run)
{
	for (int i = 0; i < run->current_size;i++)
	{
		if (this->fds[i].revents == 0)
			continue;
		if(fds[i].revents != POLLIN)
		{
			std::cout << "Error revent is  : " << fds[i].revents << std::endl;
			run->status = false;
			break;
		}
		if (fds[i].fd == this->listening_socket) // && run->n_active_fds < N_CLIENTS
     	{
			//Aceptamos el cliente
			if (!this->accept_client(run))
				break;
		}
		else
		{
			//Recibimos el mensaje
			if(!recieve_msg(run,i))
				break;
		}
	}
	return;
}

int	server::start(void)
{
	struct Data_Running *serv_run;

	this->fds[0].fd 	= this->listening_socket;
  	this->fds[0].events = POLLIN;
	serv_run = (Data_Running *)calloc(sizeof(Data_Running), 1);
	serv_run->compress_array = false;
	serv_run->current_size = 0;
	serv_run->n_active_fds = 1;
	serv_run->status = true;
	std::cout << "El server empieza este infierno que llamo proyecto status ->(" << serv_run->status<< ")"<< std::endl;
	do
	{
		serv_run->poll_result = poll(this->fds, serv_run->n_active_fds, TIMEOUT_MS);
		// std::cout << "poll is  : " << poll_result << std::endl;
		if (serv_run->poll_result < 0) 	//Poll failed
		{
			std::cout << "Poll failed ... breaking server " << std::endl;
			break;
		}	
		if (serv_run->poll_result == 0) //Poll no result/time out
		{
			std::cout << "TIME_OUT ERROR ... breaking server " << std::endl;
			break;
		}	
		serv_run->current_size = serv_run->n_active_fds;
		this->search_fds(serv_run);
	}
	while (serv_run->status);
	
	for (int i = 0; i < serv_run->n_active_fds; i++)
	{
		if(fds[i].fd >= 0)
		close(fds[i].fd);
	}
	delete serv_run;
	return (0);
}


// int	server::start(void)
// {
// 	int		poll_result;
// 	int		new_sd;
// 	bool	close_connection;
// 	bool	compress_array;
// 	char 	buff[4096];
// 	int		bytes_recieved;
// 	int		n_active_fds;

// 	this->fds[0].fd 	= this->listening_socket;
//   	this->fds[0].events = POLLIN;
// 	compress_array 		= false;
// 	n_active_fds = 1;
// 	this->status = true;
// 	std::cout << "El server empieza este infierno que llamo proyecto status ->(" << this->status<< ")"<< std::endl;
// 	do
// 	{
// 		poll_result = poll(this->fds, n_active_fds, TIMEOUT_MS);
// 		std::cout << "poll is  : " << poll_result << std::endl;
// 		if (poll_result < 1) 	//Poll failed
// 			break;
// 		if 	(poll_result == 0) //Poll no result
// 			break;
// 		current_size = n_active_fds;
// 		for (int i = 0; i < current_size;i++)
// 		{
// 			if (this->fds[i].revents == 0)
// 				continue;
// 			if(fds[i].revents != POLLIN)
// 			{
// 				std::cout << "Error revent is  : " << fds[i].revents << std::endl;
// 				this->status = false;
// 				break;
// 			}
// 			if (fds[i].fd == this->listening_socket)
//       		{
// 				if (n_active_fds >= N_CLIENTS)
// 				{
// 					std::cout << "Connection rejected ... al fds are taken " << std::endl;
// 					break;
// 				}

// 				new_sd = accept(this->listening_socket, NULL, NULL);
// 				if (new_sd < 0)
// 				{
// 					if (errno != EWOULDBLOCK)
// 					{
// 						std::cout << "Error accept failed " << std::endl;
// 						this->status = false;
// 					}
// 					break;
// 				}
// 				fds[n_active_fds].fd = new_sd;
// 				fds[n_active_fds].events = POLLIN;
// 				std::cout << "Tenemos un nuevo cliente connectado ... en el slot "<< n_active_fds << "new_sd = "<< new_sd<< std::endl;
// 				n_active_fds++;
// 				fds_search_data(N_CLIENTS,this->fds);
// 			}
// 			else
// 			{
// 				close_connection = false;
// 				bytes_recieved = recv(fds[i].fd, buff, sizeof(buff), 0);
				
// 				if (bytes_recieved < 0)
// 				{
// 					if (errno != EWOULDBLOCK)
// 					{
// 						std::cout << "Error recv() failed " << std::endl;
// 						close_connection = true;
// 					}
// 					break;
// 				}
// 				if (bytes_recieved == 0)
// 				{
// 					std::cout << "Connection closed "<< std::endl;
// 					close_connection = true;
// 					break;
// 				}
// 				std::cout << "MSG["<< i <<"] : "<< std::string(buff,bytes_recieved) << std::endl;
// 				this->fds[i].events = 0 ;

// 				if (close_connection == true)
// 				{
// 					close(this->fds[i].fd);
// 					this->fds[i].fd = -1;
//           			compress_array = true;
// 				}
// 			}
			
			
// 		}
// 		// std::cout << "Damos una vuelta ... status -> "<< this->status << std::endl;
// 	}
// 	while (this->status);
// 	return (0);
// }

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
