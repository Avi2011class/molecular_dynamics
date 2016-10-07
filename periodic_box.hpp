#ifndef PBH_INCLUDED
#define PBH_INCLUDED

#include "box.hpp"

class PeriodicBox : public Box
{
private:
	double walls_size;
public:
	PeriodicBox(double size_of_box, double dt) : Box(dt)
	{
		walls_size = size_of_box;
	};
    virtual double calc_forces();
    virtual void move();
	virtual void clear_dublicates();
};

double PeriodicBox::calc_forces()
{
	clear_forces();
	double potential_energy = 0;
	for (size_t i = 1; i < size(); i++)
		for (size_t j = 0; j < i; j++) {
			vector3d rr = (*this)[i].r - (*this)[j].r;

			if (2 * rr.x > walls_size)
				rr.x -= walls_size;
			else if (2 * rr.x < -walls_size)
				rr.x += walls_size;

			if (2 * rr.y > walls_size)
				rr.y -= walls_size;
			else if (2 * rr.y < -walls_size)
				rr.y += walls_size;

			if (2 * rr.z > walls_size)
				rr.z -= walls_size;
			else if (2 * rr.z < -walls_size)
				rr.z += walls_size;

			double dist2 = rr.length_sqr();
			rr *= (6.0 / fast_pow(dist2, 4) - 12.0 / fast_pow(dist2, 7));
			(*this)[i].f -= rr; (*this)[j].f += rr;
			#ifdef FULL_ENERGY_INFO
			potential_energy += (1.0 / fast_pow(dist2, 6)) - (1.0 / fast_pow(dist2, 3));
			#endif
		}
	return potential_energy;
}

inline void PeriodicBox::move()
{
    for (Box::iterator it = begin(); it != end(); it++)
	{
		(*it).move(dt);
		if ( (*it).r.x * 2 < -walls_size )
			(*it).r.x += walls_size;
		else if ( (*it).r.x * 2 > walls_size )
			(*it).r.x -= walls_size;

		if ( (*it).r.y * 2 < -walls_size )
			(*it).r.y += walls_size;
		else if ( (*it).r.y * 2 > walls_size )
			(*it).r.y -= walls_size;

		if ( (*it).r.z * 2 < -walls_size )
			(*it).r.z += walls_size;
		else if ( (*it).r.z * 2 > walls_size )
			(*it).r.z -= walls_size;
	}
}

void PeriodicBox::clear_dublicates()
{
	for (size_t i = 0; i < size() - 1; i++)
		for (size_t j = i + 1; j < size(); j++) {
			vector3d rr = (*this)[i].r - (*this)[j].r;

			if (2 * rr.x > walls_size)
				rr.x -= walls_size;
			else if (2 * rr.x < -walls_size)
				rr.x += walls_size;

			if (2 * rr.y > walls_size)
				rr.y -= walls_size;
			else if (2 * rr.y < -walls_size)
				rr.y += walls_size;

			if (2 * rr.z > walls_size)
				rr.z -= walls_size;
			else if (2 * rr.z < -walls_size)
				rr.z += walls_size;

			if (rr.length_sqr() < 0.2) {
				(*this)[j] = (*this)[size() - 1];
				resize(size() - 1);
			}
		}
}


#endif // PBH_INCLUDED