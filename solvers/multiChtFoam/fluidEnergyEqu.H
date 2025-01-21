forAll(fluidRegions,i)
{    

    dimensionedScalar& rho = rhoFluid[i];
    dimensionedScalar& Cp = CpFluid[i];
    dimensionedScalar& Pr = PrFluid[i];
    dimensionedScalar& Prt = PrtFluid[i];

    volScalarField& kappaEff = kappaFluid[i];

    surfaceScalarField& phi = phiFluid[i];


    incompressible::RASModel& turbulence = turbulenceFluid[i];
    radiation::radiationModel& radiation=radiationFluid[i];
    volScalarField& T = TFluid[i];

    kappaEff.internalField() = rho.value()*Cp.value()*(turbulence.nu().internalField()/Pr.value() + turbulence.nut()().internalField()/Prt.value());
    kappaEff.correctBoundaryConditions();


    fvScalarMatrix* TFluidEqn = new fvScalarMatrix
    (
            rho*Cp*
            (
                fvm::ddt(T)
              + fvm::div(phi, T)
            )
          - fvm::laplacian(kappaEff, T)
         ==
            radiation.Ru()
          - fvm::Sp(4.0*radiation.Rp()*pow3(T), T)
          + 3.0*radiation.Rp()*pow4(T)
    );

    

    if (!monolithicEnergy)
    {
	lduSolverPerformance solverPerfTI = TFluidEqn->solve();

    	finalResidualTemp += solverPerfTI.initialResidual();
    }
    else
    {
	TEqns.set(nEqs, TFluidEqn);
        nEqs++;
    }    

}

