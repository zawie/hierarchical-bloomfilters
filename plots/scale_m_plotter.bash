PLOT_FILE="plots/scale-m.png"
#Make plot
gnuplot -persist <<-EOFMarker
    set title "Duration vs. Bloom Filter Size"
    set xlabel "Bloom Filter Size (Pages)"
    set ylabel "Duration (Seconds)"
    set autoscale 
    
    set term png   
    set output "$PLOT_FILE"

    plot "$1" using 1:2 title 'Regular',\
         "$1" using 1:3 title 'Hierarchial'
EOFMarker