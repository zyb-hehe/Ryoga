SET_DEC_FILE  "pins.dec"
HEADER
CS,SCLK_IN,SD_IN,SD_OUT;
SPM_PATTERN (mode_operation_spi){

START:         *    1   0  0 X *TS1;     
               *    1   0  0 X *RPT 5;
               *    0   0  0 X *     ;
               *    0   1  0 X *     ;
               *    0   1  0 X *     ;
               *    0   1  0 X *     ;
               *    0   1  0 X *TS2  ;
               *    1   1  0 X *TS1  ;
               *    1   1  0 X *     ;
               *    1   1  0 X *     ;
               *    1   1  0 X *     ;
               *    1   1  0 X *     ;
               *    0   0  0 X *     ;
               *    0   0  0 X *     ;
               *    1   0  0 X *     ;
               *    1   0  0 X *     ;
               *    1   0  0 X *     ;
               *    1   0  0 X *     ; 
STOP_T:        *    1   1  1 X *              ;
}