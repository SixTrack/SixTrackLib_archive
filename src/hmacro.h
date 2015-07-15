#define OnePoweredToMinus38       1.0e-38
#define OnePoweredTo3             1.0e3
#define One 					  1.0	
#define Pi                        4.0*atan(1.0)

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

#define ELEMINIT \
 INT elem_floatid; \
 elem_floatid=elemi[elemid+1];

#define GETATTRF(type,name) \
 FLOAT name;                     \
 name=elemf[elem_floatid+type##_float_##name];

#define SETATTRF(type,name,value)     \
 elemf[elem_floatid+type##_float_##name]=value;

#define GETATTRI(type,name)   \
 INT name ; \
 name=elemi[elemid+2+type##_int_##name];

#define SETATTRI(type,name,value)   \
 elemi[elemid+2+type##_int_##name]=value;

#define GETATTRIDEBUG(type,name)   \
 INT name ;\
 name=elemi[elemid+2+type##_int_##name]; \
 printf(#type":"#name"-> %d \n",name);

#define INITPARTF \
 INT ndf, stf, pfstart; \
 ndf=parti[1]; \
 stf=parti[3]; \
 pfstart=stf+ndf*partid; 

#define INITPARTI \
 INT ndi, sti, pistart; \
 ndi=parti[2]; \
 sti=parti[4]; \
 pistart=sti+ndi*partid; 

#define GETPARTF(partid) \
 &partf[stf+ndf*partid]

#define GETPARTI(partid) \
 &parti[sti+ndi*partid]

#define GETCOORDF(type,name) \
 FLOAT name; \
 name=partf[pfstart+type##_##name];

#define SETCOORDF(type,name,value) \
 partf[pfstart+type##_##name]=value;

#define GETCOORDI(type,name) \
 INT name; \
 name=parti[pistart+type##_##name];

#define SETCOORDI(type,name,value) \
 parti[pistart+type##_##name]=value;


#define partf_p0                                                0
#define partf_beta0                                             1
#define partf_gamma0                                            2
#define partf_m0                                                3
#define partf_E0                                                4
#define partf_x                                                 5
#define partf_px                                                6
#define partf_y                                                 7
#define partf_py                                                8
#define partf_ds                                                9
#define partf_ps                                                10
#define partf_s                                                 11
#define partf_m                                                 12
#define partf_q                                                 13
//following are not mentioned in the wiki
#define partf_crxbj 10
#define partf_crzbj 11
#define partf_cbxbj 3
#define partf_cbzbj 2