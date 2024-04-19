#include "stdafx.h"

// Variables
int N=0,M=0;
double TIME=0.0,DT=0.0;

void MODELING(double K[])
{
	//file to write
	FILE *fOUT;	
	fOUT=fopen(".\\RESULT\\OUT.ris","w");		

	// Simulation time
	double TMODEL=5.E00;

	// State vector
	double vX[16]={0.0}; 
	// Control vector
	double vU[16]={0.0};
	// Control vectors
	double U[3]={0.0};			//calculated by PID
	double U_out[20]={0.0};		//output from PID (through saturation)
	double Ur[20]={0.0};		//input to plant (real control signal)
	double q[5]={0.0};			
	double err[3]={0.0};
	double TET0=0.0,TET=0.0,Wd=0.0,W=0.0, DW=0.0;
	double Xnew=0.0;
	int count=0;
	double T1,W0,kW0;
	//PID coeff
	kx=K[1];
	kP=K[2];
	kI=K[3];
	kD=K[4];

	//DIGPIDCOEFF(q,kP,kI,kD);;
	DIGPIDCOEFF1(q,kP,kI,kD,TAU);
	// format: fprintf(fOUT,"U1 U2 ...Um X0 X1 X2 ... Xn");
	fprintf(fOUT,"U Ur TET0 TET W0 W DW");	
	
	// Modeling loop
	do
	{			
		TET0=XDES;
		//print to file
		fprintf(fOUT,"\n%f ",TIME);		//time
		fprintf(fOUT,"%f %f %f %f %f %f %f",U[0],vU[0],TET0*57.3, TET*57.3,Wd*57.3, W*57.3, DW*57.3);	//control
		
		//one step integration
		Xnew=FXDIG(noh,nd,vX,vU,a,b);
		vers_(Xnew, vX, 16);
		TIME+=TAU;
		
		//control with current PID coeff		
		TET=TET+vX[1]*TAU;
		W=vX[0];
		DW=(vX[0]-vX[1])/TAU;
		Wd=PREGULATOR(TET0-TET,kx,W,DW);
		GETERR(Wd,W,err);
		PID_DIGITAL(q,err,U,vU);
	
	}while (TIME<TMODEL);
}