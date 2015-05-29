#include <stdio.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

#define MAKE_MAPSET(NAME) \
  int NAME##_mapset(INT elemi[], FLOAT elemf[], INT elemid,              \
                     INT parti[], FLOAT partf[], INT partid, INT partn) { \
    int exit_code=0;  \
    for(partid=0;partid<partn;partid++){   \
      exit_code = NAME##_map(elemi, elemf, elemid,          \
                             parti, partf, partid);  \
    }; \
    return exit_code;       \
  };
