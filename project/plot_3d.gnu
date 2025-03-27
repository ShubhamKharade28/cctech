set terminal wxt
set xlabel 'X'
set ylabel 'Y'
set zlabel 'Z'
set title 'Robot'
splot 'data/robo-v2.dat' with lines title '3D Plot'
