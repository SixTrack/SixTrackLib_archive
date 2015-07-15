#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define monitor_TYPE                                            4
#define monitor_int_nrec                                        0
#define monitor_int_skip                                        1
#define monitor_int_isize                                       2
#define monitor_int_fsize                                       3
#define monitor_int_count                                       4
#define monitor_int_last                                        5
#define monitor_int_index                                       6+last
#define monitor_int_datai                                       6+nrec+last*isize+i
#define monitor_float_dataf                                     last*fsize+i


INT monitor_init(INT elemi[], FLOAT elemf[], INT elemid){
    SETATTRI(monitor,count,0);
    return 1;
}

INT monitor_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT i=0;
    ELEMINIT;
    GETATTRI(monitor,count);
    GETATTRI(monitor,last);
    GETATTRI(monitor,nrec);
    GETATTRI(monitor,skip);
    GETATTRI(monitor,isize);
    GETATTRI(monitor,fsize);
    if(count%skip==0){
        if(last==nrec-1){
            SETATTRI(monitor,last,0);   //last=0;
        }
        else{
            SETATTRI(monitor,last,last+1);  //last++;
        }
        SETATTRI(monitor,index,count);
        for(i=0;i<isize;i++){
            SETATTRI(monitor,datai,parti[i]);
        }
        for(i=0;i<fsize;i++){
            SETATTRF(monitor,dataf,partf[i]);
        }
    }
    SETATTRI(monitor,count,count+1);
    return 1;
}
