#ifndef SERVER_HPP
#define SERVER_HPP

#include "../general/general.hpp"
#include "I_server.hpp"
#include "../commands/I_commands.hpp"
#include "../client/client.hpp"
#include "../channel/channel.hpp"



class	server : public I_server , public I_commands
{

	private:

		pollfd				fds[N_CLIENTS];
		client				clients[N_CLIENTS];
		//msg					msg;
		//channel				chanel;
		int					listening_socket;
		data_server 		serv_data;


		/*###########################################
		#			CLOSED    	FUNCTIONS			#
		############################################*/
		server	( void );

		/*###########################################
		#			COMMS    	FUNCTIONS			#
		############################################*/
		void	search_fds		(data_running *run);
		int		accept_client	(data_running *run);
		int		recieve_data	(data_running *run, int i);
		int		msg_to_all		(int i, std::string str);
		int		close_fds_client(int i, data_running *run);
		void	analize_msg		(int i , std::string str , data_running *run);

		/*###########################################
		#		UTILITIES    	FUNCTIONS			#
		############################################*/
		int		find_client_nick	(std::string str, data_running *run);
		int 	find_client_username(std::string str, data_running *run);
		int		find_client_realname(std::string str, data_running *run);
		int		recv_message	(int fd, std::string &str);
		int		send_message	(int fd, std::string str);
		int		check_client_NICK_USER(int i);


		/*###########################################
		#			DEBUG    	FUNCTIONS			#
		############################################*/
		void fds_search_data(void) const;

		/*###########################################
		#			COMMANDS    FUNCTIONS			#
		############################################*/
		typedef void (server::*funptr) (int i , std::string str , data_running *run);
		void 	welcome_client	(int fd);
		void	extract_MSG		(int i , std::string str , data_running *run);
		void	extract_USERNAME(int i , std::string str , data_running *run);
		void	extract_NICK	(int i , std::string str , data_running *run);

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
		data_server get_serv_data	(void) const {return(this->serv_data);};
		/*###########################################
		#			INTERFACE	FUNCTIONS			#
		############################################*/
		int		server_listening	(void);
		int		start				(void);
};

std::ostream &operator<<(std::ostream& os, const server &tmp);

sock_in	init_socket_struct(std::string port, std::string host);

#endif
