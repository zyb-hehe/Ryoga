#ifndef arithmetic_h
#define arithmetic_h

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <windows.h>
#include <C:/CRAFT/VT_TE_function.h>

using namespace std;
string change_local_path1="'D:/AQV_B20041C/B20041C/";
string change_local_path2="D:/AQV_B20041C/B20041C/";
string filepath;
char delimiter = ',';
vector<vector<string>> cvs_value ;
vector<vector<string>> data={{"X","Y",
    "VBG_0_0","VBG_0_1","VBG_0_2","VBG_0_3","VBG_0_4","VBG_0_5","VBG_0_6","VBG_0_7","VBG_0_8","VBG_0_9","VBG_0_10","VBG_0_11","VBG_0_12","VBG_0_13","VBG_0_14","VBG_0_15",
    "VBG_1_0","VBG_1_1","VBG_1_2","VBG_1_3","VBG_1_4","VBG_1_5","VBG_1_6","VBG_1_7","VBG_1_8","VBG_1_9","VBG_1_10","VBG_1_11","VBG_1_12","VBG_1_13","VBG_1_14","VBG_1_15",
    "VBG_2_0","VBG_2_1","VBG_2_2","VBG_2_3","VBG_2_4","VBG_2_5","VBG_2_6","VBG_2_7","VBG_2_8","VBG_2_9","VBG_2_10","VBG_2_11","VBG_2_12","VBG_2_13","VBG_2_14","VBG_2_15",
    "VBG_3_0","VBG_3_1","VBG_3_2","VBG_3_3","VBG_3_4","VBG_3_5","VBG_3_6","VBG_3_7","VBG_3_8","VBG_3_9","VBG_3_10","VBG_3_11","VBG_3_12","VBG_3_13","VBG_3_14","VBG_3_15",
    "VBG_4_0","VBG_4_1","VBG_4_2","VBG_4_3","VBG_4_4","VBG_4_5","VBG_4_6","VBG_4_7","VBG_4_8","VBG_4_9","VBG_4_10","VBG_4_11","VBG_4_12","VBG_4_13","VBG_4_14","VBG_4_15",
    "VBG_5_0","VBG_5_1","VBG_5_2","VBG_5_3","VBG_5_4","VBG_5_5","VBG_5_6","VBG_5_7","VBG_5_8","VBG_5_9","VBG_5_10","VBG_5_11","VBG_5_12","VBG_5_13","VBG_5_14","VBG_5_15",
    "VBG_6_0","VBG_6_1","VBG_6_2","VBG_6_3","VBG_6_4","VBG_6_5","VBG_6_6","VBG_6_7","VBG_6_8","VBG_6_9","VBG_6_10","VBG_6_11","VBG_6_12","VBG_6_13","VBG_6_14","VBG_6_15",
    "VBG_7_0","VBG_7_1","VBG_7_2","VBG_7_3","VBG_7_4","VBG_7_5","VBG_7_6","VBG_7_7","VBG_7_8","VBG_7_9","VBG_7_10","VBG_7_11","VBG_7_12","VBG_7_13","VBG_7_14","VBG_7_15",
    "VBG_8_0","VBG_8_1","VBG_8_2","VBG_8_3","VBG_8_4","VBG_8_5","VBG_8_6","VBG_8_7","VBG_8_8","VBG_8_9","VBG_8_10","VBG_8_11","VBG_8_12","VBG_8_13","VBG_8_14","VBG_8_15",
    "VBG_9_0","VBG_9_1","VBG_9_2","VBG_9_3","VBG_9_4","VBG_9_5","VBG_9_6","VBG_9_7","VBG_9_8","VBG_9_9","VBG_9_10","VBG_9_11","VBG_9_12","VBG_9_13","VBG_9_14","VBG_9_15",
    "VBG_10_0","VBG_10_1","VBG_10_2","VBG_10_3","VBG_10_4","VBG_10_5","VBG_10_6","VBG_10_7","VBG_10_8","VBG_10_9","VBG_10_10","VBG_10_11","VBG_10_12","VBG_10_13","VBG_10_14","VBG_10_15 ",
    "VBG_11_0","VBG_11_1","VBG_11_2","VBG_11_3","VBG_11_4","VBG_11_5","VBG_11_6","VBG_11_7","VBG_11_8","VBG_11_9","VBG_11_10","VBG_11_11","VBG_11_12","VBG_11_13","VBG_11_14","VBG_11_15 ",
    "VBG_12_0","VBG_12_1","VBG_12_2","VBG_12_3","VBG_12_4","VBG_12_5","VBG_12_6","VBG_12_7","VBG_12_8","VBG_12_9","VBG_12_10","VBG_12_11","VBG_12_12","VBG_12_13","VBG_12_14","VBG_12_15 ",
    "VBG_13_0","VBG_13_1","VBG_13_2","VBG_13_3","VBG_13_4","VBG_13_5","VBG_13_6","VBG_13_7","VBG_13_8","VBG_13_9","VBG_13_10","VBG_13_11","VBG_13_12","VBG_13_13","VBG_13_14","VBG_13_15 ",
    "VBG_14_0","VBG_14_1","VBG_14_2","VBG_14_3","VBG_14_4","VBG_14_5","VBG_14_6","VBG_14_7","VBG_14_8","VBG_14_9","VBG_14_10","VBG_14_11","VBG_14_12","VBG_14_13","VBG_14_14","VBG_14_15 ",
    "VBG_15_0","VBG_15_1","VBG_15_2","VBG_15_3","VBG_15_4","VBG_15_5","VBG_15_6","VBG_15_7","VBG_15_8","VBG_15_9","VBG_15_10","VBG_15_11","VBG_15_12","VBG_15_13","VBG_15_14","VBG_15_15 ",
    "VTC_0_0","VTC_0_1","VTC_0_2","VTC_0_3","VTC_0_4","VTC_0_5","VTC_0_6","VTC_0_7","VTC_0_8","VTC_0_9","VTC_0_10","VTC_0_11","VTC_0_12","VTC_0_13","VTC_0_14","VTC_0_15",
    "VTC_1_0","VTC_1_1","VTC_1_2","VTC_1_3","VTC_1_4","VTC_1_5","VTC_1_6","VTC_1_7","VTC_1_8","VTC_1_9","VTC_1_10","VTC_1_11","VTC_1_12","VTC_1_13","VTC_1_14","VTC_1_15",
    "VTC_2_0","VTC_2_1","VTC_2_2","VTC_2_3","VTC_2_4","VTC_2_5","VTC_2_6","VTC_2_7","VTC_2_8","VTC_2_9","VTC_2_10","VTC_2_11","VTC_2_12","VTC_2_13","VTC_2_14","VTC_2_15",
    "VTC_3_0","VTC_3_1","VTC_3_2","VTC_3_3","VTC_3_4","VTC_3_5","VTC_3_6","VTC_3_7","VTC_3_8","VTC_3_9","VTC_3_10","VTC_3_11","VTC_3_12","VTC_3_13","VTC_3_14","VTC_3_15",
    "VTC_4_0","VTC_4_1","VTC_4_2","VTC_4_3","VTC_4_4","VTC_4_5","VTC_4_6","VTC_4_7","VTC_4_8","VTC_4_9","VTC_4_10","VTC_4_11","VTC_4_12","VTC_4_13","VTC_4_14","VTC_4_15",
    "VTC_5_0","VTC_5_1","VTC_5_2","VTC_5_3","VTC_5_4","VTC_5_5","VTC_5_6","VTC_5_7","VTC_5_8","VTC_5_9","VTC_5_10","VTC_5_11","VTC_5_12","VTC_5_13","VTC_5_14","VTC_5_15",
    "VTC_6_0","VTC_6_1","VTC_6_2","VTC_6_3","VTC_6_4","VTC_6_5","VTC_6_6","VTC_6_7","VTC_6_8","VTC_6_9","VTC_6_10","VTC_6_11","VTC_6_12","VTC_6_13","VTC_6_14","VTC_6_15",
    "VTC_7_0","VTC_7_1","VTC_7_2","VTC_7_3","VTC_7_4","VTC_7_5","VTC_7_6","VTC_7_7","VTC_7_8","VTC_7_9","VTC_7_10","VTC_7_11","VTC_7_12","VTC_7_13","VTC_7_14","VTC_7_15",
    "VTC_8_0","VTC_8_1","VTC_8_2","VTC_8_3","VTC_8_4","VTC_8_5","VTC_8_6","VTC_8_7","VTC_8_8","VTC_8_9","VTC_8_10","VTC_8_11","VTC_8_12","VTC_8_13","VTC_8_14","VTC_8_15",
    "VTC_9_0","VTC_9_1","VTC_9_2","VTC_9_3","VTC_9_4","VTC_9_5","VTC_9_6","VTC_9_7","VTC_9_8","VTC_9_9","VTC_9_10","VTC_9_11","VTC_9_12","VTC_9_13","VTC_9_14","VTC_9_15",
    "VTC_10_0","VTC_10_1","VTC_10_2","VTC_10_3","VTC_10_4","VTC_10_5","VTC_10_6","VTC_10_7","VTC_10_8","VTC_10_9","VTC_10_10","VTC_10_11","VTC_10_12","VTC_10_13","VTC_10_14","VTC_10_15 ",
    "VTC_11_0","VTC_11_1","VTC_11_2","VTC_11_3","VTC_11_4","VTC_11_5","VTC_11_6","VTC_11_7","VTC_11_8","VTC_11_9","VTC_11_10","VTC_11_11","VTC_11_12","VTC_11_13","VTC_11_14","VTC_11_15 ",
    "VTC_12_0","VTC_12_1","VTC_12_2","VTC_12_3","VTC_12_4","VTC_12_5","VTC_12_6","VTC_12_7","VTC_12_8","VTC_12_9","VTC_12_10","VTC_12_11","VTC_12_12","VTC_12_13","VTC_12_14","VTC_12_15 ",
    "VTC_13_0","VTC_13_1","VTC_13_2","VTC_13_3","VTC_13_4","VTC_13_5","VTC_13_6","VTC_13_7","VTC_13_8","VTC_13_9","VTC_13_10","VTC_13_11","VTC_13_12","VTC_13_13","VTC_13_14","VTC_13_15 ",
    "VTC_14_0","VTC_14_1","VTC_14_2","VTC_14_3","VTC_14_4","VTC_14_5","VTC_14_6","VTC_14_7","VTC_14_8","VTC_14_9","VTC_14_10","VTC_14_11","VTC_14_12","VTC_14_13","VTC_14_14","VTC_14_15 ",
    "VTC_15_0","VTC_15_1","VTC_15_2","VTC_15_3","VTC_15_4","VTC_15_5","VTC_15_6","VTC_15_7","VTC_15_8","VTC_15_9","VTC_15_10","VTC_15_11","VTC_15_12","VTC_15_13","VTC_15_14","VTC_15_15 ",
    "VBG_a_0_0","VBG_a_0_1","VBG_a_0_2","VBG_a_0_3","VBG_a_0_4","VBG_a_0_5","VBG_a_0_6","VBG_a_0_7","VBG_a_0_8","VBG_a_0_9","VBG_a_0_10","VBG_a_0_11","VBG_a_0_12","VBG_a_0_13","VBG_a_0_14","VBG_a_0_15",
    "VBG_a_1_0","VBG_a_1_1","VBG_a_1_2","VBG_a_1_3","VBG_a_1_4","VBG_a_1_5","VBG_a_1_6","VBG_a_1_7","VBG_a_1_8","VBG_a_1_9","VBG_a_1_10","VBG_a_1_11","VBG_a_1_12","VBG_a_1_13","VBG_a_1_14","VBG_a_1_15",
    "VBG_a_2_0","VBG_a_2_1","VBG_a_2_2","VBG_a_2_3","VBG_a_2_4","VBG_a_2_5","VBG_a_2_6","VBG_a_2_7","VBG_a_2_8","VBG_a_2_9","VBG_a_2_10","VBG_a_2_11","VBG_a_2_12","VBG_a_2_13","VBG_a_2_14","VBG_a_2_15",
    "VBG_a_3_0","VBG_a_3_1","VBG_a_3_2","VBG_a_3_3","VBG_a_3_4","VBG_a_3_5","VBG_a_3_6","VBG_a_3_7","VBG_a_3_8","VBG_a_3_9","VBG_a_3_10","VBG_a_3_11","VBG_a_3_12","VBG_a_3_13","VBG_a_3_14","VBG_a_3_15",
    "VBG_a_4_0","VBG_a_4_1","VBG_a_4_2","VBG_a_4_3","VBG_a_4_4","VBG_a_4_5","VBG_a_4_6","VBG_a_4_7","VBG_a_4_8","VBG_a_4_9","VBG_a_4_10","VBG_a_4_11","VBG_a_4_12","VBG_a_4_13","VBG_a_4_14","VBG_a_4_15",
    "VBG_a_5_0","VBG_a_5_1","VBG_a_5_2","VBG_a_5_3","VBG_a_5_4","VBG_a_5_5","VBG_a_5_6","VBG_a_5_7","VBG_a_5_8","VBG_a_5_9","VBG_a_5_10","VBG_a_5_11","VBG_a_5_12","VBG_a_5_13","VBG_a_5_14","VBG_a_5_15",
    "VBG_a_6_0","VBG_a_6_1","VBG_a_6_2","VBG_a_6_3","VBG_a_6_4","VBG_a_6_5","VBG_a_6_6","VBG_a_6_7","VBG_a_6_8","VBG_a_6_9","VBG_a_6_10","VBG_a_6_11","VBG_a_6_12","VBG_a_6_13","VBG_a_6_14","VBG_a_6_15",
    "VBG_a_7_0","VBG_a_7_1","VBG_a_7_2","VBG_a_7_3","VBG_a_7_4","VBG_a_7_5","VBG_a_7_6","VBG_a_7_7","VBG_a_7_8","VBG_a_7_9","VBG_a_7_10","VBG_a_7_11","VBG_a_7_12","VBG_a_7_13","VBG_a_7_14","VBG_a_7_15",
    "VBG_a_8_0","VBG_a_8_1","VBG_a_8_2","VBG_a_8_3","VBG_a_8_4","VBG_a_8_5","VBG_a_8_6","VBG_a_8_7","VBG_a_8_8","VBG_a_8_9","VBG_a_8_10","VBG_a_8_11","VBG_a_8_12","VBG_a_8_13","VBG_a_8_14","VBG_a_8_15",
    "VBG_a_9_0","VBG_a_9_1","VBG_a_9_2","VBG_a_9_3","VBG_a_9_4","VBG_a_9_5","VBG_a_9_6","VBG_a_9_7","VBG_a_9_8","VBG_a_9_9","VBG_a_9_10","VBG_a_9_11","VBG_a_9_12","VBG_a_9_13","VBG_a_9_14","VBG_a_9_15",
    "VBG_a_10_0","VBG_a_10_1","VBG_a_10_2","VBG_a_10_3","VBG_a_10_4","VBG_a_10_5","VBG_a_10_6","VBG_a_10_7","VBG_a_10_8","VBG_a_10_9","VBG_a_10_10","VBG_a_10_11","VBG_a_10_12","BG_a_10_13","VBG_a_10_14","BG_a_10_15",
    "VBG_a_11_0","VBG_a_11_1","VBG_a_11_2","VBG_a_11_3","VBG_a_11_4","VBG_a_11_5","VBG_a_11_6","VBG_a_11_7","VBG_a_11_8","VBG_a_11_9","VBG_a_11_10","VBG_a_11_11","VBG_a_11_12","VBG_a_11_13","VBG_a_11_14","VBG_a_11_15",
    "VBG_a_12_0","VBG_a_12_1","VBG_a_12_2","VBG_a_12_3","VBG_a_12_4","VBG_a_12_5","VBG_a_12_6","VBG_a_12_7","VBG_a_12_8","VBG_a_12_9","VBG_a_12_10","VBG_a_12_11","VBG_a_12_12","VBG_a_12_13","VBG_a_12_14","VBG_a_12_15",
    "VBG_a_13_0","VBG_a_13_1","VBG_a_13_2","VBG_a_13_3","VBG_a_13_4","VBG_a_13_5","VBG_a_13_6","VBG_a_13_7","VBG_a_13_8","VBG_a_13_9","VBG_a_13_10","VBG_a_13_11","VBG_a_13_12","VBG_a_13_13","VBG_a_13_14","VBG_a_13_15",
    "VBG_a_14_0","VBG_a_14_1","VBG_a_14_2","VBG_a_14_3","VBG_a_14_4","VBG_a_14_5","VBG_a_14_6","VBG_a_14_7","VBG_a_14_8","VBG_a_14_9","VBG_a_14_10","VBG_a_14_11","VBG_a_14_12","VBG_a_14_13","VBG_a_14_14","VBG_a_14_15",
    "VBG_a_15_0","VBG_a_15_1","VBG_a_15_2","VBG_a_15_3","VBG_a_15_4","VBG_a_15_5","VBG_a_15_6","VBG_a_15_7","VBG_a_15_8","VBG_a_15_9","VBG_a_15_10","VBG_a_15_11","VBG_a_15_12","VBG_a_15_13","VBG_a_15_14","VBG_a_15_15",
    "VTC_a_0_0","VTC_a_0_1","VTC_a_0_2","VTC_a_0_3","VTC_a_0_4","VTC_a_0_5","VTC_a_0_6","VTC_a_0_7","VTC_a_0_8","VTC_a_0_9","VTC_a_0_10","VTC_a_0_11","VTC_a_0_12","VTC_a_0_13","VTC_a_0_14","VTC_a_0_15",
    "VTC_a_1_0","VTC_a_1_1","VTC_a_1_2","VTC_a_1_3","VTC_a_1_4","VTC_a_1_5","VTC_a_1_6","VTC_a_1_7","VTC_a_1_8","VTC_a_1_9","VTC_a_1_10","VTC_a_1_11","VTC_a_1_12","VTC_a_1_13","VTC_a_1_14","VTC_a_1_15",
    "VTC_a_2_0","VTC_a_2_1","VTC_a_2_2","VTC_a_2_3","VTC_a_2_4","VTC_a_2_5","VTC_a_2_6","VTC_a_2_7","VTC_a_2_8","VTC_a_2_9","VTC_a_2_10","VTC_a_2_11","VTC_a_2_12","VTC_a_2_13","VTC_a_2_14","VTC_a_2_15",
    "VTC_a_3_0","VTC_a_3_1","VTC_a_3_2","VTC_a_3_3","VTC_a_3_4","VTC_a_3_5","VTC_a_3_6","VTC_a_3_7","VTC_a_3_8","VTC_a_3_9","VTC_a_3_10","VTC_a_3_11","VTC_a_3_12","VTC_a_3_13","VTC_a_3_14","VTC_a_3_15",
    "VTC_a_4_0","VTC_a_4_1","VTC_a_4_2","VTC_a_4_3","VTC_a_4_4","VTC_a_4_5","VTC_a_4_6","VTC_a_4_7","VTC_a_4_8","VTC_a_4_9","VTC_a_4_10","VTC_a_4_11","VTC_a_4_12","VTC_a_4_13","VTC_a_4_14","VTC_a_4_15",
    "VTC_a_5_0","VTC_a_5_1","VTC_a_5_2","VTC_a_5_3","VTC_a_5_4","VTC_a_5_5","VTC_a_5_6","VTC_a_5_7","VTC_a_5_8","VTC_a_5_9","VTC_a_5_10","VTC_a_5_11","VTC_a_5_12","VTC_a_5_13","VTC_a_5_14","VTC_a_5_15",
    "VTC_a_6_0","VTC_a_6_1","VTC_a_6_2","VTC_a_6_3","VTC_a_6_4","VTC_a_6_5","VTC_a_6_6","VTC_a_6_7","VTC_a_6_8","VTC_a_6_9","VTC_a_6_10","VTC_a_6_11","VTC_a_6_12","VTC_a_6_13","VTC_a_6_14","VTC_a_6_15",
    "VTC_a_7_0","VTC_a_7_1","VTC_a_7_2","VTC_a_7_3","VTC_a_7_4","VTC_a_7_5","VTC_a_7_6","VTC_a_7_7","VTC_a_7_8","VTC_a_7_9","VTC_a_7_10","VTC_a_7_11","VTC_a_7_12","VTC_a_7_13","VTC_a_7_14","VTC_a_7_15",
    "VTC_a_8_0","VTC_a_8_1","VTC_a_8_2","VTC_a_8_3","VTC_a_8_4","VTC_a_8_5","VTC_a_8_6","VTC_a_8_7","VTC_a_8_8","VTC_a_8_9","VTC_a_8_10","VTC_a_8_11","VTC_a_8_12","VTC_a_8_13","VTC_a_8_14","VTC_a_8_15",
    "VTC_a_9_0","VTC_a_9_1","VTC_a_9_2","VTC_a_9_3","VTC_a_9_4","VTC_a_9_5","VTC_a_9_6","VTC_a_9_7","VTC_a_9_8","VTC_a_9_9","VTC_a_9_10","VTC_a_9_11","VTC_a_9_12","VTC_a_9_13","VTC_a_9_14","VTC_a_9_15",
    "VTC_a_10_0","VTC_a_10_1","VTC_a_10_2","VTC_a_10_3","VTC_a_10_4","VTC_a_10_5","VTC_a_10_6","VTC_a_10_7","VTC_a_10_8","VTC_a_10_9","VTC_a_10_10","VTC_a_10_11","VTC_a_10_12","VTC_a_10_13","VTC_a_10_14","VTC_a_10_15",
    "VTC_a_11_0","VTC_a_11_1","VTC_a_11_2","VTC_a_11_3","VTC_a_11_4","VTC_a_11_5","VTC_a_11_6","VTC_a_11_7","VTC_a_11_8","VTC_a_11_9","VTC_a_11_10","VTC_a_11_11","VTC_a_11_12","VTC_a_11_13","VTC_a_11_14","VTC_a_11_15",
    "VTC_a_12_0","VTC_a_12_1","VTC_a_12_2","VTC_a_12_3","VTC_a_12_4","VTC_a_12_5","VTC_a_12_6","VTC_a_12_7","VTC_a_12_8","VTC_a_12_9","VTC_a_12_10","VTC_a_12_11","VTC_a_12_12","VTC_a_12_13","VTC_a_12_14","VTC_a_12_15",
    "VTC_a_13_0","VTC_a_13_1","VTC_a_13_2","VTC_a_13_3","VTC_a_13_4","VTC_a_13_5","VTC_a_13_6","VTC_a_13_7","VTC_a_13_8","VTC_a_13_9","VTC_a_13_10","VTC_a_13_11","VTC_a_13_12","VTC_a_13_13","VTC_a_13_14","VTC_a_13_15",
    "VTC_a_14_0","VTC_a_14_1","VTC_a_14_2","VTC_a_14_3","VTC_a_14_4","VTC_a_14_5","VTC_a_14_6","VTC_a_14_7","VTC_a_14_8","VTC_a_14_9","VTC_a_14_10","VTC_a_14_11","VTC_a_14_12","VTC_a_14_13","VTC_a_14_14","VTC_a_14_15",
    "VTC_a_15_0","VTC_a_15_1","VTC_a_15_2","VTC_a_15_3","VTC_a_15_4","VTC_a_15_5","VTC_a_15_6","VTC_a_15_7","VTC_a_15_8","VTC_a_15_9","VTC_a_15_10","VTC_a_15_11","VTC_a_15_12","VTC_a_15_13","VTC_a_15_14","VTC_a_15_15"}};

void connect_ftp(std::string lot_str,std::string ftp_mode);
void write_csv(ofstream& file, string lot_id, string wafer_id, char delimiter, vector<vector<string>> data);
void read_csv(string lot_id1);
#endif
