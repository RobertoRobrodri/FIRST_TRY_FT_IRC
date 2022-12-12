#ifndef I_SERVER_HPP
#define I_SERVER_HPP

#include "../general/general.hpp"
#include "server.hpp"

class	server;

class	I_server {

	private:

	public:

		virtual 		~I_server 			(void){};
		virtual bool	check_data_correct	(void) const = 0;
		virtual int		server_listening	(void) = 0;
		virtual int		start				(void) = 0;
		virtual void	analize_msg			(int i) = 0;
};


#endif
