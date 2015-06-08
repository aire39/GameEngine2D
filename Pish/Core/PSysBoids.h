#ifndef PSYSBOIDS_H
#define PSYSBOIDS_H

/**
Not Implemented Yet!
*/

#include "../Core/Particles.h"

class PSysBoids : public Particles
{
    private:

    public:

        PSysBoids();
        ~PSysBoids();

        void SetNumberOfParticles(int number_of_particles, bool dynamic = false);
        void Run();
};

#endif // PSYSBOIDS_H
