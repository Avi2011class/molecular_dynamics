#include <cmath>
#include <thread>
#include <ctime>
#include <cstdlib>


#include "plotter.hpp"
#include "box.hpp"
#include "periodic_box.hpp"

void test()
{
	freopen("/tmp/md.log", "w", stdout);

    srand(time(0));
    PeriodicBox B(20, 0.002);
    //Box B(0.0005);

    vector3d location;

/*

    location = vector3d(0.8, 0, 0);
    B.push_back(Particle(location));
    location = vector3d(-0.8, 0, 0);
    B.push_back(Particle(location));
    location = vector3d(-1.8, 1, 0);
    B.push_back(Particle(location, vector3d(0.2, 0, 0), 1));

    location = vector3d(1.8, -1, 0);
    B.push_back(Particle(location, vector3d(-0.2, 0, 0), 1));
    location = vector3d(-0.2, -1.4, 0);
    B.push_back(Particle(location));
    location = vector3d(-1, 1, 0);
    B.push_back(Particle(location));
    location = vector3d(-1, -1, 0);
    B.push_back(Particle(location));
*/
	for (int i = 0; i < 50; i++)
	{
		location = vector3d(rand() % 20 - 10, rand() % 20 - 10, rand() % 20 - 10);
		B.push_back(Particle(location));
	}
	B.clear_dublicates();

    B.clear_forces();
    //B.dump();
    B.init_leapfrog();
    //B.dump();

    double e1, e2;
    std::vector< std::vector< double > > energy(1);

    for (int i = 0; i < 200000; i++)
    {
    	//B.dump();
        B.move();
        e1 = B.calc_forces();
        e2 = B.calc_v();
        if (i % 100 == 0)
        {
            energy[0].push_back(e2);
            //energy[1].push_back(e2);
            //energy[2].push_back(e1 + e2);
        }
		//B.dump();
    }
    show_plot(energy, std::vector< sf::Color >({sf::Color::Red, sf::Color::Green, sf::Color::Blue}));
    //*/
}

