/*ПРОГРАММЫ РЕАЛИЗУЮЩИЕ АЛГОРИТМ ЛИНЕЙНОЙ ОПТИМИЗАЦИИ ПО МЕТОДУ ВРАЩАЮЩИХСЯ КООРДИНАТ*/

#include "stdafx.h"


//вспомагательная функция для WRK50
double AMIN(double A,double B)
{
   double min=0.0;
   if(A<B || A==B) min=A;
   if (B<A) min=B;
   return min;
}//------------------------------   End of AMIN   ------------------------------

//--------------------------------   AMAX   ------------------------------------

double AMAX(double A,double B)
{
   double max=0.0;
   if (A>B || A==B) max=A;
   if (B>A) max=B;
   return max;
}//-----------------------------   End of AMAX   -------------------------------
//-------------------------------   PKS   --------------------------------------
//N - число балансировочных параметров
void PKS(double S[50][50],double VAR[],int N)
{
   const double EN=0.0000001;
   const double ET=10.0;
   const double DPS=0.000000000001;
   double Z=0.0, FX=0.0, A=0.0, XMX=0.0, SMN=0.0, FMN=0.0, FMX=0.0, FX1=0.0,
          APR=0.0, FX2=0.0, CH=0.0, ZN=0.0, FN=0.0;
   double XW[6];
   int KP=0, KM=0, i=0, j=0, o=0;

   for (j=0;j<N;j++)  // for 1 - цикл на все тело функции
   {
		Z=1.0;
		FX=FCT(VAR);
		A=fabs(VAR[0]);
		XMX=A;
		SMN=fabs(S[0][j]);
		for (i=0;i<N;i++)  // for 2
		{
			SMN=AMIN(SMN,fabs(S[i][j]));
			XMX=AMAX(XMX,fabs(VAR[i]));
			A=AMIN(A,fabs(VAR[i]));
		}// end for 2
		if (SMN<DPS) SMN=DPS;
		A=A*EN;
		if (A<EN) A=EN;
		FMN=FX*(1.0-DPS);
		FMX=FX*(1.0+DPS);
N4:		KP=0;
		KM=0;
		for (i=0;i<N;i++)  
		{
			XW[i]=VAR[i]+A*S[i][j];
			if (XW[i] > XMAX[i])
				XW[i] = XMAX[i];
			if (XW[i] < XMIN[i])
				XW[i] = XMIN[i];
		}
		FX1=FCT(XW);
		if (FX1<FMN) goto N5;
		if (FX1>FMX) KP=1;
		for (i=0;i<N;i++) 
		{
			XW[i]=VAR[i]-A*S[i][j];
			if (XW[i] > XMAX[i])
				XW[i] = XMAX[i];
			if (XW[i] < XMIN[i])
				XW[i] = XMIN[i];
		}
		FX1=FCT(XW);
		if (FX1<FMN) goto N7;
		if (FX1>FMX) KM=1;
		if ((KP+KM)==2) goto N3;
		if ((A*SMN)>AMAX(XMX*ET,ET) || (A*SMN)==AMAX(XMX*ET,ET)) goto N3;
		A=A*2.0;
		goto N4;
N7:		Z=-1.0;
N5:		APR=A;
		A=A*2.0;
		for (i=0;i<N;i++) 
		{
			XW[i]=VAR[i]+Z*A*S[i][j];
			if (XW[i] > XMAX[i])
				XW[i] = XMAX[i];
			if (XW[i] < XMIN[i])
				XW[i] = XMIN[i];
		}
		FX2=FCT(XW);
		if (FX2>FX1 || FX2==FX1) goto N10;
		if ((A*SMN)>AMAX(XMX*ET,ET) || (A*SMN)==AMAX(XMX*ET,ET)) goto N9;
		FX1=FX2;
		goto N5;
N10:	CH=3.0*FX-4.0*FX1+FX2;
		ZN=2.0*FX-4.0*FX1+2.0*FX2;
		if (ZN==0.0) goto N12;
		A=(CH/ZN)*A*0.5;
		for (i=0;i<N;i++) 
		{
			XW[i]=VAR[i]+Z*A*S[i][j];
			if (XW[i] > XMAX[i])
				XW[i] = XMAX[i];
			if (XW[i] < XMIN[i])
				XW[i] = XMIN[i];
		}
		FN=FCT(XW);
		if (FN<FX1 || FN==FX1) goto N9;
N12:	for (i=0;i<N;i++) 
		{
			VAR[i]=VAR[i]+Z*APR*S[i][j];
			if (VAR[i] > XMAX[i])
				VAR[i] = XMAX[i];
			if (VAR[i] < XMIN[i])
				VAR[i] = XMIN[i];
		}
		goto N3;
N9:		for (i=0;i<N;i++) VAR[i]=XW[i];
N3:; }// end for 1
}//--------------------------   PKS   ---------------------------------

//функции минимизации критерия по методу вращающихся координат
void WRK50(double VAR[], int N)
{	
   const double EPS=1.E-10;
   double S[50][50], FX=0.0, FX0=0.0, XL[30]={0.0}, A=0.0, B=0.0, ZN=0.0, KN=0.0;
   int i=0,j=0,k=0,M=0,o=0;

   FX0=FCT(VAR); 
AA: for (i=0;i<N;i++)   // for 1
   {
	  for (j=0;j<N;j++)
      {
		S[i][j]=0.0;
        if (i==j) S[i][j]=1.0;
	  }
   } // end for 1

   PKS(S,VAR,N); 

AB:
   for (i=0;i<N;i++) XL[i]=VAR[i];

   PKS(S,VAR,N); 

   A=0.0;
   for (i=0;i<N;i++)  // for 2
    {
	  B=AMIN(fabs(VAR[i]),fabs(XL[i]));
      M=0;
	  if (B<1.0) goto AC;
//      M=int(log10(B))+1;
	  M=(log10(B)+1);
AC:   A=A+pow(((XL[i]-VAR[i])/pow(10.0,M)),2);
    } // end for 2
   A=sqrt(A);  
   if (A<EPS || A==EPS) goto AG;
   A=0.0;
   for (i=0;i<N;i++) A=A+pow((XL[i]-VAR[i]),2);
   A=sqrt(A);
   for (i=0;i<N;i++) XL[i]=VAR[i]-XL[i];
   for (i=0;i<N;i++) S[i][1]=XL[i]/A;
   if (N==1) goto AB;
   for (k=2;k<N;k++)  // for 3
   {
	 if (A==0.0) goto AE;
     A=0.0;
     for (i=k;i<N;i++) A=A+pow(XL[i],2);
	 if (A==0.0) goto AE;
     B=A+pow(XL[k-1],2);
     ZN=sqrt(A)*sqrt(B);
	 if (k==2) goto AD;
     KN=k-2;
     for (i=0;i<KN;i++) S[i][k]=0.0;
AD: S[k-1][k]=-A/ZN;
     for(i=k;i<N;i++) S[i][k]=XL[k-1]*XL[i]/ZN;
     goto AF;
AE: for (i=0;i<N;i++)
     {
       S[i][k]=0.0;
	   if (i==k) S[i][k]=1.0;
     }
AF:; }  // end for 3
   goto AB;
AG:   FX=FCT(VAR); 
   if (FX>FX0*(1-EPS)  || FX==FX0*(1-EPS)) goto AH;
   else
   {	   
      FX0=FX;	
	  goto AA;
   }
AH: VAR[N]=FX;
}//--------------------------   End of WRK50   --------------------------------
