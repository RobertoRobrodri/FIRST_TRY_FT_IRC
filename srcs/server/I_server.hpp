/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   I_server.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:02:30 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/12/14 15:02:33 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		virtual void	analize_msg			(int i, data_running *run) = 0;

		//Utilities for the server
		virtual int		find_client_nick	(std::string str, data_running *run) = 0;
		virtual int 	find_client_username(std::string str, data_running *run) = 0;
		virtual int		find_client_realname(std::string str, data_running *run) = 0;
		virtual int		check_client_NICK_USER(int i) = 0;

};


#endif
