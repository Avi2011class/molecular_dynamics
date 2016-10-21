#ifndef TEMHPP_INCLUDED
#define TEMHPP_INCLUDED

#include "box.hpp"

class Thermostat
{
public:
	double current_themperature, default_themperature;

	Thermostat(double t) : default_themperature(t) {};
	double calc_themparature( Box & B )
	{
		double energy = 0;
		for (Box::iterator it = B.begin(), it != B.end(); it++)
			energy += (it->v).length_sqr() * (it->mass) / 2;
	}
};


#endif // TEMPERATURE_HPP_INCLUDED
