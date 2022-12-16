/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_comm.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:59:58 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/12/14 17:10:33 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void server::analize_msg (int i, data_running *run)
{
	std::vector <std::string>line = split_in_vector(this->msg.get_message(),'\n');
	std::string cmd[3] = {NICKNAME,USERNAME,MESSAGE};
	server::funptr function[3] = {&server::extract_NICK , &server::extract_USERNAME ,&server::extract_MSG};
  	if (line.size() >= 1)
	{
		for (int y = 0; y < (int)line.size(); y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (find_single_word_on_str(this->msg.get_message() , cmd[x]) != -1)
					(this->*(function[x]))(i , line[y] , run);
			}
		}

	}
}

int	server::close_fds_client(int i, data_running *run)
{
	client c;
	
	close(this->fds[i].fd);
	this->fds[i].fd = -1;
	c = this->clients[i];
	std::cout << this->clients[i].getnick() << " se ha desconnectado" << std::endl;
	for (int x = 0; x < run->n_active_fds; x++)
	{
		if (fds[x].fd == -1)
		{
			for(int j = x; j < run->n_active_fds; j++)
			{
				fds[j].fd = fds[j+1].fd;
				this->clients[j] = this->clients[j+1];
			}
			x--;
			run->n_active_fds--;
		}
	}
	return (1);
}

int server::msg_to_all(int i)
{

	for (int j = 0; j < N_CLIENTS; j++)
	{
		if (j == i)
			continue;
		if (fds[j].fd == this->listening_socket)
			break;
		if (!this->msg.send_message(fds[j].fd, this->msg.get_message()))
			return (0);
	}
	return (1);
}

int server::recieve_data(data_running *run, int i)
{
	bool close_connection;
	
	close_connection = false;
	//Recibimos el mensaje
	if (!this->msg.recv_message(fds[i].fd))
	{
		close_connection = true;
	}
	
	//Si paso algo raro cerramos el cliente // procesamos el mensaje
	if (close_connection)
	{
		std::cout << "Un error inesperado cerro la conexion del cliente... " << std::endl;
		this->close_fds_client(i, run);
		return (0);
	}
	else
	{
		//Analizamos el mensaje y mostramos en el terminal los datos no procesados
		std::cout << this->clients[i].getnick() << " <data before analisis>:" << std::endl << this->msg.get_message() << std::endl;
		this->analize_msg(i, run);
	}
	return (1);
}

int	server::accept_client(data_running *run)
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
		std::cout << "CLIENT REJECTED - Error to many clients "<< std::endl;
		msg.send_message(run->new_sd,"Cliente rechazado... demasiados clientes\n");
		close(run->new_sd);
	}
	else
	{
		fds[run->n_active_fds].fd = this->listening_socket;
		fds[run->n_active_fds].events = POLL_IN;
		fds[run->n_active_fds - 1].fd = run->new_sd;
		fds[run->n_active_fds - 1].events = POLLIN;
		this->clients[run->n_active_fds - 1].clear_Client();
		this->welcome_client(run->new_sd);
		std::cout << "New client added to the network ..." << std::endl;
		run->n_active_fds++;
		// fds_search_data();
	}
	msg.clear_message();
	return (1);
}