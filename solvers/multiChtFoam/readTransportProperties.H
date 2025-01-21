    
    
    laminarTransport.set
    (
	i,
	new singlePhaseTransportModel 
	(
		UFluid[i],
	 	phiFluid[i]
	)
    );
    
    // Density [kg/m^3]
    rhoFluid.set
    (
	i,
	new dimensionedScalar
	(
		laminarTransport[i].lookup("rho")
	)
     );

    TRefFluid.set
    (
	i,
	new dimensionedScalar
	(
		laminarTransport[i].lookup("TRef")
	)
     );

    CpFluid.set
    (
	i,
	new dimensionedScalar
	(
		laminarTransport[i].lookup("Cp")
	)
     );

    TRefFluid.set
    (
	i,
	new dimensionedScalar
	(
		laminarTransport[i].lookup("TRef")
	)
     );

    PrFluid.set
    (
	i,
	new dimensionedScalar
	(
		laminarTransport[i].lookup("Pr")
	)
     );

    PrtFluid.set
    (
	i,
	new dimensionedScalar
	(
		laminarTransport[i].lookup("Prt")
	)
     );

    nufFluid.set
    (
	i,
	new dimensionedScalar
	(
		laminarTransport[i].lookup("nu")
	)
     );

    betaFluid.set
    (
	i,
	new dimensionedScalar
	(
		laminarTransport[i].lookup("beta")
	)
     );


