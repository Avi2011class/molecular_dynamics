#ifndef BOX_HPP_INCLUDED
#define BOX_HPP_INCLUDED

#include "particle.hpp"
#include "vector3d.hpp"

#define FULL_ENERGY_INFO

class Box : public std::vector< Particle >
{
private:
    double dt;

    static constexpr inline double fast_pow(double x, int n)
    {
        double result = 1;
        while(n) {
            if (n & 1) { n ^= 1; result *= x; }
            else { n >>= 1; x *= x; }
        }
        return result;
    }
public:
    Box(double dt) : dt(dt) {};

	inline void clear_forces()
	{
		for (Box::iterator it = begin(); it != end(); it++)
		{
			(it->f).x = 0;
			(it->f).y = 0;
			(it->f).z = 0;
		}
	}
	inline double calc_forces()
	{
		clear_forces();
		double potential_energy = 0;
		for (size_t i = 1; i < size(); i++)
			for (size_t j = 0; j < i; j++)
			{
			    vector3d rr = (*this)[i].r - (*this)[j].r;
                double dist2 = rr.length_sqr();
                rr *= (6.0 / fast_pow(dist2, 4) - 12.0 / fast_pow(dist2, 7));
                (*this)[i].f -= rr;
                (*this)[j].f += rr;
                #ifdef FULL_ENERGY_INFO
                potential_energy += (1.0 / fast_pow(dist2, 6)) - (1.0 / fast_pow(dist2, 3));
                #endif
			}
        return potential_energy;
    }

    inline void move()
    {
        for (Box::iterator it = begin(); it != end(); it++)
            (*it).move(dt);
    }

    inline double calc_v()
    {
        double kinetic_energy = 0;
        for (Box::iterator it = begin(); it != end(); it++)
        {
            (*it).calc_v(dt);
            #ifdef FULL_ENERGY_INFO
            kinetic_energy += (*it).v.length_sqr() * (*it).mass / 2;
            #endif
        }
        return kinetic_energy;
    }

    inline void init_leapfrog()
    {
        clear_forces();
        calc_forces();
        for (size_t i = 0; i < size(); i++)
        {
            (*this)[i].v += dt / (*this)[i].mass / 2 * (*this)[i].f;
            double coeff = dt * dt / 2 / (*this)[i].mass;

            for (size_t j = 0; j < size(); j++)
                if (i != j)
                {
                    vector3d ro = (*this)[i].r - (*this)[j].r;
                    double dist2 = ro.length_sqr();
                    (*this)[i].v += coeff * (6.0 / fast_pow(dist2, 4) - 12.0 / fast_pow(dist2, 6)) * ro;
                }

        }
    }

    void dump()
    {
        for (size_t i = 0; i < size(); i++)
        {
            std::cout << i << ": " << (*this)[i];
        }
    }

};


#endif // BOX_HPP_INCLUDED
