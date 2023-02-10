#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../general/general.hpp"

class	client {

	private:
		std::string realname_host;
		std::string username_host;
		std::string nick;
		std::string	channel_title;
		bool		op;
	
	public:

		client ( void );
		client ( std::string rh, std::string uh, std::string ni);
		client ( const client & var );
		~client ( void );
		client &operator=(const client &tmp);

		/*###########################################
		#				FUNCTIONS					#
		############################################*/
		void clear_Client (void);
		
		/*###########################################
		#				GETTERS						#
		############################################*/
		std::string getnick(void)			const	{return(this->nick);};
		std::string getrealname_host(void)	const 	{return(this->realname_host);};
		std::string getusername_host(void)	const 	{return(this->username_host);};
		std::string getchannel_title(void)	const 	{return(this->channel_title);};
		bool		getoperator(void)		const 	{return(this->op);};

		/*###########################################
		#				SETTERS						#
		############################################*/
		void setnick			(std::string str)		{this->nick = str;};
		void setrealname_host	(std::string str)	 	{this->realname_host = str;};
		void setusername_host	(std::string str)	 	{this->username_host = str;};
		void setchannel_title	(std::string str)	 	{this->channel_title = str;};
		void setuseroperator	(bool		 o)	 		{this->op = o;};
};

std::ostream &operator<<(std::ostream& os, const client &tmp);

#endif
