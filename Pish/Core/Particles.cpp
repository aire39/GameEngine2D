#include "../Core/Particles.h"
#include <iostream>

Particles::Particles()
{
    set_life = 10.0f;

    emitter = NULL;
    set_type = NULL;

    update_time = 1/60.0;
    run_time = 10.0;

    global_acceleration = 0;
    position = 0;
}

Particles::~Particles()
{
    emitter = NULL;
    vparticles.clear();

    if( set_type->getName() == "particle_system_owned" )
        delete set_type;
    else
        set_type = NULL;
}

void Particles::SetEmitter(Entity * emitter)
{
    this->emitter = emitter;

    for(int i=0; i<(int)vparticles.size(); i++)
        vparticles[i].position = emitter->getPosition();
}

void Particles::SetRunTime(float seconds)
{
    run_time = seconds;
}

void Particles::SetNumberOfParticles(int number_of_particles, bool dynamic)
{
    if( !dynamic )
    {
        vparticles.reserve( number_of_particles );
        srand(time(NULL));

        for(int i=0; i<number_of_particles; i++)
        {
            Particle _particle;
            _particle.start_time = vector_math::RandomFloat(0, 1000);
            _particle.life = set_life * vector_math::RandomFloat(0, 1000);
            _particle.run_life = _particle.life;
            _particle.type = set_type;
            _particle.velocity = vector_math::RandomVector2D(1000, 0.1);
            _particle.elapsedtime = 0.0f;

            if( emitter != NULL )
                _particle.position = emitter->getPosition();

            vparticles.push_back(_particle);
        }
    }

    else
        vparticles.resize(number_of_particles);
}

void Particles::SetLife(float life)
{
    set_life = life;
}

void Particles::SetType(Entity * type)
{
    if( set_type != NULL )
    {
        if( set_type->getName() == "particle_system_owned" )
            delete set_type;
        else
            set_type = type;
    }
    else
        set_type = type;
}

void Particles::SetType(int type)
{
    if( set_type != NULL )
    {
        if( set_type->getName() == "particle_system_owned" )
            delete set_type;
        else
            set_type = NULL;
    }


    switch(type)
    {
        case 0:
        {
            Entity * empty = new Entity();
            empty->init();
            empty->setName("particle_system_owned");
            set_type = empty;
        }
        break;

        case 1:
        {
            Sprite * sprite = new Sprite();
            sprite->init();
            sprite->setName("particle_system_owned");
            set_type = sprite;

        }
        break;

        default:
        {
            Sprite * sprite = new Sprite();
            sprite->init();
            sprite->setName("particle_system_owned");
            set_type = sprite;
        }
        break;
    }

    for(int i=0; i<(int)vparticles.size(); i++)
        vparticles[i].type = set_type;

}

void Particles::SetTypeRange(int r0, int r1, Entity * type)
{
}

void Particles::SetGlobalAcceleration(Vec3<float> acceleration)
{
    global_acceleration = acceleration;
}

void Particles::Run()
{
}
