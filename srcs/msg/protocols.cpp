/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocols.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:06:53 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/12/06 19:14:21 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg.hpp"

/*###########################################
#	INTERFACE		PROTOCOL	FUNCTIONS	#
############################################*/

void msg::welcome_client(int fd)
{
  // client  c;
  // std::vector <std::string>	lines;
  // std::vector <std::string>	nick_line;
  // std::vector <std::string>	user_line;
  // std::vector <std::string>	real_user_line;
  
  // this->recv_message(fd);
  // try
  // {
  //   // std::cout << "client welcomed -> "<< this->get_message() << std::endl;
  //   lines = split_in_vector(this->get_message(),'\n');
  //   nick_line = split_in_vector(lines[1],' ');
  //   real_user_line = split_in_vector(lines[2],':');
  //   user_line = split_in_vector(real_user_line[0],' ');
  //   c = client(real_user_line[1],user_line[1],nick_line[1]);
  //   // std::cout << c << std::endl << " is welcomed " << std::endl;
  //   std::cout << c.getnick() << " is welcomed " << std::endl;
  // }
  // catch(const std::exception& e)
  // {
  //   std::cout << "ERROR GETTING CLIENT DATA "<< std::endl;
  //   return (client());
  // }

  //"<client> :Welcome to the <networkname> Network, <nick>[!<user>@<host>]"
  //"<client> :Your host is <servername>, running version <version>"
  //"<client> :This server was created <datetime>"
  //"<client> <servername> <version> <available user modes> <available channel modes> [<channel modes with a parameter>]"
  //"<client> <1-13 tokens> :are supported by this server"
  std::string rp1 = "Welcome to the Network, please set up ur NICK and USER first\n";
  this->send_message(fd,rp1);
  return;
}
