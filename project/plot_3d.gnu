set terminal wxt
set xlabel 'X'
set ylabel 'Y'
set zlabel 'Z'
set title 'My first sketch'
splot 'data/random-model.dat' with lines title '3D Plot'
