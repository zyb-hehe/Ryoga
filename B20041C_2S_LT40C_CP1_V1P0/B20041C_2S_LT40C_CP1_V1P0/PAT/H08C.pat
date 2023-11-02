SET_DEC_FILE  "pins.dec"
HEADER
EN_SET;
SPM_PATTERN (H08C){

          START:   *0* TS1          ;
                   *0* RPT 300       ;

                   *1* RPT 140      ;//8A

                   *1*TS2           ;
                   *1*RPT 140        ;
                   *1*              ;
                   *1*              ;
          STOP_T:  *1*              ;
}