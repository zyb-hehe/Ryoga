#include<stnlib\stnstatementid.h>
#define SET_STATEMENT_INFO(stnid,yylineno) Plugin.ShmPtr->TestPlanProgram.Status.line = yylineno;\
Plugin.ShmPtr->TestPlanProgram.Status.Last_TestStatementID[0] = stnid;
#ifdef _MSC_VER
#pragma warning (disable:4716)
#pragma warning (disable:4166)
#pragma warning (disable:4430)
#include<uti/value_vc.h>
#include <winsock2.h>
#endif
#include <uti/stnplan.h>
#define __B20041C_2S_LT40C_CP1_V1P0_BODY_FILE
#include "reslib.h"
#include <awilib/awilib.h>
#ifndef _MSC_VER
#pragma warn -8057
#pragma warn -8066
#pragma warn -8067
#pragma warn -8065
#pragma warn -8004
#pragma warn -8008
#pragma warn -8070
#endif
bool power_down_fail_site_same_flag = false;
bool enter_power_down_fail_site = false;
static bool fail_rejudge_once_flag = false;
const int parall_pin_cnt= DF_MAX_Pin_Count;
parall_struct parall_pin[parall_pin_cnt];
_labelstruct *craft_local_label;
int craft_local_label_count=0;
int *craft_ori_index;
char __tempcatstr[512];
 static _labelstruct *nouselabel = NULL;        
 static unsigned short nouselabelno = 0;        
 unsigned int LoadNonusedLabels() {        
 char *tmplabelptr = NULL,tmppatfile[MAXPATH];        
 FILE *tmpout = NULL;        
 if(!nouselabelno) {        
  char tmpfile[MAXPATH];        
     sprintf(tmpfile,"unlabel.txt");        
   tmpout = fopen(tmpfile,"r");        
   while(!feof(tmpout)) {        
      if(!nouselabelno) {        
        nouselabel = (_labelstruct *)malloc( sizeof(_labelstruct)*(++nouselabelno) );        
      } else {        
        nouselabel = (_labelstruct *)realloc(nouselabel,sizeof(_labelstruct)*(++nouselabelno));        
      }        
      if(nouselabel) {        
        int index = nouselabelno-1;        
        char tmplabel[128];        
        fscanf(tmpout,"%s",tmplabel);        
        if(nouselabelno>1) {        
          bool need_switch = false;        
          for(int ii=0;ii<nouselabelno-1;ii++) {        
            int jj=0;        
            bool compare_done = false;        
            while(tmplabel[jj]!='\0' && nouselabel[ii].labelname[jj]!='\0') {        
              if(tolower(tmplabel[jj])<tolower(nouselabel[ii].labelname[jj])) {      
          //printf("Switch %s to %s\n",tmplabel,nouselabel[ii].labelname);        
                need_switch = true;        
                compare_done = true;        
                break;        
              } else if(tolower(tmplabel[jj])>tolower(nouselabel[ii].labelname[jj])) {      
          //printf("%s is Larger than %s\n",tmplabel,nouselabel[ii].labelname);        
                need_switch = false;        
                compare_done = true;        
                break;        
        }        
              jj++;        
            }        
            if(!compare_done) {        
              if(strlen(tmplabel)<strlen(nouselabel[ii].labelname)) {        
                need_switch = true;        
              }        
            }        
            if(need_switch) {        
              index = ii;        
              for(jj=nouselabelno-1;jj>index;jj--) {        
                strcpy(nouselabel[jj].labelname,nouselabel[jj-1].labelname);        
                strcpy(nouselabel[jj].modulename,nouselabel[jj-1].modulename);        
                nouselabel[jj].address = nouselabel[jj-1].address;        
                nouselabel[jj].pinmode = nouselabel[jj-1].pinmode;        
                nouselabel[jj].testno = nouselabel[jj-1].testno;        
                nouselabel[jj].chk_mode = nouselabel[jj-1].chk_mode;        
                for(int kk=0;kk<DF_MAX_Pin_Count/64+1;kk++) {        
                  nouselabel[jj].pin2x[kk] = nouselabel[jj-1].pin2x[kk];        
                  nouselabel[jj].validpin[kk] = nouselabel[jj-1].validpin[kk];        
                }        
              }        
              break;        
            }        
          }        
        }        
        strcpy(nouselabel[index].labelname,tmplabel);        
        fscanf(tmpout,"%s",nouselabel[index].modulename);        
        if(!strcmp(nouselabel[index].modulename,"*"))  strcpy(nouselabel[nouselabelno-1].modulename,"");        
        fscanf(tmpout,"%ld",&nouselabel[index].address);        
        fscanf(tmpout,"%d",&nouselabel[index].pinmode);        
        fscanf(tmpout,"%u",&nouselabel[index].testno);        
        fscanf(tmpout,"%d\n",&nouselabel[index].chk_mode);        
        for(int ii=0;ii<DF_MAX_Pin_Count/64+1;ii++)        
        {        
           fscanf(tmpout,"%llx\n",&nouselabel[index].pin2x[ii]);        
        }        
        for(int ii=0;ii<DF_MAX_Pin_Count/64+1;ii++)        
        {        
           fscanf(tmpout,"%llx\n",&nouselabel[index].validpin[ii]);        
        }        
      } else printf("nouselabel allocate error\n");        
   }        
 }        
 }
 unsigned int AddNewLabel(char* labelname,char* modulename,unsigned address,int pinmode,unsigned __int64  *p2x,unsigned __int64 *vpin,unsigned int tsno,int chk_mode,int ori_index) {        
   if(!craft_local_label_count) {        
      craft_local_label = (_labelstruct*)malloc(sizeof(_labelstruct));    
      craft_ori_index = (int*)malloc(sizeof(int));        
   } else {        
      craft_local_label = (_labelstruct*)realloc(craft_local_label,sizeof(_labelstruct)*(craft_local_label_count+1));    
      craft_ori_index = (int*)realloc(craft_ori_index,sizeof(int)*(craft_local_label_count+1));        
   }    
   if(craft_local_label) {        
   strcpy(craft_local_label[craft_local_label_count].labelname,labelname);        
   strcpy(craft_local_label[craft_local_label_count].modulename,modulename);        
   craft_local_label[craft_local_label_count].address=address;        
   craft_local_label[craft_local_label_count].pinmode=pinmode;        
   for(int ii=0;ii<DF_MAX_Pin_Count/64+1;ii++)        
   {        
    craft_local_label[craft_local_label_count].pin2x[ii]=p2x[ii];        
    craft_local_label[craft_local_label_count].validpin[ii]=vpin[ii];    
   }        
   craft_local_label[craft_local_label_count].testno=tsno;        
   craft_local_label[craft_local_label_count].chk_mode=chk_mode;        
   craft_ori_index[craft_local_label_count]=ori_index;        
   craft_local_label_count++;        
   } else printf("craft_local_label allocate error\n");        
 }
 unsigned int SearchCurrUsedLabel(char *tmp) {    
   for(int ii=0;ii<craft_local_label_count;ii++) {    
       if(strcmp(tmp,craft_local_label[ii].labelname)==0) {    
           return ii;    
       }    
   }    
   return -1;    
 }    
 unsigned int SearchLabelIndex(char *tmp) {        
   //printf("Start Searching\n");        
   int index = nouselabelno/2, pre_index=0;        
   int first = 0, last = nouselabelno;        
   int counter = 0;        
   while(index!=pre_index) {        
     counter++;        
     if(!strcmp(tmp,nouselabel[index].labelname)){        
       //printf("Found %s in index %d loop %d times\n",nouselabel[index].labelname,index,counter);    
     //fflush(stdout);        
       AddNewLabel(tmp,nouselabel[index].modulename,nouselabel[index].address,nouselabel[index].pinmode,nouselabel[index].pin2x,nouselabel[index].validpin,nouselabel[index].testno,nouselabel[index].chk_mode,index);        
       return index;        
     } else {        
       int ii=0;        
       bool compare_done = false;        
       while(tmp[ii]!='\0' && nouselabel[index].labelname[ii]!='\0') {        
         if(tolower(tmp[ii])>tolower(nouselabel[index].labelname[ii])) {        
           first = index;        
           pre_index = index;        
           index = (first+last)/2;        
           compare_done = true;        
           break;        
         } else if(tolower(tmp[ii])<tolower(nouselabel[index].labelname[ii])){        
           last = index;        
           pre_index = index;        
           index = (first+last)/2;        
           compare_done = true;        
           break;        
         }        
         ii++;        
       }        
       if(!compare_done) {        
         if(strlen(tmp)>strlen(nouselabel[index].labelname)) {        
           first = index;        
           pre_index = index;        
           index = (first+last)/2;        
         } else {        
           last = index;        
           pre_index = index;        
           index = (first+last)/2;        
         }        
       }        
     }        
   //}        
   }        
   //printf("End Searching\n");        
 }
 long int GetAddr(char *address) {  
 char *tmplabelptr = NULL,tmppatfile[MAXPATH];  
 static _labelstruct *nouselabel = NULL;  
 static unsigned short nouselabelno = 0;  
 FILE *tmpout = NULL;  
 if(!nouselabelno) {  
  char tmpfile[MAXPATH];  
     sprintf(tmpfile,"unlabel.txt");  
   tmpout = fopen(tmpfile,"r");  
   while(!feof(tmpout)) {  
      if(!nouselabelno) {  
        nouselabel = (_labelstruct *)malloc( sizeof(_labelstruct)*(++nouselabelno) );  
      } else {  
        nouselabel = (_labelstruct *)realloc(nouselabel,sizeof(_labelstruct)*(++nouselabelno));  
      }  
      if(nouselabel) {  
        fscanf(tmpout,"%s",nouselabel[nouselabelno-1].labelname);  
        fscanf(tmpout,"%s",nouselabel[nouselabelno-1].modulename);  
        if(!strcmp(nouselabel[nouselabelno-1].modulename,"*"))  strcpy(nouselabel[nouselabelno-1].modulename,"");  
        fscanf(tmpout,"%ld",&nouselabel[nouselabelno-1].address);  
        fscanf(tmpout,"%d",&nouselabel[nouselabelno-1].pinmode);  
        fscanf(tmpout,"%u",&nouselabel[nouselabelno-1].testno);  
        fscanf(tmpout,"%d\n",&nouselabel[nouselabelno-1].chk_mode);  
        for(int ii=0;ii<DF_MAX_Pin_Count/64+1;ii++)  
        {  
           fscanf(tmpout,"%llx\n",&nouselabel[nouselabelno-1].pin2x[ii]);  
        }          
        for(int ii=0;ii<DF_MAX_Pin_Count/64+1;ii++)  
        {  
           fscanf(tmpout,"%llx\n",&nouselabel[nouselabelno-1].validpin[ii]);  
        }  
      } else printf("nouselabel allocate error\n");  
   }  
 }  
 long int re = -1;  
 char tmp[65],module[32],label[32];  
 tmplabelptr = strstr(address,":");  
 if(tmplabelptr) {  
   memset(module,0,32);  
   memcpy(module,address,abs(tmplabelptr-address));  
   memset(label,0,32);  
   strcpy(label,tmplabelptr+1);  
   sprintf(tmp,"%s_C_%s",module,label);  
 } else {  
   sprintf(tmp,"%s",address);  
 }  
 re = GetLabelAddress(tmp);  
 if(re==-1) {  
   for(short ii=0;ii<nouselabelno;ii++) {  
     if(!strcmp(tmp,nouselabel[ii].labelname)){  
       re = nouselabel[ii].address;  
       break;  
     }  
   }  
 }  
 return re;  
}
 long int GetAddr_X(char *address) {  
 char *tmplabelptr = NULL;  
 LoadNonusedLabels();  
 long int re = -1;  
 char tmp[65],module[32],label[32];  
 tmplabelptr = strstr(address,":");  
 if(tmplabelptr) {  
   memset(module,0,32);  
   memcpy(module,address,abs(tmplabelptr-address));  
   memset(label,0,32);  
   strcpy(label,tmplabelptr+1);  
   sprintf(tmp,"%s_C_%s",module,label);  
 } else {  
   sprintf(tmp,"%s",address);  
 }  
 re = SearchCurrUsedLabel(tmp);  
 if(re==-1) {  
   re = GetLabelAddress(tmp);  
   if(re==-1) {  
     re = SearchLabelIndex(tmp);  
     if(re!=-1) {  
       re = nouselabel[re].address;  
     }  
   } else {  
     CLABEL *tmp_label = CLABEL::GetObjectByName(tmp);  
     if(tmp_label) {  
       AddNewLabel(tmp,tmp_label->Getmodulename(),tmp_label->Getaddress(),tmp_label->Getpinmode(),tmp_label->Getpin2x(),tmp_label->GetValidpin(),tmp_label->Gettestno(),tmp_label->Getchkmode(),tmp_label->Getidx());  
     }  
   }  
 } else {  
   re = craft_local_label[re].address;  
 }  
 return re;  
}
 int GetPinMode(char *address) {  
 char *tmplabelptr = NULL,tmppatfile[MAXPATH];  
 static _labelstruct *nouselabel = NULL;  
 static unsigned short nouselabelno = 0;  
 FILE *tmpout = NULL;  
 if(!nouselabelno) {  
  char tmpfile[MAXPATH];  
     sprintf(tmpfile,"unlabel.txt");  
   tmpout = fopen(tmpfile,"r");  
   while(!feof(tmpout)) {  
      if(!nouselabelno) {  
        nouselabel = (_labelstruct *)malloc( sizeof(_labelstruct)*(++nouselabelno) );  
      } else {  
        nouselabel = (_labelstruct *)realloc(nouselabel,sizeof(_labelstruct)*(++nouselabelno));  
      }  
      if(nouselabel) {  
        fscanf(tmpout,"%s",nouselabel[nouselabelno-1].labelname);  
        fscanf(tmpout,"%s",nouselabel[nouselabelno-1].modulename);  
        if(!strcmp(nouselabel[nouselabelno-1].modulename,"*"))  strcpy(nouselabel[nouselabelno-1].modulename,"");  
        fscanf(tmpout,"%ld",&nouselabel[nouselabelno-1].address);  
        fscanf(tmpout,"%d",&nouselabel[nouselabelno-1].pinmode);  
        fscanf(tmpout,"%u",&nouselabel[nouselabelno-1].testno);  
        fscanf(tmpout,"%d\n",&nouselabel[nouselabelno-1].chk_mode);  
        for(int ii=0;ii<DF_MAX_Pin_Count/64+1;ii++)  
        {  
           fscanf(tmpout,"%llx\n",&nouselabel[nouselabelno-1].pin2x[ii]);  
        }  
        for(int ii=0;ii<DF_MAX_Pin_Count/64+1;ii++)  
        {  
           fscanf(tmpout,"%llx\n",&nouselabel[nouselabelno-1].validpin[ii]);  
        }  
      } else printf("nouselabel allocate error\n");  
   }  
 }  
 long int re = -1;  
 char tmp[65],module[32],label[32];  
 tmplabelptr = strstr(address,":");  
 if(tmplabelptr) {  
   memset(module,0,32);  
   memcpy(module,address,abs(tmplabelptr-address));  
   memset(label,0,32);  
   strcpy(label,tmplabelptr+1);  
   sprintf(tmp,"%s_C_%s",module,label);  
 } else {  
   sprintf(tmp,"%s",address);  
 }  
 unsigned __int64 p[DF_MAX_Pin_Count/64+1];  
 unsigned __int64 p2[DF_MAX_Pin_Count/64+1];  
 unsigned int     ts;  
   int     chk;  
 re = CLABEL::GetPinmodeByName(tmp,p,p2,ts,chk);  
 if(re==-1) {  
   for(short ii=0;ii<nouselabelno;ii++) {  
     if(!strcmp(tmp,nouselabel[ii].labelname)){  
       re = nouselabel[ii].pinmode;  
       break;  
     }  
   }  
 }  
 return re;  
}
 int GetPinMode_X(char *address) {  
 char *tmplabelptr = NULL;    
 LoadNonusedLabels();  
 long int re = -1;  
 char tmp[65],module[32],label[32];  
 tmplabelptr = strstr(address,":");  
 if(tmplabelptr) {  
   memset(module,0,32);  
   memcpy(module,address,abs(tmplabelptr-address));  
   memset(label,0,32);  
   strcpy(label,tmplabelptr+1);  
   sprintf(tmp,"%s_C_%s",module,label);  
 } else {  
   sprintf(tmp,"%s",address);  
 }  
 unsigned __int64 p[DF_MAX_Pin_Count/64+1];  
 unsigned __int64 p2[DF_MAX_Pin_Count/64+1];  
 unsigned int     ts;  
   int     chk;  
 re = SearchCurrUsedLabel(tmp);  
 if(re==-1) {  
   re = CLABEL::GetPinmodeByName(tmp,p,p2,ts,chk);  
   if(re==-1) {  
     re = SearchLabelIndex(tmp);  
     if(re!=-1) {  
       re = nouselabel[re].pinmode;  
     }  
   } else {  
     CLABEL *tmp_label = CLABEL::GetObjectByName(tmp);  
     if(tmp_label) {  
       AddNewLabel(tmp,tmp_label->Getmodulename(),tmp_label->Getaddress(),tmp_label->Getpinmode(),tmp_label->Getpin2x(),tmp_label->GetValidpin(),tmp_label->Gettestno(),tmp_label->Getchkmode(),tmp_label->Getidx());  
     }  
   }  
 } else {  
   re = craft_local_label[re].pinmode;  
 }  
 return re;  
}
 unsigned __int64* GetPin2x(char *address) {  
 char *tmplabelptr = NULL,tmppatfile[MAXPATH];  
 static _labelstruct *nouselabel = NULL;  
 static unsigned short nouselabelno = 0;  
 FILE *tmpout = NULL;  
 if(!nouselabelno) {  
   char tmpfile[MAXPATH];  
   sprintf(tmpfile,"unlabel.txt");  
   tmpout = fopen(tmpfile,"r");  
   while(!feof(tmpout)) {  
      if(!nouselabelno) {  
        nouselabel = (_labelstruct *)malloc( sizeof(_labelstruct)*(++nouselabelno) );  
      } else {  
        nouselabel = (_labelstruct *)realloc(nouselabel,sizeof(_labelstruct)*(++nouselabelno));  
      }  
      if(nouselabel) {  
        fscanf(tmpout,"%s",nouselabel[nouselabelno-1].labelname);  
        fscanf(tmpout,"%s",nouselabel[nouselabelno-1].modulename);  
        if(!strcmp(nouselabel[nouselabelno-1].modulename,"*"))  strcpy(nouselabel[nouselabelno-1].modulename,"");  
        fscanf(tmpout,"%ld",&nouselabel[nouselabelno-1].address);  
        fscanf(tmpout,"%d",&nouselabel[nouselabelno-1].pinmode);  
        fscanf(tmpout,"%u",&nouselabel[nouselabelno-1].testno);  
        fscanf(tmpout,"%d\n",&nouselabel[nouselabelno-1].chk_mode);  
        for(int ii=0;ii<DF_MAX_Pin_Count/64+1;ii++)  
        {  
           fscanf(tmpout,"%llx\n",&nouselabel[nouselabelno-1].pin2x[ii]);  
        }  
        for(int ii=0;ii<DF_MAX_Pin_Count/64+1;ii++)  
        {  
           fscanf(tmpout,"%llx\n",&nouselabel[nouselabelno-1].validpin[ii]);  
        }  
      } else printf("nouselabel allocate error\n");  
   }  
 }  
 static unsigned __int64 re[DF_MAX_Pin_Count/64+1];  
 memset(re,0,sizeof(unsigned __int64)*(DF_MAX_Pin_Count/64+1));  
 char tmp[65],module[32],label[32];  
 tmplabelptr = strstr(address,":");  
 if(tmplabelptr) {  
   memset(module,0,32);  
   memcpy(module,address,abs(tmplabelptr-address));  
   memset(label,0,32);  
   strcpy(label,tmplabelptr+1);  
   sprintf(tmp,"%s_C_%s",module,label);  
 } else {  
   sprintf(tmp,"%s",address);  
 }  
 unsigned __int64 p[DF_MAX_Pin_Count/64+1];  
 unsigned __int64 p2[DF_MAX_Pin_Count/64+1];  
 unsigned int  ts;  
   int  chk;  
 int a = CLABEL::GetPinmodeByName(tmp,p,p2,ts,chk);  
 if(a ==-1)  
 {  
   for(short ii=0;ii<nouselabelno;ii++) {  
     if(!strcmp(tmp,nouselabel[ii].labelname)){  
       memcpy(re,nouselabel[ii].pin2x,sizeof(unsigned __int64)*(DF_MAX_Pin_Count/64+1));  
       break;  
     }  
   }  
 }  
 else  
 {      
 memcpy(re,p,sizeof(unsigned __int64)*(DF_MAX_Pin_Count/64+1));  
 }  
 return re;  
}
 unsigned __int64* GetPin2x_X(char *address) {  
 char *tmplabelptr = NULL;    
 LoadNonusedLabels();  
 static unsigned __int64 re[DF_MAX_Pin_Count/64+1];  
 memset(re,0,sizeof(unsigned __int64)*(DF_MAX_Pin_Count/64+1));  
 char tmp[65],module[32],label[32];  
 tmplabelptr = strstr(address,":");  
 if(tmplabelptr) {  
   memset(module,0,32);  
   memcpy(module,address,abs(tmplabelptr-address));  
   memset(label,0,32);  
   strcpy(label,tmplabelptr+1);  
   sprintf(tmp,"%s_C_%s",module,label);  
 } else {  
   sprintf(tmp,"%s",address);  
 }  
 unsigned __int64 p[DF_MAX_Pin_Count/64+1];  
 unsigned __int64 p2[DF_MAX_Pin_Count/64+1];  
 unsigned int  ts;  
   int  chk;  
 int a = SearchCurrUsedLabel(tmp);  
 if(a==-1) {  
   a = CLABEL::GetPinmodeByName(tmp,p,p2,ts,chk);  
   if(a==-1) {  
     a = SearchLabelIndex(tmp);  
     if(a!=-1) {    
       memcpy(re,nouselabel[a].pin2x,sizeof(unsigned __int64)*(DF_MAX_Pin_Count/64+1));  
     }  
   } else {  
     CLABEL *tmp_label = CLABEL::GetObjectByName(tmp);  
     if(tmp_label) {  
       AddNewLabel(tmp,tmp_label->Getmodulename(),tmp_label->Getaddress(),tmp_label->Getpinmode(),tmp_label->Getpin2x(),tmp_label->GetValidpin(),tmp_label->Gettestno(),tmp_label->Getchkmode(),tmp_label->Getidx());  
     }    
     memcpy(re,p,sizeof(unsigned __int64)*(DF_MAX_Pin_Count/64+1));  
   }  
 } else {    
   memcpy(re,craft_local_label[a].pin2x,sizeof(unsigned __int64)*(DF_MAX_Pin_Count/64+1));  
 }  
 return re;  
}
 unsigned __int64* GetValidPin(char *address) {  
 char *tmplabelptr = NULL,tmppatfile[MAXPATH];  
 static _labelstruct *nouselabel = NULL;  
 static unsigned short nouselabelno = 0;  
 FILE *tmpout = NULL;  
 if(!nouselabelno) {  
  char tmpfile[MAXPATH];  
     sprintf(tmpfile,"unlabel.txt");  
   tmpout = fopen(tmpfile,"r");  
   while(!feof(tmpout)) {  
      if(!nouselabelno) {  
        nouselabel = (_labelstruct *)malloc( sizeof(_labelstruct)*(++nouselabelno) );  
      } else {  
        nouselabel = (_labelstruct *)realloc(nouselabel,sizeof(_labelstruct)*(++nouselabelno));  
      }  
      if(nouselabel) {  
        fscanf(tmpout,"%s",nouselabel[nouselabelno-1].labelname);  
        fscanf(tmpout,"%s",nouselabel[nouselabelno-1].modulename);  
        if(!strcmp(nouselabel[nouselabelno-1].modulename,"*"))  strcpy(nouselabel[nouselabelno-1].modulename,"");  
        fscanf(tmpout,"%ld",&nouselabel[nouselabelno-1].address);  
        fscanf(tmpout,"%d",&nouselabel[nouselabelno-1].pinmode);  
        fscanf(tmpout,"%u",&nouselabel[nouselabelno-1].testno);  
        fscanf(tmpout,"%d\n",&nouselabel[nouselabelno-1].chk_mode);  
        for(int ii=0;ii<DF_MAX_Pin_Count/64+1;ii++)  
        {  
           fscanf(tmpout,"%llx\n",&nouselabel[nouselabelno-1].pin2x[ii]);  
        }  
        for(int ii=0;ii<DF_MAX_Pin_Count/64+1;ii++)  
        {  
           fscanf(tmpout,"%llx\n",&nouselabel[nouselabelno-1].validpin[ii]);  
        }  
      } else printf("nouselabel allocate error\n");  
   }  
 }  
 static unsigned __int64 re[DF_MAX_Pin_Count/64+1];  
 memset(re,0,sizeof(unsigned __int64)*(DF_MAX_Pin_Count/64+1));  
 char tmp[65],module[32],label[32];  
 tmplabelptr = strstr(address,":");  
 if(tmplabelptr) {  
   memset(module,0,32);  
   memcpy(module,address,abs(tmplabelptr-address));  
   memset(label,0,32);  
   strcpy(label,tmplabelptr+1);  
   sprintf(tmp,"%s_C_%s",module,label);  
 } else {  
   sprintf(tmp,"%s",address);  
 }  
 unsigned __int64 p[DF_MAX_Pin_Count/64+1];  
 unsigned __int64 p2[DF_MAX_Pin_Count/64+1];  
 unsigned int ts;  
   int chk;  
 int a = CLABEL::GetPinmodeByName(tmp,p,p2,ts,chk);  
 if(a ==-1)  
 {  
   for(short ii=0;ii<nouselabelno;ii++) {  
     if(!strcmp(tmp,nouselabel[ii].labelname)){  
       memcpy(re,nouselabel[ii].validpin,sizeof(unsigned __int64)*(DF_MAX_Pin_Count/64+1));  
       break;  
     }  
   }  
 }  
 else  
 {      
 memcpy(re,p2,sizeof(unsigned __int64)*(DF_MAX_Pin_Count/64+1));  
 }  
 return re;  
}
 unsigned __int64* GetValidPin_X(char *address) {  
 char *tmplabelptr = NULL;    
 LoadNonusedLabels();  
 static unsigned __int64 re[DF_MAX_Pin_Count/64+1];  
 memset(re,0,sizeof(unsigned __int64)*(DF_MAX_Pin_Count/64+1));  
 char tmp[65],module[32],label[32];  
 tmplabelptr = strstr(address,":");  
 if(tmplabelptr) {  
   memset(module,0,32);  
   memcpy(module,address,abs(tmplabelptr-address));  
   memset(label,0,32);  
   strcpy(label,tmplabelptr+1);  
   sprintf(tmp,"%s_C_%s",module,label);  
 } else {  
   sprintf(tmp,"%s",address);  
 }  
 unsigned __int64 p[DF_MAX_Pin_Count/64+1];  
 unsigned __int64 p2[DF_MAX_Pin_Count/64+1];  
 unsigned int ts;  
   int chk;  
 int a = SearchCurrUsedLabel(tmp);  
 if(a==-1) {  
   a = CLABEL::GetPinmodeByName(tmp,p,p2,ts,chk);  
   if(a==-1) {  
     a = SearchLabelIndex(tmp);  
     if(a!=-1) {    
       memcpy(re,nouselabel[a].validpin,sizeof(unsigned __int64)*(DF_MAX_Pin_Count/64+1));  
     }  
   } else {  
     CLABEL *tmp_label = CLABEL::GetObjectByName(tmp);  
     if(tmp_label) {  
       AddNewLabel(tmp,tmp_label->Getmodulename(),tmp_label->Getaddress(),tmp_label->Getpinmode(),tmp_label->Getpin2x(),tmp_label->GetValidpin(),tmp_label->Gettestno(),tmp_label->Getchkmode(),tmp_label->Getidx());  
     }    
     memcpy(re,p2,sizeof(unsigned __int64)*(DF_MAX_Pin_Count/64+1));  
   }  
 } else {    
   memcpy(re,craft_local_label[a].validpin,sizeof(unsigned __int64)*(DF_MAX_Pin_Count/64+1));  
 }  
 return re;  
}
 unsigned int GetLabelTestNo(char *address) {  
 char *tmplabelptr = NULL,tmppatfile[MAXPATH];  
 static _labelstruct *nouselabel = NULL;  
 static unsigned short nouselabelno = 0;  
 FILE *tmpout = NULL;  
 if(!nouselabelno) {  
  char tmpfile[MAXPATH];  
     sprintf(tmpfile,"unlabel.txt");  
   tmpout = fopen(tmpfile,"r");  
   while(!feof(tmpout)) {  
      if(!nouselabelno) {  
        nouselabel = (_labelstruct *)malloc( sizeof(_labelstruct)*(++nouselabelno) );  
      } else {  
        nouselabel = (_labelstruct *)realloc(nouselabel,sizeof(_labelstruct)*(++nouselabelno));  
      }  
      if(nouselabel) {  
        fscanf(tmpout,"%s",nouselabel[nouselabelno-1].labelname);  
        fscanf(tmpout,"%s",nouselabel[nouselabelno-1].modulename);  
        if(!strcmp(nouselabel[nouselabelno-1].modulename,"*"))  strcpy(nouselabel[nouselabelno-1].modulename,"");  
        fscanf(tmpout,"%ld",&nouselabel[nouselabelno-1].address);  
        fscanf(tmpout,"%d",&nouselabel[nouselabelno-1].pinmode);  
        fscanf(tmpout,"%u",&nouselabel[nouselabelno-1].testno);  
        fscanf(tmpout,"%d\n",&nouselabel[nouselabelno-1].chk_mode);  
        for(int ii=0;ii<DF_MAX_Pin_Count/64+1;ii++)  
        {  
           fscanf(tmpout,"%llx\n",&nouselabel[nouselabelno-1].pin2x[ii]);  
        }  
        for(int ii=0;ii<DF_MAX_Pin_Count/64+1;ii++)  
        {  
           fscanf(tmpout,"%llx\n",&nouselabel[nouselabelno-1].validpin[ii]);  
        }  
      } else printf("nouselabel allocate error\n");  
   }  
 }  
 static unsigned int retestno;  
 char tmp[65],module[32],label[32];  
 tmplabelptr = strstr(address,":");  
 if(tmplabelptr) {  
   memset(module,0,32);  
   memcpy(module,address,abs(tmplabelptr-address));  
   memset(label,0,32);  
   strcpy(label,tmplabelptr+1);  
   sprintf(tmp,"%s_C_%s",module,label);  
 } else {  
   sprintf(tmp,"%s",address);  
 }  
 unsigned __int64 p[DF_MAX_Pin_Count/64+1];  
 unsigned __int64 p2[DF_MAX_Pin_Count/64+1];  
 unsigned int     ts;  
   int     chk;  
 int a = CLABEL::GetPinmodeByName(tmp,p,p2,ts,chk);  
 if(a ==-1)  
 {  
   for(short ii=0;ii<nouselabelno;ii++) {  
     if(!strcmp(tmp,nouselabel[ii].labelname)){  
       retestno=nouselabel[ii].testno;  
       break;  
     }  
   }  
 }  
 else  
 {      
      retestno=ts;  
 }  
 return retestno;  
}
 unsigned int GetLabelTestNo_X(char *address) {  
 char *tmplabelptr = NULL;    
 LoadNonusedLabels();  
 static unsigned int re;  
 char tmp[65],module[32],label[32];  
 tmplabelptr = strstr(address,":");  
 if(tmplabelptr) {  
   memset(module,0,32);  
   memcpy(module,address,abs(tmplabelptr-address));  
   memset(label,0,32);  
   strcpy(label,tmplabelptr+1);  
   sprintf(tmp,"%s_C_%s",module,label);  
 } else {  
   sprintf(tmp,"%s",address);  
 }  
 unsigned __int64 p[DF_MAX_Pin_Count/64+1];  
 unsigned __int64 p2[DF_MAX_Pin_Count/64+1];  
 unsigned int     ts;  
   int     chk;  
 re = SearchCurrUsedLabel(tmp);  
 if(re==-1) {  
   re = CLABEL::GetPinmodeByName(tmp,p,p2,ts,chk);  
   if(re==-1) {  
     re = SearchLabelIndex(tmp);  
     if(re!=-1) {  
       re = nouselabel[re].testno;  
     }  
   } else {  
     CLABEL *tmp_label = CLABEL::GetObjectByName(tmp);  
     if(tmp_label) {  
       AddNewLabel(tmp,tmp_label->Getmodulename(),tmp_label->Getaddress(),tmp_label->Getpinmode(),tmp_label->Getpin2x(),tmp_label->GetValidpin(),tmp_label->Gettestno(),tmp_label->Getchkmode(),tmp_label->Getidx());  
     }  
     re=ts;  
   }  
 } else {  
   re = craft_local_label[re].testno;  
 }  
 return re;  
}
 int GetLabelChkMode(char *address) {  
 char *tmplabelptr = NULL,tmppatfile[MAXPATH];  
 static _labelstruct *nouselabel = NULL;  
 static unsigned short nouselabelno = 0;  
 FILE *tmpout = NULL;  
 if(!nouselabelno) {  
  char tmpfile[MAXPATH];  
     sprintf(tmpfile,"unlabel.txt");  
   tmpout = fopen(tmpfile,"r");  
   while(!feof(tmpout)) {  
      if(!nouselabelno) {  
        nouselabel = (_labelstruct *)malloc( sizeof(_labelstruct)*(++nouselabelno) );  
      } else {  
        nouselabel = (_labelstruct *)realloc(nouselabel,sizeof(_labelstruct)*(++nouselabelno));  
      }  
      if(nouselabel) {  
        fscanf(tmpout,"%s",nouselabel[nouselabelno-1].labelname);  
        fscanf(tmpout,"%s",nouselabel[nouselabelno-1].modulename);  
        if(!strcmp(nouselabel[nouselabelno-1].modulename,"*"))  strcpy(nouselabel[nouselabelno-1].modulename,"");  
        fscanf(tmpout,"%ld",&nouselabel[nouselabelno-1].address);  
        fscanf(tmpout,"%d",&nouselabel[nouselabelno-1].pinmode);  
        fscanf(tmpout,"%u",&nouselabel[nouselabelno-1].testno);  
        fscanf(tmpout,"%d\n",&nouselabel[nouselabelno-1].chk_mode);  
        for(int ii=0;ii<DF_MAX_Pin_Count/64+1;ii++)  
        {  
           fscanf(tmpout,"%llx\n",&nouselabel[nouselabelno-1].pin2x[ii]);  
        }  
        for(int ii=0;ii<DF_MAX_Pin_Count/64+1;ii++)  
        {  
           fscanf(tmpout,"%llx\n",&nouselabel[nouselabelno-1].validpin[ii]);  
        }  
      } else printf("nouselabel allocate error\n");  
   }  
 }  
 long int re = -1;  
 char tmp[65],module[32],label[32];  
 tmplabelptr = strstr(address,":");  
 if(tmplabelptr) {  
   memset(module,0,32);  
   memcpy(module,address,abs(tmplabelptr-address));  
   memset(label,0,32);  
   strcpy(label,tmplabelptr+1);  
   sprintf(tmp,"%s_C_%s",module,label);  
 } else {  
   sprintf(tmp,"%s",address);  
 }  
 unsigned __int64 p[DF_MAX_Pin_Count/64+1];  
 unsigned __int64 p2[DF_MAX_Pin_Count/64+1];  
 unsigned int     ts;  
   int     chk;  
 re = CLABEL::GetPinmodeByName(tmp,p,p2,ts,chk);  
 if(re==-1) {  
   for(short ii=0;ii<nouselabelno;ii++) {  
     if(!strcmp(tmp,nouselabel[ii].labelname)){  
       chk = nouselabel[ii].chk_mode;  
       break;  
     }  
   }  
 }  
 return chk;  
}
 int GetLabelChkMode_X(char *address) {  
 char *tmplabelptr = NULL;    
 LoadNonusedLabels();  
 long int re = -1;  
 char tmp[65],module[32],label[32];  
 tmplabelptr = strstr(address,":");  
 if(tmplabelptr) {  
   memset(module,0,32);  
   memcpy(module,address,abs(tmplabelptr-address));  
   memset(label,0,32);  
   strcpy(label,tmplabelptr+1);  
   sprintf(tmp,"%s_C_%s",module,label);  
 } else {  
   sprintf(tmp,"%s",address);  
 }  
 unsigned __int64 p[DF_MAX_Pin_Count/64+1];  
 unsigned __int64 p2[DF_MAX_Pin_Count/64+1];  
 unsigned int     ts;  
   int     chk;  
 re = CLABEL::GetPinmodeByName(tmp,p,p2,ts,chk);  
 if(re==-1) {  
   for(short ii=0;ii<nouselabelno;ii++) {  
     if(!strcmp(tmp,nouselabel[ii].labelname)){  
       chk = nouselabel[ii].chk_mode;  
       break;  
     }  
   }  
 }  
 return chk;  
}
 int GetLabelAddrOffsetFactor(int pinmode, int offset, char *statement, int lineno) {      
 char msg[256];       
 if (pinmode==_IO2X_ && offset%2 != 0) {       
    sprintf(msg, "[Statement : %s] [Line : %d]\n The address must be even on IO_2X mode!", statement, lineno);       
    MessageBox(0,msg,"plncmp",MB_OK|MB_ICONERROR|MB_SETFOREGROUND);       
 } else if (pinmode==_DBL_IO2X_ && offset%4 != 0) {       
    sprintf(msg, "[Statement : %s] [Line : %d]\n The address must be multiple of 4 on DBL_2X mode!", statement, lineno);       
    MessageBox(0,msg,"plncmp",MB_OK|MB_ICONERROR|MB_SETFOREGROUND);       
 }           
 return pinmode==_IO2X_||pinmode==_DBL_IO2X_?2:1;          
}
int tmpfreezepin[DF_MAX_Pin_Count],tmppinno=0,alltmpsiteno=0;
FW_SharedMemory* Fw_Shmem = NULL;
HANDLE FwShmHandle = NULL;
int MARK_NO[DF_MAX_Site_Count][100]={0};
short MARK_NO_CNT[DF_MAX_Site_Count]={0};
int tmppinmode[DF_MAX_Pin_Count]={ 0 };
 int ChkMarkNo(int val) {           
 if(alltmpsiteno==0)alltmpsiteno=GetSiteNo();           
 int *ate_pin,pin_num;           
 if(tmppinno!=0)           
 socket_freeze(tmpfreezepin,tmppinno,_OFF_,tmppinmode);           
 if(val==-1)           
 {           
   LUINT s = 0;           
   for(int ii=0;ii<alltmpsiteno;ii++){           
      if(Plugin.ShmPtr->TestPlanProgram.Status.ActiveSite[ii]==1)           
      s|=((LUINT)1<<ii);           
   }           
   return 0;           
 }           
   int actives=0;           
 int mask=0;           
 LUINT s = 0;           
 for(int ii=0;ii<alltmpsiteno;ii++){           
 if(Plugin.ShmPtr->TestPlanProgram.Status.ActiveSite[ii]==1)           
   actives++;           
 }           
 for(int ii=0;ii<alltmpsiteno;ii++){           
 bool found=0;           
 for(int jj=0;jj<MARK_NO_CNT[ii];jj++){           
 if((val == MARK_NO[ii][jj]) && Plugin.ShmPtr->TestPlanProgram.Status.ActiveSite[ii]){           
   mask++;           
   found=1;           
   break;           
 }           
 }           
 if(!found)           
 {           
   s|=((LUINT)1<<ii);           
 }           
 }           
 HW_EnabledSites(s);           
 tmppinno=0;           
 if(s!=0){           
 for(int _ii_=0; _ii_<alltmpsiteno; _ii_++){           
   if(!TrueOrFalse(s,_ii_)){           
     if ((pin_num = GetPinSiteAllIOChannel(_ii_, ate_pin)) > 0) {           
     for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];           
     tmppinno += pin_num;           
     }           
     if ((pin_num = GetPinSiteAllLCDChannel(_ii_, ate_pin)) > 0) {           
     for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];           
     tmppinno += pin_num;           
     }           
   }           
 }           
 socket_freeze(tmpfreezepin,tmppinno,_ON_,tmppinmode);           
 }           
 for(int ii=0;ii<alltmpsiteno;ii++){           
 if(!TrueOrFalse(s,ii))           
     Plugin.ShmPtr->TestPlanProgram.Status.ActiveSite[ii] = 0;           
 }           
 if(mask == actives)return 1;           
 else return 0;           
 }

 int SetMarkNo(int flag,char* str) {           
 if(alltmpsiteno==0)alltmpsiteno=GetSiteNo();           
 int Lindex=0;           
 int Llist[100];           
 char str2[1024];           
 sprintf(str2,"%s",str);           
 char* pt = strtok(str2,",");           
 while(pt!=NULL){           
 Llist[Lindex++] = atoi(pt);           
 pt = strtok(NULL,",");           
 }           
 if(flag==PASS){           
 for(int kk=0;kk<Lindex;kk++){           
     for(int ii=0;ii<alltmpsiteno;ii++){           
      if((PLAN_RESULT_MS[ii]==PASS) && Plugin.ShmPtr->TestPlanProgram.Status.ActiveSite[ii]){           
       int jj=0;           
           for(jj=0;jj<MARK_NO_CNT[ii];jj++){           
           if(MARK_NO[ii][jj]==Llist[kk])break;           
         }           
       if(jj==MARK_NO_CNT[ii])           
                  MARK_NO[ii][MARK_NO_CNT[ii]++]=Llist[kk];           
       }           
   }           
  }           
 }           
 else{           
 for(int kk=0;kk<Lindex;kk++){           
     for(int ii=0;ii<alltmpsiteno;ii++){           
      if((PLAN_RESULT_MS[ii]==FAIL)&& Plugin.ShmPtr->TestPlanProgram.Status.ActiveSite[ii]){           
       int jj=0;           
           for(jj=0;jj<MARK_NO_CNT[ii];jj++){           
           if(MARK_NO[ii][jj]==Llist[kk])break;           
         }           
       if(jj==MARK_NO_CNT[ii])           
                  MARK_NO[ii][MARK_NO_CNT[ii]++]=Llist[kk];           
       }           
   }           
  }           
 }           
 LUINT s = 0;           
 for(int ii=0;ii<alltmpsiteno;ii++)           
 {           
   PLAN_RESULT_MS[ii]=PASS;           
   s|=((LUINT)1<<ii);           
 }           
 HW_EnabledSites(s);           
 return 0;           
 }

 int ClearMarkNo( ) {           
 for(int ii=0;ii<DF_MAX_Site_Count;ii++)           
    MARK_NO_CNT[ii]=0;           
 }

 LUINT TranslateLUINT(int flag) {             
 static LUINT rtn;           
 rtn = (int)flag;           
 return rtn;             
 }           
 LUINT TranslateLUINT(unsigned int flag) {             
 static LUINT rtn;           
 rtn = (int)flag;           
 return rtn;             
 }           
 LUINT TranslateLUINT(LUINT flag) {             
 static LUINT rtn;           
 rtn = flag;           
 return rtn;             
 }
 int CRAFT_Get_Bin_Value(char *BinName,int BinType) {           
   CCATEGORY *temp=NULL;           
   int bin = -1;           
   temp = CCATEGORY::GetCategoryFromNameType(BinName,BinType);           
   if(temp) {           
      bin = temp->GetVal();           
   }       
   if(bin==-1) {       
     char msg[256];       
   sprintf(msg,"Cannot find matched bin name(%s)!",BinName);       
     MessageBox(NULL,msg,"SET_FAIL_BIN",MB_OK);       
   }           
   return bin;           
 }





#line 5 "B20041C_2S_LT40C_CP1_V1P0.PLN"












using namespace std;




#line 21 "B20041C_2S_LT40C_CP1_V1P0.PLN"

           int  test_no        = 0 ;
           int  debug_mode     = 1 ;
           int  offline_mode   = 1 ;
           int  rst_lvl        = 1 ;
           int  set_lvl        = 2 ; 
           int  temp_data[8];
           int pass_flag[site_count] ;
double voltage_4bit[site_count][256];
double VBG_VO_CP1[site_count][1024]={0,0};
double VTC_VO_CP1[site_count][1024]={0,0};      
       
int m=0;
char  wafer_id[40], lot_id[40];
string lot_idstr; 
string wafer_idstr;
string filename;
ofstream file;

           double  current_VDD_CH1[site_count] ={0,0};
           double  current_VDD_CH2[site_count] ={0,0};
           double  current_VDD_CH3[site_count] ={0,0};
           double  current_VDD_CH4[site_count] ={0,0};
           double  current_V33_1_4[site_count] ={0,0};
           double  current_V33_2[site_count] ={0,0};  
           double  current_V33_3[site_count] ={0,0}; 

           double  current_AVE[site_count] ={0,0};    
           double  current_MIN[site_count] ={0,0}; 
           double  current_MAX[site_count] ={0,0}; 
           double  current_Delta[site_count] ={0,0};  
CCATEGORY all_pass_0("all_pass",0);
CCATEGORY hw_Open_short_test_0("hw_Open_short_test",0);
CCATEGORY hw_Leakage_test_0("hw_Leakage_test",0);
CCATEGORY hw_Trim_test_0("hw_Trim_test",0);
CCATEGORY fail_last_item_0("fail_last_item",0);
CCATEGORY hw_error_bin_0("hw_error_bin",0);
CCATEGORY SYS_ALARM_HW_BIN_0("SYS_ALARM_HW_BIN",0);
CCATEGORY SYS_ERROR_HW_BIN_0("SYS_ERROR_HW_BIN",0);

#line 60 "B20041C_2S_LT40C_CP1_V1P0.PLN"
                                 
                                  
CCATEGORY all_pass_1("all_pass",1);
CCATEGORY sw_OS_RESET_1("sw_OS_RESET",1);
CCATEGORY sw_V33_0p5V_Leakage_1("sw_V33_0p5V_Leakage",1);
CCATEGORY sw_V33_1V_Leakage_1("sw_V33_1V_Leakage",1);
CCATEGORY sw_VBG_TRIM_1("sw_VBG_TRIM",1);
CCATEGORY sw_VTC_TRIM_1("sw_VTC_TRIM",1);
CCATEGORY sw_VBG_a_TRIM_1("sw_VBG_a_TRIM",1);
CCATEGORY sw_VTC_a_TRIM_1("sw_VTC_a_TRIM",1);
CCATEGORY fail_last_item_1("fail_last_item",1);
CCATEGORY hw_error_bin_1("hw_error_bin",1);
CCATEGORY SYS_ALARM_SW_BIN_1("SYS_ALARM_SW_BIN",1);
CCATEGORY SYS_ERROR_SW_BIN_1("SYS_ERROR_SW_BIN",1);

#line 74 "B20041C_2S_LT40C_CP1_V1P0.PLN"


#line 1 "B20041C_2S_LT40C_CP1_V1P0.PLN"

/*BEFORE-AFTER FUNCTION ASSIGNMENT*/
__declspec(dllexport)  int test_start();
__declspec(dllexport)  int test_end();

/*FUNCTION DECLIRATION*/
__declspec(dllexport)  int OS_TEST();
__declspec(dllexport)  int V33_0p5V_Leakage();
__declspec(dllexport)  int V33_1V_Leakage();
__declspec(dllexport)  int VBG_TRIM();
__declspec(dllexport)  int VTC_TRIM();
__declspec(dllexport)  int VBG_a_TRIM();
__declspec(dllexport)  int VTC_a_TRIM();
__declspec(dllexport)  int last_item_test();

/*CITEM DECLIRATION*/
CITEM OS_TEST_Chroma_0("OS_TEST",OS_TEST);
CITEM V33_0p5V_Leakage_Chroma_1("V33_0p5V_Leakage",V33_0p5V_Leakage);
CITEM V33_1V_Leakage_Chroma_2("V33_1V_Leakage",V33_1V_Leakage);
CITEM VBG_TRIM_Chroma_3("VBG_TRIM",VBG_TRIM);
CITEM VTC_TRIM_Chroma_4("VTC_TRIM",VTC_TRIM);
CITEM VBG_a_TRIM_Chroma_5("VBG_a_TRIM",VBG_a_TRIM);
CITEM VTC_a_TRIM_Chroma_6("VTC_a_TRIM",VTC_a_TRIM);
CITEM last_item_test_Chroma_7("last_item_test",last_item_test);

#line 89 "B20041C_2S_LT40C_CP1_V1P0.PLN"

#line 89 "B20041C_2S_LT40C_CP1_V1P0.PLN"


__declspec(dllexport) int START_UP() 
{
TEST_NO(0);
if(FwShmHandle==NULL) COM_CreateAndMapSharedMemory_fw_shmem(&Fw_Shmem,&FwShmHandle);                             
#ifdef JUDGE_VARIABLE_COMMENT_TO_STDF
	FILE *temp_stdf_out=fopen("CommentOutputSTDF","w+");
	if(temp_stdf_out)  fclose(temp_stdf_out);
#endif                             
#ifdef RELOAD_PAT_OFF
	FILE *temp_reloadoff=fopen("ReloadPatOff","w+");
	if(temp_reloadoff)  fclose(temp_reloadoff);
#endif


#line 91 "B20041C_2S_LT40C_CP1_V1P0.PLN"

  string device_name="B20041C_LT40C";
  TestSpec_Fun_Std(device_name);
       
  
#line 95 "B20041C_2S_LT40C_CP1_V1P0.PLN"
SET_LEVELN("B20041C_2S_LT40C_CP1_V1P0.PLN",95,rst_lvl,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),0.000000e+000,0.000000e+000,0.000000e+000,0.000000e+000,0.000000e+000,0.000000e+000,0.000000e+000,_KEEP_CURRENT_F,_KEEP_CURRENT_F);  
  
#line 96 "B20041C_2S_LT40C_CP1_V1P0.PLN"
SET_LEVELN("B20041C_2S_LT40C_CP1_V1P0.PLN",96,set_lvl,EN_SET,(EN_SET).GetTestPinno(),0.000000e+000,3.300000e+000,8.000000e-001,1.700000e+000,0.000000e+000,0.000000e+000,0.000000e+000,_KEEP_CURRENT_F,_KEEP_CURRENT_F);
  
#line 97 "B20041C_2S_LT40C_CP1_V1P0.PLN"
SET_LEVELN("B20041C_2S_LT40C_CP1_V1P0.PLN",97,set_lvl,spi_pin,(spi_pin).GetTestPinno(),0.000000e+000,3.300000e+000,1.700000e+000,1.800000e+000,0.000000e+000,0.000000e+000,0.000000e+000,_KEEP_CURRENT_F,_KEEP_CURRENT_F); 
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"
if(enter_power_down_fail_site){          
  LUINT tmpmask = CPIN::GetMask(),tmpfailmask = 0x0;                    
  for(int _gg_=0;_gg_<DF_MAX_Site_Count;_gg_++) {                    
    if((PLAN_RESULT_MS[_gg_]==FAIL) && TrueOrFalse(tmpmask,_gg_))                    
      tmpfailmask |= (LUINT)0x1<<_gg_;                    
  }                    
  CPIN::SetMask(tmpfailmask);          
  #line 98 "B20041C_2S_LT40C_CP1_V1P0.PLN"                    
  LEVELS("B20041C_2S_LT40C_CP1_V1P0.PLN",98,rst_lvl,2.000000e-003,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),1);          
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"                    
  CPIN::SetMask(tmpmask);          
}           
  else{          
  #line 98 "B20041C_2S_LT40C_CP1_V1P0.PLN"          
  LEVELS("B20041C_2S_LT40C_CP1_V1P0.PLN",98,rst_lvl,2.000000e-003,NULL,0,0);          
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"          
  }          
  #line 98 "B20041C_2S_LT40C_CP1_V1P0.PLN"
;
  
  
#line 100 "B20041C_2S_LT40C_CP1_V1P0.PLN"
PIN_MODE("B20041C_2S_LT40C_CP1_V1P0.PLN",100,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),0,0,1,0,0);
  
#line 101 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",101,MLDPS_ALLPINS,(MLDPS_ALLPINS).GetTestPinno(),0.000000e+000,0,5,1.000000e-001,0,1,5.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);
  
#line 102 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",102,MLDPS_ALLPINS,(MLDPS_ALLPINS).GetTestPinno(),0.000000e+000,0,5,1.000000e-001,0,0,5.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);
  
#line 103 "B20041C_2S_LT40C_CP1_V1P0.PLN"
RELAY_OFF("B20041C_2S_LT40C_CP1_V1P0.PLN",103,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),127,2.000000e-003);
  
#line 104 "B20041C_2S_LT40C_CP1_V1P0.PLN"
LOAD_PAT("B20041C_2S_LT40C_CP1_V1P0.PLN",104,"./PAT/B20041C.ppo",-1); 
}

__declspec(dllexport) int test_start() 
{

power_down_fail_site_same_flag = false;
enter_power_down_fail_site = false;

#line 107 "B20041C_2S_LT40C_CP1_V1P0.PLN"

   {
SET_STATEMENT_INFO(_ID_SOCKET_INC,114);
LUINT tmpMask = CPIN::GetMask();
int *ate_pin,pin_num;
int tmpfreezepin[DF_MAX_Pin_Count],tmppinno=0;
int tmppinmode[DF_MAX_Pin_Count];
for(int _ii_=0; _ii_<DF_MAX_Site_Count; _ii_++){
	if(TrueOrFalse(tmpMask,_ii_)){
		if ((pin_num = GetPinSiteAllIOChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
	}
}
socket_freeze(tmpfreezepin,tmppinno,_ON_,tmppinmode);                       
for(short SOCKET = 0; SOCKET<DF_MAX_Site_Count; SOCKET++) {
	if(TrueOrFalse(tmpMask,SOCKET)){
		int curfreezepin[DF_MAX_Pin_Count],curpinno;
		CPIN::SetMask((LUINT)0x1<<SOCKET);
		curpinno=0;
		if ((pin_num = GetPinSiteAllIOChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		socket_freeze(curfreezepin,curpinno,_OFF_,tmppinmode);
#line 108 "B20041C_2S_LT40C_CP1_V1P0.PLN"

     for(int i=0;i<1024;i++){
       VBG_VO_CP1[SOCKET][i]=0;
       VTC_VO_CP1[SOCKET][i]=0;  
    
     }
  		socket_freeze(curfreezepin,curpinno,_ON_,NULL);
	}
}
socket_freeze(tmpfreezepin,tmppinno,_OFF_,tmppinmode);
CPIN::SetMask(tmpMask);
}
#line 114 "B20041C_2S_LT40C_CP1_V1P0.PLN"

#line 114 "B20041C_2S_LT40C_CP1_V1P0.PLN"

  for(int i = 0;i<site_count;i++)
    {
          pass_flag[i] = 1;
    }
    test_no = 0;
    SHOW_TEST_TIME(test_time) ; 
    cvs_value.clear(); 
    
    
#line 123 "B20041C_2S_LT40C_CP1_V1P0.PLN"
READ_WAFER_ID("B20041C_2S_LT40C_CP1_V1P0.PLN",123, wafer_id, lot_id);  
    if(offline_mode)
    {   
        strcpy(wafer_id,"F67750-21-F5"); 
        strcpy(lot_id,  "F67750"); 
    }
    
#line 129 "B20041C_2S_LT40C_CP1_V1P0.PLN"
READ_PROBER_XY("B20041C_2S_LT40C_CP1_V1P0.PLN",129, PHIF_X, sizeof(PHIF_X)/sizeof(PHIF_X[0]), PHIF_Y, sizeof(PHIF_Y)/sizeof(PHIF_Y[0]));  
    
{
SET_STATEMENT_INFO(_ID_SOCKET_INC,140);
LUINT tmpMask = CPIN::GetMask();
int *ate_pin,pin_num;
int tmpfreezepin[DF_MAX_Pin_Count],tmppinno=0;
int tmppinmode[DF_MAX_Pin_Count];
for(int _ii_=0; _ii_<DF_MAX_Site_Count; _ii_++){
	if(TrueOrFalse(tmpMask,_ii_)){
		if ((pin_num = GetPinSiteAllIOChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
	}
}
socket_freeze(tmpfreezepin,tmppinno,_ON_,tmppinmode);                       
for(short SOCKET = 0; SOCKET<DF_MAX_Site_Count; SOCKET++) {
	if(TrueOrFalse(tmpMask,SOCKET)){
		int curfreezepin[DF_MAX_Pin_Count],curpinno;
		CPIN::SetMask((LUINT)0x1<<SOCKET);
		curpinno=0;
		if ((pin_num = GetPinSiteAllIOChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		socket_freeze(curfreezepin,curpinno,_OFF_,tmppinmode);
#line 131 "B20041C_2S_LT40C_CP1_V1P0.PLN"
  
        if(offline_mode)
        {  
        PHIF_X[SOCKET]=die_x ;
        PHIF_Y[SOCKET]=die_y+ 1*SOCKET ; 
    
        printf("PHIF_X[%d]=%d,PHIF_Y[%d]=%d\n",SOCKET,PHIF_X[SOCKET],SOCKET,PHIF_Y[SOCKET]); 
        fflush(stdout);
        }
    		socket_freeze(curfreezepin,curpinno,_ON_,NULL);
	}
}
socket_freeze(tmpfreezepin,tmppinno,_OFF_,tmppinmode);
CPIN::SetMask(tmpMask);
}
#line 140 "B20041C_2S_LT40C_CP1_V1P0.PLN"

#line 140 "B20041C_2S_LT40C_CP1_V1P0.PLN"
   
    lot_idstr= lot_id; 
    wafer_idstr=wafer_id; 
  
    filename=change_local_path2+lot_idstr+"/CP1/"+(lot_idstr+"_"+wafer_idstr+"_CP1.csv"); 
    ifstream csvFile(filename, ios::in);
    if(!csvFile){
        csvFile.close();
        file.open(filename, ios::app);
        write_csv(file,lot_idstr,wafer_idstr,delimiter, data); 
        file << endl;
    }else{
        csvFile.close();
        file.open(filename, ios::app);
    } 
  
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"
if(enter_power_down_fail_site){          
  LUINT tmpmask = CPIN::GetMask(),tmpfailmask = 0x0;                    
  for(int _gg_=0;_gg_<DF_MAX_Site_Count;_gg_++) {                    
    if((PLAN_RESULT_MS[_gg_]==FAIL) && TrueOrFalse(tmpmask,_gg_))                    
      tmpfailmask |= (LUINT)0x1<<_gg_;                    
  }                    
  CPIN::SetMask(tmpfailmask);          
  #line 156 "B20041C_2S_LT40C_CP1_V1P0.PLN"                    
  LEVELS("B20041C_2S_LT40C_CP1_V1P0.PLN",156,rst_lvl,5.000000e-003,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),1);          
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"                    
  CPIN::SetMask(tmpmask);          
}           
  else{          
  #line 156 "B20041C_2S_LT40C_CP1_V1P0.PLN"          
  LEVELS("B20041C_2S_LT40C_CP1_V1P0.PLN",156,rst_lvl,5.000000e-003,NULL,0,0);          
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"          
  }          
  #line 156 "B20041C_2S_LT40C_CP1_V1P0.PLN"
;
  
#line 157 "B20041C_2S_LT40C_CP1_V1P0.PLN"
PIN_MODE("B20041C_2S_LT40C_CP1_V1P0.PLN",157,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),0,0,1,0,0);
  
#line 158 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",158,MLDPS_ALLPINS,(MLDPS_ALLPINS).GetTestPinno(),0.000000e+000,0,5,4.000000e-001,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);
  
#line 159 "B20041C_2S_LT40C_CP1_V1P0.PLN"
RELAY_OFF("B20041C_2S_LT40C_CP1_V1P0.PLN",159,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),4,2.000000e-003);    
  
#line 160 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",160,MLDPS_ALLPINS,(MLDPS_ALLPINS).GetTestPinno(),0.000000e+000,0,5,4.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);
}

__declspec(dllexport) int test_end() 
{


#line 163 "B20041C_2S_LT40C_CP1_V1P0.PLN"

  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"
if(enter_power_down_fail_site){          
  LUINT tmpmask = CPIN::GetMask(),tmpfailmask = 0x0;                    
  for(int _gg_=0;_gg_<DF_MAX_Site_Count;_gg_++) {                    
    if((PLAN_RESULT_MS[_gg_]==FAIL) && TrueOrFalse(tmpmask,_gg_))                    
      tmpfailmask |= (LUINT)0x1<<_gg_;                    
  }                    
  CPIN::SetMask(tmpfailmask);          
  #line 164 "B20041C_2S_LT40C_CP1_V1P0.PLN"                    
  LEVELS("B20041C_2S_LT40C_CP1_V1P0.PLN",164,rst_lvl,2.000000e-003,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),1);          
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"                    
  CPIN::SetMask(tmpmask);          
}           
  else{          
  #line 164 "B20041C_2S_LT40C_CP1_V1P0.PLN"          
  LEVELS("B20041C_2S_LT40C_CP1_V1P0.PLN",164,rst_lvl,2.000000e-003,NULL,0,0);          
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"          
  }          
  #line 164 "B20041C_2S_LT40C_CP1_V1P0.PLN"
;
  
#line 165 "B20041C_2S_LT40C_CP1_V1P0.PLN"
PIN_MODE("B20041C_2S_LT40C_CP1_V1P0.PLN",165,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),0,0,1,0,0);
  
#line 166 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",166,MLDPS_ALLPINS,(MLDPS_ALLPINS).GetTestPinno(),0.000000e+000,0,5,1.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);
  
#line 167 "B20041C_2S_LT40C_CP1_V1P0.PLN"
RELAY_OFF("B20041C_2S_LT40C_CP1_V1P0.PLN",167,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),127,2.000000e-003);
}

__declspec(dllexport) int RELEASE() 
{


#line 170 "B20041C_2S_LT40C_CP1_V1P0.PLN"

  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"
if(enter_power_down_fail_site){          
  LUINT tmpmask = CPIN::GetMask(),tmpfailmask = 0x0;                    
  for(int _gg_=0;_gg_<DF_MAX_Site_Count;_gg_++) {                    
    if((PLAN_RESULT_MS[_gg_]==FAIL) && TrueOrFalse(tmpmask,_gg_))                    
      tmpfailmask |= (LUINT)0x1<<_gg_;                    
  }                    
  CPIN::SetMask(tmpfailmask);          
  #line 171 "B20041C_2S_LT40C_CP1_V1P0.PLN"                    
  LEVELS("B20041C_2S_LT40C_CP1_V1P0.PLN",171,rst_lvl,2.000000e-003,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),1);          
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"                    
  CPIN::SetMask(tmpmask);          
}           
  else{          
  #line 171 "B20041C_2S_LT40C_CP1_V1P0.PLN"          
  LEVELS("B20041C_2S_LT40C_CP1_V1P0.PLN",171,rst_lvl,2.000000e-003,NULL,0,0);          
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"          
  }          
  #line 171 "B20041C_2S_LT40C_CP1_V1P0.PLN"
;
  
#line 172 "B20041C_2S_LT40C_CP1_V1P0.PLN"
PIN_MODE("B20041C_2S_LT40C_CP1_V1P0.PLN",172,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),0,0,1,0,0);
  
#line 173 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",173,MLDPS_ALLPINS,(MLDPS_ALLPINS).GetTestPinno(),0.000000e+000,0,5,1.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);
  
#line 174 "B20041C_2S_LT40C_CP1_V1P0.PLN"
RELAY_OFF("B20041C_2S_LT40C_CP1_V1P0.PLN",174,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),127,2.000000e-003);
  
}

__declspec(dllexport) int POWER_DOWN_FAIL_SITE_X() 
{


#line 178 "B20041C_2S_LT40C_CP1_V1P0.PLN"

    
#line 179 "B20041C_2S_LT40C_CP1_V1P0.PLN"
PIN_MODE("B20041C_2S_LT40C_CP1_V1P0.PLN",179,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),5,0,1,3,0); 
    #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"
if(enter_power_down_fail_site){          
  LUINT tmpmask = CPIN::GetMask(),tmpfailmask = 0x0;                    
  for(int _gg_=0;_gg_<DF_MAX_Site_Count;_gg_++) {                    
    if((PLAN_RESULT_MS[_gg_]==FAIL) && TrueOrFalse(tmpmask,_gg_))                    
      tmpfailmask |= (LUINT)0x1<<_gg_;                    
  }                    
  CPIN::SetMask(tmpfailmask);          
  #line 180 "B20041C_2S_LT40C_CP1_V1P0.PLN"                    
  LEVELS("B20041C_2S_LT40C_CP1_V1P0.PLN",180,rst_lvl,5.000000e-003,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),1);          
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"                    
  CPIN::SetMask(tmpmask);          
}           
  else{          
  #line 180 "B20041C_2S_LT40C_CP1_V1P0.PLN"          
  LEVELS("B20041C_2S_LT40C_CP1_V1P0.PLN",180,rst_lvl,5.000000e-003,NULL,0,0);          
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"          
  }          
  #line 180 "B20041C_2S_LT40C_CP1_V1P0.PLN"
; 
    
#line 181 "B20041C_2S_LT40C_CP1_V1P0.PLN"
PIN_MODE("B20041C_2S_LT40C_CP1_V1P0.PLN",181,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),0,0,1,0,0); 
    
#line 182 "B20041C_2S_LT40C_CP1_V1P0.PLN"
if(!power_down_fail_site_same_flag)FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",182,MLDPS_ALLPINS,(MLDPS_ALLPINS).GetTestPinno(),0.000000e+000,0,4,1.000000e-002,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);
    
#line 183 "B20041C_2S_LT40C_CP1_V1P0.PLN"
WAIT("B20041C_2S_LT40C_CP1_V1P0.PLN",183,5.000000e-003);
    
#line 184 "B20041C_2S_LT40C_CP1_V1P0.PLN"
if(!power_down_fail_site_same_flag)FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",184,MLDPS_ALLPINS,(MLDPS_ALLPINS).GetTestPinno(),0.000000e+000,0,5,4.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);
    
#line 185 "B20041C_2S_LT40C_CP1_V1P0.PLN"
RELAY_OFF("B20041C_2S_LT40C_CP1_V1P0.PLN",185,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),127,2.000000e-003); 
}

poweron()
{
    
#line 190 "B20041C_2S_LT40C_CP1_V1P0.PLN"
RELAY_ON("B20041C_2S_LT40C_CP1_V1P0.PLN",190,CS+SCLK_IN+SD_IN+SD_OUT+RESET+EN_SET,(CS+SCLK_IN+SD_IN+SD_OUT+RESET+EN_SET).GetTestPinno(),4,2.000000e-003);
    
#line 191 "B20041C_2S_LT40C_CP1_V1P0.PLN"
if(!power_down_fail_site_same_flag)FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",191,V33_dig,(V33_dig).GetTestPinno(),3.300000e+000,0,5,3.000000e-001,0,1,5.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);
    #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"
if(enter_power_down_fail_site){          
  LUINT tmpmask = CPIN::GetMask(),tmpfailmask = 0x0;                    
  for(int _gg_=0;_gg_<DF_MAX_Site_Count;_gg_++) {                    
    if((PLAN_RESULT_MS[_gg_]==FAIL) && TrueOrFalse(tmpmask,_gg_))                    
      tmpfailmask |= (LUINT)0x1<<_gg_;                    
  }                    
  CPIN::SetMask(tmpfailmask);          
  #line 192 "B20041C_2S_LT40C_CP1_V1P0.PLN"                    
  LEVELS("B20041C_2S_LT40C_CP1_V1P0.PLN",192,set_lvl,3.000000e-003,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),1);          
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"                    
  CPIN::SetMask(tmpmask);          
}           
  else{          
  #line 192 "B20041C_2S_LT40C_CP1_V1P0.PLN"          
  LEVELS("B20041C_2S_LT40C_CP1_V1P0.PLN",192,set_lvl,3.000000e-003,NULL,0,0);          
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"          
  }          
  #line 192 "B20041C_2S_LT40C_CP1_V1P0.PLN"
;
    
    double  t_write = 1.000000e-006;  
    
    
#line 196 "B20041C_2S_LT40C_CP1_V1P0.PLN"
RATEN("B20041C_2S_LT40C_CP1_V1P0.PLN",196,1,t_write);
    
#line 197 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MARKERN("B20041C_2S_LT40C_CP1_V1P0.PLN",197,1,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),0*t_write,MAXDOUBLE,MAXDOUBLE,0.000000e+000,MAXDOUBLE,6.000000e-001*t_write,MAXDOUBLE);
    
#line 198 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MARKERN("B20041C_2S_LT40C_CP1_V1P0.PLN",198,1,SCLK_IN,(SCLK_IN).GetTestPinno(),(SCLK_IN).IsIOAllPins(),3.000000e-001*t_write,8.000000e-001*t_write,MAXDOUBLE,0.000000e+000,MAXDOUBLE,5.000000e-001*t_write,MAXDOUBLE);
    
#line 199 "B20041C_2S_LT40C_CP1_V1P0.PLN"
RATEN("B20041C_2S_LT40C_CP1_V1P0.PLN",199,2,t_write);
    
#line 200 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MARKERN("B20041C_2S_LT40C_CP1_V1P0.PLN",200,2,SCLK_IN,(SCLK_IN).GetTestPinno(),(SCLK_IN).IsIOAllPins(),3.000000e-001*t_write,-1,MAXDOUBLE,0.000000e+000,MAXDOUBLE,5.000000e-001*t_write,MAXDOUBLE);  
    
#line 201 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MARKERN("B20041C_2S_LT40C_CP1_V1P0.PLN",201,2,CS,(CS).GetTestPinno(),(CS).IsIOAllPins(),4.000000e-001*t_write,MAXDOUBLE,MAXDOUBLE,0.000000e+000,MAXDOUBLE,5.000000e-001*t_write,MAXDOUBLE); 
    
#line 202 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MARKERN("B20041C_2S_LT40C_CP1_V1P0.PLN",202,2,SD_OUT,(SD_OUT).GetTestPinno(),(SD_OUT).IsIOAllPins(),0*t_write,MAXDOUBLE,MAXDOUBLE,0.000000e+000,MAXDOUBLE,7.000000e-001*t_write,MAXDOUBLE);  
  
    
#line 204 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MARKERN("B20041C_2S_LT40C_CP1_V1P0.PLN",204,1,EN_SET,(EN_SET).GetTestPinno(),(EN_SET).IsIOAllPins(),0*t_write,5.000000e-001*t_write,MAXDOUBLE,0.000000e+000,MAXDOUBLE,5.000000e-001*t_write,MAXDOUBLE);
    
#line 205 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MARKERN("B20041C_2S_LT40C_CP1_V1P0.PLN",205,2,EN_SET,(EN_SET).GetTestPinno(),(EN_SET).IsIOAllPins(),0*t_write,-1,MAXDOUBLE,0.000000e+000,MAXDOUBLE,5.000000e-001*t_write,MAXDOUBLE); 

    
#line 207 "B20041C_2S_LT40C_CP1_V1P0.PLN"
PIN_MODE("B20041C_2S_LT40C_CP1_V1P0.PLN",207,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),0,0,1,0,2);
    
#line 208 "B20041C_2S_LT40C_CP1_V1P0.PLN"
PIN_MODE("B20041C_2S_LT40C_CP1_V1P0.PLN",208,SCLK_IN+EN_SET,(SCLK_IN+EN_SET).GetTestPinno(),(SCLK_IN+EN_SET).IsIOAllPins(),2,0,1,0,2);
    
#line 209 "B20041C_2S_LT40C_CP1_V1P0.PLN"
WAIT("B20041C_2S_LT40C_CP1_V1P0.PLN",209,5.000000e-003);
    
    
#line 211 "B20041C_2S_LT40C_CP1_V1P0.PLN"
if(!power_down_fail_site_same_flag)FORCE_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",211,TP_MLDPS,(TP_MLDPS).GetTestPinno(),2.000000e-009,5,0,3.000000e+000,0,1,2.000000e-003, _IFVM_);
    
#line 212 "B20041C_2S_LT40C_CP1_V1P0.PLN"
if(!power_down_fail_site_same_flag)FORCE_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",212,TP_MLDPS,(TP_MLDPS).GetTestPinno(),2.000000e-009,4,0,3.000000e+000,0,1,5.000000e-003, _IFVM_);
 
 
    
#line 215 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(1);
#line 215 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"RESET_PAT");
    {
#line 216 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_PAT("B20041C_2S_LT40C_CP1_V1P0.PLN",216,RESET_PAT,__RESET_PAT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,(__RESET_PAT).Getpinmode(),(__RESET_PAT).Getpin2x(),(__RESET_PAT).GetValidpin(),(__RESET_PAT).Gettestno(),(__RESET_PAT).Getchkmode());}
 
}

poweroff(){
    
#line 221 "B20041C_2S_LT40C_CP1_V1P0.PLN"
PIN_MODE("B20041C_2S_LT40C_CP1_V1P0.PLN",221,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),5,0,1,3,0); 
    #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"
if(enter_power_down_fail_site){          
  LUINT tmpmask = CPIN::GetMask(),tmpfailmask = 0x0;                    
  for(int _gg_=0;_gg_<DF_MAX_Site_Count;_gg_++) {                    
    if((PLAN_RESULT_MS[_gg_]==FAIL) && TrueOrFalse(tmpmask,_gg_))                    
      tmpfailmask |= (LUINT)0x1<<_gg_;                    
  }                    
  CPIN::SetMask(tmpfailmask);          
  #line 222 "B20041C_2S_LT40C_CP1_V1P0.PLN"                    
  LEVELS("B20041C_2S_LT40C_CP1_V1P0.PLN",222,rst_lvl,5.000000e-003,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),1);          
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"                    
  CPIN::SetMask(tmpmask);          
}           
  else{          
  #line 222 "B20041C_2S_LT40C_CP1_V1P0.PLN"          
  LEVELS("B20041C_2S_LT40C_CP1_V1P0.PLN",222,rst_lvl,5.000000e-003,NULL,0,0);          
  #line 1 "B20041C_2S_LT40C_CP1_V1P0_body.cpp"          
  }          
  #line 222 "B20041C_2S_LT40C_CP1_V1P0.PLN"
; 
    
#line 223 "B20041C_2S_LT40C_CP1_V1P0.PLN"
PIN_MODE("B20041C_2S_LT40C_CP1_V1P0.PLN",223,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),0,0,1,0,0); 
    
#line 224 "B20041C_2S_LT40C_CP1_V1P0.PLN"
if(!power_down_fail_site_same_flag)FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",224,MLDPS_ALLPINS,(MLDPS_ALLPINS).GetTestPinno(),0.000000e+000,0,4,1.000000e-002,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);
    
#line 225 "B20041C_2S_LT40C_CP1_V1P0.PLN"
WAIT("B20041C_2S_LT40C_CP1_V1P0.PLN",225,5.000000e-003);
    
#line 226 "B20041C_2S_LT40C_CP1_V1P0.PLN"
if(!power_down_fail_site_same_flag)FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",226,MLDPS_ALLPINS,(MLDPS_ALLPINS).GetTestPinno(),0.000000e+000,0,5,4.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);
    
#line 227 "B20041C_2S_LT40C_CP1_V1P0.PLN"
RELAY_OFF("B20041C_2S_LT40C_CP1_V1P0.PLN",227,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),127,2.000000e-003);    
}

TIMING_SET(){
  double  t_write=1.000000e-006;
  

  
#line 234 "B20041C_2S_LT40C_CP1_V1P0.PLN"
RATEN("B20041C_2S_LT40C_CP1_V1P0.PLN",234,1,t_write);
  
#line 235 "B20041C_2S_LT40C_CP1_V1P0.PLN"
RATEN("B20041C_2S_LT40C_CP1_V1P0.PLN",235,2,t_write);
  
#line 236 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MARKERN("B20041C_2S_LT40C_CP1_V1P0.PLN",236,1,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),0*t_write,MAXDOUBLE,MAXDOUBLE,0.000000e+000,MAXDOUBLE,6.000000e-001*t_write,MAXDOUBLE);
  
#line 237 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MARKERN("B20041C_2S_LT40C_CP1_V1P0.PLN",237,1,SCLKI,(SCLKI).GetTestPinno(),(SCLKI).IsIOAllPins(),3.000000e-001*t_write,8.000000e-001*t_write,MAXDOUBLE,0.000000e+000,MAXDOUBLE,5.000000e-001*t_write,MAXDOUBLE);    
  
#line 238 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MARKERN("B20041C_2S_LT40C_CP1_V1P0.PLN",238,2,SCLKI,(SCLKI).GetTestPinno(),(SCLKI).IsIOAllPins(),3.000000e-001*t_write,-1,MAXDOUBLE,0.000000e+000,MAXDOUBLE,5.000000e-001*t_write,MAXDOUBLE);  
  
#line 239 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MARKERN("B20041C_2S_LT40C_CP1_V1P0.PLN",239,2,CS,(CS).GetTestPinno(),(CS).IsIOAllPins(),4.000000e-001*t_write,MAXDOUBLE,MAXDOUBLE,0.000000e+000,MAXDOUBLE,5.000000e-001*t_write,MAXDOUBLE); 
  
#line 240 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MARKERN("B20041C_2S_LT40C_CP1_V1P0.PLN",240,2,SDO,(SDO).GetTestPinno(),(SDO).IsIOAllPins(),0*t_write,MAXDOUBLE,MAXDOUBLE,0.000000e+000,MAXDOUBLE,7.000000e-001*t_write,MAXDOUBLE);  

  
#line 242 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MARKERN("B20041C_2S_LT40C_CP1_V1P0.PLN",242,1,EN_SET,(EN_SET).GetTestPinno(),(EN_SET).IsIOAllPins(),0*t_write,5.000000e-001*t_write,MAXDOUBLE,0.000000e+000,MAXDOUBLE,5.000000e-001*t_write,MAXDOUBLE);
  
#line 243 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MARKERN("B20041C_2S_LT40C_CP1_V1P0.PLN",243,2,EN_SET,(EN_SET).GetTestPinno(),(EN_SET).IsIOAllPins(),0*t_write,-1,MAXDOUBLE,0.000000e+000,MAXDOUBLE,5.000000e-001*t_write,MAXDOUBLE); 
  
  
#line 245 "B20041C_2S_LT40C_CP1_V1P0.PLN"
PIN_MODE("B20041C_2S_LT40C_CP1_V1P0.PLN",245,IO_ALLPINS,(IO_ALLPINS).GetTestPinno(),(IO_ALLPINS).IsIOAllPins(),0,0,1,0,2);
  
#line 246 "B20041C_2S_LT40C_CP1_V1P0.PLN"
PIN_MODE("B20041C_2S_LT40C_CP1_V1P0.PLN",246,SCLKI+EN_SET,(SCLKI+EN_SET).GetTestPinno(),(SCLKI+EN_SET).IsIOAllPins(),2,0,1,0,2);
}


PGM_TRIM_SCAN(int test_no,string monitor_addr,int register_addr,int register1_bit,int register1_startaddr,int register1_endaddr,int register2_bit,int register2_startaddr,int register2_endaddr)
{
    int i,j,m;
    int addr1_bit = 0;
    int addr2_bit = 0;
    int data1 = 0;
    int data2 = 0;
    int data1_bit = 0;
    int data2_bit = 0;
    
    int turn_data = register_addr;
    char pat_start[64],pat_end[64],msg[64],pat_message[64];
    string label,pat_end_str,pat_test_message;

    memset( pat_start , 0 , sizeof(pat_start));
    memset( pat_end , 0 , sizeof(pat_end));
    memset( msg , 0 , sizeof(msg));
    memset( voltage_4bit , 0 , sizeof(voltage_4bit));

    
                                                                                           
    
{
SET_STATEMENT_INFO(_ID_SOCKET_INC,441);
LUINT tmpMask = CPIN::GetMask();
int *ate_pin,pin_num;
int tmpfreezepin[DF_MAX_Pin_Count],tmppinno=0;
int tmppinmode[DF_MAX_Pin_Count];
for(int _ii_=0; _ii_<DF_MAX_Site_Count; _ii_++){
	if(TrueOrFalse(tmpMask,_ii_)){
		if ((pin_num = GetPinSiteAllIOChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
	}
}
socket_freeze(tmpfreezepin,tmppinno,_ON_,tmppinmode);                       
for(short SOCKET = 0; SOCKET<DF_MAX_Site_Count; SOCKET++) {
	if(TrueOrFalse(tmpMask,SOCKET)){
		int curfreezepin[DF_MAX_Pin_Count],curpinno;
		CPIN::SetMask((LUINT)0x1<<SOCKET);
		curpinno=0;
		if ((pin_num = GetPinSiteAllIOChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		socket_freeze(curfreezepin,curpinno,_OFF_,tmppinmode);
#line 428 "B20041C_2S_LT40C_CP1_V1P0.PLN"

    m = 0;
    register_addr=turn_data;
        for( j=0;j<8;j++)
        {
            addr1_bit = register_addr & 0x1;
            register_addr     = (register_addr >> 1);
            if(addr1_bit == 1)
            {
                
#line 281 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",281, (SD_IN).GetSitePins(SOCKET), (SD_IN).GetMemberno(),TRIM_SCAN_C_addr1+(7)/(TRIM_SCAN_C_addr1.Getpinmode()==_IO2X_||TRIM_SCAN_C_addr1.Getpinmode()==_DBL_IO2X_?2:1)-(j)/(TRIM_SCAN_C_addr1.Getpinmode()==_IO2X_||TRIM_SCAN_C_addr1.Getpinmode()==_DBL_IO2X_?2:1),TRIM_SCAN_C_addr1.Getpinmode()==_IO2X_||TRIM_SCAN_C_addr1.Getpinmode()==_DBL_IO2X_?j%2:0,0,"1");
                
#line 282 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",282, (SD_IN).GetSitePins(SOCKET), (SD_IN).GetMemberno(),R_TRIM_SCAN_C_addr+(7)/(R_TRIM_SCAN_C_addr.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_addr.Getpinmode()==_DBL_IO2X_?2:1)-(j)/(R_TRIM_SCAN_C_addr.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_addr.Getpinmode()==_DBL_IO2X_?2:1),R_TRIM_SCAN_C_addr.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_addr.Getpinmode()==_DBL_IO2X_?j%2:0,0,"1");
                
#line 283 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",283, (SD_IN).GetSitePins(SOCKET), (SD_IN).GetMemberno(),R_TRIM_SCAN_C_addr1+(7)/(R_TRIM_SCAN_C_addr1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_addr1.Getpinmode()==_DBL_IO2X_?2:1)-(j)/(R_TRIM_SCAN_C_addr1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_addr1.Getpinmode()==_DBL_IO2X_?2:1),R_TRIM_SCAN_C_addr1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_addr1.Getpinmode()==_DBL_IO2X_?j%2:0,0,"1");
            }else
            {    
                
#line 286 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",286, (SD_IN).GetSitePins(SOCKET), (SD_IN).GetMemberno(),TRIM_SCAN_C_addr1+(7)/(TRIM_SCAN_C_addr1.Getpinmode()==_IO2X_||TRIM_SCAN_C_addr1.Getpinmode()==_DBL_IO2X_?2:1)-(j)/(TRIM_SCAN_C_addr1.Getpinmode()==_IO2X_||TRIM_SCAN_C_addr1.Getpinmode()==_DBL_IO2X_?2:1),TRIM_SCAN_C_addr1.Getpinmode()==_IO2X_||TRIM_SCAN_C_addr1.Getpinmode()==_DBL_IO2X_?j%2:0,0,"0");
                
#line 287 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",287, (SD_IN).GetSitePins(SOCKET), (SD_IN).GetMemberno(),R_TRIM_SCAN_C_addr+(7)/(R_TRIM_SCAN_C_addr.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_addr.Getpinmode()==_DBL_IO2X_?2:1)-(j)/(R_TRIM_SCAN_C_addr.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_addr.Getpinmode()==_DBL_IO2X_?2:1),R_TRIM_SCAN_C_addr.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_addr.Getpinmode()==_DBL_IO2X_?j%2:0,0,"0");
                
#line 288 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",288, (SD_IN).GetSitePins(SOCKET), (SD_IN).GetMemberno(),R_TRIM_SCAN_C_addr1+(7)/(R_TRIM_SCAN_C_addr1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_addr1.Getpinmode()==_DBL_IO2X_?2:1)-(j)/(R_TRIM_SCAN_C_addr1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_addr1.Getpinmode()==_DBL_IO2X_?2:1),R_TRIM_SCAN_C_addr1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_addr1.Getpinmode()==_DBL_IO2X_?j%2:0,0,"0");
            }
        
        } 
    register_addr=turn_data;
                                                                                                    

        for( j=register1_startaddr;j< register1_endaddr+1 ;j++)
        {
            
            for( i=register2_startaddr;i< register2_endaddr+1 ;i++)
            {
                data1 = j;
                data2 = i;
                
              if(register_addr==0x27 || register_addr==39) {  
                for (int k = 0;k < register1_bit;k++)
                {
                    data1_bit = data1 & 0x1;
                    data1  = (data1 >> 1);
                    if(data1_bit == 1)
                    {
                        
#line 310 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",310, (SD_IN).GetSitePins(SOCKET), (SD_IN).GetMemberno(),TRIM_SCAN_C_data1+(register1_bit)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(2)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"1");
                        
#line 311 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",311, (SD_OUT).GetSitePins(SOCKET), (SD_OUT).GetMemberno(),R_TRIM_SCAN_C_data1+(register1_bit)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(2)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"H");
                    }else
                    {
                        
#line 314 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",314, (SD_IN).GetSitePins(SOCKET), (SD_IN).GetMemberno(),TRIM_SCAN_C_data1+(register1_bit)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(2)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"0");
                        
#line 315 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",315, (SD_OUT).GetSitePins(SOCKET), (SD_OUT).GetMemberno(),R_TRIM_SCAN_C_data1+(register1_bit)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(2)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"L");
                    } 
                    
                }
                for (int k = 0;k < register2_bit;k++)
                {
                    data2_bit = data2 & 0x1;
                    data2  = (data2 >> 1);
                    if(data2_bit == 1)
                    {
                        
#line 325 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",325, (SD_IN).GetSitePins(SOCKET), (SD_IN).GetMemberno(),TRIM_SCAN_C_data1+(register1_bit)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)+(register2_bit)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(2)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"1");
                        
#line 326 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",326, (SD_OUT).GetSitePins(SOCKET), (SD_OUT).GetMemberno(),R_TRIM_SCAN_C_data1+(register1_bit)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)+(register2_bit)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(2)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"H");
                    }else
                    {
                        
#line 329 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",329, (SD_IN).GetSitePins(SOCKET), (SD_IN).GetMemberno(),TRIM_SCAN_C_data1+(register1_bit)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)+(register2_bit)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(2)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"0");
                        
#line 330 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",330, (SD_OUT).GetSitePins(SOCKET), (SD_OUT).GetMemberno(),R_TRIM_SCAN_C_data1+(register1_bit)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)+(register2_bit)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(2)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"L");
                    }
                    
                }
              }
                                                                                                    
              else{  
                for (int k = 0;k < register1_bit;k++)
                {
                    data1_bit = data1 & 0x1;
                    data1  = (data1 >> 1);
                    if(data1_bit == 1)
                    {
                        
#line 343 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",343, (SD_IN).GetSitePins(SOCKET), (SD_IN).GetMemberno(),TRIM_SCAN_C_data1+(register1_bit)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(1)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"1");
                        
#line 344 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",344, (SD_OUT).GetSitePins(SOCKET), (SD_OUT).GetMemberno(),R_TRIM_SCAN_C_data1+(register1_bit)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(1)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"H");
                    }else
                    {
                        
#line 347 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",347, (SD_IN).GetSitePins(SOCKET), (SD_IN).GetMemberno(),TRIM_SCAN_C_data1+(register1_bit)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(1)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"0");
                        
#line 348 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",348, (SD_OUT).GetSitePins(SOCKET), (SD_OUT).GetMemberno(),R_TRIM_SCAN_C_data1+(register1_bit)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(1)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"L");
                    } 
                    
                }
                for (int k = 0;k < register2_bit;k++)
                {
                    data2_bit = data2 & 0x1;
                    data2  = (data2 >> 1);
                    if(data2_bit == 1)
                    {
                        
#line 358 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",358, (SD_IN).GetSitePins(SOCKET), (SD_IN).GetMemberno(),TRIM_SCAN_C_data1+(register1_bit)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)+(register2_bit)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(1)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"1");
                        
#line 359 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",359, (SD_OUT).GetSitePins(SOCKET), (SD_OUT).GetMemberno(),R_TRIM_SCAN_C_data1+(register1_bit)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)+(register2_bit)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(1)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"H");
                    }else
                    {
                        
#line 362 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",362, (SD_IN).GetSitePins(SOCKET), (SD_IN).GetMemberno(),TRIM_SCAN_C_data1+(register1_bit)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)+(register2_bit)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(1)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"0");
                        
#line 363 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",363, (SD_OUT).GetSitePins(SOCKET), (SD_OUT).GetMemberno(),R_TRIM_SCAN_C_data1+(register1_bit)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)+(register2_bit)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(1)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)-(k)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"L");
                    }
                    
                }
              }
                if(debug_mode){printf("register_addr=%d,j=%d ,i = %d\n",register_addr,j,i) ;  fflush(stdout);}
                
#line 369 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);
                test_no++;
                
#line 371 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"TRIM_SCAN");
                {
#line 372 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_PAT("B20041C_2S_LT40C_CP1_V1P0.PLN",372,TRIM_SCAN,__TRIM_SCAN,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,(__TRIM_SCAN).Getpinmode(),(__TRIM_SCAN).Getpin2x(),(__TRIM_SCAN).GetValidpin(),(__TRIM_SCAN).Gettestno(),(__TRIM_SCAN).Getchkmode());}
                
                
#line 374 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);
                test_no++;
                
#line 376 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"R_TRIM_SCAN");
                {
#line 377 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_PAT("B20041C_2S_LT40C_CP1_V1P0.PLN",377,R_TRIM_SCAN,__R_TRIM_SCAN,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,(__R_TRIM_SCAN).Getpinmode(),(__R_TRIM_SCAN).Getpin2x(),(__R_TRIM_SCAN).GetValidpin(),(__R_TRIM_SCAN).Gettestno(),(__R_TRIM_SCAN).Getchkmode());}
                
                strcpy(pat_start,monitor_addr.c_str());
                pat_end_str="__";
                pat_end_str.append(monitor_addr);       
                strcpy(pat_end,pat_end_str.c_str());
                
                pat_test_message= monitor_addr;
    









                pat_test_message.append("_Pattern");
                strcpy(pat_message,pat_test_message.c_str());
                
#line 397 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);
                test_no++;
                
#line 399 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,pat_message);
   
                {
#line 401 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_PAT("B20041C_2S_LT40C_CP1_V1P0.PLN",401,GetAddr(pat_start),GetAddr(pat_end),MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,GetPinMode(pat_end),GetPin2x(pat_end),GetValidPin(pat_end),GetLabelTestNo(pat_end),GetLabelChkMode(pat_end));}




















                
                
#line 423 "B20041C_2S_LT40C_CP1_V1P0.PLN"
WAIT("B20041C_2S_LT40C_CP1_V1P0.PLN",423,3.000000e-003);
                test_no++; 
                
#line 425 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);  
                
#line 426 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"TRIM_0-15");            
                
#line 427 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MEAS_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",427,TP_MLDPS,(TP_MLDPS).GetTestPinno(),1.000000e-003,16,_3500_AVE_MODE,1.000000e-005);
                {
SET_STATEMENT_INFO(_ID_SOCKET_INC,431);
LUINT tmpMask = CPIN::GetMask();
int *ate_pin,pin_num;
int tmpfreezepin[DF_MAX_Pin_Count],tmppinno=0;
int tmppinmode[DF_MAX_Pin_Count];
for(int _ii_=0; _ii_<DF_MAX_Site_Count; _ii_++){
	if(TrueOrFalse(tmpMask,_ii_)){
		if ((pin_num = GetPinSiteAllIOChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
	}
}
socket_freeze(tmpfreezepin,tmppinno,_ON_,tmppinmode);                       
for(short SOCKET = 0; SOCKET<DF_MAX_Site_Count; SOCKET++) {
	if(TrueOrFalse(tmpMask,SOCKET)){
		int curfreezepin[DF_MAX_Pin_Count],curpinno;
		CPIN::SetMask((LUINT)0x1<<SOCKET);
		curpinno=0;
		if ((pin_num = GetPinSiteAllIOChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		socket_freeze(curfreezepin,curpinno,_OFF_,tmppinmode);
#line 428 "B20041C_2S_LT40C_CP1_V1P0.PLN"

                  voltage_4bit[SOCKET][m]=RESULT_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",429,((LUINT)1<<SOCKET),TP_MLDPS,(TP_MLDPS).GetTestPinno(),1);
                  if(debug_mode){printf("SOCKET=%d,TP_MLDPS voltage:=%f\n",SOCKET,voltage_4bit[SOCKET][m]) ;  fflush(stdout);} 
                		socket_freeze(curfreezepin,curpinno,_ON_,NULL);
	}
}
socket_freeze(tmpfreezepin,tmppinno,_OFF_,tmppinmode);
CPIN::SetMask(tmpMask);
}
#line 431 "B20041C_2S_LT40C_CP1_V1P0.PLN"
 
          
                m++;
            }
        }
        for (int k = 0;k < 16;k++)
        {
            
#line 438 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",438, (SD_IN).GetSitePins(SOCKET), (SD_IN).GetMemberno(),TRIM_SCAN_C_data1-(6)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)+(k)/(TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"0");
            
#line 439 "B20041C_2S_LT40C_CP1_V1P0.PLN"
zz_20150729_WRITE_PAT_MEM("B20041C_2S_LT40C_CP1_V1P0.PLN",439, (SD_OUT).GetSitePins(SOCKET), (SD_OUT).GetMemberno(),R_TRIM_SCAN_C_data1-(6)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1)+(k)/(R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?2:1),R_TRIM_SCAN_C_data1.Getpinmode()==_IO2X_||R_TRIM_SCAN_C_data1.Getpinmode()==_DBL_IO2X_?k%2:0,0,"L");
        }   
    		socket_freeze(curfreezepin,curpinno,_ON_,NULL);
	}
}
socket_freeze(tmpfreezepin,tmppinno,_OFF_,tmppinmode);
CPIN::SetMask(tmpMask);
}
#line 441 "B20041C_2S_LT40C_CP1_V1P0.PLN"

#line 441 "B20041C_2S_LT40C_CP1_V1P0.PLN"

}              





__declspec(dllexport) int OS_TEST() 
{


#line 448 "B20041C_2S_LT40C_CP1_V1P0.PLN"

  
#line 449 "B20041C_2S_LT40C_CP1_V1P0.PLN"
RELAY_ON("B20041C_2S_LT40C_CP1_V1P0.PLN",449,os_pin,(os_pin).GetTestPinno(),128,2.000000e-003);
  
#line 450 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",450,MLDPS_ALLPINS-TP_MLDPS-VFS_MLDPS,(MLDPS_ALLPINS-TP_MLDPS-VFS_MLDPS).GetTestPinno(),0.000000e+000,0,5,1.000000e-001,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);    
  
#line 451 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",451,MLDPS_ALLPINS-TP_MLDPS-VFS_MLDPS,(MLDPS_ALLPINS-TP_MLDPS-VFS_MLDPS).GetTestPinno(),0.000000e+000,0,4,2.500000e-002,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);
  
#line 452 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_I_PPMU("B20041C_2S_LT40C_CP1_V1P0.PLN",452,os_pin,(os_pin).GetTestPinno(),-1.000000e-004,6,2147483647,2.000000e+000,-2.000000e+000,-1,5.000000e-003);
  
#line 453 "B20041C_2S_LT40C_CP1_V1P0.PLN"
WAIT("B20041C_2S_LT40C_CP1_V1P0.PLN",453,5.000000e-003);
  
  test_no=1;    
#line 455 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);    
#line 455 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"TP+SCLKO_negative");
  {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 456 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_V_PPMU("B20041C_2S_LT40C_CP1_V1P0.PLN",456,TP+SCLKO,(TP+SCLKO).GetTestPinno(),limit_spec_min[1]*1.000000e+000,limit_spec_max[1]*1.000000e+000,2.000000e-003,16,_3500_AVE_MODE,2.000000e-005,_KEEP_CURRENT_F,_KEEP_CURRENT_F,NULL);}  
  test_no++;    
#line 457 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);    
#line 457 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"EN_SET_negative");
  {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 458 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_V_PPMU("B20041C_2S_LT40C_CP1_V1P0.PLN",458,EN_SET,(EN_SET).GetTestPinno(),limit_spec_min[2]*1.000000e+000,limit_spec_max[2]*1.000000e+000,2.000000e-003,16,_3500_AVE_MODE,2.000000e-005,_KEEP_CURRENT_F,_KEEP_CURRENT_F,NULL);}  
  test_no++;    
#line 459 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);    
#line 459 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"RST+CS+SDI+SCLKI+LD+TRT+TRR_negative");
  {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 460 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_V_PPMU("B20041C_2S_LT40C_CP1_V1P0.PLN",460,RST+CS+SDI+SCLKI+LD+TRT+TRR,(RST+CS+SDI+SCLKI+LD+TRT+TRR).GetTestPinno(),limit_spec_min[3]*1.000000e+000,limit_spec_max[3]*1.000000e+000,2.000000e-003,16,_3500_AVE_MODE,2.000000e-005,_KEEP_CURRENT_F,_KEEP_CURRENT_F,NULL);} 
  test_no++;    
#line 461 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);    
#line 461 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"VFS_negative");
  {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 462 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_V_PPMU("B20041C_2S_LT40C_CP1_V1P0.PLN",462,VFS,(VFS).GetTestPinno(),limit_spec_min[4]*1.000000e+000,limit_spec_max[4]*1.000000e+000,2.000000e-003,16,_3500_AVE_MODE,2.000000e-005,_KEEP_CURRENT_F,_KEEP_CURRENT_F,NULL);} 
  test_no++;    
#line 463 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);    
#line 463 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"SDO_negative");
  {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 464 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_V_PPMU("B20041C_2S_LT40C_CP1_V1P0.PLN",464,SDO,(SDO).GetTestPinno(),limit_spec_min[5]*1.000000e+000,limit_spec_max[5]*1.000000e+000,2.000000e-003,16,_3500_AVE_MODE,2.000000e-005,_KEEP_CURRENT_F,_KEEP_CURRENT_F,NULL);} 
  
  
  
#line 467 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_I_PPMU("B20041C_2S_LT40C_CP1_V1P0.PLN",467,os_pin-VFS,(os_pin-VFS).GetTestPinno(),1.000000e-004,6,2147483647,2.000000e+000,-2.000000e+000,-1,5.000000e-003);
  
#line 468 "B20041C_2S_LT40C_CP1_V1P0.PLN"
WAIT("B20041C_2S_LT40C_CP1_V1P0.PLN",468,5.000000e-003);
  test_no++;    
#line 469 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);    
#line 469 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"TP+SCLKO_postive");
  {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 470 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_V_PPMU("B20041C_2S_LT40C_CP1_V1P0.PLN",470,TP+SCLKO,(TP+SCLKO).GetTestPinno(),limit_spec_min[6]*1.000000e+000,limit_spec_max[6]*1.000000e+000,2.000000e-003,16,_3500_AVE_MODE,2.000000e-005,_KEEP_CURRENT_F,_KEEP_CURRENT_F,NULL);} 
  test_no++;    
#line 471 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);    
#line 471 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"EN_SET+RST_postive");
  {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 472 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_V_PPMU("B20041C_2S_LT40C_CP1_V1P0.PLN",472,EN_SET+RST,(EN_SET+RST).GetTestPinno(),limit_spec_min[7]*1.000000e+000,limit_spec_max[7]*1.000000e+000,2.000000e-003,16,_3500_AVE_MODE,2.000000e-005,_KEEP_CURRENT_F,_KEEP_CURRENT_F,NULL);} 
  test_no++;    
#line 473 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);    
#line 473 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"CS+SDI+SCLKI+LD+TRT+TRR_postive");
  {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 474 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_V_PPMU("B20041C_2S_LT40C_CP1_V1P0.PLN",474,CS+SDI+SCLKI+LD+TRT+TRR,(CS+SDI+SCLKI+LD+TRT+TRR).GetTestPinno(),limit_spec_min[8]*1.000000e+000,limit_spec_max[8]*1.000000e+000,2.000000e-003,16,_3500_AVE_MODE,2.000000e-005,_KEEP_CURRENT_F,_KEEP_CURRENT_F,NULL);} 
  test_no++;    
#line 475 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);    
#line 475 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"SDO_postive");
  {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 476 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_V_PPMU("B20041C_2S_LT40C_CP1_V1P0.PLN",476,SDO,(SDO).GetTestPinno(),limit_spec_min[9]*1.000000e+000,limit_spec_max[9]*1.000000e+000,2.000000e-003,16,_3500_AVE_MODE,2.000000e-005,_KEEP_CURRENT_F,_KEEP_CURRENT_F,NULL);} 
  
  
#line 478 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_I_PPMU("B20041C_2S_LT40C_CP1_V1P0.PLN",478,os_pin,(os_pin).GetTestPinno(),0.000000e+000,6,2147483647,2.000000e+000,-2.000000e+000,-1,2.000000e-003); 
  
#line 479 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_PPMU("B20041C_2S_LT40C_CP1_V1P0.PLN",479,os_pin,(os_pin).GetTestPinno(),0.000000e+000,2147483647,6,MAXDOUBLE,-1,2.000000e-003);         
  
#line 480 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",480,MLDPS_ALLPINS-TP_MLDPS-VFS_MLDPS,(MLDPS_ALLPINS-TP_MLDPS-VFS_MLDPS).GetTestPinno(),0.000000e+000,0,5,1.000000e-001,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);    
  
#line 481 "B20041C_2S_LT40C_CP1_V1P0.PLN"
RELAY_OFF("B20041C_2S_LT40C_CP1_V1P0.PLN",481,os_pin,(os_pin).GetTestPinno(),(os_pin).IsIOAllPins(),128,2.000000e-003); 
  
#line 482 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",482,MLDPS_ALLPINS-TP_MLDPS-VFS_MLDPS,(MLDPS_ALLPINS-TP_MLDPS-VFS_MLDPS).GetTestPinno(),0.000000e+000,0,5,1.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);    
}

__declspec(dllexport) int V33_0p5V_Leakage() 
{


#line 485 "B20041C_2S_LT40C_CP1_V1P0.PLN"


  test_no=20;    
#line 487 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);    
#line 487 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"V33_0p5V_Leakage");
  
#line 488 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",488,V33_dig,(V33_dig).GetTestPinno(),0.000000e+000,0,5,1.000000e-001,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
  
#line 490 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",490,VDD_CH1,(VDD_CH1).GetTestPinno(),5.000000e-001,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 491 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MEAS_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",491,VDD_CH1,(VDD_CH1).GetTestPinno(),1.000000e-003,8,_3500_AVE_MODE,1.000000e-005);  
  RESULT_MLDPS_MS("B20041C_2S_LT40C_CP1_V1P0.PLN",492,VDD_CH1,(VDD_CH1).GetTestPinno(),1,current_VDD_CH1,sizeof(current_VDD_CH1)/sizeof(double));
  
#line 493 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",493,VDD_CH1,(VDD_CH1).GetTestPinno(),0.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 494 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",494,VDD_CH1,(VDD_CH1).GetTestPinno(),0.000000e+000,0,5,2.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        

  
#line 496 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",496,VDD_CH2,(VDD_CH2).GetTestPinno(),5.000000e-001,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 497 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MEAS_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",497,VDD_CH2,(VDD_CH2).GetTestPinno(),1.000000e-003,8,_3500_AVE_MODE,1.000000e-005);  
  RESULT_MLDPS_MS("B20041C_2S_LT40C_CP1_V1P0.PLN",498,VDD_CH2,(VDD_CH2).GetTestPinno(),1,current_VDD_CH2,sizeof(current_VDD_CH2)/sizeof(double));
  
#line 499 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",499,VDD_CH2,(VDD_CH2).GetTestPinno(),0.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 500 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",500,VDD_CH2,(VDD_CH2).GetTestPinno(),0.000000e+000,0,5,2.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);  

  
#line 502 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",502,VDD_CH3,(VDD_CH3).GetTestPinno(),5.000000e-001,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 503 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MEAS_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",503,VDD_CH3,(VDD_CH3).GetTestPinno(),1.000000e-003,8,_3500_AVE_MODE,1.000000e-005);  
  RESULT_MLDPS_MS("B20041C_2S_LT40C_CP1_V1P0.PLN",504,VDD_CH3,(VDD_CH3).GetTestPinno(),1,current_VDD_CH3,sizeof(current_VDD_CH3)/sizeof(double));
  
#line 505 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",505,VDD_CH3,(VDD_CH3).GetTestPinno(),0.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 506 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",506,VDD_CH3,(VDD_CH3).GetTestPinno(),0.000000e+000,0,5,2.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);  
  
  
#line 508 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",508,VDD_CH4,(VDD_CH4).GetTestPinno(),5.000000e-001,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 509 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MEAS_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",509,VDD_CH4,(VDD_CH4).GetTestPinno(),1.000000e-003,8,_3500_AVE_MODE,1.000000e-005);  
  RESULT_MLDPS_MS("B20041C_2S_LT40C_CP1_V1P0.PLN",510,VDD_CH4,(VDD_CH4).GetTestPinno(),1,current_VDD_CH4,sizeof(current_VDD_CH4)/sizeof(double));
  
#line 511 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",511,VDD_CH4,(VDD_CH4).GetTestPinno(),0.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 512 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",512,VDD_CH4,(VDD_CH4).GetTestPinno(),0.000000e+000,0,5,2.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);  
  
  
#line 514 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",514,V33_1_4,(V33_1_4).GetTestPinno(),5.000000e-001,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 515 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MEAS_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",515,V33_1_4,(V33_1_4).GetTestPinno(),1.000000e-003,8,_3500_AVE_MODE,1.000000e-005);  
  RESULT_MLDPS_MS("B20041C_2S_LT40C_CP1_V1P0.PLN",516,V33_1_4,(V33_1_4).GetTestPinno(),1,current_V33_1_4,sizeof(current_V33_1_4)/sizeof(double));
  
#line 517 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",517,V33_1_4,(V33_1_4).GetTestPinno(),0.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 518 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",518,V33_1_4,(V33_1_4).GetTestPinno(),0.000000e+000,0,5,2.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);  
  
  
#line 520 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",520,V33_2,(V33_2).GetTestPinno(),5.000000e-001,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 521 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MEAS_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",521,V33_2,(V33_2).GetTestPinno(),1.000000e-003,8,_3500_AVE_MODE,1.000000e-005);  
  RESULT_MLDPS_MS("B20041C_2S_LT40C_CP1_V1P0.PLN",522,V33_2,(V33_2).GetTestPinno(),1,current_V33_2,sizeof(current_V33_2)/sizeof(double));
  
#line 523 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",523,V33_2,(V33_2).GetTestPinno(),0.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 524 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",524,V33_2,(V33_2).GetTestPinno(),0.000000e+000,0,5,2.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);  
  
  
#line 526 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",526,V33_3,(V33_3).GetTestPinno(),5.000000e-001,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 527 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MEAS_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",527,V33_3,(V33_3).GetTestPinno(),1.000000e-003,8,_3500_AVE_MODE,1.000000e-005);  
  RESULT_MLDPS_MS("B20041C_2S_LT40C_CP1_V1P0.PLN",528,V33_3,(V33_3).GetTestPinno(),1,current_V33_3,sizeof(current_V33_3)/sizeof(double));
  
#line 529 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",529,V33_3,(V33_3).GetTestPinno(),0.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 530 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",530,V33_3,(V33_3).GetTestPinno(),0.000000e+000,0,5,2.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);  
  
  {
SET_STATEMENT_INFO(_ID_SOCKET_INC,554);
LUINT tmpMask = CPIN::GetMask();
for(short SOCKET = 0; SOCKET<DF_MAX_Site_Count; SOCKET++) {
	if(TrueOrFalse(tmpMask,SOCKET)){
		CPIN::SetMask((LUINT)0x1<<SOCKET);
#line 532 "B20041C_2S_LT40C_CP1_V1P0.PLN"

    current_MAX[SOCKET] = current_VDD_CH1[SOCKET];
      if(current_MAX[SOCKET] < current_VDD_CH2[SOCKET])  current_MAX[SOCKET] = current_VDD_CH2[SOCKET];
      if(current_MAX[SOCKET] < current_VDD_CH3[SOCKET])  current_MAX[SOCKET] = current_VDD_CH3[SOCKET];
      if(current_MAX[SOCKET] < current_VDD_CH4[SOCKET])  current_MAX[SOCKET] = current_VDD_CH4[SOCKET];
      if(current_MAX[SOCKET] < current_V33_1_4[SOCKET])  current_MAX[SOCKET] = current_V33_1_4[SOCKET];
      if(current_MAX[SOCKET] < current_V33_2[SOCKET])    current_MAX[SOCKET] = current_V33_2[SOCKET];
      if(current_MAX[SOCKET] < current_V33_3[SOCKET])    current_MAX[SOCKET] = current_V33_3[SOCKET];
    current_MIN[SOCKET] = current_VDD_CH1[SOCKET];
      if(current_MIN[SOCKET] > current_VDD_CH2[SOCKET])  current_MIN[SOCKET] = current_VDD_CH2[SOCKET];
      if(current_MIN[SOCKET] > current_VDD_CH3[SOCKET])  current_MIN[SOCKET] = current_VDD_CH3[SOCKET];
      if(current_MIN[SOCKET] > current_VDD_CH4[SOCKET])  current_MIN[SOCKET] = current_VDD_CH4[SOCKET];
      if(current_MIN[SOCKET] > current_V33_1_4[SOCKET])  current_MIN[SOCKET] = current_V33_1_4[SOCKET];
      if(current_MIN[SOCKET] > current_V33_2[SOCKET])    current_MIN[SOCKET] = current_V33_2[SOCKET];
      if(current_MIN[SOCKET] > current_V33_3[SOCKET])    current_MIN[SOCKET] = current_V33_3[SOCKET];
      
    current_Delta[SOCKET]=current_MAX[SOCKET]-current_MIN[SOCKET];
    current_AVE[SOCKET]=(current_VDD_CH1[SOCKET]+current_VDD_CH2[SOCKET]+current_VDD_CH3[SOCKET]+current_VDD_CH4[SOCKET]+current_V33_1_4[SOCKET]+current_V33_2[SOCKET]+current_V33_3[SOCKET])/7;
  test_no=200;  
#line 550 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);  
#line 550 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"current_Delta_0p5V");
  {strcpy(USE_TYPE ,"A")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"A")  ;
USE_UNIT = 0  ;

#line 551 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_VARIABLE("B20041C_2S_LT40C_CP1_V1P0.PLN",551,((LUINT)1<<SOCKET),current_Delta[SOCKET],limit_spec_min[10]*1.000000e+000,limit_spec_max[10]*1.000000e+000,"current_Delta_0p5V");} 
  test_no=201;  
#line 552 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);  
#line 552 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"current_AVE_0p5V");
  {strcpy(USE_TYPE ,"A")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"A")  ;
USE_UNIT = 0  ;

#line 553 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_VARIABLE("B20041C_2S_LT40C_CP1_V1P0.PLN",553,((LUINT)1<<SOCKET),current_AVE[SOCKET],limit_spec_min[10]*1.000000e+000,limit_spec_max[10]*1.000000e+000,"current_AVE_0p5V");} 
  	}
	}
CPIN::SetMask(tmpMask);
}
#line 554 "B20041C_2S_LT40C_CP1_V1P0.PLN"

#line 554 "B20041C_2S_LT40C_CP1_V1P0.PLN"

  
#line 555 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",555,MLDPS_ALLPINS,(MLDPS_ALLPINS).GetTestPinno(),0.000000e+000,0,5,1.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);    
}

__declspec(dllexport) int V33_1V_Leakage() 
{


#line 558 "B20041C_2S_LT40C_CP1_V1P0.PLN"


  test_no=20;    
#line 560 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);    
#line 560 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"V33_0p5V_Leakage");
  
#line 561 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",561,V33_dig,(V33_dig).GetTestPinno(),0.000000e+000,0,5,1.000000e-001,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
  
#line 563 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",563,VDD_CH1,(VDD_CH1).GetTestPinno(),1.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 564 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MEAS_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",564,VDD_CH1,(VDD_CH1).GetTestPinno(),1.000000e-003,8,_3500_AVE_MODE,1.000000e-005);  
  RESULT_MLDPS_MS("B20041C_2S_LT40C_CP1_V1P0.PLN",565,VDD_CH1,(VDD_CH1).GetTestPinno(),1,current_VDD_CH1,sizeof(current_VDD_CH1)/sizeof(double));
  
#line 566 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",566,VDD_CH1,(VDD_CH1).GetTestPinno(),0.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 567 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",567,VDD_CH1,(VDD_CH1).GetTestPinno(),0.000000e+000,0,5,2.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        

  
#line 569 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",569,VDD_CH2,(VDD_CH2).GetTestPinno(),1.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 570 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MEAS_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",570,VDD_CH2,(VDD_CH2).GetTestPinno(),1.000000e-003,8,_3500_AVE_MODE,1.000000e-005);  
  RESULT_MLDPS_MS("B20041C_2S_LT40C_CP1_V1P0.PLN",571,VDD_CH2,(VDD_CH2).GetTestPinno(),1,current_VDD_CH2,sizeof(current_VDD_CH2)/sizeof(double));
  
#line 572 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",572,VDD_CH2,(VDD_CH2).GetTestPinno(),0.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 573 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",573,VDD_CH2,(VDD_CH2).GetTestPinno(),0.000000e+000,0,5,2.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);  

  
#line 575 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",575,VDD_CH3,(VDD_CH3).GetTestPinno(),1.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 576 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MEAS_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",576,VDD_CH3,(VDD_CH3).GetTestPinno(),1.000000e-003,8,_3500_AVE_MODE,1.000000e-005);  
  RESULT_MLDPS_MS("B20041C_2S_LT40C_CP1_V1P0.PLN",577,VDD_CH3,(VDD_CH3).GetTestPinno(),1,current_VDD_CH3,sizeof(current_VDD_CH3)/sizeof(double));
  
#line 578 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",578,VDD_CH3,(VDD_CH3).GetTestPinno(),0.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 579 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",579,VDD_CH3,(VDD_CH3).GetTestPinno(),0.000000e+000,0,5,2.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);  
  
  
#line 581 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",581,VDD_CH4,(VDD_CH4).GetTestPinno(),1.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 582 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MEAS_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",582,VDD_CH4,(VDD_CH4).GetTestPinno(),1.000000e-003,8,_3500_AVE_MODE,1.000000e-005);  
  RESULT_MLDPS_MS("B20041C_2S_LT40C_CP1_V1P0.PLN",583,VDD_CH4,(VDD_CH4).GetTestPinno(),1,current_VDD_CH4,sizeof(current_VDD_CH4)/sizeof(double));
  
#line 584 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",584,VDD_CH4,(VDD_CH4).GetTestPinno(),0.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 585 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",585,VDD_CH4,(VDD_CH4).GetTestPinno(),0.000000e+000,0,5,2.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);  
  
  
#line 587 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",587,V33_1_4,(V33_1_4).GetTestPinno(),1.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 588 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MEAS_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",588,V33_1_4,(V33_1_4).GetTestPinno(),1.000000e-003,8,_3500_AVE_MODE,1.000000e-005);  
  RESULT_MLDPS_MS("B20041C_2S_LT40C_CP1_V1P0.PLN",589,V33_1_4,(V33_1_4).GetTestPinno(),1,current_V33_1_4,sizeof(current_V33_1_4)/sizeof(double));
  
#line 590 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",590,V33_1_4,(V33_1_4).GetTestPinno(),0.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 591 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",591,V33_1_4,(V33_1_4).GetTestPinno(),0.000000e+000,0,5,2.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);  
  
  
#line 593 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",593,V33_2,(V33_2).GetTestPinno(),1.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 594 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MEAS_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",594,V33_2,(V33_2).GetTestPinno(),1.000000e-003,8,_3500_AVE_MODE,1.000000e-005);  
  RESULT_MLDPS_MS("B20041C_2S_LT40C_CP1_V1P0.PLN",595,V33_2,(V33_2).GetTestPinno(),1,current_V33_2,sizeof(current_V33_2)/sizeof(double));
  
#line 596 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",596,V33_2,(V33_2).GetTestPinno(),0.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 597 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",597,V33_2,(V33_2).GetTestPinno(),0.000000e+000,0,5,2.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);  
  
  
#line 599 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",599,V33_3,(V33_3).GetTestPinno(),1.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 600 "B20041C_2S_LT40C_CP1_V1P0.PLN"
MEAS_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",600,V33_3,(V33_3).GetTestPinno(),1.000000e-003,8,_3500_AVE_MODE,1.000000e-005);  
  RESULT_MLDPS_MS("B20041C_2S_LT40C_CP1_V1P0.PLN",601,V33_3,(V33_3).GetTestPinno(),1,current_V33_3,sizeof(current_V33_3)/sizeof(double));
  
#line 602 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",602,V33_3,(V33_3).GetTestPinno(),0.000000e+000,0,3,2.000000e-003,0,1,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);        
  
#line 603 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",603,V33_3,(V33_3).GetTestPinno(),0.000000e+000,0,5,2.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);  
  
  {
SET_STATEMENT_INFO(_ID_SOCKET_INC,628);
LUINT tmpMask = CPIN::GetMask();
for(short SOCKET = 0; SOCKET<DF_MAX_Site_Count; SOCKET++) {
	if(TrueOrFalse(tmpMask,SOCKET)){
		CPIN::SetMask((LUINT)0x1<<SOCKET);
#line 605 "B20041C_2S_LT40C_CP1_V1P0.PLN"

    current_MAX[SOCKET] = current_VDD_CH1[SOCKET];
      if(current_MAX[SOCKET] < current_VDD_CH2[SOCKET])  current_MAX[SOCKET] = current_VDD_CH2[SOCKET];
      if(current_MAX[SOCKET] < current_VDD_CH3[SOCKET])  current_MAX[SOCKET] = current_VDD_CH3[SOCKET];
      if(current_MAX[SOCKET] < current_VDD_CH4[SOCKET])  current_MAX[SOCKET] = current_VDD_CH4[SOCKET];
      if(current_MAX[SOCKET] < current_V33_1_4[SOCKET])  current_MAX[SOCKET] = current_V33_1_4[SOCKET];
      if(current_MAX[SOCKET] < current_V33_2[SOCKET])    current_MAX[SOCKET] = current_V33_2[SOCKET];
      if(current_MAX[SOCKET] < current_V33_3[SOCKET])    current_MAX[SOCKET] = current_V33_3[SOCKET];
    current_MIN[SOCKET] = current_VDD_CH1[SOCKET];
      if(current_MIN[SOCKET] > current_VDD_CH2[SOCKET])  current_MIN[SOCKET] = current_VDD_CH2[SOCKET];
      if(current_MIN[SOCKET] > current_VDD_CH3[SOCKET])  current_MIN[SOCKET] = current_VDD_CH3[SOCKET];
      if(current_MIN[SOCKET] > current_VDD_CH4[SOCKET])  current_MIN[SOCKET] = current_VDD_CH4[SOCKET];
      if(current_MIN[SOCKET] > current_V33_1_4[SOCKET])  current_MIN[SOCKET] = current_V33_1_4[SOCKET];
      if(current_MIN[SOCKET] > current_V33_2[SOCKET])    current_MIN[SOCKET] = current_V33_2[SOCKET];
      if(current_MIN[SOCKET] > current_V33_3[SOCKET])    current_MIN[SOCKET] = current_V33_3[SOCKET];
      
    current_Delta[SOCKET]=current_MAX[SOCKET]-current_MIN[SOCKET];
    current_AVE[SOCKET]=(current_VDD_CH1[SOCKET]+current_VDD_CH2[SOCKET]+current_VDD_CH3[SOCKET]+current_VDD_CH4[SOCKET]+current_V33_1_4[SOCKET]+current_V33_2[SOCKET]+current_V33_3[SOCKET])/7;

  test_no=202;  
#line 624 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);  
#line 624 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"current_Delta_1V");
  {strcpy(USE_TYPE ,"A")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"A")  ;
USE_UNIT = 0  ;

#line 625 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_VARIABLE("B20041C_2S_LT40C_CP1_V1P0.PLN",625,((LUINT)1<<SOCKET),current_Delta[SOCKET],limit_spec_min[10]*1.000000e+000,limit_spec_max[10]*1.000000e+000,"current_Delta_1V");} 
  test_no=203;  
#line 626 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);  
#line 626 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"current_AVE_1V");
  {strcpy(USE_TYPE ,"A")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"A")  ;
USE_UNIT = 0  ;

#line 627 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_VARIABLE("B20041C_2S_LT40C_CP1_V1P0.PLN",627,((LUINT)1<<SOCKET),current_AVE[SOCKET],limit_spec_min[10]*1.000000e+000,limit_spec_max[10]*1.000000e+000,"current_AVE_1V");} 
  	}
	}
CPIN::SetMask(tmpMask);
}
#line 628 "B20041C_2S_LT40C_CP1_V1P0.PLN"

#line 628 "B20041C_2S_LT40C_CP1_V1P0.PLN"

  
#line 629 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",629,MLDPS_ALLPINS,(MLDPS_ALLPINS).GetTestPinno(),0.000000e+000,0,5,1.000000e-001,0,0,2.000000e-003, MAXINT, MAXINT, MAXINT, MAXINT);    
}


__declspec(dllexport) int VBG_TRIM() 
{


#line 633 "B20041C_2S_LT40C_CP1_V1P0.PLN"

  poweron();
  
#line 635 "B20041C_2S_LT40C_CP1_V1P0.PLN"
WAIT("B20041C_2S_LT40C_CP1_V1P0.PLN",635,1.000000e-002);
  
  int read_temp_data[site_count][8]={0};
  int read_temp_check[site_count]={0};
  test_no++;  
#line 639 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);  
#line 639 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"read_temp_check");
  
#line 640 "B20041C_2S_LT40C_CP1_V1P0.PLN"
SET_CLOG_MODE("B20041C_2S_LT40C_CP1_V1P0.PLN",640,SD_OUT,(SD_OUT).GetTestPinno(),3,1,0,2147483647,2147483647,2147483647,2147483647);     
  {
#line 641 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_PAT("B20041C_2S_LT40C_CP1_V1P0.PLN",641,R_0_a0x002,__R_0_a0x002,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,(__R_0_a0x002).Getpinmode(),(__R_0_a0x002).Getpin2x(),(__R_0_a0x002).GetValidpin(),(__R_0_a0x002).Gettestno(),(__R_0_a0x002).Getchkmode());}  
  {
SET_STATEMENT_INFO(_ID_SOCKET_INC,649);
LUINT tmpMask = CPIN::GetMask();
for(short SOCKET = 0; SOCKET<DF_MAX_Site_Count; SOCKET++) {
	if(TrueOrFalse(tmpMask,SOCKET)){
		CPIN::SetMask((LUINT)0x1<<SOCKET);
#line 642 "B20041C_2S_LT40C_CP1_V1P0.PLN"

    
#line 643 "B20041C_2S_LT40C_CP1_V1P0.PLN"
READ_CAPTURE_MEM_BLOCK("B20041C_2S_LT40C_CP1_V1P0.PLN",643,(SD_OUT).GetSitePins(SOCKET),(SD_OUT).GetMemberno(),0,7,read_temp_data[SOCKET]);
    for(int k=0;k<8;k++){
      read_temp_check[SOCKET]+=read_temp_data[SOCKET][k]*pow(2,7-k);
      if(debug_mode){printf("read_temp_data[%d][%d]=%d\n",SOCKET, k,read_temp_data[SOCKET][k]) ;  fflush(stdout);}
    }
    {strcpy(USE_TYPE ,"")  ;
USE_UNIT = 3  ;
strcpy(USE_TYPE ,"")  ;
USE_UNIT = 0  ;
TEST_NO(33000001);
#line 648 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_VARIABLE("B20041C_2S_LT40C_CP1_V1P0.PLN",648,((LUINT)1<<SOCKET),read_temp_check[SOCKET],0,256,"read_temp_check");}        
  	}
	}
CPIN::SetMask(tmpMask);
}
#line 649 "B20041C_2S_LT40C_CP1_V1P0.PLN"

#line 649 "B20041C_2S_LT40C_CP1_V1P0.PLN"
    
  
#line 650 "B20041C_2S_LT40C_CP1_V1P0.PLN"
SET_CLOG_MODE("B20041C_2S_LT40C_CP1_V1P0.PLN",650,SD_OUT,(SD_OUT).GetTestPinno(),3,0,0,2147483647,2147483647,2147483647,2147483647);  
  
  
  
#line 653 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",653,TP_MLDPS,(TP_MLDPS).GetTestPinno(),0.000000e+000,5,0,3.000000e+000,0,1,2.000000e-003, _IFVM_);  
  test_no=50,  
#line 654 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);    
#line 654 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"H087_pattern");
  {
#line 655 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_PAT("B20041C_2S_LT40C_CP1_V1P0.PLN",655,H087,__H087,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,(__H087).Getpinmode(),(__H087).Getpin2x(),(__H087).GetValidpin(),(__H087).Gettestno(),(__H087).Getchkmode());}
  
#line 656 "B20041C_2S_LT40C_CP1_V1P0.PLN"
WAIT("B20041C_2S_LT40C_CP1_V1P0.PLN",656,5.000000e-003);  
  
#line 657 "B20041C_2S_LT40C_CP1_V1P0.PLN"
FORCE_I_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",657,TP_MLDPS,(TP_MLDPS).GetTestPinno(),0.000000e+000,4,0,3.000000e+000,0,1,2.000000e-003, _IFVM_);
  test_no++;    
#line 658 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);   
#line 658 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"VBG_init");      
  {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 659 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",659,TP_MLDPS,(TP_MLDPS).GetTestPinno(),0.000000e+000,1.800000e+000,2.000000e-003,_KEEP_CURRENT_I,_3500_AVE_MODE,_KEEP_CURRENT_F,_KEEP_CURRENT_F,_KEEP_CURRENT_F);} 
  
  
  test_no++;   
#line 662 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);    
#line 662 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"H086_pattern");
  {
#line 663 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_PAT("B20041C_2S_LT40C_CP1_V1P0.PLN",663,H086,__H086,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,(__H086).Getpinmode(),(__H086).Getpin2x(),(__H086).GetValidpin(),(__H086).Gettestno(),(__H086).Getchkmode());} 
  
#line 664 "B20041C_2S_LT40C_CP1_V1P0.PLN"
WAIT("B20041C_2S_LT40C_CP1_V1P0.PLN",664,5.000000e-003);
  test_no++; 
#line 665 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);  
#line 665 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"VTC_init");   
  {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 666 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",666,TP_MLDPS,(TP_MLDPS).GetTestPinno(),0.000000e+000,1.800000e+000,2.000000e-003,_KEEP_CURRENT_I,_3500_AVE_MODE,_KEEP_CURRENT_F,_KEEP_CURRENT_F,_KEEP_CURRENT_F);} 
  
  
  test_no=50,  
#line 669 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);    
#line 669 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"H08C_pattern");
  {
#line 670 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_PAT("B20041C_2S_LT40C_CP1_V1P0.PLN",670,H08C,__H08C,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,(__H08C).Getpinmode(),(__H08C).Getpin2x(),(__H08C).GetValidpin(),(__H08C).Gettestno(),(__H08C).Getchkmode());}
  
#line 671 "B20041C_2S_LT40C_CP1_V1P0.PLN"
WAIT("B20041C_2S_LT40C_CP1_V1P0.PLN",671,5.000000e-003);  
  test_no++;    
#line 672 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);   
#line 672 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"VBG_a_init");      
  {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 673 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",673,TP_MLDPS,(TP_MLDPS).GetTestPinno(),0.000000e+000,2.800000e+000,2.000000e-003,_KEEP_CURRENT_I,_3500_AVE_MODE,_KEEP_CURRENT_F,_KEEP_CURRENT_F,_KEEP_CURRENT_F);} 
  
  
  test_no++;   
#line 676 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);    
#line 676 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"H08B_pattern");
  {
#line 677 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_PAT("B20041C_2S_LT40C_CP1_V1P0.PLN",677,H08B,__H08B,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,MAXINT,(__H08B).Getpinmode(),(__H08B).Getpin2x(),(__H08B).GetValidpin(),(__H08B).Gettestno(),(__H08B).Getchkmode());} 
  
#line 678 "B20041C_2S_LT40C_CP1_V1P0.PLN"
WAIT("B20041C_2S_LT40C_CP1_V1P0.PLN",678,5.000000e-003);
  test_no++; 
#line 679 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);  
#line 679 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"VTC_a_init");   
  {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 680 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_V_MLDPS("B20041C_2S_LT40C_CP1_V1P0.PLN",680,TP_MLDPS,(TP_MLDPS).GetTestPinno(),0.000000e+000,1.800000e+000,2.000000e-003,_KEEP_CURRENT_I,_3500_AVE_MODE,_KEEP_CURRENT_F,_KEEP_CURRENT_F,_KEEP_CURRENT_F);} 
  
  
  




  PGM_TRIM_SCAN(400 , "H087",0x24,4,0,15,4,0,15);
  for(int s=0;s<256;s++){
    {
SET_STATEMENT_INFO(_ID_SOCKET_INC,696);
LUINT tmpMask = CPIN::GetMask();
int *ate_pin,pin_num;
int tmpfreezepin[DF_MAX_Pin_Count],tmppinno=0;
int tmppinmode[DF_MAX_Pin_Count];
for(int _ii_=0; _ii_<DF_MAX_Site_Count; _ii_++){
	if(TrueOrFalse(tmpMask,_ii_)){
		if ((pin_num = GetPinSiteAllIOChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
	}
}
socket_freeze(tmpfreezepin,tmppinno,_ON_,tmppinmode);                       
for(short SOCKET = 0; SOCKET<DF_MAX_Site_Count; SOCKET++) {
	if(TrueOrFalse(tmpMask,SOCKET)){
		int curfreezepin[DF_MAX_Pin_Count],curpinno;
		CPIN::SetMask((LUINT)0x1<<SOCKET);
		curpinno=0;
		if ((pin_num = GetPinSiteAllIOChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		socket_freeze(curfreezepin,curpinno,_OFF_,tmppinmode);
#line 690 "B20041C_2S_LT40C_CP1_V1P0.PLN"
     
      VBG_VO_CP1[SOCKET][s]=voltage_4bit[SOCKET][s];
      if(debug_mode){printf("s=%d,TRIM_VBG_SCAN[%d][%d]=%f\n",s,SOCKET,s,voltage_4bit[SOCKET][s]) ;  fflush(stdout);}   
      test_no++; 
#line 693 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);  
#line 693 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"TRIM_VBG_SCAN");   
      {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 694 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_VARIABLE("B20041C_2S_LT40C_CP1_V1P0.PLN",694,((LUINT)1<<SOCKET),VBG_VO_CP1[SOCKET][s],0.000000e+000,2.000000e+000,"TRIM_VBG_SCAN");}
      if(JUDGE_RESULT_MS[SOCKET]==FAIL) pass_flag[SOCKET] = 0;
    		socket_freeze(curfreezepin,curpinno,_ON_,NULL);
	}
}
socket_freeze(tmpfreezepin,tmppinno,_OFF_,tmppinmode);
CPIN::SetMask(tmpMask);
}
#line 696 "B20041C_2S_LT40C_CP1_V1P0.PLN"

#line 696 "B20041C_2S_LT40C_CP1_V1P0.PLN"
 
  }
  poweroff();
}


__declspec(dllexport) int VTC_TRIM() 
{


#line 702 "B20041C_2S_LT40C_CP1_V1P0.PLN"

  poweron();
  PGM_TRIM_SCAN(test_no , "H086",0x24,4,0,15,4,0,15);
  printf("VTC_TRIM\n");fflush(stdout);
  
  int t=256;  
  for(int s=0;s<256;s++){
    {
SET_STATEMENT_INFO(_ID_SOCKET_INC,715);
LUINT tmpMask = CPIN::GetMask();
int *ate_pin,pin_num;
int tmpfreezepin[DF_MAX_Pin_Count],tmppinno=0;
int tmppinmode[DF_MAX_Pin_Count];
for(int _ii_=0; _ii_<DF_MAX_Site_Count; _ii_++){
	if(TrueOrFalse(tmpMask,_ii_)){
		if ((pin_num = GetPinSiteAllIOChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
	}
}
socket_freeze(tmpfreezepin,tmppinno,_ON_,tmppinmode);                       
for(short SOCKET = 0; SOCKET<DF_MAX_Site_Count; SOCKET++) {
	if(TrueOrFalse(tmpMask,SOCKET)){
		int curfreezepin[DF_MAX_Pin_Count],curpinno;
		CPIN::SetMask((LUINT)0x1<<SOCKET);
		curpinno=0;
		if ((pin_num = GetPinSiteAllIOChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		socket_freeze(curfreezepin,curpinno,_OFF_,tmppinmode);
#line 709 "B20041C_2S_LT40C_CP1_V1P0.PLN"
     
      VTC_VO_CP1[SOCKET][t]=voltage_4bit[SOCKET][s];
      if(debug_mode){printf("s=%d,TRIM_VTC_SCAN[%d][%d]=%f\n",s,SOCKET,t,voltage_4bit[SOCKET][s]) ;  fflush(stdout);}   
      test_no++; 
#line 712 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);  
#line 712 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"TRIM_VTC_SCAN");   
      {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 713 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_VARIABLE("B20041C_2S_LT40C_CP1_V1P0.PLN",713,((LUINT)1<<SOCKET),VTC_VO_CP1[SOCKET][t],0.000000e+000,2.000000e+000,"TRIM_VTC_SCAN");} 
      if(JUDGE_RESULT_MS[SOCKET]==FAIL) pass_flag[SOCKET] = 0;
    		socket_freeze(curfreezepin,curpinno,_ON_,NULL);
	}
}
socket_freeze(tmpfreezepin,tmppinno,_OFF_,tmppinmode);
CPIN::SetMask(tmpMask);
}
#line 715 "B20041C_2S_LT40C_CP1_V1P0.PLN"

#line 715 "B20041C_2S_LT40C_CP1_V1P0.PLN"
 
  t++;
  
  }
  poweroff();
}
 
__declspec(dllexport) int VBG_a_TRIM() 
{


#line 722 "B20041C_2S_LT40C_CP1_V1P0.PLN"

    poweron();
    PGM_TRIM_SCAN(test_no , "H08C",0x27 ,4,0,15,4,0,15);
    printf("VBG_a_TRIM\n");fflush(stdout);
    
  







  
  int t=512;  
  for(int s=0;s<256;s++){
    {
SET_STATEMENT_INFO(_ID_SOCKET_INC,744);
LUINT tmpMask = CPIN::GetMask();
int *ate_pin,pin_num;
int tmpfreezepin[DF_MAX_Pin_Count],tmppinno=0;
int tmppinmode[DF_MAX_Pin_Count];
for(int _ii_=0; _ii_<DF_MAX_Site_Count; _ii_++){
	if(TrueOrFalse(tmpMask,_ii_)){
		if ((pin_num = GetPinSiteAllIOChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
	}
}
socket_freeze(tmpfreezepin,tmppinno,_ON_,tmppinmode);                       
for(short SOCKET = 0; SOCKET<DF_MAX_Site_Count; SOCKET++) {
	if(TrueOrFalse(tmpMask,SOCKET)){
		int curfreezepin[DF_MAX_Pin_Count],curpinno;
		CPIN::SetMask((LUINT)0x1<<SOCKET);
		curpinno=0;
		if ((pin_num = GetPinSiteAllIOChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		socket_freeze(curfreezepin,curpinno,_OFF_,tmppinmode);
#line 738 "B20041C_2S_LT40C_CP1_V1P0.PLN"
     
      VBG_VO_CP1[SOCKET][t]=voltage_4bit[SOCKET][s];
      if(debug_mode){printf("s=%d,TRIM_VBG_SCAN[%d][%d]=%f\n",s,SOCKET,t,voltage_4bit[SOCKET][s]) ;  fflush(stdout);}   
      test_no++; 
#line 741 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);  
#line 741 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"TRIM_VBG_SCAN");   
      {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 742 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_VARIABLE("B20041C_2S_LT40C_CP1_V1P0.PLN",742,((LUINT)1<<SOCKET),VBG_VO_CP1[SOCKET][t],0.000000e+000,2.000000e+000,"TRIM_VBG_SCAN");} 
      if(JUDGE_RESULT_MS[SOCKET]==FAIL) pass_flag[SOCKET] = 0;
    		socket_freeze(curfreezepin,curpinno,_ON_,NULL);
	}
}
socket_freeze(tmpfreezepin,tmppinno,_OFF_,tmppinmode);
CPIN::SetMask(tmpMask);
}
#line 744 "B20041C_2S_LT40C_CP1_V1P0.PLN"

#line 744 "B20041C_2S_LT40C_CP1_V1P0.PLN"
 
  t++;
  
  }
    poweroff();
}

__declspec(dllexport) int VTC_a_TRIM() 
{


#line 751 "B20041C_2S_LT40C_CP1_V1P0.PLN"

    poweron();
    PGM_TRIM_SCAN(test_no , "H08B",0x27,4,0,15,4,0,15);
    printf("VTC_a_TRIM\n");fflush(stdout);
      
  int t=768;  
  for(int s=0;s<256;s++){
    {
SET_STATEMENT_INFO(_ID_SOCKET_INC,764);
LUINT tmpMask = CPIN::GetMask();
int *ate_pin,pin_num;
int tmpfreezepin[DF_MAX_Pin_Count],tmppinno=0;
int tmppinmode[DF_MAX_Pin_Count];
for(int _ii_=0; _ii_<DF_MAX_Site_Count; _ii_++){
	if(TrueOrFalse(tmpMask,_ii_)){
		if ((pin_num = GetPinSiteAllIOChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
	}
}
socket_freeze(tmpfreezepin,tmppinno,_ON_,tmppinmode);                       
for(short SOCKET = 0; SOCKET<DF_MAX_Site_Count; SOCKET++) {
	if(TrueOrFalse(tmpMask,SOCKET)){
		int curfreezepin[DF_MAX_Pin_Count],curpinno;
		CPIN::SetMask((LUINT)0x1<<SOCKET);
		curpinno=0;
		if ((pin_num = GetPinSiteAllIOChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		socket_freeze(curfreezepin,curpinno,_OFF_,tmppinmode);
#line 758 "B20041C_2S_LT40C_CP1_V1P0.PLN"
     
      VTC_VO_CP1[SOCKET][t]=voltage_4bit[SOCKET][s];
      if(debug_mode){printf("s=%d,TRIM_VTC_SCAN[%d][%d]=%f\n",s,SOCKET,t,voltage_4bit[SOCKET][s]) ;  fflush(stdout);}   
      test_no++; 
#line 761 "B20041C_2S_LT40C_CP1_V1P0.PLN"
TEST_NO(test_no);  
#line 761 "B20041C_2S_LT40C_CP1_V1P0.PLN"
strcpy(DATALOG_MSG,"TRIM_VTC_SCAN");   
      {strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;
strcpy(USE_TYPE ,"V")  ;
USE_UNIT = 0  ;

#line 762 "B20041C_2S_LT40C_CP1_V1P0.PLN"
JUDGE_VARIABLE("B20041C_2S_LT40C_CP1_V1P0.PLN",762,((LUINT)1<<SOCKET),VTC_VO_CP1[SOCKET][t],0.000000e+000,2.000000e+000,"TRIM_VTC_SCAN");}
      if(JUDGE_RESULT_MS[SOCKET]==FAIL) pass_flag[SOCKET] = 0;
    		socket_freeze(curfreezepin,curpinno,_ON_,NULL);
	}
}
socket_freeze(tmpfreezepin,tmppinno,_OFF_,tmppinmode);
CPIN::SetMask(tmpMask);
}
#line 764 "B20041C_2S_LT40C_CP1_V1P0.PLN"

#line 764 "B20041C_2S_LT40C_CP1_V1P0.PLN"
 
  t++;
  
  
  }
    {
SET_STATEMENT_INFO(_ID_SOCKET_INC,790);
LUINT tmpMask = CPIN::GetMask();
int *ate_pin,pin_num;
int tmpfreezepin[DF_MAX_Pin_Count],tmppinno=0;
int tmppinmode[DF_MAX_Pin_Count];
for(int _ii_=0; _ii_<DF_MAX_Site_Count; _ii_++){
	if(TrueOrFalse(tmpMask,_ii_)){
		if ((pin_num = GetPinSiteAllIOChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(_ii_, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) tmpfreezepin[tmppinno+_jj_] = ate_pin[_jj_];
		tmppinno += pin_num;
		}
	}
}
socket_freeze(tmpfreezepin,tmppinno,_ON_,tmppinmode);                       
for(short SOCKET = 0; SOCKET<DF_MAX_Site_Count; SOCKET++) {
	if(TrueOrFalse(tmpMask,SOCKET)){
		int curfreezepin[DF_MAX_Pin_Count],curpinno;
		CPIN::SetMask((LUINT)0x1<<SOCKET);
		curpinno=0;
		if ((pin_num = GetPinSiteAllIOChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		if ((pin_num = GetPinSiteAllLCDChannel(SOCKET, ate_pin)) > 0) {
		for (int _jj_=0;_jj_<pin_num;_jj_++) curfreezepin[curpinno+_jj_] = ate_pin[_jj_];
		curpinno += pin_num;
		}
		socket_freeze(curfreezepin,curpinno,_OFF_,tmppinmode);
#line 769 "B20041C_2S_LT40C_CP1_V1P0.PLN"

    vector<string> row; 
    row.push_back(to_string(PHIF_X[SOCKET]));
    row.push_back(to_string(PHIF_Y[SOCKET]));
      for(int j=0;j<1024;j++){
        if     (j<256){row.push_back(to_string(VBG_VO_CP1[SOCKET][j]));}
        else if(j<512){row.push_back(to_string(VTC_VO_CP1[SOCKET][j]));}
        else if(j<768){row.push_back(to_string(VBG_VO_CP1[SOCKET][j]));}
        else          {row.push_back(to_string(VTC_VO_CP1[SOCKET][j]));}
      
      }
      cvs_value.clear();
      cvs_value.push_back(row);  
      if(pass_flag[SOCKET] == 1)
      {
        write_csv(file,lot_idstr,wafer_idstr,delimiter, cvs_value);
        file << endl;  
      }else
      {
        cvs_value.clear();
      }
    		socket_freeze(curfreezepin,curpinno,_ON_,NULL);
	}
}
socket_freeze(tmpfreezepin,tmppinno,_OFF_,tmppinmode);
CPIN::SetMask(tmpMask);
}
#line 790 "B20041C_2S_LT40C_CP1_V1P0.PLN"

#line 790 "B20041C_2S_LT40C_CP1_V1P0.PLN"
 
    file.close();
    poweroff();
}

__declspec(dllexport) int last_item_test() 
{


#line 795 "B20041C_2S_LT40C_CP1_V1P0.PLN"

   printf("last item test finished !!\n");
   fflush(stdout);
}
	__declspec(dllexport) int LOADPIN()
{
IO_ALLPINS.GetFunc();
}


void
#line 3 "arithmetic.pln"
 connect_ftp(std::string lot_str,std::string ftp_mode) {
  string FTP_Path="\n    remote_path = '/B20041C/"+(lot_str+"/CP1'\n");
  string local_path= change_local_path1+(lot_str + "/CP1'");
  string data_path = "\n    local_path ="+local_path;
  
  FILE *ftp_file =NULL;
  ftp_file=fopen("..\\flag.txt","w");
  fclose(ftp_file);
  
#line 11 "arithmetic.pln"
WAIT("arithmetic.pln",11,5.000000e-002);
  FILE *fp =NULL;
  fp=fopen("..\\ftp.py","w");
  if (fp!=NULL) {
      fprintf(fp, "import os");
      fprintf(fp, "\nimport time");      
      fprintf(fp, "\nimport ftplib");      
      fprintf(fp, "\nimport subprocess");               
      fprintf(fp, "\nftp = ftplib.FTP()");
      fprintf(fp, "\nftp.timeout = 5");  
      
      fprintf(fp, "\ntry:");     
      fprintf(fp, "\n    ftp.connect('195.170.13.230', 21)");
      fprintf(fp, "\n    ftp.login('AQV', 'jb8yNC5e9x9Sq6r')");
      fprintf(fp, "\n    flag=1");      
      fprintf(fp, "\nexcept ftplib.all_errors as e:");
      fprintf(fp, "\n    flag=0");
      fprintf(fp, "\n    print('Connect to FTP Fail !!!')"); 

      
      fprintf(fp, "\nif flag==1:"); 
      fprintf(fp, "\n    print('Connected to FTP server')"); 
      fprintf(fp, "\n    with open(os.path.join(os.getcwd(), 'flag.txt'), 'w') as f:"); 
      fprintf(fp, "\n        f.write(str(1))");  
      fprintf(fp, FTP_Path.c_str());
      fprintf(fp, data_path.c_str());
      if(ftp_mode=="up" || ftp_mode=="Up" || ftp_mode=="UP"){
        fprintf(fp, "\n    if remote_path not in ftp.nlst():");
        fprintf(fp, "\n        folders = remote_path.strip(\"/\").split(\"/\")");
        fprintf(fp, "\n        for folder in folders:");
        fprintf(fp, "\n            try:ftp.cwd(folder)");
        fprintf(fp, "\n            except:ftp.mkd(folder);ftp.cwd(folder)");
        fprintf(fp, "\n    for file in os.listdir(local_path):");
        fprintf(fp, "\n        if file.endswith('.csv'):");
        fprintf(fp, "\n            with open(os.path.join(local_path, file), 'rb') as f:");
        fprintf(fp, "\n                ftp.storbinary('STOR ' + file, f)");
        fprintf(fp, "\n                print('Uploaded file:', file)"); 
      }
      else if(ftp_mode=="down" || ftp_mode=="Down" || ftp_mode=="DOWN"){
        fprintf(fp, "\n    ftp.cwd(remote_path)");
        fprintf(fp, "\n    if not os.path.exists(local_path):");
        fprintf(fp, "\n        os.makedirs(local_path)");
        fprintf(fp, "\n    for file in ftp.nlst():");
        fprintf(fp, "\n        if file.endswith('.csv'):");
        fprintf(fp, "\n            with open(os.path.join(local_path, file), 'wb') as f:");       
        fprintf(fp, "\n                ftp.retrbinary('RETR ' + file, f.write)"); 
        fprintf(fp, "\n                print('Downloaded file:', file)"); 
      }
      fprintf(fp, "\nelse:"); 
      fprintf(fp, "\n    with open(os.path.join(os.getcwd(), 'flag.txt'), 'w') as f:"); 
      fprintf(fp, "\n        f.write(str(0))"); 

      fprintf(fp, "\nftp.quit()");        
      fprintf(fp, "\nos.remove(os.path.abspath(__file__))"); 
      fclose(fp);
      
#line 66 "arithmetic.pln"
WAIT("arithmetic.pln",66,5.000000e-002);
      cout << "Data transmission in progress, please be patient..." << endl;
      
      string py_path="cmd /c python ";
      char buffer[MAX_PATH];
      GetCurrentDirectory(MAX_PATH,buffer);
      std::string path(buffer);
      size_t pos = path.find_last_of("\\/"); 
      if (pos != std::string::npos) {
          path = path.substr(0, pos); 
      }
      py_path=py_path+path+"\\ftp.py";
      
      system(py_path.c_str());
      cout << "done!" << endl;
      
#line 81 "arithmetic.pln"
WAIT("arithmetic.pln",81,5.000000e-002);
      
                                                                                                                                            
      std::ifstream file("..\\flag.txt");
      if (file.is_open()) {
          std::string line;
          std::getline(file, line);
          if (line == "0") {
            MessageBoxA(NULL,"FTP Connect Fail,program will be aborted,Please comfirm!","Shanghai V-Test Semiconductor Co.,Ltd.", MB_OK + 16); 
            ABORT_TEST_PLN();
          } 
          else if (line == "1") {
              std::cout << "FTP Connect succeed" << std::endl;
          } 
          file.close();
      } 
      else {
          MessageBoxA(NULL,"Unable to open file flag.txt.,Please comfirm!","Shanghai V-Test Semiconductor Co.,Ltd.", MB_OK + 16); 
          ABORT_TEST_PLN();
      }
  }
  else{
      MessageBoxA(NULL,"can not creat ftp.py file,Please comfirm!","Shanghai V-Test Semiconductor Co.,Ltd.", MB_OK + 16); 
      ABORT_TEST_PLN();
  }
}


void write_csv(ofstream& file,string lot_id,string wafer_id, char delimiter, vector<vector<string>> data) { 
  for (vector<string> row : data) 
  {
    for (int i = 0; i < row.size(); i++)
    {
      file << row[i];
      if (i != row.size() - 1) 
      {
        file << delimiter;
      }
    }
    file << delimiter;
  }
}




































































































