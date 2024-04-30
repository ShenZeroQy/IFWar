#pragma once
/***************   system lib   ******/
#include <iostream>
#include<fstream>
#include<vector>

#include<algorithm>
#include<cmath>
#include<ccomplex>

#include<random>

#include<ctime>

//����������Ҫ������֧��C++11
#include<thread>
#include<atomic>
//�������������м���
#include<string>
#include<stack>
#include<queue>

/*******   external lib  ********/
//��Ҫ���ⲿ����������⣬Eigen�ṩ�ܺõ����Դ���֧�����������֧��
//#include <Eigen/core>
//#include <Eigen//Dense>
//#include<opencv>


/******    golbal defination for Problem    ********/

#define Param_Y_Num 50
#define Param_Z_Num Param_Y_Num
#define Param_Area 10000
#define Param_Interference_Distance  (1000)
#define Param_Interference_Max_enhance_count  5
#define Param_Interference_Max_disturb_count  Param_Z_Num

#define Param_Communicate_Distance (3000)
#define Param_Max_X 30

#define Param_Y_prize 0.5
#define Param_Z_prize 0.3


/**************    Macro Functions defination    *******/
//#define Func_dist_squ(x,y) ((x)*(x)+(y)*(y))
//#define A_big_bear 0

//np
using namespace std;
//data struct
typedef complex<double> dot;
typedef vector<dot> VecCd;
typedef queue<dot> QueCd;

extern std::default_random_engine rn;
