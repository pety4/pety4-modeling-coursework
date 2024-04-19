#include "stdafx.h"


/*********************************************************
C Служит для pешения дифеpенциального уpавнения
C Y(K)=B(1)U(K-1-D)+...+B(NOH)U(K-NOH-D)-
C     -A(1)Y(K-1)+...+A(NOH)Y(K-NOH)
C
C NOH-поpядок
C ND-вpемя запаздывания
C YR-вектоp pеакции с истоpией
C UR-вектоp воздействий с истоpией
C A и B -вектоpа коэффициентов пеp.функции
C
C**********************************************************/
double FXDIG(int m, int nd, double x[], double u[], double a[], double b[])
{
	double res = 0.0;
	int i;	
	for (i = 0; i < m; ++i)
	{
		res += b[i] * u[i + nd] - a[i+1] * x[i];
	}
	return res;
}


/* ***************************************************** */
/* Служит для сдвига вектоpа XR(I)=XR(I+1) */
/*  и XR(1)=XN */
/* ****************************************************** */
void vers_(double xn, double xr[], int n)
{
	int i;
	for (i = n-1; i > 0; --i)
	{
		xr[i] = xr[i-1];
	}
	xr[0] = xn;
}


//генератор белого шума
double GAUSS()
{
	double ran=0.0;
	for (int i=1;i<=12;i++)
		ran+=(1 - (1-0)*((double)rand()/32768));;        
	ran-=6.0;
	return ran;
}//end GAUSS