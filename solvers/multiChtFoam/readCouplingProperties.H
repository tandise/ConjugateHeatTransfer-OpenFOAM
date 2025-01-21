    
    Info << "\nReading coupling properties" << endl;
    IOdictionary couplingProperties
    (
        IOobject
        (
            "couplingProperties",
            runTime.constant(),
            runTime.db(),
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    );

scalar energyTolerance
(
    readScalar(couplingProperties.lookup("energyTolerance"))
);

scalar pressureTolerance
(
    couplingProperties.lookupOrDefault("pressureTolerance",1e-3)
);

scalar maxOuterCorr
(
    readScalar(couplingProperties.lookup("maxOuterCorr"))
);

#if (!energyMonolithic)
    scalar patchTolerance
    (
    	couplingProperties.lookupOrDefault("patchTolerance",1e-6)
    );

Switch energyLoop(couplingProperties.lookupOrDefault("energyLoop",true));
#endif
