#ifndef SERVER_HPP
#define SERVER_HPP

#include "../general/general.hpp"
#include "I_server.hpp"
#include "../client/client.hpp"
#include "../msg/msg.hpp"



class	server : public I_server
{

	private:

		pollfd				fds[N_CLIENTS];
		client				clients[N_CLIENTS];
		msg					msg;
		int					listening_socket;
		data_server 		serv_data;


		/*###########################################
		#			CLOSED    	FUNCTIONS			#
		############################################*/
		server	( void );

		/*###########################################
		#			PRIVATE    	FUNCTIONS			#
		############################################*/
		bool	is_good_port	(std::string port) const;
		bool	is_good_host	(std::string host) const;
		void	search_fds		(data_running *run);
		int		accept_client	(data_running *run);
		int		recieve_msg		(data_running *run, int i);
		int		msg_to_all		(int i);
		int		close_fds_client(int i, data_running *run);

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
		#			INTERFACE	FUNCTIONS			#
		############################################*/
		bool	check_data_correct	(void) const;
		int		server_listening	(void);
		int		start				(void);
};

std::ostream &operator<<(std::ostream& os, const server &tmp);

sock_in	init_socket_struct(std::string port, std::string host);

#endif
