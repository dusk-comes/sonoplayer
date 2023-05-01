#! /usr/bin/gnuplot
set pm3d map
splot 'spectral.dat'
set terminal png crop
set output 'spectral-map.png'
set xlabel 'Pulse generator voltage [V]'
set ylabel 'Frequency [THz]'
set cblabel 'Intensity [a.u.]'
set cbrange [0 to GPVAL_DATA_Z_MAX]
set xrange [GPVAL_DATA_X_MIN to GPVAL_DATA_X_MAX]
set yrange [GPVAL_DATA_Y_MIN to GPVAL_DATA_Y_MAX]
unset key
replot
unset output
