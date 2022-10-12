PLOT_FILE="plots/scale-nm.png"
#Make plot
gnuplot -persist <<-EOFMarker
    set title "Duration vs. N"
    set xlabel "Number of Operations (#)"
    set ylabel "Duration (Seconds)"
    set key left top
    
    set autoscale 
    set grid

    set term png   
    set output "$PLOT_FILE"

    set style line 1 lw 4 lc rgb '#990042' pt 6 pi 5   
    set style line 2 lw 3 lc rgb '#31f120' pt 12 pi 3

    plot "$1" using 1:2 title 'Regular' ls 1,\
         "$1" using 1:3 title 'Hierarchial' ls 2 
EOFMarker