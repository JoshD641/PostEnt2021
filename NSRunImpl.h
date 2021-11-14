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

} // namespace

#endif
