#include <stdio.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

#define make_map(NAME,ND) \
  int  map_vec_##NAME(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid) { \
    int iii,exit_code; exit_code=0;         \
    int np = parti[0];  \
    for(iii=0;iii<np;iii=iii+1){   \
      exit_code=map_##NAME(elemi, elemf, elemid, parti, partf, partid);  \
      if (exit_code<0){ break;};  \
    }; \
         return exit_code;       \
  }; \

#define make_vecmap(NAME,ND) \
  int  map_vec_mul_##NAME(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn) { \
    int iii,exit_code; exit_code=0;         \
    int np = parti[0];  \
    for(iii=0;iii<np;iii=iii+1){   \
      exit_code=map_mul_##NAME(elemi, elemf, elemid, parti, partf, partid, partn);  \
      if (exit_code<0){ break;};  \
    }; \
         return exit_code;       \
  }; 
