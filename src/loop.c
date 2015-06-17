#include "hmacro.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

INT rot2d_init(INT [], FLOAT [], INT );
INT rot2d_map(INT [], FLOAT [], INT , INT [], FLOAT [], INT , INT );
INT kick2d_init(INT [], FLOAT [], INT );
INT kick2d_map(INT [], FLOAT [], INT , INT [], FLOAT [], INT , INT );
INT counter_init(INT [], FLOAT [], INT );
INT counter_map(INT [], FLOAT [], INT , INT [], FLOAT [], INT , INT );

INT loop_init(INT elemi[], FLOAT elemf[], INT elemid){
    INT nelem,mapid,id,i;
    nelem=elemi[2];
    for(i=0;i<nelem;i++){
        id=elemi[elemid+3+2*i];
        mapid=elemi[elemid+4+2*i];
        switch(mapid){
            case rot2d_TYPE:
                rot2d_init(elemi, elemf, id);
                break;
            case counter_TYPE:
                counter_init(elemi, elemf, id);
                break;
        }
    }
    return 1;
}

INT loop_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT nelem,mapid,i,id,retval=1;
    nelem=elemi[2];
    while(retval>0){ 
        for(i=0;i<nelem;i++){
            id=elemi[elemid+3+2*i];
            mapid=elemi[elemid+4+2*i];
            switch(mapid){
              case rot2d_TYPE:
                retval=rot2d_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
              case kick2d_TYPE:
                retval=kick2d_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
              case counter_TYPE:
                retval=counter_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
            }
        }
    }
    return 1;
}