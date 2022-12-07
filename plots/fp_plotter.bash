PLOT_FILE="plots/fp.png"
#Make plot
gnuplot -persist <<-EOFMarker
    set title "False Positive Rate vs Bits per Element"
    set xlabel "Bits per Element"
    set ylabel "False Positive Rate (log scaled)"
    set key top right

    set autoscale 
    set grid
    set logscale y 10

    set term png   
    set output "$PLOT_FILE"

    set style line 1 lw 1 lc rgb '#0000FF' pt 27 lt 5
    set style line 2 lw 1 lc rgb '#FF0000' pt 28 lt 5
    set style line 3 lw 1 lc rgb '#A020F0' lt 5
    set style line 4 lt 2 lc rgb '#d0a1ed' lw 1

    k = 7
    t(x) = (1 - exp(-k/x))**k

    plot "$1" using 1:2 title 'Standard' ls 1,\
         "$1" using 1:3 title 'Hierarchical' ls 2,\
         t(x) title 'Theoretical' ls 3,\
         t(x) + 0.0005 title "Theoretical ± 0.0005" ls 4, \
         t(x) - 0.0005 notitle ls 4, \
         t(x) notitle ls 3;

EOFMarker