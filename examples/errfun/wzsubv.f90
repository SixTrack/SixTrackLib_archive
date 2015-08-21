      subroutine wzsubv(napx,vx,vy,vu,vv)
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
!  Vectorised for up to 64 argument values by E.McIntosh, 30.10.1997.
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
!  *********************************************************************
      implicit none
      integer(4), INTENT(IN):: napx
      real(8), INTENT(IN):: vx,vy
      real(8), INTENT(OUT):: vu,vv
!       double precision sin_rn,cos_rn,tan_rn,sinh_rn,cosh_rn,asin_rn,    &
!      &acos_rn,atan_rn,atan2_rn,exp_rn,log_rn,log10_rn
      integer j,k,vmu,vnu
      real(8) a1,a2,b1,b2,ss,vd12i,vd12r,vd23i,vd23r,          &
     &vd34i,vd34r,vp,vq,vqsq,vr,vsimag,vsreal,vt,vtdd13i,vtdd13r,       &
     &vtdd24i,vtdd24r,vtdddi,vtdddr,vti,vtr,vusum,vusum3,         &
     &vvsum,vvsum3,vw1i,vw1r,vw2i,vw2r,vw3i,vw3r,vw4i,vw4r,          &
     &vxh,vxhrel,vyh,vyhrel
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
      double precision h,half,hrecip,one,wtimag,wtreal,xcut,ycut
      parameter ( xcut = 7.77d0, ycut = 7.46d0 )
      parameter ( h = 1.d0/63.d0 )
      parameter ( nx = 490, ny = 470 )
      parameter ( idim = 492*472 )
      parameter ( half = 0.5d0, one = 1.d0 )
      common /wzcom1/ hrecip, kstep
      common /wzcom2/ wtreal(idim), wtimag(idim)
      parameter ( a1 = 0.5124242248d0, a2 = 0.0517653588d0 )
      parameter ( b1 = 0.2752551286d0, b2 = 2.7247448714d0 )
!     temporary arrays to facilitate vectorisation
      dimension vx(64),vy(64),vu(64),vv(64)
      dimension vsreal(64),vsimag(64),vp(64),vq(64)
      dimension vqsq(64),vt(64),vr(64)
      dimension vxh(64),vyh(64),vmu(64),vnu(64)
      dimension vw4r(64),vw4i(64)
      dimension vw3r(64),vw3i(64),vd34r(64),vd34i(64)
      dimension vw2r(64),vw2i(64),vd23r(64),vd23i(64)
      dimension vtr(64),vti(64),vtdd24r(64),vtdd24i(64)
      dimension vw1r(64),vw1i(64)
      dimension vd12r(64),vd12i(64),vtdd13r(64),vtdd13i(64)
      dimension vtdddr(64),vtdddi(64),vxhrel(64),vyhrel(64)
      dimension vusum(64),vvsum(64),vusum3(64),vvsum3(64)
      save
!-----------------------------------------------------------------------
      ss=0d0
      do j=1,napx
!     if ( vx.ge.xcut .or. vy.ge.ycut )
        ss=ss+sign(1.0d0,                                               &
     &sign(1.0d0,vx(j)-xcut)+sign(1.0d0,vy(j)-ycut))
      enddo
!
      if (nint(ss).eq.napx) then
!     everything outside the rectangle so approximate
 
        do j=1,napx
 
      vp(j)=vx(j)**2-vy(j)**2
!hr05 vq(j)=2.d0*vx(j)*vy(j)
      vq(j)=(2.d0*vx(j))*vy(j)                                           !hr05
      vqsq(j)=vq(j)**2
!  First term.
      vt(j)=vp(j)-b1
      vr(j)=a1/(vt(j)**2+vqsq(j))
      vsreal(j)=vr(j)*vt(j)
!hr05 vsimag(j)=-vr(j)*vq(j)
      vsimag(j)=(-1d0*vr(j))*vq(j)                                       !hr05
!  Second term
      vt(j)=vp(j)-b2
      vr(j)=a2/(vt(j)**2+vqsq(j))
      vsreal(j)=vsreal(j)+vr(j)*vt(j)
      vsimag(j)=vsimag(j)-vr(j)*vq(j)
!  Multiply by i*z.
!hr05 vu(j)=-(vy(j)*vsreal(j)+vx(j)*vsimag(j))
      vu(j)=-1d0*(vy(j)*vsreal(j)+vx(j)*vsimag(j))                       !hr05
      vv(j)=vx(j)*vsreal(j)-vy(j)*vsimag(j)
        enddo
 
      elseif (nint(ss).ne.-napx) then
!     we have a mixture
 
        do j=1,napx
 
          if ( vx(j).ge.xcut .or. vy(j).ge.ycut ) then
 
      vp(j)=vx(j)**2-vy(j)**2
!hr05 vq(j)=2.d0*vx(j)*vy(j)
      vq(j)=(2.d0*vx(j))*vy(j)                                           !hr05
      vqsq(j)=vq(j)**2
!  First term.
      vt(j)=vp(j)-b1
      vr(j)=a1/(vt(j)**2+vqsq(j))
      vsreal(j)=vr(j)*vt(j)
!hr05 vsimag(j)=-vr(j)*vq(j)
      vsimag(j)=(-1d0*vr(j))*vq(j)                                       !hr05
!  Second term
      vt(j)=vp(j)-b2
      vr(j)=a2/(vt(j)**2+vqsq(j))
      vsreal(j)=vsreal(j)+vr(j)*vt(j)
      vsimag(j)=vsimag(j)-vr(j)*vq(j)
!  Multiply by i*z.
!hr05 vu(j)=-(vy(j)*vsreal(j)+vx(j)*vsimag(j))
      vu(j)=-1d0*(vy(j)*vsreal(j)+vx(j)*vsimag(j))                       !hr05
      vv(j)=vx(j)*vsreal(j)-vy(j)*vsimag(j)
 
          else
 
      vxh(j) = hrecip*vx(j)
      vyh(j) = hrecip*vy(j)
      vmu(j) = int(vxh(j))
      vnu(j) = int(vyh(j))
!  Compute divided differences.
      k = 2 + vmu(j) + vnu(j)*kstep
      vw4r(j) = wtreal(k)
      vw4i(j) = wtimag(k)
      k = k - 1
      vw3r(j) = wtreal(k)
      vw3i(j) = wtimag(k)
      vd34r(j) = vw4r(j) - vw3r(j)
      vd34i(j) = vw4i(j) - vw3i(j)
      k = k + kstep
      vw2r(j) = wtreal(k)
      vw2i(j) = wtimag(k)
      vd23r(j) = vw2i(j) - vw3i(j)
      vd23i(j) = vw3r(j) - vw2r(j)
      vtr(j) = vd23r(j) - vd34r(j)
      vti(j) = vd23i(j) - vd34i(j)
      vtdd24r(j) = vti(j) - vtr(j)
!hr05 vtdd24i(j) = - ( vtr(j) + vti(j) )
      vtdd24i(j) = -1d0* ( vtr(j) + vti(j) )                             !hr05
      k = k + 1
      vw1r(j) = wtreal(k)
      vw1i(j) = wtimag(k)
      vd12r(j) = vw1r(j) - vw2r(j)
      vd12i(j) = vw1i(j) - vw2i(j)
      vtr(j) = vd12r(j) - vd23r(j)
      vti(j) = vd12i(j) - vd23i(j)
      vtdd13r(j) = vtr(j) + vti(j)
      vtdd13i(j) = vti(j) - vtr(j)
      vtdddr(j) = vtdd13i(j) - vtdd24i(j)
      vtdddi(j) = vtdd24r(j) - vtdd13r(j)
!  Evaluate polynomial.
      vxhrel(j) = vxh(j) - dble(vmu(j))
      vyhrel(j) = vyh(j) - dble(vnu(j))
      vusum3(j)=half*(vtdd13r(j)+                                       &
     &(vxhrel(j)*vtdddr(j)-vyhrel(j)*vtdddi(j)))
      vvsum3(j)=half*(vtdd13i(j)+                                       &
     &(vxhrel(j)*vtdddi(j)+vyhrel(j)*vtdddr(j)))
      vyhrel(j) = vyhrel(j) - one
      vusum(j)=vd12r(j)+(vxhrel(j)*vusum3(j)-vyhrel(j)*vvsum3(j))
      vvsum(j)=vd12i(j)+(vxhrel(j)*vvsum3(j)+vyhrel(j)*vusum3(j))
      vxhrel(j) = vxhrel(j) - one
      vu(j)=vw1r(j)+(vxhrel(j)*vusum(j)-vyhrel(j)*vvsum(j))
      vv(j)=vw1i(j)+(vxhrel(j)*vvsum(j)+vyhrel(j)*vusum(j))
 
          endif
 
        enddo
 
      else
!     everything inside the square, so interpolate
 
        do j=1,napx
 
      vxh(j) = hrecip*vx(j)
      vyh(j) = hrecip*vy(j)
      vmu(j) = int(vxh(j))
      vnu(j) = int(vyh(j))
!  Compute divided differences.
      k = 2 + vmu(j) + vnu(j)*kstep
      vw4r(j) = wtreal(k)
      vw4i(j) = wtimag(k)
      k = k - 1
      vw3r(j) = wtreal(k)
      vw3i(j) = wtimag(k)
      vd34r(j) = vw4r(j) - vw3r(j)
      vd34i(j) = vw4i(j) - vw3i(j)
      k = k + kstep
      vw2r(j) = wtreal(k)
      vw2i(j) = wtimag(k)
      vd23r(j) = vw2i(j) - vw3i(j)
      vd23i(j) = vw3r(j) - vw2r(j)
      vtr(j) = vd23r(j) - vd34r(j)
      vti(j) = vd23i(j) - vd34i(j)
      vtdd24r(j) = vti(j) - vtr(j)
!hr05 vtdd24i(j) = - ( vtr(j) + vti(j) )
      vtdd24i(j) = -1d0* ( vtr(j) + vti(j) )                             !hr05
      k = k + 1
      vw1r(j) = wtreal(k)
      vw1i(j) = wtimag(k)
      vd12r(j) = vw1r(j) - vw2r(j)
      vd12i(j) = vw1i(j) - vw2i(j)
      vtr(j) = vd12r(j) - vd23r(j)
      vti(j) = vd12i(j) - vd23i(j)
      vtdd13r(j) = vtr(j) + vti(j)
      vtdd13i(j) = vti(j) - vtr(j)
      vtdddr(j) = vtdd13i(j) - vtdd24i(j)
      vtdddi(j) = vtdd24r(j) - vtdd13r(j)
!  Evaluate polynomial.
      vxhrel(j) = vxh(j) - dble(vmu(j))
      vyhrel(j) = vyh(j) - dble(vnu(j))
      vusum3(j)=half*(vtdd13r(j)+                                       &
     &(vxhrel(j)*vtdddr(j)-vyhrel(j)*vtdddi(j)))
      vvsum3(j)=half*(vtdd13i(j)+                                       &
     &(vxhrel(j)*vtdddi(j)+vyhrel(j)*vtdddr(j)))
      vyhrel(j) = vyhrel(j) - one
      vusum(j)=vd12r(j)+(vxhrel(j)*vusum3(j)-vyhrel(j)*vvsum3(j))
      vvsum(j)=vd12i(j)+(vxhrel(j)*vvsum3(j)+vyhrel(j)*vusum3(j))
      vxhrel(j) = vxhrel(j) - one
      vu(j)=vw1r(j)+(vxhrel(j)*vusum(j)-vyhrel(j)*vvsum(j))
      vv(j)=vw1i(j)+(vxhrel(j)*vvsum(j)+vyhrel(j)*vusum(j))
        enddo
      endif
      return
end subroutine wzsubv