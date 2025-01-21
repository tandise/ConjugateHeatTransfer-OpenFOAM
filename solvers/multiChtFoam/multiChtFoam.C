/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     | Version:     4.0
    \\  /    A nd           | Web:         http://www.foam-extend.org
     \\/     M anipulation  | For copyright notice see file Copyright
-------------------------------------------------------------------------------
License
    This file is part of foam-extend.

    foam-extend is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    foam-extend is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

Application
    multiChtFoam

Description
    Monolithic/partitioned transient solver for buoyancy-driven turbulent flow
    of incompressible Newtonian fluids with conjugate heat transfer, complex
    heat conduction and radiation.

Authors
    Note: this solver is based heavily on chtMutiRegionSimpleFoam and
    conjugateSimpleHeatFoam from foam-extend-4.1.
    Modifications by:
    Authors of the Manuscript ID92 submitted for publication in the OpenFOAM
    Journal (to be disclosed after the double-blind peer review process)


\*---------------------------------------------------------------------------*/


#include "fvCFD.H"
#include "coupledFvMatrices.H"
#include "regionCouplePolyPatch.H"
#include "radiationModel.H"
#include "thermalModel.H"
#include "singlePhaseTransportModel.H"
#include "RASModel.H"
#include "pisoControl.H"
#include "simpleControl.H"
#include "regionProperties.H"
#include "solidWallMixedTemperatureCoupledFvPatchScalarField.H"
#include "directMappedPolyPatch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    bool monolithicEnergy=false;
#   include "setRootCase.H"
#   include "createTime.H"
    regionProperties rp(runTime);
#   include "createFluidMeshes.H"
#   include "createSolidMeshes.H"
#   include "readPISOControls.H"
#   include "createFields.H"
#   include "createSolidFields.H"
#   include "initContinuityErrs.H"
#   include "createTimeControls.H"
#   include "multiRegionCourantNo.H"
#   include "setInitialDeltaT.H"
#   include "readCouplingProperties.H"
#   include "initResiduals.H"
#   include "checkForMonolithic.H"
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (runTime.loop())
    {
        Info<< "#Time = " << runTime.timeName() << nl << endl;

	
#	include "readTimeControls.H"
#   	include "multiRegionCourantNo.H"
#       include "setDeltaT.H"


        label outerCorr=0;

	scalar initialResidualTemp=1.0; 
	scalar finalResidualTemp; 
    	scalar initialResidualPress;

	do
	{

	    initialResidualPress=0.0;
	    outerCorr++;
	    
	    Info << "Time = " << runTime.timeName()
    		<< ", iteration: " << outerCorr <<"\n"<< endl;
    	    forAll(fluidRegions,i)
	    {	

	    	if (monolithicEnergy)
		{
		    fvMesh& mesh = fluidRegions[i];
	            #include "detachPatches.H"
		}
	    	
                #include "setRegionFluidFields.H"

		#include "UEqn.H"

        	p_rgh.storePrevIter();
	        scalar initialResidualPressRegI=1.0;
        	while (piso.correct() || initialResidualPressRegI > pressureTolerance*100)
        	{
           	    #include "pEqn.H"
        	}

        	// Update turbulent quantities
        	turbulence->correct();


        	radiation.correct();

	    }
    	  
	    label nEqs=0;
	    coupledFvScalarMatrix TEqns(fluidRegions.size()+solidRegions.size());


            // Monolithic solution of energy equations
            if (monolithicEnergy)
            {
		label nEqs=0;

	    	forAll(fluidRegions,regionI)
	    	{
		    fvMesh& mesh = fluidRegions[regionI];
	            #include "attachPatches.H"
	    	}
	     	#include "fluidEnergyEqu.H"

	    	#include "solidEnergyEqu.H"

            	coupledSolverPerformance solverPerfT = TEqns.solve();

	    	initialResidualTemp = solverPerfT.initialResidual();

	    }
            // Partitioned solution of energy equations
	    else
	    {
            
	    	label innerCorr=0;
	    	do
	    	{
	            finalResidualTemp=0.0;
		    innerCorr++;	    
	            #include "fluidEnergyEqu.H"

	            #include "solidEnergyEqu.H"

		    finalResidualTemp = finalResidualTemp/(fluidRegions.size()+solidRegions.size());

		    #include "calcIntResidual.H"
		    if (innerCorr == 1)
		        initialResidualTemp = finalResidualTemp;


		}
		while
        	(
			energyLoop
		    &&
	   	      (innerCorr < maxOuterCorr)
         	    &&
		      (finalResidualTemp > energyTolerance)
              	    &&  
                      (patchResidualNorm > patchTolerance)
	    	      //(relTempChange < energyTolerance)
	         
		);
	    }

	    #include "calcResiduals.H"
            

            forAll(fluidRegions,i)
	    {
       		volScalarField& rhok=rhokFluid[i];
		rhok = 1.0 - betaFluid[i]*(TFluid[i] - TRefFluid[i]);
                rhok.correctBoundaryConditions();

	    }

	     	    
	}
    	while
        (
	   (outerCorr < maxOuterCorr)
         &&
	 ( 
	    (initialResidualPress > pressureTolerance) 
		|| 
	    (
		(initialResidualTemp > energyTolerance) && (relTempChange > energyTolerance) // energy convergence : 1) Initial residual or 2)Relative change in temperature wintin two outer iterations
	    )
	 )        
	);

        runTime.write();

        Info<< "ExecutionTime = "
            << runTime.elapsedCpuTime()
            << " s\n\n" << endl;
    }

    Info<< "End\n" << endl;

    return(0);
}


// ************************************************************************* //
