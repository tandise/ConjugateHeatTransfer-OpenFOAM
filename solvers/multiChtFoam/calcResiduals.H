    scalar Tmax=0;
    scalar Tmin=0;
    scalar Tdif=0;
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


    scalar relTempChangePrevReg = 0;
    forAll(fluidRegions,i)
    {
    	volScalarField& T=TFluid[i];	
    
    	relTempChange = ::sqrt
				(
					gSum
					(
						magSqr
						(
							(T-T.prevIter())
						)()
					)
				)/Tdif;
			   

    	

     
    	relTempChange=max
			 (
   				relTempChangePrevReg,
				relTempChange
			 );

   	relTempChangePrevReg = relTempChange;
   
     }


     Info <<"relTempChange: " << relTempChange <<"\n"<< endl;

