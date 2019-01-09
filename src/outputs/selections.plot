set datafile separator ","
set key outside
set title 'Robby Evolution Selections Performance'
set xlabel 'Generations'
set ylabel 'f(g)'
plot 'elite.csv' u 2 w l t 'Elite' lc 1, 'roulette.csv' u 2 w l t 'Roulette' lc 4, 'tournament.csv' u 2 w l t '2-Tournament' lc 8
