#Make throughput plot
gnuplot -persist <<-EOFMarker
    set title "Throughput vs Bits per Element"
    set xlabel "Bits per Element"
    set ylabel "Insertions per Second"
    set key bottom left

    set autoscale 
    set grid

    set term png   
    set output "plots/aol_thru.png"

    set style line 1 lw 1 lc rgb '#0000FF' pt 27 lt 5
    set style line 2 lw 1 lc rgb '#FF0000' pt 28 lt 5

    f(x) = m*x + b
    g(x) = k*x + l

    fit f(x) "$1" using 1:2 via m,b
    fit g(x) "$1" using 1:3 via k,l

    plot "$1" using 1:2 title 'Standard' ls 1, f(x) title "Standard Fit" ls 1,\
         "$1" using 1:3 title 'Hierarchical' ls 2, g(x) title "Hierarchical Fit" ls 2

EOFMarker

#Make fp plot
gnuplot -persist <<-EOFMarker
    set title "False Positive Rate vs Bits per Element"
    set xlabel "Bits per Element"
    set ylabel "False Positive Rate (log scaled)"
    set key top right

    set autoscale 
    set grid
    set logscale y 10

    set term png   
    set output "plots/aol_fp.png"

    set style line 1 lw 1 lc rgb '#0000FF' pt 27 lt 5
    set style line 2 lw 1 lc rgb '#FF0000' pt 28 lt 5
    set style line 3 lw 1 lc rgb '#A020F0' lt 5
    set style line 4 lt 2 lc rgb '#d0a1ed' lw 1

    k = 7
    t(x) = (1 - exp(-k/x))**k

    plot "$1" using 1:4 title 'Standard' ls 1,\
         "$1" using 1:5 title 'Hierarchical' ls 2,\
         t(x) title 'Theoretical' ls 3,\
         t(x) + 0.0005 title "Theoretical ± 0.0005" ls 4, \
         t(x) - 0.0005 notitle ls 4, \
         t(x) notitle ls 3;

EOFMarker