#include "../Core/PSysSpray.h"

PSysSpray::PSysSpray()
{
    set_life = 1.0f;

    emitter = NULL;
    set_type = NULL;

    update_time = 1.0f/60.0f;
    run_time = 5.0f;

    global_acceleration = Vec3<float>(0.0f, -0.98f, 0.0f);

    spray_deviation = 15.0f;
}

PSysSpray::~PSysSpray()
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

void PSysSpray::SetNumberOfParticles(int number_of_particles, bool dynamic)
{
    if( !dynamic )
    {
        vparticles.reserve( number_of_particles );
        srand(time(NULL));

        for(int i=0; i<number_of_particles; i++)
        {
            float tmp0 = vector_math::RandomFloat(0, 1000) * Degree2Radian(spray_deviation);
            float tmp1 = vector_math::RandomFloat(0, 1000) * Degree2Radian(spray_deviation);

            Particle _particle;

            if(emitter != NULL)
                _particle.position = emitter->getPosition();
            else
                _particle.position = position;

            _particle.start_time = vector_math::RandomFloat(0, 1000);
            _particle.life = set_life * vector_math::RandomFloat(0, 1000);
            _particle.run_life = _particle.life;
            _particle.type = set_type;
            _particle.velocity = Vec3<float>(0.5f+tmp0, 0.5f+tmp1, 0.0f);
            _particle.elapsedtime = 0.0f;

            if( emitter != NULL )
                _particle.position = emitter->getPosition();

            vparticles.push_back(_particle);
        }
    }

    else
        vparticles.resize(number_of_particles);
}

void PSysSpray::SetDirection(Vec3<float> direction)
{
    for(int i=0; i<(int)vparticles.size(); i++)
        vparticles[i].velocity = direction;
}

void PSysSpray::AngleDeviation(float angle_in_degrees)
{
    spray_deviation = angle_in_degrees;
}

void PSysSpray::Run()
{
    if(emitter != NULL)
    {
        if( (timer_run.elapsed() <= run_time) || (run_time == -1) )
        {
            if( timer_update.elapsed() > update_time )
            {
                timer_update.restart();
                vparticles_alive.clear();
                vparticles_dead.clear();

                for(int i=0; i<(int)vparticles.size(); i++)
                {

                    if( vparticles[i].run_life > 0 )
                        vparticles_alive.push_back(&vparticles[i]);
                    else
                        vparticles_dead.push_back(&vparticles[i]);

                }

                for(int i=0; i<(int)vparticles_alive.size(); i++)
                {
                    if( timer_run.elapsed() >= vparticles_alive[i]->start_time )
                    {
                        vparticles[i].run_life -= update_time;
                        vparticles[i].elapsedtime += update_time;
                        vparticles_alive[i]->position += (vparticles_alive[i]->velocity*vparticles_alive[i]->elapsedtime) + (global_acceleration*vparticles_alive[i]->elapsedtime*vparticles_alive[i]->elapsedtime);
                    }
                }

                for(int i=0; i<(int)vparticles_dead.size(); i++)
                {
                    float tmp0 = vector_math::RandomFloat(0, 1000) * Degree2Radian(spray_deviation);
                    float tmp1 = vector_math::RandomFloat(0, 1000) * Degree2Radian(spray_deviation);

                    vparticles_dead[i]->run_life = vparticles_dead[i]->life;
                    vparticles_dead[i]->velocity = Vec3<float>(0.5f+tmp0, 0.5f+tmp1, 0.0);
                    vparticles_dead[i]->position = emitter->getPosition();
                    vparticles_dead[i]->elapsedtime = 0.0f;
                }

            }


        }
        else
        {
            for(int i=0; i<(int)vparticles.size(); i++)
            {
                float tmp0 = vector_math::RandomFloat(0, 1000) * Degree2Radian(spray_deviation);
                float tmp1 = vector_math::RandomFloat(0, 1000) * Degree2Radian(spray_deviation);

                vparticles[i].position = emitter->getPosition();
                vparticles[i].run_life = set_life * vector_math::RandomFloat(0, 1000);
                vparticles[i].velocity = Vec3<float>(0.5f*tmp0, 0.5f*tmp1, 0.0);
                vparticles[i].elapsedtime = 0.0f;
            }


            timer_run.restart();
        }

    }
    else
    {
        if( (timer_run.elapsed() <= run_time) || (run_time == -1) )
        {
            if( timer_update.elapsed() > update_time )
            {
                timer_update.restart();
                vparticles_alive.clear();
                vparticles_dead.clear();

                for(int i=0; i<(int)vparticles.size(); i++)
                {

                    if( vparticles[i].run_life > 0 )
                        vparticles_alive.push_back(&vparticles[i]);
                    else
                        vparticles_dead.push_back(&vparticles[i]);

                }

                for(int i=0; i<(int)vparticles_alive.size(); i++)
                {
                    if( timer_run.elapsed() >= vparticles_alive[i]->start_time )
                    {
                        vparticles[i].run_life -= update_time;
                        vparticles[i].elapsedtime += update_time;
                        vparticles_alive[i]->position += (vparticles_alive[i]->velocity*vparticles_alive[i]->elapsedtime) + (global_acceleration*vparticles_alive[i]->elapsedtime*vparticles_alive[i]->elapsedtime);
                    }
                }

                for(int i=0; i<(int)vparticles_dead.size(); i++)
                {
                    vparticles_dead[i]->run_life = vparticles_dead[i]->life;
                    vparticles_dead[i]->velocity = Vec3<float>(0.5f, 0.5f, 0.0);
                    vparticles_dead[i]->position = position;
                    vparticles_dead[i]->elapsedtime = 0.0f;
                }

            }


        }
        else
        {
            for(int i=0; i<(int)vparticles.size(); i++)
            {
                vparticles[i].position = position;
                vparticles[i].run_life = set_life * vector_math::RandomFloat(0, 1000);
                vparticles[i].velocity = Vec3<float>(0.5f, 0.5f, 0.0);
                vparticles[i].elapsedtime = 0.0f;
            }


            timer_run.restart();
        }

    }

        if( (timer_run.elapsed() < run_time) || (run_time < 0) )
            for(int i=0; i<(int)vparticles_alive.size(); i++)
            {
                vparticles_alive[i]->type->setPosition( vparticles[i].position );
                vparticles_alive[i]->type->draw();
            }
}
