
#include "ParticleSystem.hpp"

RainSystem::RainSystem()
{
    for (int i = 0; i < N_PARTICLES; i++)
    {
        particles[i] = sParticle();
    }
    
}

void RainSystem::Render(const Camera &cam)
{
    (void)cam;
}

void RainSystem::Update(GlobalData &gData)
{
    (void)gData;

    for (int i = 0; i < N_PARTICLES; i++)
    {
        sParticle * p = &particles[i];

        p->X += 1;
		p->Y += 2;
		p->ttl++; // increase lifetime

		// Reset position once they reach the limit
        // TO DO

    }
}