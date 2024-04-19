// stdafx.cpp : source file that includes just the standard includes
// OPTIMIZATION.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
FILE *fout,*fJ;
double TAU=0.0;
double kx=0.0, kP=0.0,kI=0.0,kD=0.0;
double a[10]={0.0},b[10]={0.0};
int noh=0, nd=0;
double XDES=0.0, DXMAX=0.0, DX2MAX=0.0, UMAX=0.0;
double VARMAX[5]={0.0},VARMIN[5]={0.0};
