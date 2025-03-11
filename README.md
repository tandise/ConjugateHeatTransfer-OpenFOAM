# Conjugate Heat Transfer

This repository compares the performance of three CHT algorithms in various coupling conditions. All algorithms are written and implemented in one solver using foam-extend libraries.

## What is this repository for?

Monolithic and partitioned solvers are two approaches for solving problems in conjugate heat transfer. The main difference between these two approaches is how the interface conditions are enforced for the energy equations across sub-domains (regions). In this repository, the following contributions are made:

* The conventional monolithic solver in `foam-extend-4.0` is extended to multi-region problems; the momentum-energy coupling in the fluid regions is ensured.

* An option is added to the partitioned solver that allows for applying an additional loop for coupling the energy equation in all regions.

* Partitioned and monolithic algorithms have been unified in one solver called `multiChtFoam`.


## How do I get set up?

* Install and source `foam-extend-4.0`

* Execute the included `Allwmake` script to build the solver

* Navigate to the `tutorials` directory and use the `Allrun` script to run the tutorials. This produces the figures within the `results` directory. Alternatively, use the `Allrun` script in each case.


## Authors?
Emad Tandis;
Philip Cardiff;
Ali Ashrafizadeh

## Who do I talk to?

* Dr Emad Tandis
  email: e.tandis@aston.ac.uk
