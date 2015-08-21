import numpy

def wwerf(xx,yy,mathlib=numpy):
  """
    modification of wwerf, double precision complex error function,
    written at cern by K. Koelbig.
     xx, yy    (double)    real + imag argument
     wx, wy    (double)    real + imag function result
    used in mad8,madx,ptc,sixtrack for maps
  """
  abs=mathlib.abs
  cos=mathlib.cos
  sin=mathlib.sin
  sqrt=mathlib.sqrt
  exp=mathlib.exp
  cc=1.12837916709551
  xlim=5.33
  ylim=4.29
  fac1=3.2
  fac2=23.0
  fac3=21.0
  x = abs(xx)
  y = abs(yy)
  if y < ylim  and  x < xlim:
      q  = (1.0 - y / ylim) * sqrt(1.0 - (x/xlim)**2)
      h  = 1.0 / (fac1 * q)
      nc = 7 + int(fac2*q)
      xl = h**(1 - nc)
      xh = y + 0.5/h
      yh = x
      nu = 10 + int(fac3*q)
      rx=[0.0]
      ry=[0.0]
      for n in range(nu):
          tx = xh + n * rx[-1]
          ty = yh - n * ry[-1]
          tn = tx*tx + ty*ty
          rx.append( 0.5 * tx / tn)
          ry.append( 0.5 * ty / tn)
      sx = 0.0
      sy = 0.0
      for n in range(nu):
         saux = sx + xl
         sx = rx[n] * saux - ry[n] * sy
         sy = rx[n] * sy + ry[n] * saux
         xl = h * xl
      wx = cc * sx
      wy = cc * sy
  else:
      xh = y
      yh = x
      rx=0.0
      ry=0.0
      for n in range(9):
          tx = xh + n * rx
          ty = yh - n * ry
          tn = tx*tx + ty*ty
          rx = 0.5 * tx / tn
          ry = 0.5 * ty / tn
      wx = cc * rx
      wy = cc * ry
  if yy < 0:
     wx =   2.0 * exp(y*y-x*x) * cos(2.0*x*y) - wx
     wy = - 2.0 * exp(y*y-x*x) * sin(2.0*x*y) - wy
     if xx > 0:
         wy = -wy
  elif xx < 0:
      wy = -wy

  return wx,wy
