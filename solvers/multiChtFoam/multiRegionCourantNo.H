    scalar CoNum = -GREAT;
    forAll(fluidRegions, i)
    {
        const fvMesh& mesh = fluidRegions[i];
    	surfaceScalarField& phi = phiFluid[i];
	scalar CoNumI = 0.0;
	if (mesh.nInternalFaces())
	{
   	 	surfaceScalarField magPhi = mag(phi);

    	 	surfaceScalarField SfUfbyDelta =
        	mesh.surfaceInterpolation::deltaCoeffs()*magPhi;
    		const scalar deltaT = runTime.deltaT().value();
    		CoNumI = max(SfUfbyDelta/mesh.magSf()).value()*deltaT;

	}
        CoNum = max
        (
            CoNum,
            CoNumI
        );
    }
    Info<< "Courant Number: " << CoNum     << endl;

