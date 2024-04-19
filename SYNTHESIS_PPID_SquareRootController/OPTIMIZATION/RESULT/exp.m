G=tf([2600],[1 100 2600 0]);
H=tf([25],[1 25]);
oltf=G*H;
GHnum=oltf.num{1};
GHden=oltf.den{1};
zeta=0.5;
tol=1.e-12;
rlocus(GHnum,GHden);