#ifndef GENERAL_HPP
#define GENERAL_HPP

#define	sock_in		struct sockaddr_in
#define	sock_addr	struct sockaddr
#define N_CLIENTS 5+1			//Numero de Clientes (fd) + el fd del host
#define TIMEOUT_MS 10*1000*60 	//Tiempo de desconexion en caso de no recivir nada

#include <poll.h>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <vector>
#include <sstream>

//Struct para almacenar los datos del servidor
typedef struct data_server {             
	std::string host;
	std::string network_port;
	std::string network_pass;
	std::string port;
	std::string password;
} data_server; 

//Struct para almacenar los datos que debe tener el servidor activo
typedef struct data_running {            
	bool		status;
	int			current_size;
	int			poll_result;
	int			new_sd;
	bool		close_connection;
	int			n_active_fds;
} data_running; 

#endif