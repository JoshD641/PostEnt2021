PostEnt2021
===========

(c) 2021 Brendon J. Brewer. LICENCE: GNU GPL v3.

Usage
=====

```
git clone --recursive https://github.com/eggplantbren/PostEnt2021
cd PostEnt2021
make
./main
R
source("showresults.R")
```

Example Output from showresults.R
=================================

```
depth = 6.4335 nats.
H(theta | d) = 2.083693 +- 0.167323 nats.
```

Edit `Constants.h` and recompile to change the numerical parameters.
To implement different models, use the same implied structure as the Binomial
example. If you have a different number of cared-about parameters
or if you need to edit the distance threshold, those are in `showresults.R`.
