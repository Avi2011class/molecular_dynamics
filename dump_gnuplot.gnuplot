average_potential(x) = a
average_kinetic(x) = b
fit average_potential(x) '<python3 split.py' using 1:2 via a
fit average_kinetic(x) '<python3 split.py' using 1:3 via b

#set terminal png size 1200, 600
set terminal dumb size 160, 30
#set output 'plot.png'
set xlabel 'step'
set ylabel 'energy'

plot '~/oldhome/md2.log' using 1:2 title 'potential' with lines, \
	'~/oldhome/md2.log' using 1:3 title 'kinetic' with lines, \
	'~/oldhome/md2.log' using 1:4 title 'full energy' with lines lw 2, \
	average_potential(x) title 'aproximation of potential energy' lw 2, \
	average_kinetic(x) title 'aproximation of kinetic energy' lw 2
