/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:15:25 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/11/09 13:34:23 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

client::client( void ) : realname_host(""), username_host(""), nick(""), op(false)
{
  return ;
}

client::client( std::string rh, std::string uh, std::string ni) : realname_host(rh), username_host(uh), nick(ni), op(false)
{
  return ;
}

client::client( const client & var ) {
  *this = var;
  std::cout << "Copy constructor called" << std::endl;

}

client::~client( void ) 
{
  return ;
}

client &client::operator=(const client &tmp)
{
  this->nick = tmp.nick;
  this->realname_host = tmp.realname_host;
  this->username_host = tmp.username_host;
  this->op = tmp.op;
  // std::cout << "Operator Client equalizer called" << std::endl;
  return (*this);
}

std::ostream &operator<<(std::ostream& os, const client &tmp)
{
	std::cout << "Operator output called" << std::endl;
	os << "Client output" << std::endl;
	os << "realname_host	|     " << tmp.getrealname_host() << std::endl;
	os << "username_host	|     " << tmp.getusername_host() << std::endl;
	os << "nickname	|     " << tmp.getnick() << std::endl;
	return (os);
}

void client::clear_Client(void)
{
  this->nick = "";
  this->realname_host = "";
  this->username_host = "";
  this->op = false;
  return ;
}
