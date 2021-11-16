#ifndef PostEnt2021_NSRun_h
#define PostEnt2021_NSRun_h

namespace PostEnt2021
{

template<typename Params, typename Data>
class NSRun
{
    private:
        const int ns_run_id;
        Params truth;//JD - I don't understand the reasoning behind calling this variable truth from reading the code, so it probably needs an explanation
        Data data;

        // Nested Sampling particles and associated quantities
        std::vector<Params> particles;
        std::vector<double> log_likelihoods;
        std::vector<double> distances_from_truth;

        // Distance threshold for NS
        double threshold; 

        // Iteration
        int iteration;

		//JD - this function name (and comment) explains what the function is about, but not what it achieves - e.g what does the int that is returned mean?
        // Explore for a single particle
        int explore_posterior(int which_particle,
                              Tools::RNG& rng);

		//JD - similarly to above, what does calling this function achieve? It's hard to tell from the name.
		//JD - Also, overloading the name "explore_posterior" like this suggests to me that this function achieves the same effect as the function above (on/with different inputs), which is not the case.
        // Explore for all particles (to move away from truth initially)
        void explore_posterior(Tools::RNG& rng);

        // Do one NS iteration
        void do_iteration(Tools::RNG& rng);

    public:
        NSRun(int _ns_run_id, Tools::RNG& rng);
        void execute(Tools::RNG& rng);
};

// Entry point for multiple NS Runs
void launch(Tools::RNG& rng);

} // namespace

#endif

#include "NSRunImpl.h"
