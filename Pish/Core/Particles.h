#ifndef PARTICLES_H
#define PARTICLES_H

#include "../Common/amath.h"
#include "../Core/Entity.h"
#include "../Core/Sprite.h"

#include <vector>
#include <boost/progress.hpp>

using namespace vector_math;

class Particle
{
    public:

        float elapsedtime;
        float start_time;
        float life;
        float run_life;

        Vec3<float> position;
        Vec3<float> velocity;
        Vec4<float> color;

        Entity * type;
        Texture * texture;

};

class Particles : public Entity
{
    protected:

        boost::timer timer_run;
        boost::timer timer_update;

        Vec3<float> global_acceleration;

        Entity * emitter;
        Entity * set_type;

        float set_life;
        float run_time;
        float update_time;

        std::vector<Particle> vparticles;
        std::vector<Particle*> vparticles_alive;
        std::vector<Particle*> vparticles_dead;

    public:
                                ///Constructor
        Particles();
                                ///Destructor
        virtual ~Particles();

        ////////////////////////////////////////////
        //Set Particle System Looks And Attachment//
        ////////////////////////////////////////////
                                            ///Set Object That Will Be Used As An Emitter [If NULL Then The System Is Independant]
        void SetEmitter(Entity * emitter);
                                            ///Set Look Type
        void SetType(Entity * type);
                                            ///Set An Internal Look Type
        void SetType(int type);
                                            ///Set A Range Were The Types May Be Different [Not Implemented and may not be]
        void SetTypeRange(int r0, int r1, Entity * type);

        ///////////////////////////////
        //Set Particle System Options//
        ///////////////////////////////
                                                                ///Set Whole Particle System Run Time
        void SetRunTime(float seconds = 1.0f);
                                                                ///Set Number Of Particles
        virtual void SetNumberOfParticles(int number_of_particles, bool dynamic = false);
                                                                ///Set Life Os Particles
        void SetLife(float life);
                                                                ///Set A Global Gravity Control
        void SetGlobalAcceleration(Vec3<float> acceleration);

        ///////////////////////
        //Run Particle System//
        ///////////////////////
                            ///Run Particle System
        virtual void Run();
};

#endif // PARTICLES_H
