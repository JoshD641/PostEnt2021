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

    public:
        NSRun(Tools::RNG& rng);

};

} // namespace

#endif

#include "NSRunImpl.h"
