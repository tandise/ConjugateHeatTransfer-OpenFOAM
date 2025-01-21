forAll(solidRegions,i)
{
    //#include "attachPatches.H"    
    //const fvMesh& mesh = solidRegions[i];
    thermalModel& solidThermo=solidThermophysic[i];
    volScalarField& ksolid=ksolids[i];
    volScalarField& rhoCpsolid=rhoCpsolids[i]; 

   
    solidThermo.correct();
    ksolid.internalField() = solidThermo.k()().internalField();

    rhoCpsolid.oldTime();
    rhoCpsolid = solidThermo.rho()*solidThermo.C();



    
    volScalarField& Ts = Tsolid[i];
    ksolid.correctBoundaryConditions();
    // Interpolate to the faces and add thermal resistance
    surfaceScalarField ksolidf = fvc::interpolate(ksolid);
    solidThermo.modifyResistance(ksolidf);
    Ts.storePrevIter();

    fvScalarMatrix* TSolidEqn = new fvScalarMatrix
        (
            fvm::ddt(rhoCpsolid, Ts)
          - fvm::laplacian(ksolidf, Ts, "laplacian(k,T)")
          + fvm::SuSp(-solidThermo.S()/Ts, Ts)
        );


    if (!monolithicEnergy)
    {
     lduSolverPerformance solverPerfTI = TSolidEqn->solve();
     Info<<solidRegions[i].name()<<endl;
     //finalResidualTemp = max(solverPerfTI.initialResidual(),finalResidualTemp);
     
     finalResidualTemp += solverPerfTI.initialResidual();
    }
    else
    {
	TEqns.set(nEqs, TSolidEqn);
     	nEqs++;
    }
     
    
}

