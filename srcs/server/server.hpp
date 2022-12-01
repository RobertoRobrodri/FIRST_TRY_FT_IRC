#ifndef SERVER_HPP
#define SERVER_HPP
#define	sock_in		struct sockaddr_in
#define	sock_addr	struct sockaddr

#define N_CLIENTS 5+1			//Numero de Clientes (fd) + el fd del host
#define TIMEOUT_MS 10*1000*60 	//Tiempo de desconexion en caso de no recivir nada

#include "../client/client.hpp"
#include "../msg/msg.hpp"
#include <poll.h>
#include <string>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

struct Data_Server {             //Struct para almacenar los datos del servidor
	std::string host;
	std::string network_pass;
	std::string network_port;
	std::string port;
	std::string password;   
}; 

struct Data_Running {             //Struct para almacenar los datos que debe tener el servidor activo
	bool		status;
	int			current_size;
	int			poll_result;
	int			new_sd;
	bool		close_connection;
	bool		compress_array;
	int			n_active_fds;
}; 

class	server {

	private:

		pollfd				fds[N_CLIENTS];
		client				clients[N_CLIENTS];
		msg					msg;
		int					listening_socket;
		struct Data_Server 	serv_data;


		/*###########################################
		#			CLOSED    	FUNCTIONS			#
		############################################*/
		server	( void );

		/*###########################################
		#			PRIVATE    	FUNCTIONS			#
		############################################*/
		bool	is_good_port	(std::string port) const;
		bool	is_good_host	(std::string host) const;
		void	search_fds		(Data_Running *run);
		int		accept_client	(Data_Running *run);
		int		recieve_msg		(Data_Running *run, int i);
		int		msg_to_all		(int i);
		int		close_fds_client(int i, Data_Running *run);

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
		std::string get_host		(void) const {return(this->serv_data.host);};
		std::string get_network_pass(void) const {return(this->serv_data.network_pass);};
		std::string get_network_port(void) const {return(this->serv_data.network_port);};
		std::string get_port		(void) const {return(this->serv_data.port);};
		std::string get_password	(void) const {return(this->serv_data.password);};

		/*###########################################
		#			PUBLIC	FUNCTIONS				#
		############################################*/
		bool	check_data_correct	(void) const;
		int		server_listening	(void);
		int		start				(void);
};

std::ostream &operator<<(std::ostream& os, const server &tmp);
sock_in	init_socket_struct(std::string port, std::string host);

#endif
