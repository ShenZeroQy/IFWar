#pragma once
#include"base.h"
bool compdis(dot a, dot b);

class flyy
{
public:
	flyy() 
	{
	}
	;
	void flyy_init(double d,double prize_fac,int max_carry)
	{
		max_c = max_carry;
		interfacedis = d;
		prize = prize_fac;
	}
	;
	~flyy() 
	{}
	;
	dot center;
	vector<dot> child;
	bool mount_child(dot c)
	{
		if (carrier >= max_c)
		{
			return 0;
		}
		else
		{
			child.push_back(c);
			carrier = child.size();			
			return 1;
		}
	}
	void sort_child()
	{
		for (int i = 0; i < carrier; i++)
		{
			child[i] -= center;
		}
		sort(child.begin(), child.end(),compdis);
			for (int i = 0; i < carrier; i++)
			{
				child[i] += center;
			}
	}
	
	
	int carrier;
	double prize;

	double interfacedis;
	int max_c;
private:
};

class Monitor
{
public:
	Monitor()
	{}
	/*void Monitor_init(Warmap& map)
	{
		M = map;

		for (int i = 0; i < Param_Y_Num; i++)
		{

		}
	}*/
	;
	~Monitor()
	{}
	;
	
	
	
	//int Xyi_count[Param_Max_X];
	//int Xyi_r[Param_Max_X];
	//int Xzi_count[Param_Max_X];
	//int Xzi_r[Param_Max_X];
	int Z_slol[Param_Z_Num];
	int Y_slol[Param_Y_Num];
	queue<dot> local_Y;
	queue<dot> local_Z;
};
class Warmap
{
public:
	Warmap();
	void Init_map(int);
	~Warmap();
	vector<flyy> XY;
	vector<flyy> XZ;
	vector<dot> X;
	vector<dot> DetX;

	void init_flyys(double ceny[][2], double cenz[][2], int yn, int zn)
	{
		XY.clear();
		XZ.clear();
		flyy newfly;
		//dot tocomplex;
		for (int i = 0; i < yn; i++)
		{
			newfly.flyy_init(Param_Interference_Distance, Param_Y_prize, Param_Interference_Max_enhance_count);
			dot tocomplex(ceny[i][0], ceny[i][1]);
			newfly.center = tocomplex;
			XY.push_back(newfly);
		}
		for (int j = 0; j < zn; j++)
		{
			newfly.flyy_init(Param_Interference_Distance, Param_Z_prize, Param_Interference_Max_disturb_count);
			dot tocomplex(cenz[j][0], cenz[j][1]);
			newfly.center = tocomplex;
			XZ.push_back(newfly);
		}
		cout << "init flys done";
	}
	double distance(dot, dot);
	double Prize_Func_commu(vector<flyy> y, vector<flyy> z, double commu_dis)
	{
		double cost = 0;
		vector<flyy>::const_iterator citer;
		vector<flyy>::const_iterator jiter;
		vector<flyy> flys(y);
		for(citer = z.begin(); citer != z.end(); citer++)
			flys.push_back(*citer);
		for (citer = flys.begin(); citer != flys.end(); citer++)
		{
			double mind = 2*commu_dis;
			for (jiter = flys.begin(); jiter != flys.end(); jiter++)
			{
				
				if (citer != jiter)
				{

					double dis = distance(citer->center, jiter->center);
					if (dis < mind)
						mind = dis;
				}
				
			}
			mind -= commu_dis;
			if (mind > 0)
			{
				cost += mind;
			}
		}
		return cost;
	}
	double Prize_Func_global(vector<flyy> y, vector<flyy> z,int flag)
	{
		double prize;
		int yn = y.size();
		int zn = z.size();
		if (flag == 0)
		{
			dot iter;
			int i,j;
			vector<flyy>::const_iterator citer;
			queue<dot> restY(Y);
			queue<dot> restZ(Z);
			queue<dot> rest;
			for (i=0;i<yn;i++)
			{
				y[i].child.clear();
				y[i].carrier = 0;
			}
			for (i = 0; i < zn; i++)
			{
				z[i].child.clear();
				z[i].carrier = 0;
			}
			while (!restY.empty())
			{
				iter = restY.front();
				restY.pop();
				bool mount_flag = 0;
				for (i = 0; i < yn; i++)
				{
					double dis = distance(iter, y[i].center);
					if (dis < y[i].interfacedis)
					{
						if (y[i].mount_child(iter))
						{
							mount_flag = 1;
							break;
						}
					}

				}
				if (!mount_flag)//fail
				{
					rest.push(iter);
				}
			}
			int breakpoint;
			while (!restZ.empty())
			{
				iter = restZ.front();
				restZ.pop();
				bool mount_flag = 0;
				for (i = 0; i < zn; i++)
				{
					double dis = distance(iter, z[i].center);
					if (dis < z[i].interfacedis)
					{
						if (z[i].mount_child(iter))
						{
							mount_flag = 1;
							break;
						}
					}

				}
				if (!mount_flag)//fail
				{
					rest.push(iter);
				}
			}
			prize = 0;
			for (i = 0; i < yn; i++)
				prize +=y[i].carrier*y[i].prize;
			for (i = 0; i < zn; i++)
				prize +=z[i].carrier*z[i].prize;
			cout << "未分配：" << rest.size();

		}
		
		return prize;
	}
	/*double Prize_Func(vector<dot>& in, dot one_p, double area)
	{
		double prize = 0;
		for (int i = 0; i < in.size(); i++)
		{
			double dist= abs(in[i]-one_p);
			if (dist < area)
			{
				prize += 1;
			}
			
		}
		
		return prize;
	}*/
	/**For PSO*****************************/
	//double Prize_func(ZPSO_Partical& partical)
	//{
	//	return 0;
	//}
	//int PSOsolve(int curr)
	//{
	//	
	//	//pso._fitnessFunction = FitFuncPointer(Prize_func);
	//	//运行pso算法
	//	ZPSO_Partical bestPartical; //粒子群最终进化结果
	//}
	//

protected:
	queue<dot> Y;
	queue<dot> Z;
	dot Random_locate(int bound);
	
	/**For PSO***/
	//double minPos[2] = { -10,-10 };
	//double maxPos[2] = { 10,10 };
	////定义问题描述参数
	//int dimension = 2; //候选解维度
	//int particalCount = 200; //粒子群粒子个数
	//double globalGuideCoe = 1; //全局引导加速度
	//double localGuideCoe = 1; //局部引导加速度
	//double maxSpeed = 4; //粒子最大速度
};

