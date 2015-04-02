#ifndef BIN2ASC_H
#define BIN2ASC_H

#include <stdio.h>

/* If you change MAX_NR_VERTICES, change MAX_NR_VERTICESdiv8 to be
 * the 1/8th of it */
#include <functional>
#define MAX_NR_VERTICES 20000
#define MAX_NR_VERTICESdiv8 2500
using namespace std;
extern int Nr_vert, Nr_edges;
extern char Bitmap[MAX_NR_VERTICES][MAX_NR_VERTICESdiv8];

#define MAX_PREAMBLE 10000
extern char Preamble[MAX_PREAMBLE];

extern void write_graph_DIMACS_ascii(char*, function<void(int,int)>);

#endif
