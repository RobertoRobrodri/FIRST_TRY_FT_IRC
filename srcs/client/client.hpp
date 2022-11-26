#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define N_CLIENTS 5+1			//Numero de Clientes (fd) + el fd del host
#define TIMEOUT_MS 3*1000*60 	//Tiempo de desconexion en caso de no recivir nada

class	client {

	private:
		std::string realname_host;
		std::string username_host;
		std::string nick;
	public:

		pollfd		fds[N_CLIENTS];

		client ( void );
		client ( std::string rh, std::string uh, std::string ni);
		client ( const client & var );
		~client ( void );
		client &operator=(const client &tmp);

		/*###########################################
		#				GETTERS						#
		############################################*/
		std::string getnick(void) const 			{return(this->nick);};
		std::string getrealname_host(void) const 	{return(this->realname_host);};
		std::string getusername_host(void) const 	{return(this->username_host);};

};

std::ostream &operator<<(std::ostream& os, const client &tmp);

#endif
