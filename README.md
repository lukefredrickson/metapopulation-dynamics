# Metapopulation Dynamics Simulation
#### Author: Luke Fredrickson

---

##What is Metapopulation Dynamics?

A metapopulation, put simply, is a population of populations. Metapopulation dynamics is an ecological concept which
deals with populations not as a single large entities, but as networks of spatially explicit discrete local
population patches which interact dynamically with one another. Metapopulations are a more realistic way of
thinking about populations in real world settings, as suitable habitats often don't occur in a vacuum -- often there
is dynamic movement between several suitable habitats located close to one another. 

A key effect of thinking about populations through the lens of metapopulation dynamics, is that populations show a
much higher level of resiliency in the metapopulation model than the traditional local population model. When a
single local patch goes extinct, be it from disease, intervention, increased predation, diminished resources, or
any other reason, that patch can be repopulated from other adjacent patches through migration -- this is called the
rescue effect.

##This Simulation

This simulation is a simple model showcasing key ideas of metapopulation dynamics -- migration between patches, and
the rescue effect. The user begins by creating the layout of local habitat patches and populating them how they
please. Once running, the simulation will step through some number of generations, simulating four seasons per
generation. Populations change locally in the winter, spring, and summer, adjusting relative to changing carrying
capacities during these seasons. In the fall, individuals from each patch migrate to other patches in the
metapopulation. In each season, there is a chance of a stochastic environmental effect occuring -- either disease or
habitat destruction. If disease occurs, each patch has a chance of going extinct, and all patches will at least
suffer some population loss. If habitat destruction occurs, a random patch (and its local population) will be removed
from the simulation.

##Parameters

To adjust parameters for the simulation, you may change the following in main.cpp (descriptions of species params can
 be found in the species.h file):
- Species R value
- Species emigration proportion
- Species migration distance modifier
- Species migrant mortality rate
- Species probable extinction population
- Window width and height
- Number of generations to simulate
- Wait time between season simulations
- Harshness of winter

And the following in simulation.cpp:
- Disease probability
- Disease extinction probability
- Patch destruction probability

##Controls

- **Left Mouse Click (and drag):** create habitat patch of desired radius
- **Up Arrow:** increase population in most recent patch
- **Down Arrow:** decrease population in most recent patch
- **DEL:** delete most recent patch
- **ENTER:** begin simulation (locks all other controls)
- **ESC:** quit simulation

##Dependencies

This simulation uses the Eigen linear algebra library (v.3.3.7). The header files are included in this repository
, but downloads for all versions can be found at [the Eigen homepage](http://eigen.tuxfamily.org).

This Simulation also uses FreeGLUT and OpenGL to perform graphics output.