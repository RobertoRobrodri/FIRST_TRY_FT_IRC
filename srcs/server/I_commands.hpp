/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   I_commands.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:01:34 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/12/14 16:08:55 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_COMMANDS_HPP
#define I_COMMANDS_HPP

#include "../general/general.hpp"
#include "server.hpp"

class	server;

class	I_commands {

	private:

	public:

		virtual ~I_commands (void){};
		virtual void welcome_client		(int fd) = 0;
		virtual void extract_NICK		(int i) = 0;
		virtual void extract_USERNAME	(int i) = 0;
		virtual void extract_MSG		(int i) = 0;
		
};


#endif
