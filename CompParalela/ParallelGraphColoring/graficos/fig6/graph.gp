#!/usr/bin/gnuplot
set terminal png size 2300,2300 crop enhanced font "/usr/share/fonts/truetype/times.ttf,30" dashlength 2; set termoption linewidth 3
set output "output.png"
set title "Benchmarks"
A = "#99ffff"; B = "#4671d5"; C = "#ff0000"; D = "#f36e00"
set auto x
set logscale y
set style data histogram
set style histogram cluster gap 1
set style fill solid border -1
set boxwidth 0.9
set xtic scale 0
set title "Gargalos - 8 threads"
set xlabel "Instancia"
set ylabel "Gargalos"
set xtics font "Times-Roman, 20" 
set ytics font "Times-Roman, 20" 
set title font "Times-Roman, 30" 
set xlabel font "Times-Roman, 30" 
set ylabel font "Times-Roman, 30" 
plot 'data' using 2:xtic(1) ti "BFS" fc rgb A, '' u 3 ti "DFS" fc rgb B, '' u 4 ti "Greedy" fc rgb C, '' u 5 ti "Randomic" fc rgb D
