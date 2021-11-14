#include "Binomial.h"
#include <cmath>
#include "Tools/Misc.hpp"


namespace PostEnt2021
{

namespace Examples
{

BinomialParams::BinomialParams(Tools::RNG& rng)
:theta(rng.rand())
{

}

double BinomialParams::perturb(Tools::RNG& rng)
{
    theta += rng.randh();
    Tools::wrap(theta);
    return 0.0;
}

BinomialData::BinomialData(const BinomialParams& params, Tools::RNG& rng)
{
    x = 0;
    for(int i=0; i<N; ++i)
    {
        if(rng.rand() <= params.theta)
            ++x;
    }
}

} // namespace Examples

} // namespace
