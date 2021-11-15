#include <iostream>
#include "Examples/Binomial.h"
#include "NSRun.h"

using namespace PostEnt2021;
using namespace PostEnt2021::Examples;

int main()
{
    Tools::RNG rng;
    launch<BinomialParams, BinomialData>(rng);

    return 0;
}
