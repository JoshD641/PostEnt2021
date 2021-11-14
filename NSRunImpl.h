#ifndef PostEnt2021_NSRunImpl_h
#define PostEnt2021_NSRunImpl_h

namespace PostEnt2021
{

template<typename Params, typename Data>
NSRun<Params, Data>::NSRun(int num_particles, Tools::RNG& rng)
:truth(rng)
,data(truth, rng)
,ns_particles(num_particles, truth)
,log_likelihoods(num_particles, data.log_likelihood(truth))
,distances_from_truth(num_particles, 0.0)
{

}

template<typename Params, typename Data>
void NSRun<Params, Data>::explore_posterior(int mcmc_steps_per_particle,
                                            Tools::RNG& rng)
{
    std::cout << "Exploring for " << ns_particles.size() << " particles...";
    std::cout << std::flush;

    int accepted = 0;
    for(size_t i=0; i<ns_particles.size(); ++i)
    {
        for(int j=0; j<mcmc_steps_per_particle; ++j)
        {
            Params proposal = ns_particles[i];
            double logh = proposal.perturb(rng);
            if(rng.rand() <= exp(logh))
            {
                double proposal_logl = data.log_likelihood(proposal);
                if(rng.rand() <= exp(proposal_logl - log_likelihoods[i]))
                {
                    ns_particles[i] = proposal;
                    log_likelihoods[i] = proposal_logl;
                    ++accepted;
                }
            }
        }

        distances_from_truth[i] = ns_particles[i].distance_from(truth);
    }

    std::cout << "done. Acceptance rate = " << accepted << '/';
    std::cout << (mcmc_steps_per_particle*ns_particles.size()) << '.';
    std::cout << std::endl;
}

} // namespace

#endif
