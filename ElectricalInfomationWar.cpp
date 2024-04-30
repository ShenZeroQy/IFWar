// ElectricalInfomationWar.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "Warmap.h"
#include"FCM.h"
#include"pso.h"

Warmap p;
Warmap& mappointer = p;
int main()
{
	
	p.Init_map(0);

	//测试排序
	/*flyy afly;
	dot s ( 5, 6);
	afly.center = s;
	dot s1(5, 7);
	afly.child.push_back (s1);
	dot s2(5.1, 6);
	afly.child.push_back(s2);
	dot s3(5.5, 6);
	afly.child.push_back(s3);
	afly.carrier = afly.child.size();
	cout << s;
	afly.sort_child();
	s = afly.child[2];
	cout << s;
	afly.center = s;*/
	int yn = 10, zn = 10;
	main_forFCM(yn,zn);
	ifstream fcmin("./data/obj_fcm_result.txt");
	double YnCenter[500][2];
	double ZnCenter[500][2];
	int adj = 0; int repeat = 0;
	int cnt; double R;
	for (int i = 0; i < yn; i++)
	{
		fcmin >> YnCenter[i+adj][0];
		fcmin >> YnCenter[i+adj][1];
		fcmin >> R;
		fcmin >> cnt;
		if (R <= 0)
			adj -= 1;
		else
		{
			repeat = cnt/Param_Interference_Max_enhance_count;
			
			//adj += repeat;
			for (int j = 1; j <=repeat;j++)
			{
				YnCenter[i + adj+j][0]=YnCenter[i + adj][0];
				YnCenter[i + adj + j][1] = YnCenter[i + adj][1];
			}
			adj += repeat;
		}
	}
	yn = yn + adj;
	adj = 0;
	for (int i = 0; i < zn; i++)
	{
		fcmin >> ZnCenter[i + adj][0];
		fcmin >> ZnCenter[i + adj][1];
		fcmin >> R;
		fcmin >> cnt;
		if (R <= Param_Interference_Distance/2)
			adj -= 1;
		else
		{
			repeat = int(R /Param_Interference_Distance);
			if (repeat >= 4)
				repeat = 9;
			else
				repeat = repeat * repeat;
			//adj += repeat;
			for (int j = 1; j <= repeat; j++)
			{
				ZnCenter[i + adj + j][0] = ZnCenter[i + adj][0];
				ZnCenter[i + adj + j][1] = ZnCenter[i + adj][1];
			}
			adj += repeat - 1;
		}
	}
	zn = zn +adj;
	p.init_flyys(YnCenter, ZnCenter, yn, zn);
	double seeprize=p.Prize_Func_commu(p.XY, p.XZ, Param_Communicate_Distance);
	seeprize = p.Prize_Func_global(p.XY, p.XZ, 0);
	int breakpoint;
	main_forPSO();
    std::cout << "Hello World!\n"; 
}

