#ifndef PSYSSMOKE_H
#define PSYSSMOKE_H

/**
Not Finished With Implementation!
*/

#include "../Core/Particles.h"

class PSysSmoke : public Particles
{
    private:

    public:

        PSysSmoke();
        ~PSysSmoke();

        void SetNumberOfParticles(int number_of_particles, bool dynamic = false);
        void Run();
};

#endif // PSYSSMOKE_H
