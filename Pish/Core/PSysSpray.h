#ifndef PSYSSPRAY_H
#define PSYSSPRAY_H

#include "../Core/Particles.h"

class PSysSpray : public Particles
{
    private:

        float spray_deviation;

    public:

        PSysSpray();
        ~PSysSpray();

        void SetNumberOfParticles(int number_of_particles, bool dynamic = false);

        void SetDirection(Vec3<float> direction = Vec3<float>(0.5,0.5,0.0));
        void AngleDeviation(float angle_in_degrees);

        void Run();
};

#endif // PSYSSPRAY_H
