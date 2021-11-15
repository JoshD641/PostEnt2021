#ifndef PostEnt2021_NSRunImpl_h
#define PostEnt2021_NSRunImpl_h

#include <fstream>

namespace PostEnt2021
{

template<typename Params, typename Data>
NSRun<Params, Data>::NSRun(int _ns_run_id, int num_particles, Tools::RNG& rng)
:ns_run_id(_ns_run_id)
,truth(rng)
,data(truth, rng)
,ns_particles(num_particles, truth)
,log_likelihoods(num_particles, data.log_likelihood(truth))
,distances_from_truth(num_particles, 0.0)
,threshold(1E300)
,iteration(0)
{

}


template<typename Params, typename Data>
int NSRun<Params, Data>::explore_posterior(int which_particle,
                                           int mcmc_steps,
                                           Tools::RNG& rng)
{
    const int& i = which_particle;
    int accepted = 0;
    for(int j=0; j<mcmc_steps; ++j)
    {
        Params proposal = ns_particles[i];
        double logh = proposal.perturb(rng);
        if(rng.rand() <= exp(logh))
        {
            double proposal_logl = data.log_likelihood(proposal);
            double proposal_dist = proposal.distance_from(truth);
            if(rng.rand() <= exp(proposal_logl - log_likelihoods[i])
                && proposal_dist < threshold)
            {
                ns_particles[i] = proposal;
                log_likelihoods[i] = proposal_logl;
                distances_from_truth[i] = proposal_dist;
                ++accepted;
            }
        }
    }
    return accepted;
}

template<typename Params, typename Data>
void NSRun<Params, Data>::explore_posterior(int mcmc_steps_per_particle,
                                            Tools::RNG& rng)
{
    std::cout << "Exploring for " << ns_particles.size() << " particles...";
    std::cout << std::flush;

    int accepted = 0;
    for(size_t i=0; i<ns_particles.size(); ++i)
        accepted += explore_posterior(i, mcmc_steps_per_particle, rng);

    std::cout << "done. Acceptance rate = " << accepted << '/';
    std::cout << (mcmc_steps_per_particle*ns_particles.size()) << '.';
    std::cout << std::endl;
}

template<typename Params, typename Data>
void NSRun<Params, Data>::do_iteration(Tools::RNG& rng)
{
    ++iteration;

    // Find worst particle
    int worst = 0;
    for(size_t i=1; i<ns_particles.size(); ++i)
    {
        if(distances_from_truth[i] > distances_from_truth[worst])
            worst = i;
    }
    threshold = distances_from_truth[worst];

    // Open output file
    auto mode = std::ios::out;
    if(iteration > 1)
        mode = mode | std::ios::app;
    std::fstream fout("output.csv", mode);

    // Header
    if(ns_run_id == 1 && iteration == 1)
        fout << "ns_run_id,iteration,depth,distance" << std::endl;

    // Output line
    fout << ns_run_id << ',';
    fout << iteration << ',' << (double)(iteration)/ns_particles.size() << ',';
    fout << distances_from_truth[worst] << std::endl;
    fout.close();

    std::cout << "(ns_run_id, iteration, depth, distance) = ";
    std::cout << '(' << ns_run_id << ", ";
    std::cout << iteration << ", " << (double)(iteration)/ns_particles.size() << ", ";
    std::cout << distances_from_truth[worst] << ")." << std::endl;

    // Replace worst particle
    int copy;
    while(true)
    {
        copy = rng.rand_int(ns_particles.size());
        if(ns_particles.size() == 1 || copy != worst)
            break;
    }

    ns_particles[worst] = ns_particles[copy];
    log_likelihoods[worst] = log_likelihoods[copy];
    distances_from_truth[worst] = distances_from_truth[copy];

    // Refresh with MCMC
    explore_posterior(worst, 1000, rng);
}


template<typename Params, typename Data>
void NSRun<Params, Data>::execute(double depth, Tools::RNG& rng)
{
    explore_posterior(10000, rng);

    int iterations = depth*ns_particles.size();
    for(int i=0; i<iterations; ++i)
        do_iteration(rng);
}


} // namespace

#endif
