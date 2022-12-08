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

    set style line 1 lw 1 lc rgb '#0000ff' pt 27 lt 5
    set style line 2 lw 1 lc rgb '#8400ff' pt 28 lt 5
    set style line 3 lw 1 lc rgb '#ea00ff' pt 28 lt 5
    set style line 4 lw 1 lc rgb '#FF0000' pt 28 lt 5
    set style line 5 lw 1 lc rgb '#ff6a00' pt 28 lt 5
    set style line 6 lw 1 lc rgb '#b4eb34' pt 28 lt 5

    f(x) = q*x + w
    g(x) = e*x + r
    h(x) = t*x + y
    j(x) = u*x + i
    k(x) = o*x + p
    l(x) = a*x + s

    fit f(x) "$1" using 1:2 via q,w
    fit g(x) "$1" using 1:3 via e,r
    fit h(x) "$1" using 1:4 via t,y
    fit j(x) "$1" using 1:5 via u,i
    fit k(x) "$1" using 1:6 via o,p
    fit l(x) "$1" using 1:7 via a,s

    set yrange [0:]
    plot "$1" using 1:2 title "Standard" with points ls 1, f(x) notitle ls 1, \
         "$1" using 1:3 title "Hierarchical 4096" with points ls 2, g(x) notitle  ls 2, \
         "$1" using 1:4 title "Hierarchical 1024" with points ls 3, h(x) notitle  ls 3, \
         "$1" using 1:5 title "Hierarchical 256" with points ls 4, j(x) notitle  ls 4, \
         "$1" using 1:6 title "Hierarchical 64" with points ls 5, k(x) notitle ls 5, \
         "$1" using 1:7 title "Hierarchical 8" with points ls 6, l(x) notitle ls 6;

EOFMarker