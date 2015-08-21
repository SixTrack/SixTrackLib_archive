!hr08   if(kzz.eq.20.and.nbeam.ge.1.and.parbe(ix,2).eq.0) then
        if(kzz.eq.20.and.nbeam.ge.1.and.parbe(ix,2).eq.0d0) then         !hr08
          strack(i)=crad*ptnfac(ix)
          if(abs(strack(i)).le.pieni) then
            ktrack(i)=31
            goto 290
          endif


          if(nbeaux(imbb(i)).eq.1) then
            ktrack(i)=41
            if(ibeco.eq.1) then
              do 42 j=1,napx
              if(ibbc.eq.0) then
                crkveb(j)=ed(ix)
                cikveb(j)=ek(ix)
              else
                crkveb(j)=ed(ix)*bbcu(imbb(i),11)+                      &
     &ek(ix)*bbcu(imbb(i),12)
C !hr03           cikveb(j)=-ed(ix)*bbcu(imbb(i),12)+                     &
C !hr03&ek(ix)*bbcu(imbb(i),11)
                cikveb(j)=ek(ix)*bbcu(imbb(i),11)-                      &!hr03
     &ed(ix)*bbcu(imbb(i),12)                                            !hr03
              endif
!hr08       rho2b(j)=crkveb(j)*crkveb(j)+cikveb(j)*cikveb(j)
            rho2b(j)=crkveb(j)**2+cikveb(j)**2                           !hr08
            if(rho2b(j).le.pieni)                                       &
     &goto 42
            tkb(j)=rho2b(j)/(two*sigman2(1,imbb(i)))
C !hr03           beamoff(4,imbb(i))=strack(i)*crkveb(j)/rho2b(j)*        &
C !hr03           beamoff(4,imbb(i))=strack(i)*crkveb(j)/rho2b(j)*        &
C !hr03&(one-exp_rn(-tkb(j)))
                beamoff(4,imbb(i))=((strack(i)*crkveb(j))/rho2b(j))*    &!hr03
     &(one-exp_rn(-1d0*tkb(j)))                                          !hr03
! C !hr03           beamoff(5,imbb(i))=strack(i)*cikveb(j)/rho2b(j)*        &
! C !hr03           beamoff(5,imbb(i))=strack(i)*cikveb(j)/rho2b(j)*        &
! C !hr03&(one-exp_rn(-tkb(j)))
                beamoff(5,imbb(i))=((strack(i)*cikveb(j))/rho2b(j))*    &!hr03
     &(one-exp_rn(-1d0*tkb(j)))                                          !hr03
   42         continue
            endif
          endif
          

          if(nbeaux(imbb(i)).eq.2) then
            ktrack(i)=42
            if(ibeco.eq.1) then  


            if(ibtyp.eq.0) then
            do j=1,napx

              r2b(j)=two*(sigman2(1,imbb(i))-sigman2(2,imbb(i)))
              rb(j)=sqrt(r2b(j))
C               if(j.eq.1) then
C               endif
C !hr03         rkb(j)=strack(i)*pisqrt/rb(j)
              rkb(j)=(strack(i)*pisqrt)/rb(j)                            !hr03
              if(ibbc.eq.0) then
                crkveb(j)=ed(ix)
                cikveb(j)=ek(ix)
              else
                crkveb(j)=ed(ix)*bbcu(imbb(i),11)+                      &
     &ek(ix)*bbcu(imbb(i),12)
C !hr03           cikveb(j)=-ed(ix)*bbcu(imbb(i),12)+                     &
C !hr03&ek(ix)*bbcu(imbb(i),11)
                cikveb(j)=ek(ix)*bbcu(imbb(i),11)-                      &!hr03
     &ed(ix)*bbcu(imbb(i),12)                                            !hr03
              endif
              xrb(j)=abs(crkveb(j))/rb(j)
              zrb(j)=abs(cikveb(j))/rb(j)
              call errf(xrb(j),zrb(j),crxb(j),crzb(j))
C !hr03         tkb(j)=(crkveb(j)*crkveb(j)/sigman2(1,imbb(i))+           &
C !hr03&cikveb(j)*cikveb(j)/sigman2(2,imbb(i)))*half
              tkb(j)=(crkveb(j)**2/sigman2(1,imbb(i))+ cikveb(j)**2/sigman2(2,imbb(i)))*half                              !hr03
              xbb(j)=sigmanq(2,imbb(i))*xrb(j)
              zbb(j)=sigmanq(1,imbb(i))*zrb(j)
              call errf(xbb(j),zbb(j),cbxb(j),cbzb(j))
C !hr03         beamoff(4,imbb(i))=rkb(j)*(crzb(j)-exp_rn(-tkb(j))*       &
C !hr03&cbzb(j))*
C !hr03&sign(one,crkveb(j))
              beamoff(4,imbb(i))=(rkb(j)*(crzb(j)-exp_rn(-1d0*tkb(j))*cbzb(j)))*sign(one,crkveb(j))                                                !hr03
C !hr03&sign(one,crkveb(j))
C !hr03         beamoff(5,imbb(i))=rkb(j)*(crxb(j)-exp_rn(-tkb(j))*       &
C !hr03&cbxb(j))*
C !hr03&sign(one,cikveb(j))
              beamoff(5,imbb(i))=(rkb(j)*(crxb(j)-exp_rn(-1d0*tkb(j))*cbxb(j)))*sign(one,cikveb(j))                                                !hr03
C !hr03&sign(one,cikveb(j))
            enddo


            else if(ibtyp.eq.1) then            
            do j=1,napx
              r2b(j)=two*(sigman2(1,imbb(i))-sigman2(2,imbb(i)))
              rb(j)=sqrt(r2b(j))
              if(j.eq.1) then
              endif
!hr03         rkb(j)=strack(i)*pisqrt/rb(j)
              rkb(j)=(strack(i)*pisqrt)/rb(j)                            !hr03
              if(ibbc.eq.0) then
                crkveb(j)=ed(ix)
                cikveb(j)=ek(ix)
              else
                crkveb(j)=ed(ix)*bbcu(imbb(i),11)+ ek(ix)*bbcu(imbb(i),12)
C !hr03           cikveb(j)=-ed(ix)*bbcu(imbb(i),12)+                     &
C !hr03&ek(ix)*bbcu(imbb(i),11)
                cikveb(j)=ek(ix)*bbcu(imbb(i),11)-                      &!hr03
     &ed(ix)*bbcu(imbb(i),12)                                            !hr03
              endif
              xrb(j)=abs(crkveb(j))/rb(j)
              zrb(j)=abs(cikveb(j))/rb(j)
C !hr03         tkb(j)=(crkveb(j)*crkveb(j)/sigman2(1,imbb(i))+           &
C !hr03&cikveb(j)*cikveb(j)/sigman2(2,imbb(i)))*half
              tkb(j)=(crkveb(j)**2/sigman2(1,imbb(i))+                  &!hr03
     &cikveb(j)**2/sigman2(2,imbb(i)))*half                              !hr03
              xbb(j)=sigmanq(2,imbb(i))*xrb(j)
              zbb(j)=sigmanq(1,imbb(i))*zrb(j)
            enddo
            call wzsubv(napx,xrb(1),zrb(1),crxb(1),crzb(1))
            call wzsubv(napx,xbb(1),zbb(1),cbxb(1),cbzb(1))
            do j=1,napx
C !hr03         beamoff(4,imbb(i))=rkb(j)*(crzb(j)-exp_rn(-tkb(j))*       &
C !hr03&cbzb(j))*
C !hr03&sign(one,crkveb(j))
              beamoff(4,imbb(i))=(rkb(j)*(crzb(j)-exp_rn(-1d0*tkb(j))*cbzb(j)))*sign(one,crkveb(j))                                                !hr03
C !hr03&sign(one,crkveb(j))
C !hr03         beamoff(5,imbb(i))=rkb(j)*(crxb(j)-exp_rn(-tkb(j))*       &
C !hr03&cbxb(j))*
C !hr03&sign(one,cikveb(j))
              beamoff(5,imbb(i))=(rkb(j)*(crxb(j)-exp_rn(-1d0*tkb(j))*cbxb(j)))*sign(one,cikveb(j))                                                !hr03
!hr03&sign(one,cikveb(j))
            enddo
            endif
            endif
          endif


          if(nbeaux(imbb(i)).eq.3) then
            ktrack(i)=43
            if(ibeco.eq.1) then
            if(ibtyp.eq.0) then
            do j=1,napx
              r2b(j)=two*(sigman2(2,imbb(i))-sigman2(1,imbb(i)))
              rb(j)=sqrt(r2b(j))
              if(j.eq.1) then
              endif
!hr03         rkb(j)=strack(i)*pisqrt/rb(j)
              rkb(j)=(strack(i)*pisqrt)/rb(j)                            !hr03
              if(ibbc.eq.0) then
                crkveb(j)=ed(ix)
                cikveb(j)=ek(ix)
              else
                crkveb(j)=ed(ix)*bbcu(imbb(i),11)+                      &
     &ek(ix)*bbcu(imbb(i),12)
!hr03           cikveb(j)=-ed(ix)*bbcu(imbb(i),12)+                     &
!hr03&ek(ix)*bbcu(imbb(i),11)
                cikveb(j)=ek(ix)*bbcu(imbb(i),11)-                      &!hr03
     &ed(ix)*bbcu(imbb(i),12)                                            !hr03
              endif
              xrb(j)=abs(crkveb(j))/rb(j)
              zrb(j)=abs(cikveb(j))/rb(j)
              call errf(zrb(j),xrb(j),crzb(j),crxb(j))
!hr03         tkb(j)=(crkveb(j)*crkveb(j)/sigman2(1,imbb(i))+           &
!hr03&cikveb(j)*cikveb(j)/sigman2(2,imbb(i)))*half
              tkb(j)=(crkveb(j)**2/sigman2(1,imbb(i))+                  &!hr03
     &cikveb(j)**2/sigman2(2,imbb(i)))*half                              !hr03
              xbb(j)=sigmanq(2,imbb(i))*xrb(j)
              zbb(j)=sigmanq(1,imbb(i))*zrb(j)
              call errf(zbb(j),xbb(j),cbzb(j),cbxb(j))
!hr03         beamoff(4,imbb(i))=rkb(j)*(crzb(j)-exp_rn(-tkb(j))*       &
!hr03&cbzb(j))*
!hr03&sign(one,crkveb(j))
              beamoff(4,imbb(i))=(rkb(j)*(crzb(j)-exp_rn(-1d0*tkb(j))*  &!hr03
     &cbzb(j)))*                                                        &!hr03
     &sign(one,crkveb(j))                                                !hr03
!hr03&sign(one,crkveb(j))
!hr03         beamoff(5,imbb(i))=rkb(j)*(crxb(j)-exp_rn(-tkb(j))*       &
!hr03&cbxb(j))*
!hr03&sign(one,cikveb(j))
              beamoff(5,imbb(i))=(rkb(j)*(crxb(j)-exp_rn(-1d0*tkb(j))*  &!hr03
     &cbxb(j)))*                                                        &!hr03
     &sign(one,cikveb(j))                                                !hr03
!hr03&sign(one,cikveb(j))
            enddo
            else if(ibtyp.eq.1) then
            do j=1,napx
              r2b(j)=two*(sigman2(2,imbb(i))-sigman2(1,imbb(i)))
              rb(j)=sqrt(r2b(j))
              if(j.eq.1) then
              endif
!hr03         rkb(j)=strack(i)*pisqrt/rb(j)
              rkb(j)=(strack(i)*pisqrt)/rb(j)                            !hr03
              if(ibbc.eq.0) then
                crkveb(j)=ed(ix)
                cikveb(j)=ek(ix)
              else
                crkveb(j)=ed(ix)*bbcu(imbb(i),11)+                      &
     &ek(ix)*bbcu(imbb(i),12)
!hr03           cikveb(j)=-ed(ix)*bbcu(imbb(i),12)+                     &
!hr03&ek(ix)*bbcu(imbb(i),11)
                cikveb(j)=ek(ix)*bbcu(imbb(i),11)-                      &!hr03
     &ed(ix)*bbcu(imbb(i),12)                                            !hr03
              endif
              xrb(j)=abs(crkveb(j))/rb(j)
              zrb(j)=abs(cikveb(j))/rb(j)
!hr03         tkb(j)=(crkveb(j)*crkveb(j)/sigman2(1,imbb(i))+           &
!hr03&cikveb(j)*cikveb(j)/sigman2(2,imbb(i)))*half
              tkb(j)=(crkveb(j)**2/sigman2(1,imbb(i))+                  &!hr03
     &cikveb(j)**2/sigman2(2,imbb(i)))*half                              !hr03
              xbb(j)=sigmanq(2,imbb(i))*xrb(j)
              zbb(j)=sigmanq(1,imbb(i))*zrb(j)
            enddo
            call wzsubv(napx,zrb(1),xrb(1),crzb(1),crxb(1))
            call wzsubv(napx,zbb(1),xbb(1),cbzb(1),cbxb(1))
            do j=1,napx
!hr03         beamoff(4,imbb(i))=rkb(j)*(crzb(j)-exp_rn(-tkb(j))*       &
!hr03&cbzb(j))*
!hr03&sign(one,crkveb(j))
              beamoff(4,imbb(i))=(rkb(j)*(crzb(j)-exp_rn(-1d0*tkb(j))*  &!hr03
     &cbzb(j)))*                                                        &!hr03
     &sign(one,crkveb(j))                                                !hr03
!hr03&sign(one,crkveb(j))
!hr03         beamoff(5,imbb(i))=rkb(j)*(crxb(j)-exp_rn(-tkb(j))*       &
!hr03&cbxb(j))*
!hr03&sign(one,cikveb(j))
              beamoff(5,imbb(i))=(rkb(j)*(crxb(j)-exp_rn(-1d0*tkb(j))*  &!hr03
     &cbxb(j)))*                                                        &!hr03
     &sign(one,cikveb(j))                                                !hr03
!hr03&sign(one,cikveb(j))
            enddo
            endif
            endif
          endif
          goto 290