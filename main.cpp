#include <iostream>
#include "Examples/Binomial.h"
#include "NSRun.h"

using namespace PostEnt2021;
using namespace PostEnt2021::Examples;

int main()
{
    Tools::RNG rng;

    for(int ns_run_id=1; ns_run_id <= 100; ++ns_run_id)
    {
        NSRun<BinomialParams, BinomialData> ns_run(ns_run_id, 100, rng);
        ns_run.execute(30.0, rng);
    }

    return 0;
}
