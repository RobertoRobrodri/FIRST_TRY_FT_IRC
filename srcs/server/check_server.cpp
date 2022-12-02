/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:34:45 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/12/02 18:55:54 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

bool    is_good_host(std::string host)
{
  	std::stringstream test(host);
    std::string segment;
    std::vector <int>seglist;

    while (std::getline(test,segment,'.'))
    {
      if (segment.c_str() != std::to_string(atoi(segment.c_str())))
        seglist.push_back(-1);
      else
        seglist.push_back(atoi(segment.c_str()));
    }
    if (seglist.size() != 4)
      return (0);
    for (int i = 0; i < 4; i++)
      if (seglist[i] < 0 || seglist[i] > 255)
        return (0);
    
    return (1);
}

bool    is_good_port(std::string port)
{
  int port_i;

  port_i = atoi(port.c_str());
  if (port != std::to_string(port_i))
    return(0);
  if (port_i < 6000 || port_i > 7000)
    return (0);
  return (1);
}

bool	server::check_data_correct(void) const
{

	bool base[5] = { (this->serv_data.host == "" || !is_good_host(this->serv_data.host)) 					\
					,(this->serv_data.network_pass == "")														\
					,(this->serv_data.network_port == "" || !is_good_port(this->serv_data.network_port)) 	\
					,(this->serv_data.password == "")															\
					,(this->serv_data.port == "" || !is_good_port(this->serv_data.port))};
	for (int i = 0; i < 5; i++)
		if (base[i] == true)
			return (0);
  return (1);
}