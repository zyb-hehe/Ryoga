#ifdef _MSC_VER
#include <winsock2.h>
#endif
#include <uti/stnplan.h>
#include "reslib.h"
#include <awilib/awilib.h>
#pragma warn -8057
#pragma warn -8067
#pragma warn -8065
#pragma warn -8004
#pragma warn -8070
void main(int argc,char *argv[]){
	CITEM::load_pin = LOADPIN;
	Main_Flow(76,test_start,test_end,START_UP,RELEASE,NULL,NULL,"B20041C_2S_LT40C_CP1_V1P0.PLN","pins.dec",false);
}
