#ifndef PostEnt2021_Examples_Binomial_h
#define PostEnt2021_Examples_Binomial_h

#include "Tools/RNG.hpp"

namespace PostEnt2021
{

namespace Examples
{


//JD - my comments below are treating this class as if it's the reference implementation of an experiment, that people are meant to use as the learning example.
class BinomialParams
{
    private:
        double theta;

    public:

        // Generate from the prior
        BinomialParams(Tools::RNG& rng);

		//JD - this comment doesn't explain more than the reader already knows. What does the function edit when called, and what is the meaning of the return value?
        // Perturb in the usual way
        double perturb(Tools::RNG& rng);

        // Distance from another particle
        double distance_from(const BinomialParams& other) const;

        friend class BinomialData;

};


class BinomialData
{
    private:
        static constexpr int N = 100;
        int x; //JD - This variable name could be more descriptive

    public:

        // Generate given the parameters
        BinomialData(const BinomialParams& params, Tools::RNG& rng);

        // Evaluate log likelihood
        double log_likelihood(const BinomialParams& params) const;

};



} // namespace Examples

} // namespace

#endif
