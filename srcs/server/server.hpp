#ifndef SERVER_HPP
#define SERVER_HPP
#define	sock_in		struct sockaddr_in
#define	sock_addr	struct sockaddr

#define N_CLIENTS 5+1			//Numero de Clientes (fd) + el fd del host
#define TIMEOUT_MS 3*1000*60 	//Tiempo de desconexion en caso de no recivir nada

#include "../client/client.hpp"
#include <poll.h>
#include <string>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

class	server {

	private:

		pollfd		fds[N_CLIENTS];
		// client		clients[N_CLIENTS];
		int			host_socket;
		std::string host;
		std::string network_pass;
		std::string network_port;
		std::string port;
		std::string password;
		bool		status;
		int			current_size;

		server	( void );
		/*###########################################
		#			PRIVATE    	FUNCTIONS			#
		############################################*/
		bool	is_good_port(std::string port) const;
		bool	is_good_host(std::string host) const;


		/*###########################################
		#			DEBUG    	FUNCTIONS			#
		############################################*/
		void fds_search_data(void) const;
	public:

		server	( std::string network , std::string prt , std::string pass );
		server 	( const server & var );
		~server ( void );
		server &operator=(const server &tmp);

		/*###########################################
		#				GETTERS						#
		############################################*/
		std::string get_host(void) const 			{return(this->host);};
		std::string get_network_pass(void) const 	{return(this->network_pass);};
		std::string get_network_port(void) const 	{return(this->network_port);};
		std::string get_port(void) const 			{return(this->port);};
		std::string get_password(void) const 		{return(this->password);};

		/*###########################################
		#			PUBLIC	FUNCTIONS				#
		############################################*/
		bool	check_data_correct(void) const;
		int		start(void);
		int		server_listening(void);
		void	wait_for_msg(void); //Innecesario pero escucha un cliente (ahira toca con multiples)
};

std::ostream &operator<<(std::ostream& os, const server &tmp);
sock_in	init_socket_struct(std::string port, std::string host);

#endif
