#include "../Core/PSysSmoke.h"

PSysSmoke::PSysSmoke()
{

}

PSysSmoke::~PSysSmoke()
{
    this->vparticles_alive.clear();
    this->vparticles_dead.clear();
    this->vparticles.clear();

    emitter = NULL;

    if( set_type->getName() == "particle_system_owned" )
        delete set_type;
    else
        set_type = NULL;
}

void PSysSmoke::SetNumberOfParticles(int number_of_particles, bool dynamic)
{
}

void PSysSmoke::Run()
{
}
