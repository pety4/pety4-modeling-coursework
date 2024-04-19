#include "stdafx.h"
// Ddigital PID (standart)
void DIGPIDCOEFF(double q[], double kP, double kI,double kD)
{  
  float K=kP, tI=kI/kP, tD=kD/kP;  //поменял tI (исходная формула tI=kP/kI) --> не делить на 0 при kI=0;
  q[0]=K*(1+tD/TAU);
  q[1]=-K*(1+2*tD/TAU-TAU*tI);
  q[2]=K*tD/TAU;
  q[3]=1;
  q[4]=0;
}
//Digital PID with D-component filter
void DIGPIDCOEFF1(double q[], double kPa, double kIa, double kDa, double TAU)
{  
  float kP,kI,kD,d;
  int N=10;
  kP=kPa;
  kI=TAU*kIa;
  kD=N*kDa/(kDa+N*TAU);
  d=kD/N;
  // a1=1+d;
  // a2=-d;
  // b0=kP+kI+kD;
  // b1=-kP*(1+d)-kI*d-2*kD;
  // b2=kP*d+kD;  
  q[0]=kP+kI+kD;
  q[1]=-kP*(1+d)-kI*d-2*kD;
  q[2]=kP*d+kD;
  q[3]=1+d;
  q[4]=-d;
}
// calculate err
void GETERR(double xd, double x, double err[])
{
	err[2]=err[1];
	err[1]=err[0];
	err[0]=xd-x;
}

// Реализация алгоритмов цифровых ПИД регуляторов в общем виде
 void PID_DIGITAL(double q[],  double err[], double u[], double u_out[])
 {  
    double unew;

    // расчет нового значения корректирующего сигнала управления
    unew=q[3]*u[0]+q[4]*u[1]+q[0]*err[0]+q[1]*err[1]+q[2]*err[2]; 

    // хранение для следующего вызова
    u[2]=u[1];    u[1]=u[0];    u[0]=unew; 
	
	// выходной сигнал ПИД
	// ограничение
	if (fabs(unew)>UMAX)
		unew=UMAX*unew/fabs(unew);		
	//сдвиг
	vers_(unew, u_out, 16);
}

// Реализация алгоритмов цифровых ПИ регуляторов в общем виде
void PI_DIGITAL(double q[],  double err[], double u[])
{           
   double unew, urnew;
   // расчет нового значения корректирующего сигнала управления
   unew=u[1]+q[0]*err[0]+q[1]*err[1]; 
   // хранение для следующего вызова
   u[1]=u[0];    u[0]=unew; 
}


double PROGCNTRL(double TIME)
{
	double res;
	res=0;
	if (TIME>0.0& TIME<=2.5)
		res=180/57.3;
	else
	//if (TIME>2.5 && TIME<=10)
		res=-180/57.3;
	return res;
}

// вычисление требуемой угловой скоости
double PREGULATOR(double thetaErr, double k,double W, double DW)
{
    double wd=0.0, wmax=360.0/57.3, amax=720/57.3;    
    double theta0=amax/k/k, theta1=0.5*theta0;
	/*double thetaErrmax=0.0;
	if (DW!=0)
		thetaErrmax=fabs(DW)/2*k*k+W*W/2/fabs(DW);
	if (thetaErr>thetaErrmax)
		thetaErr=thetaErrmax;	
	if (thetaErr<-thetaErrmax)
		thetaErr=-thetaErrmax;*/

    if (fabs(thetaErr)>theta0)
        wd=pow(2*amax*(fabs(thetaErr)-theta1),0.5)*fabs(thetaErr)/thetaErr;
    else
        wd=k*thetaErr;    
    return wd;
}