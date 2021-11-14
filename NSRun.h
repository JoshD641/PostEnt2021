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

        // Nested Sampling particles
        std::vector<Params> ns_particles;
        std::vector<double> distances_from_truth;

    public:
        NSRun(int num_particles, Tools::RNG& rng);

};

} // namespace

#endif

#include "NSRunImpl.h"
