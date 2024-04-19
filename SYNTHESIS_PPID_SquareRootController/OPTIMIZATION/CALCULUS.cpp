#include "stdafx.h"

/*ОДИН ШАГ ИНТЕГРИРОВАНИЯ ПО МЕТОДУ РУНГЕ-КУТТА
N	- число параметров состояния
DT	- шаг интегрирования
X	- вектор параметров состояния
DX	- вектор производных от X
U	- вектор управления
fFX	- система дифф. уравнений 
*/
void RKS(int N,double DT, double& TIME, double DX[], double X[], double U[], FUNC_FX fFX)
{
   double A[5]={0.5,0.5,1.0,1.0,0.5};
   double DXT[50], D=0.0, C=0.0, T=0.0;
   int i=0,j=0,k=0;
   double XT[50];
  
   T=TIME;
   for (i=0;i<N;i++) 
   {
	   DXT[i]=0.0;
	   //сохраняем вектор состояния
	   //потом востанавливаем их
	   XT[i]=X[i];
   }

      
   for (j=0;j<4;j++)
   {
	  fFX(DX,X,U,T);
	  D=A[j+1];
	  C=A[j];
	  T=TIME+C*DT;
	  for (i=0;i<N;i++) 
	  {		  
		  DXT[i] = DXT[i] + D*DT*DX[i]/3.0;
		  X[i]  = XT[i] + C*DT*DX[i];
	  }
   }
   //новые значения вектор состояния
   for (i=0;i<N;i++) 
	   X[i]=XT[i]+DXT[i];

   TIME+=DT;
}//--------------------------   End of RKS   -----------------------------------