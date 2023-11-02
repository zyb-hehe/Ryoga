SET_DEC_FILE  "pins.dec"

HEADER
CS,SCLK_IN,SD_IN,SD_OUT;

SPM_PATTERN (R_0_a0x002){
    //CS,SCLK_IN,SD_IN,SD_OUT;
START:  *1   0  0 X *TS1       ;
        *1   0  0 X *RPT 5    ;
        *0   0  0 X *          ;
        *0   0  0 X *          ;
        *0   1  0 X *          ; //mode 010
        *0   1  1 X *          ;

        *0   1  1 X *          ; //R/w 1

        *0   1  0 X *          ; //OP 0

        *0   1  0 X *          ; //address 8'002
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  1 X *          ;
        *0   1  0 X *          ;

        *0   1  X X *          ; //DATA 16'0000
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X * TS2          ;

        *0   1  0 X *     ;  //LOAD DATA
        *1   1  0 X *         ;
        *1   0  0 X * TS1     ;  //LOGIC PROCESS
        *1   1  0 X *         ;
        *1   1  0 X *         ;
        *1   1  0 X *         ;
        *1   1  0 X *         ;
        *1   0  0 X *         ;
                        
        *0   0  0 X *         ; //CONFIGURATION
        *0   0  0 X *         ;
        *1   0  0 X *         ;
        *1   0  0 X *         ;

        *1   0  0 X *         ;//STOP_T
        *1   0  0 X *         ;
        *1   0  0 X *         ;
        *0   0  0 X *          ;

        *0   1  0 X *          ; //mode 010
        *0   1  1 X *          ;

        *0   1  1 X *          ; //R/w 1

        *0   1  0 X *          ; //OP 0

        *0   1  0 X *          ; //address 8'002
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  1 X *          ;
        *0   1  0 X *          ;


        *0   1  X X *          ; //DATA 16'0000
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X X *          ;
        *0   1  X K *          ;
        *0   1  X K *          ;
        *0   1  X K *          ;
        *0   1  X K *          ;
        *0   1  X K *          ;
        *0   1  X K *          ;
        *0   1  X K *          ;
        *0   1  X K * TS2         ;

        *0   1  0 X *      ;  //LOAD DATA
        *1   1  0 X *         ;
        *1   0  0 X * TS1     ;  //LOGIC PROCESS
        *1   1  0 X *         ;
        *1   1  0 X *         ;
        *1   1  0 X *         ;
        *1   1  0 X *         ;
        *1   0  0 X *         ;
                        
        *0   0  0 X *         ; //CONFIGURATION
        *0   0  0 X *         ;
        *1   0  0 X *         ;
        *1   0  0 X *         ;

STOP_T: *1   0  0 X *         ;
}
