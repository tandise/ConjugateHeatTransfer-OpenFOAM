    scalar Tmax=0;
    scalar Tmin=0;

    forAll(fluidRegions,i)
    {
	scalar TmaxRegI=gMax(TFluid[i]);
	Tmax=max(TmaxRegI,Tmax);
	scalar TminRegI=gMin(TFluid[i]);
	Tmin=min(TminRegI,Tmin);
    }
    forAll(solidRegions,i)
    {
	scalar TmaxRegI=gMax(Tsolid[i]);
	Tmax=max(TmaxRegI,Tmax);
	scalar TminRegI=gMin(Tsolid[i]);
	Tmin=min(TminRegI,Tmin);
    }
    Tdif=Tmax-Tmin;
    if (Tdif == 0)
    {
	Tdif=1;
    }
   
    scalar patchResidualNormPrevReg = 0;

    forAll(fluidRegions,i)
    {
    	
	const polyPatchList& fluidPatches = fluidRegions[i].boundaryMesh();
	forAll(fluidPatches,patchI)
	{				
	    if (isType<solidWallMixedTemperatureCoupledFvPatchScalarField>(TFluid[i].boundaryField()[patchI]))
	    {


		scalarField& fluidPatchTemp=TFluid[i].boundaryField()[patchI];
		const scalarField& shadowField=refCast<const solidWallMixedTemperatureCoupledFvPatchScalarField>
						(TFluid[i].boundaryField()[patchI]).nbrField();
		
    		patchResidualNorm = ::sqrt
				    (
					magSqr
					(
						gSum
						(
							shadowField
						)-gSum(fluidPatchTemp)
					)/Tdif
				    );
	    }
	}
			   

    	/*if (outerCorr == 1 && innerCorr == 1)
    	{

		patchInitialResidualNorm=patchResidualNorm;
    	}*/


    	
	patchResidualNorm=max
			 (
   				patchResidualNormPrevReg,
				patchResidualNorm
			 );
	patchResidualNormPrevReg = patchResidualNorm;


     }

 

