#ifndef PostEnt2021_Examples_Binomial_h
#define PostEnt2021_Examples_Binomial_h

#include "Tools/RNG.hpp"

namespace PostEnt2021
{

namespace Examples
{

class BinomialParams
{
    private:
        double theta;

    public:

        // Generate from the prior
        BinomialParams(Tools::RNG& rng);

        // Perturb in the usual way
        double perturb(Tools::RNG& rng);

        friend class BinomialData;

};


class BinomialData
{
    private:
        static constexpr int N = 100;
        int x;

    public:

        // Generate given the parameters
        BinomialData(const BinomialParams& params, Tools::RNG& rng);

};



} // namespace Examples

} // namespace

#endif
