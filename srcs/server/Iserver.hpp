#ifndef ISERVER_HPP
#define ISERVER_HPP

#include "../general/general.hpp"
#include "server.hpp"

class	server;

class	Iserver {

	private:

	public:

		virtual 		~Iserver 			(void){};
		virtual bool	check_data_correct	(void) const = 0;
		virtual int		server_listening	(void) = 0;
		virtual int		start				(void) = 0;
		
};


#endif
