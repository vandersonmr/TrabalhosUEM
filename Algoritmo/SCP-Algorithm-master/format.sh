#!/bin/bash
head -n 1 $1 | sed 's/LINHAS//g' | sed 's/ //g' > .aux
tail $1 -n $(echo $(cat $1 | wc -l) - 3 | bc) | sed 's/  / /g' | sed 's/  / /g' | sed 's/  / /g' >> .aux
mv .aux $1
