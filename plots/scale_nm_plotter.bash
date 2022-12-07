PLOT_FILE="plots/scale-nm.png"
#Make plot
gnuplot -persist <<-EOFMarker
    set title "Duration vs. Number of Insertions"
    set xlabel "Insertions in Millions"
    set ylabel "Duration in Seconds"
    set key left top
    
    set autoscale 
    set grid

    set term png   
    set output "$PLOT_FILE"

    set style line 1 lw 1 lc rgb '#0000FF' pt 27 lt 5
    set style line 2 lw 1 lc rgb '#FF0000' pt 28 lt 5

    f(x) = m*x + b
    g(x) = k*x + l

    fit f(x) "$1" using 1:2 via m,b
    fit g(x) "$1" using 1:3 via k,l

    set yrange [0:]
    plot "$1" using 1:2 title "Standard" with points ls 1, f(x) title "Standard Fit" ls 1, \
         "$1" using 1:3 title "Hierarchical" with points ls 2, g(x) title "Hierarchical Fit" ls 2
EOFMarker