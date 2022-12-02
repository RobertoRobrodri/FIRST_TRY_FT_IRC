/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_comm.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:59:58 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/12/02 19:00:41 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

int	server::close_fds_client(int i, data_running *run)
{
	close(this->fds[i].fd);
	this->fds[i].fd = -1;
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
	std::cout << "CLIENT["<< i <<"] left the server..." << std::endl;
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

int server::recieve_msg(data_running *run, int i)
{
	run->close_connection = false;

	//Recibimos el mensaje
	if (!this->msg.recv_message(fds[i].fd))
	{
		run->close_connection = true;
		return (0);
	}
	//Procesamos el mensaje
	this->msg.set_message("CLIENT["+std::to_string(i)+"] :"+this->msg.get_message());
	//Mostramos el mensaje en el servidor
	std::cout << msg;
	//Mandamos el mensaje a los demas clientes
	if (!this->msg_to_all(i))
	{
		run->close_connection = true;
		return (0);
	}
	//Mandamos una confirmaion al cliente de vuelta
	// if (!this->msg.send_message(fds[i].fd,"mensaje recibido\n"))
	// {
	// 	run->close_connection = true;
	// 	return (0);
	// }

	if (run->close_connection == true)
	{
		std::cout << "Un error inesperado cerro la conexion del cliente... "<< i << std::endl;
		this->close_fds_client(i, run);
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
		std::cout << "Tenemos un nuevo cliente connectado ... hay un total de -> "<< run->n_active_fds << std::endl;
		run->n_active_fds++;
		// fds_search_data();
	}
	msg.clear_message();
	return (1);
}