PLOT_FILE="plots/fp.png"
#Make plot
gnuplot -persist <<-EOFMarker
    set title "False Positive Rate vs Bits per Element"
    set xlabel "Bits per Element"
    set ylabel "False Positive Rate (log scaled)"
    set key bottom left

    set autoscale 
    set grid
    set logscale y 10

    set term png   
    set output "$PLOT_FILE"

    set style line 1 lw 4 lc rgb '#990042' pt 6 pi 5   
    set style line 2 lw 3 lc rgb '#31f120' pt 12 pi 3

    plot "$1" using 1:2 title 'Regular' ls 1,\
         "$1" using 1:3 title 'Hierarchial' ls 2 
EOFMarker