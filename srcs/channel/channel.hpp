/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:35:49 by mortiz-d          #+#    #+#             */
/*   Updated: 2023/02/09 23:54:43 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../general/general.hpp"

class	channel {

	private:

	public:

		channel 			( void );
		channel 			( std::string str );
		channel 			( const channel & var );
		~channel			( void );
		channel &operator=	(const channel &tmp);
};
std::ostream &operator<<(std::ostream& os, const channel &tmp);

#endif
