#define OnePoweredToMinus3  1.0e-3
#define OnePoweredTo3       1.0e3
#define One                 1.0

#define ELEMINIT \
 INT elem_floatid; \
 elem_floatid=elemi[elemid+1];

#define GETATTRF(type,name)     \
 FLOAT name;                     \
 name=elemf[elem_floatid+type##_float_##name];

#define thin4d_exact_drift_float_PhysicalLengthOfBlock 0
#define thin6d_exact_drift_float_PhysicalLengthOfBlock 0

#define INITPARTF \
 INT ndf, psf, pfstart; \
 ndf=parti[1]; \
 psf=parti[3]; \
 pfstart=psf+ndf*partid; 

#define INITPARTI \
 INT ndi, psi, pistart; \
 ndi=parti[2]; \
 psi=parti[4]; \
 pistart=psi+ndi*partid; 

#define GETPARTF(partid) \
 &partf[psf+ndf*partid]

#define GETCOORDF(type,name) \
 FLOAT name; \
 name=partf[pfstart+type##_##name];

#define SETCOORDF(type,name,value)     \
 partf[elem_floatid+type##_##name]=value;

#define GETCOORDI(type,name) \
 INT name; \
 name=parti[pistart+type##_##name];

#define SETCOORDI(type,name,value)     \
 parti[elem_floatid+type##_##name]=value; 

#define partf_p0 0
#define partf_beta0 1
#define partf_gamma0 2
#define partf_m0 3
#define partf_E0 4
#define partf_x 5
#define partf_y 6
#define partf_px 7
#define partf_py 8
#define partf_ct 9
#define partf_dp 10
#define partf_pt 11
#define partf_s 12
#define partf_m 13
#define partf_q 14
#define partf_PathLengthDiff 5	//doubt (no such variable mentioned in wiki)
#define partf_RatioBetaToBetaj 12 //doubt (no such variable mentioned in wiki)