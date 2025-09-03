set title "Binary vs Ternary Search Comparisons"
set xlabel "Array Size (n)"
set ylabel "No. of Comparisons"
set grid
set key left top
plot "output.dat" using 1:2 with linespoints title "Binary Search", \
     "output.dat" using 1:3 with linespoints title "Ternary Search"