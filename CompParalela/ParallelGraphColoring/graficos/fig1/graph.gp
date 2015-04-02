#!/usr/bin/gnuplot
set terminal png size 2300,2300 crop enhanced font "/usr/share/fonts/truetype/times.ttf,30" dashlength 2; set termoption linewidth 3
set output "output.png"
set xtics font "Times-Roman, 25" 
set ytics font "Times-Roman, 25" 
set title font "Times-Roman, 40" 
set xlabel font "Times-Roman, 40" 
set ylabel font "Times-Roman, 40" 
set style fill transparent solid 1 noborder
set title "Relacao tempo e stalls - 2 threads"
set xlabel "Tempo de execucao"
set ylabel "Stalls"
plot "data" u 1:2, '' u 1:2 smooth bezier 
