#define ELEMINIT \
 INT elem_floatid; \
 elem_floatid=elemi[elemid+1];

#define GETATTRF(type,name)     \
 FLOAT name;                     \
 name=elemf[elem_floatid+type##_float_##name];

#define SETATTRF(type,name,value)     \
 elemf[elem_floatid+type##_float_##name]=value;

#define GETATTRI(type,name)   \
 INT name ;\
 name=elemi[elemid+2+type##_int_##name];


#define rot2d_TYPE 0
#define kick2d_TYPE 1
#define counter_TYPE 2

#define rot2d_float_angle  0
#define rot2d_float_cx  1
#define rot2d_float_sx  2
#define rot2d_int_i   0
#define rot2d_int_j   1


#define kick2d_float_k   0 //float
#define kick2d_int_i   0
#define kick2d_int_j   1
#define kick2d_int_o   2





#define INITPARTF \
 int ndf, stf; \
 ndf=parti[1]; \
 stf=parti[3]; \

#define INITPARTI \
 int ndi, sti; \
 ndi=parti[2]; \
 sti=parti[4]; \

#define GETPARTF(partid) \
 &partf[stf+ndf*partid]

#define GETPARTI(partid) \
 &parti[sti+ndi*partid]


#define GETCOORDF(type,name) \
 name=partf[pfstart+type##_##name]

#define GETCOORDI(type,name) \
 name=parti[pfstart+type##_##name]

#define six_x 0
#define six_px 1
#define six_y 2
#define six_py 3

// GETCOORDF(six,x);
// GETCOORDF(six,px);
