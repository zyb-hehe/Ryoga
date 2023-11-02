SET_DEC_FILE  "pins.dec"

HEADER
CS,SCLK_IN,SD_IN,SD_OUT;

SPM_PATTERN (WR_024H){
    //CS,SCLK_IN,SD_IN,SD_OUT;
    
// write short reg
START: *1   0  0 X *TS1       ;
       *1   0  0 X *RPT 5     ;
       *0   0  0 X *          ;
       *0   0  0 X *          ;
       *0   1  0 X *          ; //mode 01
       *0   1  1 X *          ;

       *0   1  0 X *          ; //R/w 0

       *0   1  0 X *          ; //OP 0

       *0   1  0 X *          ;  //addr: 24H
       *0   1  0 X *          ;
       *0   1  1 X *          ;
       *0   1  0 X *          ;
       *0   1  0 X *          ;
       *0   1  1 X *          ;
       *0   1  0 X *          ;
       *0   1  0 X *          ;

       *0   1  X X *          ;  //data: 
       *0   1  X X *          ;
       *0   1  X X *          ;
       *0   1  X X *          ;
       *0   1  X X *          ;
       *0   1  X X *          ;
       *0   1  0 X *          ;  //VBG_trim code[9]
       *0   1  0 X *          ;
       *0   1  0 X *          ;
       *0   1  1 X *          ;
       *0   1  0 X *          ;  //VTC_trim code[5]
       *0   1  0 X *          ;
       *0   1  0 X *          ;
       *0   1  1 X *          ;
       *0   1  X X *          ;
       *0   1  X X *TS2       ;


       *0   1  0 X *TS2       ;  //LOAD DATA
       *1   1  0 X *          ;
       *1   0  0 X *TS1       ;  //LOGIC PROCESS
       *1   1  0 X *          ;
       *1   1  0 X *          ;
       *1   1  0 X *          ;
       *1   1  0 X *          ;
       *1   0  0 X *          ;
       *0   0  0 X *          ; //CONFIGURATION
       *0   0  0 X *          ;
       *1   0  0 X *          ;
       *1   0  0 X *          ;

       *1   0  0 X *          ;




// read short reg
       *1   0  0 X *TS1       ;
       *1   0  0 X *RPT 500   ;
       *0   0  0 X *          ;
       *0   0  0 X *          ;
       *0   1  0 X *          ; //mode 01
       *0   1  1 X *          ;

       *0   1  1 X *          ; //R/w 1

       *0   1  0 X *          ; //OP 0

       *0   1  0 X *          ; //address 8'1E
       *0   1  0 X *          ;
       *0   1  1 X *          ;
       *0   1  0 X *          ;
       *0   1  0 X *          ;
       *0   1  1 X *          ;
       *0   1  0 X *          ;
       *0   1  0 X *          ;

       *0   1  X X *          ; //DATA 16'477A
       *0   1  X X *          ;
       *0   1  X X *          ;
       *0   1  X X *          ;
       *0   1  X X *          ;
       *0   1  X X *          ;
       *0   1  0 X *          ;
       *0   1  0 X *          ;
       *0   1  0 X *          ;
       *0   1  0 X *          ;
       *0   1  0 X *          ;
       *0   1  0 X *          ;
       *0   1  0 X *          ;
       *0   1  0 X *          ;
       *0   1  X X *          ;
       *0   1  X X * TS2      ;

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

       *1   0  0 X *          ;//STOP_T
       *1   0  0 X *          ;
       *1   0  0 X *          ;
       *0   0  0 X *          ;
       
       *0   1  0 X *          ; //mode 01
       *0   1  1 X *          ;

       *0   1  1 X *          ; //R/w 1

       *0   1  0 X *          ; //OP 0

       *0   1  0 X *          ; //address 8'1E
       *0   1  0 X *          ;
       *0   1  1 X *          ;
       *0   1  0 X *          ;
       *0   1  0 X *          ;
       *0   1  1 X *          ;
       *0   1  0 X *          ;
       *0   1  0 X *          ;

       *0   1  1 X *          ; //DATA 16'477A
       *0   1  0 X *          ;
       *0   1  0 X *          ;
       *0   1  1 X *          ;
       *0   1  0 X *          ;
       *0   1  0 X *          ;
       *0   1  0 L *          ;
       *0   1  0 L *          ;
       *0   1  0 L *          ;
       *0   1  1 H *          ;
       *0   1  0 L *          ;
       *0   1  0 L *          ;
       *0   1  0 L *          ;
       *0   1  1 H *          ;
       *0   1  0 X *          ;
       *0   1  0 X * TS2      ;



       *0   1  0 X * TS2     ;//CAPTURE-STOP 
       *0   1  0 X *         ;  //LOAD DATA
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

STOP_T:*1   0  0 X *         ;
}
