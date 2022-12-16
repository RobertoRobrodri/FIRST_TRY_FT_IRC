
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelortizdelburgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:15:25 by miguelangelortizdelburgo          #+#    #+#             */
/*   Updated: 2022/03/03 15:58:16 by miguelangelortizdelburgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <string>
#include <iostream>

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
