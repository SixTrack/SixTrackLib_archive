  subroutine ccperrfr(xx, yy, wx, wy)
    implicit none
    !----------------------------------------------------------------------*
    ! purpose:                                                             *
    !   modification of wwerf, double precision complex error function,    *
    !   written at cern by K. Koelbig.                                     *
    ! input:                                                               *
    !   xx, yy    (double)    real + imag argument                         *
    ! output:                                                              *
    !   wx, wy    (double)    real + imag function result                  *
    !----------------------------------------------------------------------*
    integer n,nc,nu
    real(8), INTENT(IN):: xx,yy
    real(8), INTENT(OUT):: wx,wy
    real(8) x,y,q,h,xl,xh,yh,tx,ty,tn,sx,sy,saux,  &
         rx(33),ry(33),cc,xlim,ylim,fac1,fac2,fac3
    parameter(cc=1.12837916709551,        &
         xlim=5.33,ylim=4.29,fac1=3.2,fac2=23.0,fac3=21.0)

    x = abs(xx)
    y = abs(yy)

    if (y .lt. ylim  .and.  x .lt. xlim) then
       q  = (1.0 - y / ylim) * sqrt(1.0 - (x/xlim)**2)
       h  = 1.0 / (fac1 * q)
       nc = 7 + int(fac2*q)
       xl = h**(1 - nc)
       xh = y + 0.5/h
       yh = x
       nu = 10 + int(fac3*q)
       rx(nu+1) = 0.0
       ry(nu+1) = 0.0

       do n = nu, 1, -1
          tx = xh + n * rx(n+1)
          ty = yh - n * ry(n+1)
          tn = tx*tx + ty*ty
          rx(n) = 0.5 * tx / tn
          ry(n) = 0.5 * ty / tn
       enddo

       sx = 0.0
       sy = 0.0

       do n = nc, 1, -1
          saux = sx + xl
          sx = rx(n) * saux - ry(n) * sy
          sy = rx(n) * sy + ry(n) * saux
          xl = h * xl
       enddo

       wx = cc * sx
       wy = cc * sy
    else
       xh = y
       yh = x
       rx(1) = 0.0
       ry(1) = 0.0

       do n = 9, 1, -1
          tx = xh + n * rx(1)
          ty = yh - n * ry(1)
          tn = tx*tx + ty*ty
          rx(1) = 0.5 * tx / tn
          ry(1) = 0.5 * ty / tn
       enddo

       wx = cc * rx(1)
       wy = cc * ry(1)
    endif

    !      if(y .eq. zero) wx = exp(-x**2)
    if(yy .lt. 0.0) then
       wx =   2.0 * exp(y*y-x*x) * cos(2.0*x*y) - wx
       wy = - 2.0 * exp(y*y-x*x) * sin(2.0*x*y) - wy
       if(xx .gt. 0.0) wy = -wy
    else
       if(xx .lt. 0.0) wy = -wy
    endif

  end SUBROUTINE ccperrfr
