#! /usr/bin/gnuplot -c
set pm3d map
splot ARG1
set terminal png crop
set output ARG1[1:strlen(ARG1)-4].".png"
set xlabel 'Time [V]'
set ylabel 'Frequency [THz]'
set cblabel 'Intensity [a.u.]'
set cbrange [0 to GPVAL_DATA_Z_MAX]
set xrange [GPVAL_DATA_X_MIN to GPVAL_DATA_X_MAX]
set yrange [GPVAL_DATA_Y_MIN to GPVAL_DATA_Y_MAX]
unset key
replot
unset output
