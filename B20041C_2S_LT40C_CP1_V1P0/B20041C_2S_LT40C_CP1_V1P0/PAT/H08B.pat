SET_DEC_FILE  "pins.dec"
HEADER
EN_SET;
SPM_PATTERN (H08B){

          START:   *0* TS1          ;
                   *0* RPT 300       ;

                   *1* RPT 139      ;//8A

                   *1*TS2           ;
                   *1*RPT 140        ;
                   *1*              ;
                   *1*              ;
          STOP_T:  *1*              ;
}