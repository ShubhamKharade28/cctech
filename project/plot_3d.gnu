set terminal wxt
set xlabel 'X'
set ylabel 'Y'
set zlabel 'Z'
set title 'Generated Plot'
splot 'data/mycylinder.dat' with lines title '3D Plot'
