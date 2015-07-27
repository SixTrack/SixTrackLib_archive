#define OnePoweredToMinus38       1.0e-38
#define OnePoweredTo3             1.0e3
#define One                       1.0
#define Pi                        4.0*atan(1.0)
#define Clight                    299792458

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

#define INITPARTI \
 INT ndi, sti, pistart; \
 ndi=parti[2]; \
 sti=parti[4]; \

#define GETPARTF(partid) \
 &partf[stf+ndf*partid]

#define GETPARTI(partid) \
 &parti[sti+ndi*partid]

#define GETCOORDF(type,name) \
 FLOAT name; \
 name=partf[stf+ndf*partid+type##_##name];

#define SETCOORDF(type,name,value) \
 coordf[type##_##name]=value;

#define GETCOORDI(type,name) \
 INT name; \
 name=parti[sti+ndi*partid+type##_##name];

#define SETCOORDI(type,name,value) \
 coordi[type##_##name]=value;

#define GETCONSTF(type,name) \
 FLOAT name; \
 name=partf[type##_##name];

#define partf_p0                                                0
#define partf_beta0                                             1
#define partf_gamma0                                            2
#define partf_m0                                                3
#define partf_E0                                                4
// #define partf_q0                                                5
#define partf_x                                                 0
#define partf_px                                                1
#define partf_y                                                 2
#define partf_py                                                3
#define partf_tau                                               4
#define partf_pt                                                5
#define partf_delta                                             6
#define partf_s                                                 7
#define partf_chi                                               8
// #define partf_q                                                 9

#define coordf_p0                                                0
#define coordf_beta0                                             1
#define coordf_gamma0                                            2
#define coordf_m0                                                3
#define coordf_E0                                                4
// #define coordf_q0                                                5
#define coordf_x                                                 0
#define coordf_px                                                1
#define coordf_y                                                 2
#define coordf_py                                                3
#define coordf_tau                                               4
#define coordf_pt                                                5
#define coordf_delta                                             6
#define coordf_s                                                 7
#define coordf_chi                                               8
// #define coordf_q                                                 9
//following are not mentioned in the wiki
#define partf_crxbj 0
#define partf_crzbj 1
#define partf_cbxbj 2
#define partf_cbzbj 3

#define parti_pid                                               0
#define parti_tlost                                             1
#define parti_parent                                            2
