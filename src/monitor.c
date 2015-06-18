#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

void print_var(INT [], FLOAT [], INT [], FLOAT [], INT);

INT monitor_init(INT elemi[], FLOAT elemf[], INT elemid){
    return 1;
}

INT monitor_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT i=0;
    ELEMINIT;
    GETATTRI(monitor,count);
    GETATTRI(monitor,last);
    GETATTRI(monitor,nrec);
    GETATTRI(monitor,skip);
    INITPARTI;
    INITPARTF;
    if(count%skip==0){
        if(last==nrec-1){
            SETATTRI(monitor,last,0);   //last=0;
        }
        else{
            SETATTRI(monitor,last,last+1);  //last++;
        }
        SETATTRI(monitor,index,count);
        for(i=0;i<ndi;i++){
            SETATTRI(monitor,datai,parti[sti+ndi*partid+i]);
        }
        for(i=0;i<ndf;i++){
            SETATTRF(monitor,dataf,partf[stf+ndf*partid+i]);
        }
    }
    SETATTRI(monitor,count,count+1);
    print_var(elemi, elemf, parti, partf, monitor_TYPE);
    return 1;
}
