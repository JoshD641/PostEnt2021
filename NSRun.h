#ifndef PostEnt2021_NSRun_h
#define PostEnt2021_NSRun_h

namespace PostEnt2021
{

template<typename Params, typename Data>
class NSRun
{
    private:
        Params truth;
        Data data;

        // Nested Sampling particles and associated quantities
        std::vector<Params> ns_particles;
        std::vector<double> log_likelihoods;
        std::vector<double> distances_from_truth;

        // Distance threshold for NS
        double threshold;

        // Explore for a single particle
        int explore_posterior(int which_particle, int mcmc_steps, Tools::RNG& rng);


    public:
        NSRun(int num_particles, Tools::RNG& rng);

        void explore_posterior(int mcmc_steps_per_particle, Tools::RNG& rng);
};

} // namespace

#endif

#include "NSRunImpl.h"
