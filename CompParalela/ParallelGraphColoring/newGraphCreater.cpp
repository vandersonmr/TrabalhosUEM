#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv) {
  long long int p,e;
  scanf("p edge %lld %lld\n", &p, &e);
  int m = atoi(argv[1]);
  printf("p edge %lld %lld\n", p*m, (e*m)+(m*atoi(argv[2])));
  for(int i=0; i < e; i++) {
    long long int a,b;
    scanf("e %lld %lld\n", &a, &b);
    for(int j = 0; j < m; j++) {
      printf("e %lld %lld\n", a+(p*j), b+(p*j));
    }
  }

  for(int j = 0; j < m; j++) {
    for(int i=0; i < atoi(argv[2]); i++) {
      long long int a = (rand() % p + 1) + (p*j);  
      long long int b = (rand() % p + 1) + ((rand() % m)*p);  
      printf("e %lld %lld\n", a, b);
    }
  }
  return 0;
}
