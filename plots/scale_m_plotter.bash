PLOT_FILE="plots/scale-m.png"
#Make plot
gnuplot -persist <<-EOFMarker
    set title "Throughput vs. Bloom Filter Size"
    set xlabel "Bloom Filter Size (Pages)"
    set ylabel "Throughput (Insertions per Second)"
    set key right center

    set autoscale 
    set grid

    set term png   
    set output "$PLOT_FILE"

    set yrange [1000000:]
    set style line 1 lw 1 lc rgb '#0000FF' pt 6 lt 5
    set style line 2 lw 1 lc rgb '#FF0000' pt 6 lt 5

    plot "$1" using 1:2 title 'Standard' ls 1,\
         "$1" using 1:3 title 'Hierarchial' ls 2 
EOFMarker