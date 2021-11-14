#ifndef PostEnt2021_NSRunImpl_h
#define PostEnt2021_NSRunImpl_h

namespace PostEnt2021
{

template<typename Params, typename Data>
NSRun<Params, Data>::NSRun(Tools::RNG& rng)
:truth(rng)
,data(truth, rng)
{

}

} // namespace

#endif
