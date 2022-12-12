/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_comm.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:59:58 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/12/06 18:36:10 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void server::analize_msg (int i)
{
  	std::vector <std::string>	line;
  	std::string str;
	std::string str_aux;
  	int aux;

  	aux = find_single_word_on_str(this->msg.get_message() , NICKNAME);
  	str = this->msg.get_message();
  	// str = find_single_word_on_str(this->get_message() , NICKNAME);
  	if (aux != -1)
	{
		line = split_in_vector(&str[aux],' ');
		if ( line.size() >= 2)
		{
		// str_from_start_to_end(str,line[1])
		//" next pos -> " << aux + str_end_word_position(&str[aux] , line[1]) 
		this->msg.set_message(this->msg.get_message().erase(aux , aux + str_end_word_position(&str[aux] , line[1])));
		line[1].erase(line[1].find_last_not_of(" \n\r\t")+1);
		this->clients[i].setnick(line[1]);
		}
		else
		std::cout << "No hay suficientes palabras en Nick para asignar un nickname :( " << std::endl;
	}

	aux = find_single_word_on_str(this->msg.get_message() , MESSAGE);
  	str = this->msg.get_message();
	if (aux != -1)
	{
		str_aux = this->msg.get_message();
		this->msg.set_message(clients[i].getnick() + ":" + &str[aux + 4]);
		this->msg_to_all(i);
		std::cout << "crash 1" << std::endl;
		// str_from_start_to_end(str,line[1])
		//" next pos -> " << aux + str_end_word_position(&str[aux] , line[1]) 
		this->msg.set_message(str_aux.erase(aux , str_aux.length()));
		std::cout << "No hay suficientes palabras en Nick para asignar un mensaje" << std::endl;
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
	// std::cout << c.getnick() << " se ha desconnectado" << std::endl;
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
	this->analize_msg(i);
	//Mandamos el mensaje a los demas clientes
	// if (!this->msg_to_all(i))
	// {
	// 	run->close_connection = true;
	// 	return (0);
	// }
	// Mandamos una confirmacion al cliente de vuelta
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
		this->clients[run->n_active_fds - 1].clear_Client();
		msg.welcome_client(run->new_sd);
		std::cout << "Tenemos un nuevo cliente connectado ... saludar a "<< this->clients[run->n_active_fds - 1].getnick() << std::endl;
		run->n_active_fds++;
		// fds_search_data();
	}
	msg.clear_message();
	return (1);
}