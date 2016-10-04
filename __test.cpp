#include <cmath>

#include "plotter.hpp"
#include "box.hpp"

void test()
{
    Box B(0.001);
    vector3d location;
    location = vector3d(-1.3, 0, 0);
    B.push_back(Particle(location));
    location = vector3d(1.3, 0, 0);
    B.push_back(Particle(location));
    location = vector3d(-0.2, -0.4, 0);
    B.push_back(Particle(location));

    B.clear_forces();
    //B.dump();
    B.init_leapfrog();
    //B.dump();

    double e1, e2;
    std::vector< std::vector< double > > energy(3);

    for (int i = 0; i < 10000; i++)
    {
        B.move();
        e1 = B.calc_forces();
        e2 = B.calc_v();

        energy[0].push_back(e1);
        energy[1].push_back(e2);
        energy[2].push_back(e1 + e2);
    }
    show_plot(energy, std::vector< sf::Color >({sf::Color::Red, sf::Color::Green, sf::Color::Blue}));
}

