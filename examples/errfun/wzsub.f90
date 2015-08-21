subroutine wzset
!  *********************************************************************
!
!  This subroutine must be called before subroutine WZSUB can be used to
!  compute values of the complex error function w(z).
!
!  Parameters xcut and ycut specify the opposite corners (xcut,0) and
!  (0,ycut) of the rectangle inside which interpolation is to be used
!  by subroutine WZSUB.
!
!  Parameter h is the side of the squares of the interpolation grid.
!
!  Parameters nx and ny must be set to the nearest integers to xcut/h
!  and ycut/h respectively (or to larger values).
!
!  Calls MYWWERF new version of (CERN library) WWERF (C335)
!
!  (G.A.Erskine, 29.09.1995)
!
!  *********************************************************************
      implicit none
!       real(8) sin_rn,cos_rn,tan_rn,sinh_rn,cosh_rn,asin_rn,    &
!      &acos_rn,atan_rn,atan2_rn,exp_rn,log_rn,log10_rn
      integer i,j,k
      real(8) wi,wr,x,y
!       integer mbea,mcor,mcop,mmul,mpa,mran,nbb,nblo,nblz,ncom,ncor1,    &
!      &nelb,nele,nema,ninv,nlya,nmac,nmon1,npart,nper,nplo,npos,nran,    &
!      &nrco,ntr,nzfz
!       parameter(npart = 64,nmac = 1)
!       parameter(nele=1200,nblo=600,nper=16,nelb=140,nblz=20000,         &
!      &nzfz = 300000,mmul = 20)
!       parameter(nran = 2000000,ncom = 100,mran = 500,mpa = 6,nrco = 5,  &
!      &nema = 15)
!       parameter(mcor = 10,mcop = mcor+6, mbea = 99)
!       parameter(npos = 20000,nlya = 10000,ninv = 1000,nplo = 20000)
!       parameter(nmon1 = 600,ncor1 = 600)
!       parameter(ntr = 20,nbb = 350)
      integer idim,kstep,nx,ny
      real(8) h,half,hrecip,one,wtimag,wtreal,xcut,ycut
      parameter ( xcut = 7.77d0, ycut = 7.46d0 )
      parameter ( h = 1.d0/63.d0 )
      parameter ( nx = 490, ny = 470 )
      parameter ( idim = 492*472 )
      parameter ( half = 0.5d0, one = 1.d0 )
      common /wzcom1/ hrecip, kstep
      common /wzcom2/ wtreal(idim), wtimag(idim)
      save
!-----------------------------------------------------------------------
      hrecip = 1.d0/h
      kstep = nx+2
      k = 0
      do 2 j=0,ny+1
         do 1 i=0,nx+1
            k = k+1
!hr05       x=i*h
            x=dble(i)*h                                                  !hr05
!hr05       y=j*h
            y=dble(j)*h                                                  !hr05
            call mywwerf(x,y,wr,wi)
            wtreal(k)=wr
            wtimag(k)=wi
 1       continue
 2    continue
      end subroutine wzset

      subroutine mywwerf(x,y,wr,wi)
      implicit none
      real(8), INTENT(IN):: x,y
      real(8), INTENT(OUT):: wr,wi
!       real(8) sin_rn,cos_rn,tan_rn,sinh_rn,cosh_rn,asin_rn,    &
!      &acos_rn,atan_rn,atan2_rn,exp_rn,log_rn,log10_rn
      integer n
      real(8) c,c1,c2,c3,c4,hf,p,rr,ri,sr0,sr,si,tr,ti,vi,vr,  &
     &xa,xl,ya,zhi,zhr,z1,z10
     parameter (z1=1,hf=1/2d0,z10=10d0)
     parameter (c1=74d0/10d0,c2=83d0/10d0,c3=10d0/32d0,c4=16d0/10d0)
! !       parameter (z1=1,hf=z1/2d0,z10=10d0)
! !       parameter (c1=74d0/z10,c2=83d0/z10,c3=z10/32d0,c4=16d0/z10)
! !     parameter (c=1.12837916709551257d0,p=(2d0*c4)**33)
      parameter (c=1.12837916709551257d0,p=46768052394588893.3825d0)
      dimension rr(37),ri(37)
      save
! !-----------------------------------------------------------------------
      xa=abs(x)
      ya=abs(y)
!       WRITE(*,'(A,e23.16, e23.16)') "F",xa,ya
      if(ya.lt.c1.and.xa.lt.c2) then
!        zh=dcmplx(ya+c4,xa)
        zhr=ya+c4
        zhi=xa
        rr(37)=0d0
        ri(37)=0d0
        do n=36,1,-1
!          t=zh+n*dconjg(r(n+1))
!hr05     tr=zhr+n*rr(n+1)
          tr=zhr+dble(n)*rr(n+1)                                         !hr05
!hr05     ti=zhi-n*ri(n+1)
          ti=zhi-dble(n)*ri(n+1)                                         !hr05
!          r(n)=hf*t/(dreal(t)**2+dimag(t)**2)
!hr05     rr(n)=hf*tr/(tr**2+ti**2)
          rr(n)=(hf*tr)/(tr**2+ti**2)                                    !hr05
!hr05     ri(n)=hf*ti/(tr**2+ti**2)
          ri(n)=(hf*ti)/(tr**2+ti**2)                                    !hr05
        enddo
        xl=p
        sr=0d0
        si=0d0
        do n=33,1,-1
          xl=c3*xl
!          s=r(n)*(s+xl)
          sr0=rr(n)*(sr+xl)-ri(n)*si
          si=rr(n)*si+ri(n)*(sr+xl)
          sr=sr0
        enddo
!        v=c*s
        vr=c*sr
        vi=c*si
      else
        zhr=ya
        zhi=xa
        rr(1)=0d0
        ri(1)=0d0
        do n=9,1,-1
!          t=zh+n*dconjg(r(1))
!hr05     tr=zhr+n*rr(1)
          tr=zhr+dble(n)*rr(1)                                           !hr05
!hr05     ti=zhi-n*ri(1)
          ti=zhi-dble(n)*ri(1)                                           !hr05
!          r(1)=hf*t/(dreal(t)**2+dimag(t)**2)
!hr05     rr(1)=hf*tr/(tr**2+ti**2)
          rr(1)=(hf*tr)/(tr**2+ti**2)                                    !hr05
!hr05     ri(1)=hf*ti/(tr**2+ti**2)
          ri(1)=(hf*ti)/(tr**2+ti**2)                                    !hr05
        enddo
!        v=c*r(1)
        vr=c*rr(1)
        vi=c*ri(1)
      endif
!hr05 if(ya.eq.0) then
      if(ya.eq.0d0) then                                                 !hr05
!        v=dcmplx(exp(-xa**2),dimag(v))
!hr05   vr=exp_rn(-xa**2)
        vr=exp(-1d0*xa**2)                                            !hr05
      endif
      if(y.lt.0d0) then
!        v=2*exp(-dcmplx(xa,ya)**2)-v
!hr05   vr=2d0*exp_rn(ya**2-xa**2)*cos_rn(2d0*xa*ya)-vr
        vr=(2d0*exp(ya**2-xa**2))*cos((2d0*xa)*ya)-vr              !hr05
        vi=(-2d0*exp(ya**2-xa**2))*sin((2d0*xa)*ya)-vi             !hr05
!hr05   if(x.gt.0) vi=-vi
        if(x.gt.0d0) vi=-1d0*vi                                          !hr05
      else
!hr05   if(x.lt.0) vi=-vi
        if(x.lt.0d0) vi=-1d0*vi                                          !hr05
      endif
      wr=vr
      wi=vi
      return
      end subroutine mywwerf

      subroutine wzsub(x,y,u,v)
!  *********************************************************************
!
!  This subroutine sets u=real(w(z)) and v=imag(w(z)), where z=x+i*y and
!  where w(z) is the complex error function defined by formula 7.1.3 in
!  "Handbook of Mathematical functions [eds. M.Abramowitz & I.A.Stegun,
!  Washington, 1966].  The absolute error of the computed value is less
!  than 1E-8.
!
!  *** Note.  Subroutine WZSET must have been called before this sub-
!  routine can be used.
!
!  For (x,y) inside the rectangle with opposite corners (xcut,0) and
!  (0,ycut), where xcut and ycut have been set by WZSET, an interpo-
!  lation formula is used.  For (x,y) outside this rectangle, a two-
!  term rational approximation is used.
!
!  (G.A.Erskine, 29.09.1997)
!
!
!  Third-order divided-difference interpolation over the corners of a
!  square [e.g. formula (2.5.1) in "Introduction to Numerical Analysis"
!  (F.B.Hildebrand New York, 1957), but with complex nodes and
!  function values].
!
!  In the interpolation formula the corners of the grid square contain-
!  ing (x,y) are numbered (0,0)=3, (h,0)=4, (h,h)=1, (0,h)=2.
!  Identifiers d, dd and ddd denote divided-differences of orders 1, 2
!  and 3 respectively, and a preceding 't' indicates twice the value.
!
!  *********************************************************************
      implicit none
      real(8), INTENT(IN):: x,y
      real(8), INTENT(OUT):: u,v
      integer k,mu,nu
      real(8) a1,a2,b1,b2,d12i,d12r,d23i,d23r,d34i,d34r,p,     &
     &q,qsq,r,simag,sreal,t,tdd13i,tdd13r,tdd24i,tdd24r,tdddi,tdddr,ti, &
     &tr,usum,usum3,vsum,vsum3,w1i,w1r,w2i,w2r,w3i,w3r,w4i,w4r,xh,&
     &xhrel,yh,yhrel
! !       integer mbea,mcor,mcop,mmul,mpa,mran,nbb,nblo,nblz,ncom,ncor1,    &
! !      &nelb,nele,nema,ninv,nlya,nmac,nmon1,npart,nper,nplo,npos,nran,    &
! !      &nrco,ntr,nzfz
! !       parameter(npart = 64,nmac = 1)
! !       parameter(nele=1200,nblo=600,nper=16,nelb=140,nblz=20000,         &
! !      &nzfz = 300000,mmul = 20)
! !       parameter(nran = 2000000,ncom = 100,mran = 500,mpa = 6,nrco = 5,  &
! !      &nema = 15)
! !       parameter(mcor = 10,mcop = mcor+6, mbea = 99)
! !       parameter(npos = 20000,nlya = 10000,ninv = 1000,nplo = 20000)
! !       parameter(nmon1 = 600,ncor1 = 600)
! !       parameter(ntr = 20,nbb = 350)
      integer idim,kstep,nx,ny
      real(8) h,half,hrecip,one,wtimag,wtreal,xcut,ycut
      parameter ( xcut = 7.77d0, ycut = 7.46d0 )
      parameter ( h = 1.d0/63.d0 )
      parameter ( nx = 490, ny = 470 )
      parameter ( idim = 492*472 )
      parameter ( half = 0.5d0, one = 1.d0 )
      common /wzcom1/ hrecip, kstep
      common /wzcom2/ wtreal(idim), wtimag(idim)
      parameter ( a1 = 0.5124242248d0, a2 = 0.0517653588d0 )
      parameter ( b1 = 0.2752551286d0, b2 = 2.7247448714d0 )
      save
! !-----------------------------------------------------------------------
      if ( x.ge.xcut .or. y.ge.ycut ) goto 1000
      xh = hrecip*x
      yh = hrecip*y
      mu = int(xh)
      nu = int(yh)
!  Compute divided differences.
      k = 2 + mu + nu*kstep
      w4r = wtreal(k)
      w4i = wtimag(k)
      k = k - 1
      w3r = wtreal(k)
      w3i = wtimag(k)
      d34r = w4r - w3r
      d34i = w4i - w3i
      k = k + kstep
      w2r = wtreal(k)
      w2i = wtimag(k)
      d23r = w2i - w3i
      d23i = w3r - w2r
      tr = d23r - d34r
      ti = d23i - d34i
      tdd24r = ti - tr
!hr05 tdd24i = - ( tr + ti )
      tdd24i = -1d0* ( tr + ti )                                         !hr05
      k = k + 1
      w1r = wtreal(k)
      w1i = wtimag(k)
      d12r = w1r - w2r
      d12i = w1i - w2i
      tr = d12r - d23r
      ti = d12i - d23i
      tdd13r = tr + ti
      tdd13i = ti - tr
      tdddr = tdd13i - tdd24i
      tdddi = tdd24r - tdd13r
!  Evaluate polynomial.
      xhrel = xh - dble(mu)
      yhrel = yh - dble(nu)
      usum3 = half*( tdd13r + ( xhrel*tdddr - yhrel*tdddi ) )
      vsum3 = half*( tdd13i + ( xhrel*tdddi + yhrel*tdddr ) )
      yhrel = yhrel - one
      usum = d12r + ( xhrel*usum3 - yhrel*vsum3 )
      vsum = d12i + ( xhrel*vsum3 + yhrel*usum3 )
      xhrel = xhrel - one
      u = w1r + ( xhrel*usum - yhrel*vsum )
      v = w1i + ( xhrel*vsum + yhrel*usum )
      return
!
!  Two-term rational approximation to w(z) [Footnote to Table 7.9
!  in "Handbook of Mathematical Functions (eds. M.Abramowitz &
!  I.A.Stegun, Washington, 1966), but with additional digits in
!  the constants]:
!              u+i*v = i*z*( a1/(z**2-b1) + a2/(z**2-b2) ).
!  Maximum absolute error:
!        <1.E-6  for  x>=4.9  or  y>=4.4
!        <1.E-7  for  x>=6.1  or  y>=5.7
!        <1.E-8  for  x>=7.8  or  y>=7.5
!
 1000 p=x**2-y**2
!hr05 q=2.d0*x*y
      q=(2.d0*x)*y                                                       !hr05
      qsq=q**2
!  First term.
      t=p-b1
      r=a1/(t**2+qsq)
      sreal=r*t
!hr05 simag=-r*q
      simag=(-1d0*r)*q                                                   !hr05
!  Second term
      t=p-b2
      r=a2/(t**2+qsq)
      sreal=sreal+r*t
      simag=simag-r*q
!  Multiply by i*z.
!hr05 u=-(y*sreal+x*simag)
      u=-1d0*(y*sreal+x*simag)                                           !hr05
      v=x*sreal-y*simag
      return
end subroutine wzsub