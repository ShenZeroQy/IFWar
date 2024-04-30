#pragma once
//source:https://blog.csdn.net/hyacinthhome/article/details/105883265
#include"base.h"
#include<iostream>
#include<cstdio>
#include<vector>
#include<fstream>
#include<cmath>
#include<ctime>
#include<cstdlib>


#define Pre_n (2*Param_Y_Num)
#define Pre_c 40
using namespace std;
struct Mode
{
	//int x, y;
	int di;
	vector<double> datas;
};
typedef vector<vector<Mode> > ModeVec;
const int N = Param_Y_Num;
const double eps = 1e-2;
const double eps_dis = 1e-3;
const int R_f = 100;
const int R_e = 80;

double getDistance(Mode &m1, Mode &m2);
void FCM(Mode *p, int n, int di, int clusternum, vector<vector<Mode> > &ans);
void init_c(Mode *p, int n, int clusternum, Mode *c);
void comp_dis(Mode *p, Mode *c, int n, int clusternum, double dis[][Pre_c]);
void comp_u(double dis[][Pre_c], int n, int clusternum, double u[][Pre_c], int* Cnt);
void update_c(Mode *p, double u[][Pre_c], int n, int clusternum, Mode *c);
double comp_obj_func(double u[][Pre_c], double dis[][Pre_c], int n, int clusternum, int di);
int main_forFCM(int yn,int zn);
