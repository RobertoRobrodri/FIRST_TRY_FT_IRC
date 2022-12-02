/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:15:25 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/11/09 13:34:23 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg.hpp"

/*###########################################
#		CANNONICAL		FUNCTIONS			#
############################################*/
msg::msg( void ) : message(""), bytes_recieved (0)
{
  return ;
}

msg::msg( std::string str ) : message(str), bytes_recieved (0)
{
  return ;
}

msg::msg( const msg & var ) 
{
  *this = var;
  return ;
}

msg::~msg( void ) {
  
  return ;

}

msg &msg::operator=(const msg &tmp)
{
  this->message = tmp.message;
  return (*this);
}

std::ostream &operator<<(std::ostream& os, const msg &tmp)
{
  os << tmp.get_message();
	return (os);
}

/*###########################################
#		PUBLIC			FUNCTIONS			#
############################################*/

int msg::recv_message(int fd)
{
  char 		buff[4096];

  this->clear_message();
  this->set_bytes_recieved(recv(fd, buff, sizeof(buff), 0));
	this->set_message(std::string(buff,this->get_bytes_recieved()));
	
	if (this->get_bytes_recieved() < 0)
	{
		std::cout << "Error recv() failed " << std::endl;
		return (0);
	}
	if (this->get_bytes_recieved() == 0)
	{
		std::cout << "Connection closed "<< std::endl;
		return (0);;
	}
  return (1);
}

int msg::send_message(int fd, std::string str)
{
  int result;

	result = send(fd, str.c_str(), str.size(), 0);
	if (result < 0)
	{
		std::cout << "Error send() failed " << std::endl;
		return (0);
	}
  return (1);
}

void msg::clear_message(void)
{
  this->message = "";
  this->bytes_recieved = 0;
  return ;
}

/*###########################################
#	INTERFACE		PROTOCOL	FUNCTIONS	#
############################################*/

void msg::welcome_client(int fd)
{
  (void)fd;
  std::cout << "Test " << std::endl;
}
