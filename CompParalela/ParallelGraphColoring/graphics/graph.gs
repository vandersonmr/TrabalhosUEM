#!/usr/bin/gnuplot
@png
set output "output.png"
set xtics font "Times-Roman, 20" 
set ytics font "Times-Roman, 20" 
set title font "Times-Roman, 30" 
set xlabel font "Times-Roman, 30" 
set ylabel font "Times-Roman, 30" 
set style fill transparent solid 0.3 noborder
set boxwidth 0.3 relative
set title "Relacao tempo e stalls - 2 threads - BFS"
set xlabel "Entradas ordenadas pelo resultado do PSR"
set ylabel "Número de nós visitados na árvore de recursão"
plot "graph2bfs" u 1:2 title "PSR" with boxes#, '' u ($1+0.3):3 title "Informada" with boxes
