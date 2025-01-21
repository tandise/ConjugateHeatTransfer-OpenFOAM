    Info<< "Reading field Tsolid\n" << endl;
    PtrList<volScalarField> Tsolid(solidRegions.size());
    PtrList<volScalarField> rhoCpsolids(solidRegions.size());
    PtrList<volScalarField> ksolids(solidRegions.size());
    PtrList<thermalModel> solidThermophysic(solidRegions.size());
    forAll(solidRegions, i)
    {
        Info<< "*** Reading solid mesh transport properties for region "
            << solidRegions[i].name() << nl << endl;

    	Tsolid.set
    	(
            i,
            new volScalarField
            (
                IOobject
                (
                    "T",
                    runTime.timeName(),
                    solidRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                solidRegions[i]
            )
        );

    	Info<< "Reading solid thermal properties" << endl;
    	solidThermophysic.set
    	(
		i,
		new thermalModel(Tsolid[i])
	);

    	Info<< "Reading solid diffusivity k\n" << endl;
    	ksolids.set
    	(
            i,
            new volScalarField
            (
                IOobject
                (
                    "k",
                    runTime.timeName(),
                    solidRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                solidRegions[i]
            )
        );
    	Info<< "Constructing rhoCp\n" << endl;

        rhoCpsolids.set
    	(
            i,
            new volScalarField
            (
                IOobject
        	(
            	    "rhoCpsolid",
                    runTime.timeName(),
                    solidRegions[i],
            	    IOobject::NO_READ,
                    IOobject::NO_WRITE
        	),
	        solidThermophysic[i].rho()*solidThermophysic[i].C()
    	    )
        );

    	rhoCpsolids[i].oldTime();
    }
