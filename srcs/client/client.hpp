#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../general/general.hpp"

class	client {

	private:
		std::string realname_host;
		std::string username_host;
		std::string nick;
	public:

		//pollfd		fds[N_CLIENTS];

		client ( void );
		client ( std::string rh, std::string uh, std::string ni);
		client ( const client & var );
		~client ( void );
		client &operator=(const client &tmp);

		/*###########################################
		#				FUNCTIONS					#
		############################################*/
		void clear_Client(void);
		
		/*###########################################
		#				GETTERS						#
		############################################*/
		std::string getnick(void)			const	{return(this->nick);};
		std::string getrealname_host(void)	const 	{return(this->realname_host);};
		std::string getusername_host(void)	const 	{return(this->username_host);};

		/*###########################################
		#				SETTERS						#
		############################################*/
		void setnick(std::string s)				{this->nick = s;};
		void setrealname_host(std::string s)	 	{this->realname_host = s;};
		void setusername_host(std::string s)	 	{this->username_host = s;};
};

std::ostream &operator<<(std::ostream& os, const client &tmp);

#endif
