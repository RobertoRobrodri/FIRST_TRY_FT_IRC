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

/*###########################################
#			CONSTRUCTOR						#
############################################*/

server::server( void )
{
  return ;
}

server::server( std::string network , std::string prt , std::string pass )
{
	std::vector <std::string>	seglist;
	
	seglist = split_in_vector(network,':');
    if (seglist.size() == 3)
		this->serv_data = (data_server) {seglist[0], seglist[1], seglist[2], prt, pass};
	else
		this->serv_data = (data_server) {"", "", "", prt, pass};
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

/*###########################################
#			OVERLOADING						#
############################################*/

server & server::operator=(const server &tmp)
{
	(void) tmp;
	std::cout << "Operator equalizer called" << std::endl;
	return *this;
}

std::ostream &operator<<(std::ostream& os, const server &tmp)
{
	os << "Parameter Server called - "<< &tmp << std::endl;
	os << "Operator output called" << std::endl;
	os << "host           |     " << tmp.get_host() << std::endl;
	os << "network pass   |     " << tmp.get_network_pass() << std::endl;
	os << "network port   |     " << tmp.get_network_port() << std::endl;
	os << "password       |     " << tmp.get_password() << std::endl;
	os << "port           |     " << tmp.get_port() << std::endl;
	return (os);
}

/*###########################################
#			PARSEO							#
############################################*/

void server::fds_search_data(void) const
{
	for (int i = 0;i < N_CLIENTS ; i++)
		std::cout << "fds[" << i <<"]fd = "<< this->fds[i].fd <<" events = "<< this->fds[i].events << " revents = "<< this->fds[i].revents << std::endl;
}

/*###########################################
#			THE REAL DEAL					#
############################################*/

void	server::search_fds(data_running *run)
{
	for (int i = 0; i < run->current_size;i++)
	{
		if (this->fds[i].revents ==  0)
			continue;
		if(fds[i].revents != POLLIN && fds[i].revents != 17)
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
		else if(fds[i].revents != 17)
		{
			//Recibimos el mensaje
			if(!recieve_data(run,i))
			{
				break;
			}
		}
		else
		{
			//Corte de conexion
			std::cout << "Cerramos connexion" << std::endl;
			this->close_fds_client(i, run);
		}
	}
	return;
}

int	server::start(void)
{
	data_running *serv_run;

	this->fds[0].fd 	= this->listening_socket;
  	this->fds[0].events = POLLIN;
	serv_run = (data_running *)calloc(sizeof(data_running), 1);
	serv_run->current_size = 0;
	serv_run->n_active_fds = 1;
	serv_run->status = true;
	
	do
	{
		serv_run->poll_result = poll(this->fds, serv_run->n_active_fds, TIMEOUT_MS);
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