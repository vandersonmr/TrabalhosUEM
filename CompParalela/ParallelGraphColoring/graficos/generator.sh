#!/bin/bash

root=$(pwd);

cdToSequential(){
  local instance=$1;
  local execution=$2;

  cd results/sequencial;

  if [ "$instance" -gt 8 ]; then
    instance=$(echo "$instance - 8" | bc);
    cd "r"$instance".b";
  else
    cd "g"$instance".b";
  fi;
}

cdToParallel(){
  local instance=$1;
  local execution=$2;
  local numerOfThreads=$3;
  local algorithm=$4;
 
  cd results/parallel/$numberOfThreads/$algorithm;

  if [ "$instance" -gt 8 ]; then
    instance=$(echo "$instance - 8" | bc);
    cd "r"$instance".b";
  else
    cd "g"$instance".b";
  fi;
}

returnToRoot(){
  cd $root;
}

checkExecution(){
  execution=$1;
  if [ "$execution" -gt 13 ] || [ "$execution" -lt 1 ]; then
    echo "Execution is out of the range. execution=$execution";
    exit;
  fi;
}

checkInstance(){
  if [ "$instance" -gt 16 ] || [ "$instance" -lt 1 ]; then
    echo "Instance is out of the range. instance=$instance";
    exit;
  fi;
}

#To get execution time of sequential, g1.b, third execution: 
#getExecutionTime true 1 3
getExecutionTime(){ 
  local execution=$1;
  local isSequential=$2;
  local instance=$3;
  
  checkExecution $execution;
  checkInstance $instance;

  if [ "$isSequential" = true ]; then
    cdToSequential $instance $execution;
    local result=$(cat tim$execution | head -n 2 | tail -n 1 | cut -f2); 
    echo $result;
    returnToRoot;
    return 0;
  else
    local numberOfThreads=$4;
    local algorithm=$5;
    cdToParallel $instance $execution $numberOfThreads $algorithm;
    local result=$(cat tim$execution | head -n 3 | tail -n 1 | cut -f2);
    echo $result;
    returnToRoot;    
    return 0;
  fi; 
}

getStalls(){
  local execution=$1;
  local instance=$2;
  local numberOfThreads=$3;
  local algorithm=$4;

  checkExecution $execution;
  checkInstance $instance;

  cdToParallel $instance $execution $numberOfThreads $algorithm;
  local result=$(cat tim$execution | head -n 1 | cut -d: -f2);
  echo $result;
  returnToRoot;    
  return 0;
}

getPAPIValue(){
  local execution=$1;
  local isSequential=$2;
  local instance=$3;
  local PAPILabel=$4;

  checkExecution $execution;
  checkInstance $instance;

  if [ "$isSequential" = true ]; then
    cdToSequential $instance $execution;
    local result=$(cat $execution.0.* | grep "$PAPILabel" | sed "s/. $PAPILabel\.* *//g" | sed 's/ //g' | head -n 1); 
    echo $result;
    returnToRoot;
    return 0;
  else
    local numberOfThreads=$5;
    local thread=$6;
    local algorithm=$7;

    cdToParallel $instance $execution $numberOfThreads $algorithm;
    local result=$(cat $execution.$thread.* | grep "$PAPILabel" | sed "s/. $PAPILabel\.* *//g" | sed 's/ //g' | head -n 1); 
    echo $result;
    returnToRoot;    
    return 0;
  fi; 
}

getAverage(){
  local function=$1;
  local params=$2

  local value=0.0;
  for i in $(seq 1 13); do
    value=$(echo "$value + $($function $i $params)" | bc -l);   
  done;
  value=$(echo "$value / 13.00" | bc -l);
  echo $value;
  return 0;
}

getSpeedup(){
  local instances=$1
  local algorithms=$2

  local value="#thread  bfs dfs greedy  randomic";
  for numberOfThreads in 2 4 8; do
    local line="$numberOfThreads";
    for algorithm in $algorithms; do
      local speedup=0.0;
      for instance in $instances; do
        local sp=$(echo "$(getAverage getExecutionTime "true $instance") / $(getAverage getExecutionTime "false $instance $numberOfThreads $algorithm")" | bc -l);
        speedup=$(echo "$speedup + $sp" | bc -l);
      done;
      speedup=$(echo "$speedup / $(echo "$instances" | wc -w)" | bc -l);
      line="$line $speedup";
    done;
    value="$value"$'\n'"$line";
  done;
  echo "$value";
}

generateDataStallsVsTime(){
  local numberOfThreads=$1;
  local algorithm="randomic";
  local allTimes="";
  for execution in $(seq 1 13); do
    for instance in $(seq 1 8); do
        allTimes="$allTimes"$'\n'"$(getStalls $execution $instance $numberOfThreads $algorithm)";
        allTimes="$allTimes   $(getExecutionTime $execution false $instance $numberOfThreads $algorithm)";
    done;
  done;
  allTimesSorted=$(echo "$allTimes" | sort -n);
  echo "$allTimesSorted";
}

generateDataStallsPerInstance(){
  local numberOfThreads=$1;
  local allStalls="#instance  bfs dfs greedy  randomic";
  for instance in $(seq 1 8); do 
    local line="$instance ";
    for algorithm in bfs dfs greedy randomic; do
      line="$line $(getAverage getStalls "$instance $numberOfThreads $algorithm")";
    done;
    allStalls="$allStalls"$'\n'"$line";
  done;
  echo "$allStalls";
}

generateDataFromPAPI(){
  local PAPI=$1;
  local instance=$2;
  local algorithm=$3;

  local value="Title   1  2  3  4  5  6  7  8"$'\n';
  value="$value\"Seq.\" "$(getAverage getPAPIValue "true $instance $PAPI"); 
  for numberOfThreads in 2 4 8; do
    value="$value"$'\n'"\"$numberOfThreads\"  ";
    for thread in $(seq 0 $(echo "$numberOfThreads - 1" | bc)); do
      value="$value$(getAverage getPAPIValue "false $instance $PAPI $numberOfThreads $thread $algorithm")  ";
    done;
  done;
  echo "$value";
}

generateDataFig1(){
  generateDataStallsVsTime 2;
}

generateDataFig2(){
  generateDataStallsVsTime 4;
}

generateDataFig3(){
  generateDataStallsVsTime 8;
}

generateDataFig5(){
  generateDataStallsPerInstance 2;
}

generateDataFig6(){
  generateDataStallsPerInstance 4;
}

generateDataFig7(){
  generateDataStallsPerInstance 8;
}

generateDataFig8(){
  getSpeedup "$(seq 1 8)" "bfs dfs greedy randomic";
}

generateDataFig9(){
  getSpeedup "16" "bfs dfs greedy randomic";
}

generateDataFig10(){
  generateDataFromPAPI PAPI_L2_TCM 16 randomic;
}

generateDataFig11(){
  generateDataFromPAPI PAPI_L1_TCM 16 randomic;
}

$1;
