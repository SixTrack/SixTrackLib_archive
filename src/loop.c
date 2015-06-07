#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

#define rot2d_TYPE 0
#define kick2d_TYPE 1
#define counter_TYPE 2

INT rot2d_init(INT elemi[], FLOAT elemf[], INT elemid);
INT rot2d_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn);
INT kick2d_init(INT elemi[], FLOAT elemf[], INT elemid);
INT kick2d_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn);
INT counter_init(INT elemi[], FLOAT elemf[], INT elemid);
INT counter_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn);

INT loop_init(INT elemi[], FLOAT elemf[], INT elemid){
    /*int res_into,temp,type_id,res_type;
    res_into = datai[elem_id+4];
    res_type = datai[elem_id+5];
    temp = (res_into-2)/3;
    if(temp%2==0)
        datai[temp/2]=resi;
    else
        dataf[(temp-1)/2]=resf;
    switch(res_type)
    {
        case rot2d_TYPE: 
            update_rot2d(dataf,datai,(temp-1)/2); break;
        case kick2d_TYPE: 
            update_kick2d(dataf, datai); break;
        case counter_TYPE:
            update_counter(dataf, datai); break;
    }  */
    return 1;
}

inline void loop_calc(INT i, INT j, FLOAT cx, FLOAT sx, FLOAT partf[]){
}

/*
INT rot2d_init(INT elemi[], FLOAT elemf[], INT elemid){
    FLOAT angle;
    INT elem_floatid;
    elem_floatid=elemi[elemid+1];
    angle=elemf[elem_floatid];
    elemf[elem_floatid+1]=cos(angle);
    elemf[elem_floatid+2]=sin(angle);
    return 1;
}

inline void rot2d_calc(INT i, INT j, FLOAT cx, FLOAT sx, FLOAT partf[]){
   FLOAT x=partf[i];
   FLOAT y=partf[j];
   partf[i]= cx*x+sx*y;
   partf[j]=-sx*x+cx*y;
}

INT rot2d_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    FLOAT cx,sx;
    INT elem_floatid,ndf,stf,i,j;
    elem_floatid=elemi[elemid+1];
    ndf=parti[1]; 
    stf=parti[3]; 
    i=elemi[elemid+2];
    j=elemi[elemid+3];
    cx=elemf[elem_floatid+1];
    sx=elemf[elem_floatid+2];
    for(partid=0;partid<partn;partid++){
      rot2d_calc(i,j,cx,sx,&partf[stf+partid*ndf]);
    };
    printf("ROT2D:\n");
    print_var(elemi, elemf, parti, partf);
    return 1;
}

INT kick2d_init(INT elemi[], FLOAT elemf[], INT elemid){
    return 1;
}

inline void kick2d_calc(INT i, INT j, FLOAT k, INT o, FLOAT partf[]){
    printf("(i: %d j: %d k: %lf o: %d)\n", i,j,k,o);
    partf[j]+=k*pow(partf[i],o);
}

INT kick2d_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    FLOAT k;
    INT elem_floatid,ndf,stf,o,i,j;
    elem_floatid=elemi[elemid+1];
    ndf=parti[1]; 
    stf=parti[3];     
    i=elemi[elemid+2];
    j=elemi[elemid+3];
    o=elemi[elemid+4];
    k=elemf[elem_floatid];
    for(partid=0;partid<partn;partid++){
      kick2d_calc(i,j,k,o,&partf[stf+partid*ndf]);
    };
    printf("KICK2D:\n");
    print_var(elemi, elemf, parti, partf);
    return 1;
}

INT counter_init(INT elemi[], FLOAT elemf[], INT elemid){    
    return 1;
}

inline void counter_calc(INT *retval, INT count, INT count_max, FLOAT partf[]){
    if (count<count_max){
        *retval=1;
    } 
    else{
        *retval=-1;
    }
}

INT counter_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT ndf,stf,count,count_max,retval=-1;
    ndf=parti[1];
    stf=parti[3];
    count_max=elemi[elemid+2];
    count=elemi[elemid+3]++;
    counter_calc(&retval,count,count_max,&partf[stf+partid*ndf]);
    printf("COUNTER:\n");
    print_var(elemi, elemf, parti, partf);
    return retval;
}
*/

INT loop_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT nelem,mapid,i,id,retval=1;
    nelem=elemi[2];
    while(retval>0){ 
        for(i=0;i<nelem;i++){
            id=elemi[elemid+3+2*i];
            mapid=elemi[elemid+4+2*i];
            printf("|%d|%d|\n", id, mapid);
            switch(mapid){
              case rot2d_TYPE:
                rot2d_init(elemi, elemf, id);
                retval=rot2d_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
              case kick2d_TYPE:
                kick2d_init(elemi, elemf, id);
                retval=kick2d_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
              case counter_TYPE:
                counter_init(elemi, elemf, id);
                retval=counter_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
            }
        }
    }
    return 1;
}

/*
INT map_kcuda_loop(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid){
    //to be completed
    return 1;
}


INT map_kopencl_loop(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid){
    //to be completed
    return 1;
}
*/

/*
elemi: {mapid, mapst, attr1, attr..., mapid, mapst}
elemf: {attr1,attr...,attr1,attr...,}
parti: {npart,ndf,ndi,stf,sti}
partf: {const1,....,coord1,...,coord<ndf>,coord1,....,coord<ndf>}
*/

//for checking
void print_var(INT elemi[], FLOAT elemf[], INT parti[], FLOAT partf[]){
    INT i;

    printf("elemi: {");
    for(i=0;i<27;i++){
        printf("%d, ",elemi[i]);
    }
    printf("%d}\n",elemi[i]);

    printf("elemf: {");
    for(i=0;i<6;i++){
        printf("%f, ",elemf[i]);
    }
    printf("%f}\n",elemf[i]);

    printf("parti: {");
    for(i=0;i<4;i++){
        printf("%d, ",parti[i]);
    }
    printf("%d}\n", parti[i]);

    printf("partf: {");
    for(i=0;i<1;i++){
        printf("%f, ",partf[i]);
    }
    printf("%f}\n\n",partf[i]);
}
/*#define PI (3.141592653589793)

int main(){
    INT elemi[] = { 3,-1,4,7,11,15,20,
                    0,0,0,1,
                    0,3,0,1,
                    1,6,0,1,2,
                    2,-1,2,1};

    FLOAT elemf[] = { PI/2,0,0,
                      PI/4,0,0,
                      0.3};
    INT elemid = 0;
    INT parti[] = {1,2,0,0,0};
    FLOAT partf[] = {12,2};
    INT npart=parti[0];
    INT partid = 0;
    //loop_init(elemi, elemf, elemid);
    print_var(elemi, elemf, parti, partf);
    printf("%d\n", loop_map(elemi, elemf, elemid,
                                parti, partf, partid, npart));
    print_var(elemi, elemf, parti, partf);
    return 0;
}*/
