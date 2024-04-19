// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include <time.h>
#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <math.h>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <clocale>


// TODO: reference additional headers your program requires here
extern FILE *fout, *fJ;
extern double TAU;
extern double kx, kP,kI,kD;
extern double a[10],b[10];
extern int noh, nd;
extern double XDES, DXMAX, DX2MAX, UMAX;
extern double VARMAX[5],VARMIN[5];


//Prototype of functions
//Criterion
typedef double(*Func_FCT)(double[]);
//Functions
//Criterion
double FCT(double X[]);
//Optimization
//Метод вращающихся координат
void WRK50(double VAR[], int N);
//Simulation
void MODELING(double K[]);
//Control
void DIGPIDCOEFF(double q[], double kP, double kI,double kD);
void DIGPIDCOEFF1(double q[], double kPa, double kIa, double kDa, double TAU);
void GETERR(double xd, double x, double err[]);
void PID_DIGITAL(double q[],  double err[], double u[], double ur[]);
//генератор белого шума
double GAUSS();
void vers_(double xn, double xr[], int n);
double FXDIG(int m, int nd, double x[], double u[], double a[], double b[]);
void SPRGR(Func_FCT F,double TT[], int N, double &EPS);
double PROGCNTRL(double TIME);
//double PREGULATOR(double thetaErr, double k);
double PREGULATOR(double thetaErr, double k,double W, double DW);