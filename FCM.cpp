#include"pch.h"
#include"FCM.h"
//#include<iostream>
//#include<cstdio>
//#include<vector>
//#include<fstream>
//#include<cmath>
//#include<ctime>
//#include<cstdlib>
//using namespace std;
//struct Mode
//{
//	int x, y;
//	int di;
//	vector<double> datas;
//};
//typedef vector<vector<Mode> > ModeVec;
//const int N = 1000;
//const double eps = 1e-2;
//const double eps_dis = 1e-6;
//
//double getDistance(Mode &m1, Mode &m2);
//void FCM(Mode *sample_y, int samplenum, int di, int clusternum, vector<vector<Mode> > &ans);
//void init_c(Mode *sample_y, int samplenum, int clusternum, Mode *c);
//void comp_dis(Mode *sample_y, Mode *c, int samplenum, int clusternum, double dis[][10]);
//void comp_u(double dis[][10], int samplenum, int clusternum, double u[][10]);
//void update_c(Mode *sample_y, double u[][10], int samplenum, int clusternum, Mode *c);
//double comp_obj_func(double u[][10], double dis[][10], int samplenum, int clusternum, int di);



ifstream objin("./data/obj_locate.txt");
ofstream fcmobjout("./data/obj_fcm.txt");
ofstream fcmresult("./data/obj_fcm_result.txt");
/**************global variables********/
vector<vector<Mode> > ans;
Mode Rem_f_c[Pre_c]; //��������
Mode Rem_e_c[Pre_c]; //��������
double Rem_f_u[N][Pre_c];  //�����Ⱦ���
double Rem_e_u[N][Pre_c];  //�����Ⱦ���

Mode c[Pre_c]; //��������
double u[N][Pre_c];  //�����Ⱦ���

int main_forFCM(int yn ,int zn)
{
	int samplenum, dim, clusternum;
	Mode sample_y[Pre_n];
	Mode sample_z[Pre_n];	
	// >> samplenum >> dim >> clusternum;  //��ĸ�����ά�ȣ�������Ŀ
	//cin  >> clusternum;  //���������Ŀ
	clusternum = yn;
	dim = 2;//ά��
	samplenum = Param_Y_Num;
	if (!objin.is_open())
		cout << "no dot file ";
	for (int i = 0; i < samplenum; i++)
	{
		sample_y[i].di = dim;
		sample_z[i].di = dim;
		double temp;
		for (int j = 1; j < dim; j++)
		{
			
			objin >> temp;
			cout << "  load:" << temp;
			sample_y[i].datas.push_back(temp);
			objin >> temp;
			cout << "load:" << temp;
			sample_y[i].datas.push_back(temp);
			objin >> temp;
			cout << "load:" << temp;
			sample_z[i].datas.push_back(temp);
			objin >> temp;
			cout << "load:" << temp;
			sample_z[i].datas.push_back(temp);
			cout << endl;
		}
	}
	if (!fcmobjout.is_open())
		fcmobjout.open("./data/obj_fcmme.txt");
		//init_c(p, n, clusternum, c);
	FCM(sample_y, samplenum, dim, clusternum, ans);
	fcmobjout.close();
	//��������sample_y����samplenum���㣬ά��Ϊdim�����������ans
	//for (int i = 0; i < clusternum; i++)
	//{
	//	fcmobjout<<("��%d�ࣺ\n", i + 1);
	//	for (int j = 0; j < ans[i].size(); j++)
	//	{
	//		fcmobjout<<("(");
	//		for (int k = 0; k < dim; k++)
	//		{
	//			if (k == 0) fcmobjout<<("%f", ans[i][j].datas[k]);
	//			else fcmobjout<<(",%f", ans[i][j].datas[k]);
	//		}
	//		fcmobjout<<(") ");
	//	}
	//	fcmobjout<<("\n");
	//}
	for (int i = 0; i < clusternum; i++)
	{
		Rem_f_c[i] = c[i];
		for (int j = 0; j < samplenum; j++)
		{
			Rem_f_u[j][i] = u[j][i];
		}
	}
	cout << "curry on";
	//cin >> clusternum;
	clusternum = zn;
	if (!fcmobjout.is_open())
		fcmobjout.open("./data/obj_fcmyou.txt");
	FCM(sample_z, samplenum, dim, clusternum, ans);
	return 0;
}
double getDistance(Mode &m1, Mode &m2)
{
	int di = m1.di;
	double ans = 0;
	for (int i = 0; i < di; i++)
		ans += (m1.datas[i] - m2.datas[i])*(m1.datas[i] - m2.datas[i]);
	return sqrt(ans);
}
void init_c(Mode *p, int n, int clusternum, Mode *c) //��ʼ����������
{
	int di = p[0].di;
	srand(time(NULL));
	for (int i = 0; i < clusternum; i++)
	{
		c[i].di = di;
		c[i].datas.clear();
		for (int j = 0; j < di; j++)
			c[i].datas.push_back(0);
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < di; j++)
			for (int k = 0; k < clusternum; k++)
				c[k].datas[j] += p[i].datas[j];
	for (int i = 0; i < clusternum; i++)
	{
		for (int j = 0; j < di; j++)
		{
			int tp = rand() % n + 1;
			c[i].datas[j] /= tp;
		}
	}
}
void comp_dis(Mode *p, Mode *c, int n, int clusternum, double dis[][Pre_c]) //��ʼ��ÿ�����ÿ���صľ���
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < clusternum; j++)
			dis[i][j] = getDistance(p[i], c[j]);
}
void comp_u(double dis[][Pre_c], int n, int clusternum, double u[][Pre_c], int* Cnt)  //���������Ⱦ���
{
	for (int i = 0; i < n; i++)
	{
		double tp = 0;
		for (int j = 0; j < clusternum; j++)
		{
			//if (dis[i][j] < eps_dis)  //��������ܽӽ�һ���������ģ���ô�����������Ϊ1������Ϊ0
			
			if (dis[i][j] < -1) {
				for (int k = 0; k < clusternum; k++)
					u[i][k] = 0;
				u[i][j] = 1;
				return;
			}
			u[i][j] = (1 / dis[i][j]/dis[i][j]);
		/*	if(dis[i][j]>Param_Interference_Distance)
				u[i][j] = (Param_Interference_Distance / dis[i][j]);
			else
				u[i][j] = 2- dis[i][j]/Param_Interference_Distance ;
		*/
		//u[i][j] /= sqrt(sqrt(2+Cnt[j]));
		//��ͼ�������ھ������Լ��پۼ�
			tp += u[i][j];

		}
		tp = 1 / tp;
		for (int j = 0; j < clusternum; j++)
			u[i][j] = tp * u[i][j];
	}
}
void update_c(Mode *p, double u[][Pre_c], int n, int clusternum, Mode *c)
{
	
	int di = p[0].di;
	for (int j = 0; j < clusternum; j++)
	{
		c[j].di = di;
		c[j].datas.clear();
		for (int i = 0; i < di; i++)
			c[j].datas.push_back(0);
		double tp = 0;
		for (int i = 0; i < n; i++)
		{
			for (int k = 0; k < di; k++)
				c[j].datas[k] += u[i][j] * u[i][j] * p[i].datas[k];
			tp += u[i][j] * u[i][j];
		}
		for (int k = 0; k < di; k++)
			c[j].datas[k] /= tp;
	}
}
double comp_obj_func(double u[][Pre_c], double dis[][Pre_c], int n, int clusternum, int di)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < clusternum; j++)
			sum += u[i][j] * u[i][j] * dis[i][j];
	return sum;
}
void FCM(Mode *p, int n, int di, int clusternum, vector<vector<Mode> > &ans)        //in: samplenum,d,c       time:O(c*samplenum*d) ʱ�临�Ӷ�=������*����*ά��
{
	int index = 0;
	double sum = 0, psum;
	//Mode c[Pre_c]; //��������
	double dis[N][Pre_c]; //����
	//double u[N][Pre_c];  //�����Ⱦ���
	double R[Pre_c];//��������ȵ��д洢����С����,R�м�¼��ǰ��������
	int Cnt[Pre_c] = { 0 };
	
	init_c(p, n, clusternum, c); // ��ʼ����������  time: O(c)
	comp_dis(p, c, n, clusternum, dis); //���¾������dis
	while (1)
	{
		index++;
		fcmobjout<<"��"<<index<<"��ѭ��----------------------------------------\n" ;
		comp_u(dis, n, clusternum, u,Cnt);  //���������Ⱦ���u  time:O(samplenum*c);
		for (int i = 0; i < n; i++)
		{
			if(i%2==1)//ÿ2�����һ��
			{
				fcmobjout<<"��"<< i + 1 <<"���������ֵ\n" ;
				for (int j = 0; j < clusternum; j++)
				{
					fcmobjout<< u[i][j]<<"	";
				}
				fcmobjout<<endl; 
			}
		}
		update_c(p, u, n, clusternum, c);   //���¾������� time:O(c*(2*d+(samplenum*d))) = O(c*samplenum*d)
		comp_dis(p, c, n, clusternum, dis); //���¼���������

		//compute R and num
		int indexm ;
		double tpm ;
		//int indexr;
		//double tpr;
		for (int j = 0; j < clusternum; j++)
		{
			Cnt[j] = 0;
		}
		for (int i = 0; i < clusternum; i++)
		{
			R[i] = -1;
		}
		for (int i = 0; i < n; i++)
		{
			indexm = -1;
			tpm = -1;
			for (int j = 0; j < clusternum; j++)
			{
				if (u[i][j] > tpm)
				{
					tpm = u[i][j];
					indexm = j;
					//������Ŷ���
				}
			}
			Cnt[indexm] += 1;
			if (R[indexm] < dis[i][indexm])
			{
				R[indexm] = dis[i][indexm];//���ÿһ�����������
			}
		}
		for (int j = 0; j < clusternum; j++)
		{
			fcmobjout<<"����"<<j<<"����:��"<<c[j].datas[0]<<"	"<< c[j].datas[1]<<");	";
			fcmobjout<<"R="<< R[j] <<" ;count="<<Cnt[j]<<endl;
		}
		//compute R and num done
		psum = sum;
		sum = comp_obj_func(u, dis, n, clusternum, di);
	fcmobjout<<"����Ȩ��="<< sum<<endl;
	
	if (fabs(psum - sum) < eps)
	{
		fcmobjout << "�������"<<endl;
		break;
	}
	}
	ans.clear();
	for (int j = 0; j < clusternum; j++)
	{
		fcmresult <<  c[j].datas[0] << "	" << c[j].datas[1] << "		"<<R[j]<<"	"<<Cnt[j]<<endl;
	}
	for (int i = 0; i < clusternum; i++)
	{
		vector<Mode> m;
		ans.push_back(m);
	}
	for (int i = 0; i < n; i++)
	{
		double tp = -1;
		int index = 0;
		for (int j = 0; j < clusternum; j++)
			{
			if (u[i][j] > tp)
			{
				tp = u[i][j];
				index = j;
			}
		}
		ans[index].push_back(p[i]);
	}
}