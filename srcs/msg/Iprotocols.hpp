#ifndef IPROTOCOLS_HPP
#define IPROTOCOLS_HPP

#include "../general/general.hpp"
#include "msg.hpp"

class	msg;

class	Iprotocols {

	private:

	public:

		virtual ~Iprotocols (void){};
		virtual void welcome_client	(int fd) = 0;
		
};


#endif
