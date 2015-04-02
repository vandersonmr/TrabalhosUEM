#!/usr/bin/gnuplot
@png
set output "output.png"
set xtics font "Times-Roman, 20" 
set ytics font "Times-Roman, 20" 
set title font "Times-Roman, 30" 
set xlabel font "Times-Roman, 30" 
set ylabel font "Times-Roman, 30" 
set style fill transparent solid 1 noborder
set title "Speedups"
set xlabel "Quantidade de threads"
set ylabel "Speedup"
plot "data" u 1:2 smooth bezier title "BFS", '' u 1:3 smooth bezier title "DFS", '' u 1:5 smooth bezier title "Randomic", '' u (2**($0+1)):(2**($0+1)) title "Linear speedup" w lines 
