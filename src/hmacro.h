
#define rot2d_TYPE 0
#define kick2d_TYPE 1
#define counter_TYPE 2

#define ELEMINIT \
 elem_floatid=elemi[elemid+1];

#define GETATTRF(type,name)     \
 name=elemf[elem_floatid+type##_##name];

#define GETATTRI(type,name)   \
 name=elemi[elemid+2+type##_##name];

#define rot2d_angle  0
#define rot2d_cx  1
#define rot2d_sx  2

#define GETPARTF \
 ndf=parti[1]; \
 stf=parti[3]; \
 pfstart=stf+ndf*partid; \

#define GETPARTI \
 ndi=parti[2]; \
 sti=parti[4]; \
 pistart=stf+ndi*partid; \

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