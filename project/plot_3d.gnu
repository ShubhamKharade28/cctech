set terminal wxt
set xlabel 'X'
set ylabel 'Y'
set zlabel 'Z'
set title 'robot'
splot 'data/robot.dat' with lines title '3D Plot'
