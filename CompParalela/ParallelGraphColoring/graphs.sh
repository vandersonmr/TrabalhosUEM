#!/bin/bash

data="time";
for d in $(echo divisor bfs dfs randomic greedy); do 
  for p in $(echo 2 4 8); do
    :> graphics/$data$p$d; 
    for i in $(seq 1 8); do 
      value=0.0;
      for f in $(seq 1 13); do
        value=`echo "$value + $(cat results/parallel/$p/$d/g$i.b/tim$f | head -n 3 | tail -n 1 | cut -f2)" | bc -l` ;  
      done;
      value=`echo "$value / 13.00" | bc -l` ;
      echo $value >> graphics/$data$p$d; 
    done;
  done; 
done;
