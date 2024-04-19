#include "stdafx.h"

// Criterion
double FCT(double K[])
{	
	// Time parameters
	double TF,DT,TIME,T0;
	// Cost function	
	double J,J1,J2,J3,J4; 
	// State vector
	double vX[16]={0.0}; 
	// Control vector
	double vU[16]={0.0};
	// PID coeff
	double q[5]={0.0};
	// error
	double err[3]={0.0};
	// Control vectors
	double U[3]={0.0};			//calculated by PID
	// auxl
	double TET0=0.0, TET=0.0, Wd=0.0,W=0.0, DW=0.0;
	double Xnew=0.0, Unew=0.0;
	// count
	static int count=0;
	
	// Initialization	
	TF=10.0;
	// reset time and cost function
	TIME=0.0;
	J=0.0;J1=0.0;J2=0.0;J3=0.0;J4=0.0;
	//command
	TET0=XDES;
	// current PID coeff and T0
	T0=K[0];
	kx=K[1];
	kP=K[2];
	kI=K[3];
	kD=K[4];
	DIGPIDCOEFF1(q,kP,kI,kD,TAU);
	// modeling loop
	//моделирование системы
	do
	{	
		//one step integration
		Xnew=FXDIG(noh,nd,vX,vU,a,b);
		vers_(Xnew, vX, 16);
		TIME+=TAU;
		//control with current PID coeff 		
		TET=TET+vX[1]*TAU;
		W=vX[0];
		DW=(vX[0]-vX[1])/TAU;
		//П-регулятор
		Wd=PREGULATOR(TET0-TET,kx,W,DW);
		//Рассогласование омеги
		GETERR(Wd,W,err);
		//ПИД-регулятор
		PID_DIGITAL(q,err,U,vU);

		//constraint on overshoot before T0 (desired settle time)
		/*if (TIME<=T0)		
		{
			J1=J1+1.E-2*pow(TET/TET0,2);
		}*/
		// constraint on energy
		//Органичение на энергию
		J2=J2+1.E-2*pow(U[0]/UMAX,2.0);			
		// integral error
		if (TIME>T0)
		{	
			// integral error rate
			J3=J3+1.0E00*pow((TET0-TET)*57.3,2.0)+1.E00*pow((Wd-W)*57.3,2.0);		
			// integral error accel
			J4=J4+1.0E-3*pow(DW*57.3,2.0);
		}
		J=J1+J2+J3+J4;
		// if J->inf
		if (J!=J)
			J=1.E+9;
	}while (TIME<TF);
	J=J*TAU+1.E00*T0*T0;
	count++;
	//print		
	printf("n= %i T0=%f kx=%f kP= %f kI=%f kD=%f F=%f\n",count,T0,kx,kP,kI,kD,J);
	//printf("					J:J1=%f J2=%f J3=%f J4=%f J5=%f\n",J1,J2,J3,J4,J5);

	fprintf(fJ,"%i %f %f %f %f %f %f\n",count,T0,kx,kP,kI,kD,J);
	
	return J;
}