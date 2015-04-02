ALL:
	cd ./src/simulator/; \
	gcc  -Wall -Wextra -O3 auxFunctions.c logicUnit.c interface.c execution.c memory.c registerBank.c simulator.c -I./headers/ -o ../../sim; \
	cd ../../
debug:
	cd ./src/simulator/; \
	gcc -w -g -O0 auxFunctions.c logicUnit.c interface.c execution.c memory.c registerBank.c simulator.c -I./headers/ -g -o ../../sim; \
	cd ../../
clear:
	cd ./src/simulator/; \
	rm sim; \
	cd ../../

