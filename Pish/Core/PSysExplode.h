#ifndef PSYSEXPLODE_H
#define PSYSEXPLODE_H

#include "../Core/Particles.h"

class PSysExplode : public Particles
{
    private:

    public:

        PSysExplode();
        ~PSysExplode();

        void SetNumberOfParticles(int, bool);

        void Run();
};

#endif // PSYSEXPLODE_H
