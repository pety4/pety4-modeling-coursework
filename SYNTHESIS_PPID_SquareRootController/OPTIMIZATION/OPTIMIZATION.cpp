// OPTIMIZATION.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//File to write
	fout = fopen(".\\RESULT\\RES_OPT.ris", "w");
	fJ = fopen(".\\RESULT\\FJ.ris", "w");
	fprintf(fJ,"T0 kTET kP kI kD J\n");
	//Number of variables
	int N = 5;
	//Variable (PID coeff, time T0)
	double K[6] = {0.0};
	//For optimization
	double EPS=1.E-9;
	double MINMAX=0.0;
	
	// Math model of plant
	//коэффициенты, найденные при идентификации(не нами)
	noh = 5; nd = 0;
	a[0]=1.00000;
	//PITCH
	a[1] = -1.196475569945; a[2] = -0.265487706455; a[3] = 0.411416227657; a[4] = 0.168904791600; a[5] = -0.110025336649;
	b[0] = 0.008463983273; b[1] = -0.005601482560; b[2] = 0.024027988158; b[3] = 0.032259066845; b[4] = 0.021739589106;

	//ROLL
//	a[1] = -0.639251505211; a[2] = -0.471922141655; a[3] = -0.322724650206; a[4] = 0.203455745846; a[5] = 0.228672817457;
	//b[0] = 0.003937313629; b[1] = -0.003823785606; b[2] = 0.004155310902; b[3] = 0.001852412052; b[4] = 0.003589368526;

	//YAW
	//a[1] = -0.872881501840; a[2] = -0.424330507838; a[3] = -0.029459906267; a[4] = 0.187295601605; a[5] = 0.153855391565;
	//b[0] = 0.001691548984; b[1] = -0.000451724888; b[2] = 0.000625715382; b[3] = -0.002422108398; b[4] = 0.001813485532;
//	noh=5; nd=2;	
//	a[0]=1.00000;
	
	//Pitch
//	a[1]=-1.95039;a[2]=1.27233;a[3]=-0.28999;a[4]=-0.07416;a[5]=0.06719;
//	b[0]=0.43600;b[1]=7.63339;b[2]=4.96046;b[3]=-1.05772;b[4]=-0.13398;

	//Roll
//	a[1]=-1.57482;a[2]=1.02155;a[3]=-0.61455;a[4]=0.14493;a[5]=0.07649;
//	b[0]=1.13621;b[1]=4.79170;b[2]=7.54898;b[3]=2.47784;b[4]=2.54280;


	//a[1]=-1.663892630193; a[2]=  0.795671595423; a[3]= -0.531913945386; a[4]=  0.478376919728; a[5]= -0.066795107865;
	//b[0]=-0.019983614316; b[1]=  0.028202211678; b[2]= -0.004933296810; b[3]=  0.022499365822; b[4]=  0.066216727724;
	
	//Initial values of variables
	K[0]=1.0;	//T0
	K[1]=5.0;	//kx
	K[2]=1.0E-5;	//kP
	K[3]=1.0E-5;	//kI
	K[4]=1.0E-5;	//kD	

	TAU=0.03; //(10ms)
	//Constraint on variables
	// for PID coeff
	MINMAX=10.0;
	for (int i=0;i<N;i++) 
	{
		VARMAX[i]=MINMAX;
		VARMIN[i]=1.E-5;
	}
	//Ограничения параметров
	// for T0
	VARMAX[0]=5.0;   
	VARMIN[0]=0.0;
	
	//for kx
	VARMAX[1]=10.0;   
	VARMIN[1]=0.0;

	// for criterion
	int KEY=0;

	//for PITCH & ROLL
	XDES=45/57.3;		//max angle command value = 45 deg
	DXMAX=360/57.3;		//see https://github.com/ArduPilot/ardupilot/blob/master/libraries/AC_AttitudeControl/AC_AttitudeControl.h#L102
	DX2MAX=360/57.3l;
	//max control
	UMAX=2.5;//for small drone 0.2;

	//for YAW
	if (KEY==1)
	{
		XDES=45.0/57.3;
		DXMAX=90/57.3;
		DX2MAX=120/57.3;
		UMAX=0.15;
	}
	// Optimization
	WRK50(K,N);//Метод вращающихся координат
	//double EPS1=1.E-6;
	//SPRGR(FCT,K,N,EPS1);
	// print results
	fprintf(fout, "T0=%f kTET =%f kP=%f; kI=%f; kD=%f; FMIN=%f", K[0],K[1],K[2],K[3],K[4],K[5]);
	// close files
	fclose(fout);
	fclose(fJ);
	
	// Simualtion with found PID
	//K[1]=7.420256; K[2]=0.000875; K[3]= 0.0160; 
	MODELING(K);	
	return 0;
}