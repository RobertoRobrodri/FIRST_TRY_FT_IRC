/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:06:53 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/12/14 16:45:23 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

/*###########################################
#	INTERFACE		PROTOCOL	FUNCTIONS	#
############################################*/

void server::welcome_client(int fd)
{
	std::string rp1 = "Welcome to the Network, please set up ur NICK and USER first\n";
	this->msg.send_message(fd,rp1);
	return;
}

void server::extract_NICK	(int i , std::string str , data_running *run)
{
	(void)run;
	std::vector <std::string>	line;
	int aux;

	aux = find_single_word_on_str(str , NICKNAME);
	
	line = split_in_vector(&str[aux],' ');
	if ( line.size() >= 2)
	{
		line[1].erase(line[1].find_last_not_of(" \n\r\t")+1);
		if (this->find_client_nick(line[1],run))
			this->msg.send_message(this->fds[i].fd,"Server : NICK is already taken\n");
		else			
		{
			this->clients[i].setnick(line[1]);
			this->msg.send_message(this->fds[i].fd,"Server : NICK successfully established\n");
		}			
	}
	else
	{
		// ERR_NONICKNAMEGIVEN
		this->msg.send_message(this->fds[i].fd,"Server : Not enought args to set up NICK\n");
		std::cout << "Server : Not enough args to set up NICK for client["<<i<<"]" << std::endl;
	}
	return;
}

//BASED ON  -> USER <username> <hostname> <servername> <realname> (RFC 1459)
void server::extract_USERNAME	(int i , std::string str , data_running *run)
{
	(void)run;
	std::vector <std::string>	line;
	std::vector <std::string>	line2;
	int aux;

	aux = find_single_word_on_str(str , USERNAME);
	line = split_in_vector(&str[aux],' ');
	line2 = split_in_vector(&str[aux],':');
	if ( line.size() >= 5 && line2.size() == 2)
	{
		line[1].erase(line[1].find_last_not_of(" \n\r\t")+1);
		line2[1].erase(line2[1].find_last_not_of("\n\r\t")+1);
		if (this->find_client_realname(line2[1],run) || this->find_client_username(line[1],run))
		{
			if (this->find_client_realname(line2[1],run))
				this->msg.send_message(this->fds[i].fd,"Server : USER realname is already taken \n" );
			else
				this->msg.send_message(this->fds[i].fd,"Server : USER username is already taken \n" );
		}
		else
		{
			this->clients[i].setusername_host(line[1]);
			this->clients[i].setrealname_host(line2[1]);
			this->msg.send_message(this->fds[i].fd,"Server : USER successfully established\n");
		}
	}
	else
	{
		this->msg.send_message(this->fds[i].fd,"Server : Can not set up USER bad USER format\n");
		std::cout << "Server : Could not to set up USER for client["<<i<<"]" << std::endl;
	}
		
  
  	return;
}

void server::extract_MSG	(int i , std::string str , data_running *run)
{
	(void)run;
	int aux;
	
	aux = find_single_word_on_str(this->msg.get_message() , MESSAGE);
	
		
	this->msg.set_message(clients[i].getnick() + ":" + &str[aux + 4] + "\n");
	if (this->check_client_NICK_USER(i))
		this->msg_to_all(i);
	else
	{
		this->msg.send_message(this->fds[i].fd,"Server : Set up ur NICK/USER first before sending an MSG\n");
		std::cout << "Server : client["<<i<<"] couldnt send an MSG beacuse his NICK isnt set up" << std::endl;
	}
  return;
}
