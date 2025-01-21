    const fvMesh& mesh = fluidRegions[i];
    volScalarField rhok
		   (
			IOobject
    		        (
    		        	"rhok",
    		        	runTime.timeName(),
    		        	fluidRegions[i]
            		),
            		rhokFluid[i]
		   );
    volVectorField& U = UFluid[i];
    surfaceScalarField& phi = phiFluid[i];
    const surfaceScalarField& ghf = ghfFluid[i];

    incompressible::RASModel *turbulence = &turbulenceFluid[i];
    radiation::radiationModel& radiation=radiationFluid[i];
    volScalarField& p_rgh = p_rghFluid[i];
    volScalarField& T = TFluid[i];
    pisoControl& piso=pisoFluid[i];
    scalar sumLocalContErr=sumLocalContErrFluid[i];
    scalar globalContErr=globalContErrFluid[i];
    scalar cumulativeContErr=cumulativeContErrFluid[i];
    T.storePrevIter();




