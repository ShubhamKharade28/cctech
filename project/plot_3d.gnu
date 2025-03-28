set terminal wxt
set xlabel 'X'
set ylabel 'Y'
set zlabel 'Z'
set title 'robo-v4'
splot 'data/robo-v4.dat' with lines title '3D Plot'
