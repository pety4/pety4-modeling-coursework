#include "stdafx.h"

// ¬€◊»—À≈Õ»≈ √–¿ƒ»≈Õ“¿
inline void GRAD(double TT[], double GRX[], const int N, Func_FCT F)
{
	double E = 1.e-9;
	double DXmin = 1.e-9;
	for (int i = 0; i < N; i++)
	{
		double A = TT[i];
		double DX = abs(A)*E;
		if (DX < DXmin)
			DX = DXmin;
		TT[i] = A + DX;
		double F1 = F(TT);
		TT[i] = A - DX;
		double F2 = F(TT);
		GRX[i] = (F1 - F2) / (2 * DX);
		TT[i] = A;
	}
}

// ¿À√Œ–»“Ã —Œœ–ﬂ∆≈ÕÕŒ√Œ √–¿ƒ»≈Õ“¿
void SPRGR(Func_FCT F,double TT[], int N, double &EPS)
{
	double W[2][20]={0.0};
	double GRX[20]={0.0};
	double ET = 10.;
	double CA=2.0,CB = 2.;
	double DPS = 1.e-10;
	int LMT = 500;
	int LIMIT_ = 0;
	int KB = 0;
	int KC = 0;
	int M=0;
	double C = 1.;
	double FX1,FX2,FX3,FMN,FMX,FN,XMN,XMX,W1MX,W1MN,G_,CMIN,CH,ZN,CPR,S1,S2,B;
	GRAD(TT, GRX, N, F);
L27:
	for (int i = 0; i < N; i++)
		W[0][i] = GRX[i];
	M = 0;
L17:
	FX1 = F(TT);
	FMN = FX1 * (1.-DPS);
	FMX = FX1 * (1.+DPS);
	for (int i = 0; i < N; i++)
		W[1][i] = TT[i];
	XMN = abs(TT[0]);
	XMX = XMN;
	W1MX = abs(W[0][0]);
	W1MN = W1MX;
	for (int i = 0; i < N; i++)
	{
		XMN = min(XMN, abs(TT[i]));
		XMX = max(XMX, abs(TT[i]));
		W1MN = min(W1MN, abs(W[0][i]));
		W1MX = max(W1MX, abs(W[0][i]));
	}
	if (KB == 1)
		goto L19;
	KB = 1;
	G_ = W1MX;
	if (G_ <= EPS)
		goto L25;
L19://continue
	if (W1MN < 1.e-6)
		W1MN = 1.e-6;
	CMIN = XMN / W1MX * 1.e-6;	// ???
	if (XMN < 1.)
		CMIN = 1.e-6 / W1MX;
	C=CMIN;
//	C=1.E-15;	
	
L2:
	for (int i = 0; i < N; i++)
	{
		TT[i] = W[1][i] - W[0][i] * C;
		TT[10] = W[1][10] - floor(W[0][10] * C+1);
		if (TT[i] > VARMAX[i])
			TT[i] = VARMAX[i];
		if (TT[i] < VARMIN[i])
			TT[i] = VARMIN[i];
	}

	FX2 = F(TT);
	if (FX2 < FMN)
		goto L6;
	if (FX2 > FMX)
		goto L5;
	if (C*W1MN>=max(XMX*ET,ET))
		goto L5;
	C = CA * C;
	goto L2;
L5:
	for (int i = 0; i < N; i++)
		TT[i] = W[1][i];
	KC = 1;
	goto L14;
L6:
	CPR = C;
	C = CB * C;
	for (int i = 0; i < N; i++)
	{
		TT[i] = W[1][i] - W[0][i] * C;
		TT[10] = W[1][10] - floor(W[0][10] * C+1);
		if (TT[i] > VARMAX[i])
			TT[i] = VARMAX[i];
		if (TT[i] < VARMIN[i])
			TT[i] = VARMIN[i];
	}
	FX3 = F(TT);
	if (FX3 - FX2 < 0)	// !!!
	{
		FX2 = FX3;
		if (C * W1MN >= max(XMX * ET, ET))
			goto L11;	
		goto L6;
	}
	CH = (CB * CB - 1.) * FX1 - CB * CB * FX2 + FX3;	// !!!
	ZN = CB * (CB - 1.) * FX1 - CB * CB * FX2 + CB * FX3;	// !!!
	C = .5 * C * (CH / ZN);
L11:
	for (int i = 0; i < N; i++)
	{
		TT[i] = W[1][i] - W[0][i] * C;
		TT[10] = W[1][10] - floor(W[0][10] * C+1);
		if (TT[i] > VARMAX[i])
			TT[i] = VARMAX[i];
		if (TT[i] < VARMIN[i])
			TT[i] = VARMIN[i];
	}
	FN = F(TT);
	if (FN <= FX2)
		goto L14;
	for (int i = 0; i < N; i++)
	{
		TT[i] = W[1][i] - W[0][i] * CPR;
		TT[10] = W[1][10] - floor(W[0][10] * C+1);
		if (TT[i] > VARMAX[i])
			TT[i] = VARMAX[i];
		if (TT[i] < VARMIN[i])
			TT[i] = VARMIN[i];
	}
L14:
	GRAD(TT, GRX, N, F);
	G_ = abs(GRX[0]);
	for (int i = 0; i < N; i++)
		G_ = max(G_, abs(GRX[i]));	
	if (KC == 1)
		goto L25;
	LIMIT_++;
	if (G_ < EPS || LIMIT_ >= LMT)
		goto L25;
	M++;
	if (M == N)
		goto L27;
	S1 = 0.;
	for (int i = 0; i < N; i++)
		S1 += GRX[i] * (GRX[i] - W[0][i]);
	S2 = 0.;
	for (int i = 0; i < N; i++)
		S2 += pow(W[0][i],2.0);
	B = S1 / S2;
	for (int i = 0; i < N; i++)
		W[0][i] = GRX[i] + B * W[0][i];
	goto L17;
L25:
	TT[N] = F(TT);
	EPS = G_;
}
