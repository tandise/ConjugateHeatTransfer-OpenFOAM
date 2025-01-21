  // Initialise fluid field pointer lists
    PtrList<IOdictionary> transportProperties(fluidRegions.size());
    PtrList<volScalarField> TFluid(fluidRegions.size());
    PtrList<volScalarField> p_rghFluid(fluidRegions.size());
    PtrList<volScalarField> ghFluid(fluidRegions.size());
    PtrList<surfaceScalarField> ghfFluid(fluidRegions.size());
    PtrList<volScalarField> kappaFluid(fluidRegions.size());
    PtrList<volScalarField> rhokFluid(fluidRegions.size());

    PtrList<volVectorField> UFluid(fluidRegions.size());

    PtrList<surfaceScalarField> phiFluid(fluidRegions.size());
    PtrList<uniformDimensionedVectorField> gFluid(fluidRegions.size());
    PtrList<incompressible::RASModel> turbulenceFluid(fluidRegions.size());
    PtrList<radiation::radiationModel> radiationFluid(fluidRegions.size());


    PtrList<singlePhaseTransportModel> laminarTransport(fluidRegions.size());
    PtrList<dimensionedScalar> rhoFluid(fluidRegions.size());
    PtrList<dimensionedScalar> CpFluid(fluidRegions.size());    
    PtrList<dimensionedScalar> betaFluid(fluidRegions.size());    
    PtrList<dimensionedScalar> TRefFluid(fluidRegions.size());    
    PtrList<dimensionedScalar> PrFluid(fluidRegions.size());    
    PtrList<dimensionedScalar> PrtFluid(fluidRegions.size());    
    PtrList<dimensionedScalar> nufFluid(fluidRegions.size()); 
           




    Info<< "Reading transportProperties\n" << endl;
 
    forAll(fluidRegions, i)
    {
        Info<< "*** Reading fluid mesh transport properties for region "
            << fluidRegions[i].name() << nl << endl;

    	transportProperties.set
    	(
	    i,
	    new IOdictionary
	    ( 
            	IOobject
            	(
            	    "transportProperties",
            	    runTime.constant(),
            	    fluidRegions[i],
            	    IOobject::MUST_READ,
            	    IOobject::NO_WRITE
        	)
	    )
        );

	gFluid.set
        (
            i,
            new uniformDimensionedVectorField
            (
                IOobject
                (
                    "g",
                    runTime.constant(),
                    fluidRegions[i],
                    IOobject::MUST_READ,
                    IOobject::NO_WRITE
                )
            )
        );

    	Info<< "Calculating field g.h\n" << endl;
    	ghFluid.set
    	(
	     i,
	     new volScalarField
	     (
		"gh",
		 gFluid[i] & fluidRegions[i].C()
	     )
	);

    	ghfFluid.set
    	(
	     i,
	     new surfaceScalarField
	     (
		"gh",
		 gFluid[i] & fluidRegions[i].Cf()
	     )
	);
	

    	Info<< "Reading field p_rgh\n" << endl;
  
    
    	p_rghFluid.set
    	(
            i,
            new volScalarField
            (
                IOobject
                (
                    "p_rgh",
                    runTime.timeName(),
                    fluidRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                fluidRegions[i]
            )
        );

    	Info<< "Reading field U\n" << endl;


    	UFluid.set
    	(
            i,
            new volVectorField
            (
                IOobject
                (
                    "U",
                    runTime.timeName(),
                    fluidRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                fluidRegions[i]
            )
        );
    

    	Info<< "Reading field T\n" << endl;
    	TFluid.set
    	(
            i,
            new volScalarField
            (
                IOobject
                (
                    "T",
                    runTime.timeName(),
                    fluidRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                fluidRegions[i]
            )
        );
        Info<< "    Adding to phiFluid\n" << endl;
        phiFluid.set
        (
            i,
            new surfaceScalarField
            (
                IOobject
                (
                    "phi",
                    runTime.timeName(),
                    fluidRegions[i],
                    IOobject::READ_IF_PRESENT,
                    IOobject::AUTO_WRITE
                ),
                linearInterpolate(UFluid[i])
                    & fluidRegions[i].Sf()
            )
        );

#   	include "readTransportProperties.H"

    	label pRefCell = 0;
    	scalar pRefValue = 0.0;
    	setRefCell(p_rghFluid[i], pisoFluid[i].dict(), pRefCell, pRefValue);
    	fluidRegions[i].schemesDict().setFluxRequired(p_rghFluid[i].name());

    	turbulenceFluid.set
    	(
		i,
		incompressible::RASModel::New(UFluid[i], phiFluid[i], laminarTransport[i])
    	);
       

    	Info<< "Reading field kappaEff\n" << endl;
    	kappaFluid.set
    	(
            i,
            new volScalarField
            (
                IOobject
                (
                    "kappaEff",
                    runTime.timeName(),
                    fluidRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                fluidRegions[i]
            )
        );

    	// Kinematic density for buoyancy force
    	rhokFluid.set
    	(
		i,
		new volScalarField
		(
    		        IOobject
    		        (
    		        	"rhok",
    		        	runTime.timeName(),
    		        	fluidRegions[i]
            		),
            		1.0 - betaFluid[i]*(TFluid[i] - TRefFluid[i])
    		)
     	);

    	Info<< "Creating radiation model\n" << endl;
    	radiationFluid.set
    	(
		i,
        	radiation::radiationModel::New(TFluid[i])
    	);
    }
    
    

    label pRefCell = 0;
    scalar pRefValue = 0.0;
