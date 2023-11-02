SET_DEC_FILE  "pins.dec"

HEADER
CS,SCLK_IN,SD_IN,SD_OUT;

SPM_PATTERN (R_TRIM_SCAN){
    //CS,SCLK_IN,SD_IN,SD_OUT;
START:  *1   0  0 X *TS1       ;
        *1   0  0 X *RPT 500   ;
        *0   0  0 X *          ;
        *0   0  0 X *          ;
        *0   1  0 X *          ; //mode 01
        *0   1  1 X *          ;

        *0   1  1 X *          ; //R/w 1

        *0   1  0 X *          ; //OP 0

addr:   *0   1  0 X *          ; //address 
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;

        *0   1  0 X *          ; //DATA 
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X * TS2      ;



        *0   1  0 X * TS2      ;  //LOAD DATA
        *1   1  0 X *          ;
        *1   0  0 X * TS1      ;  //LOGIC PROCESS
        *1   1  0 X *          ;
        *1   1  0 X *          ;
        *1   1  0 X *          ;
        *1   1  0 X *          ;
        *1   0  0 X *          ;
        *0   0  0 X *          ; //CONFIGURATION
        *0   0  0 X *          ;
        *1   0  0 X *          ;
        *1   0  0 X *          ;

        *1   0  0 X *          ;//STOP_T
        *1   0  0 X *          ;
        *1   0  0 X *          ;
        *0   0  0 X *          ;

        *0   1  0 X *          ; //mode 01
        *0   1  1 X *          ;
        
        *0   1  1 X *          ; //R/w 1
        *0   1  0 X *          ; //OP 0

addr1:  *0   1  0 X *          ; //address 
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;

        *0   1  0 X *          ; //DATA 
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
data1:  *0   1  0 X *          ;//VBG REG [9:6]  bit 9
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;//VTC REG [5:2]//bit3
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X *          ;
        *0   1  0 X * TS2      ;


        *0   1  0 X * TS2      ;//CAPTURE-STOP 
        *0   1  0 X *          ;  //LOAD DATA
        *1   1  0 X *          ;
        *1   0  0 X * TS1      ;  //LOGIC PROCESS
        *1   1  0 X *          ;
        *1   1  0 X *          ;
        *1   1  0 X *          ;
        *1   1  0 X *          ;
        *1   0  0 X *          ;
        *0   0  0 X *          ; //CONFIGURATION
        *0   0  0 X *          ;
        *1   0  0 X *          ;
        *1   0  0 X *          ;
                              
STOP_T: *1   0  0 X *          ;
}                             
