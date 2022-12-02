#ifndef I_PROTOCOLS_HPP
#define I_PROTOCOLS_HPP

#include "../general/general.hpp"
#include "../client/client.hpp"
#include "msg.hpp"

class	msg;

class	I_protocols {

	private:

	public:

		virtual ~I_protocols (void){};
		virtual client welcome_client	(int fd) = 0;
		
};


#endif
