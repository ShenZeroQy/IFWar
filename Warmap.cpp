#include "pch.h"
#include "Warmap.h"
//**********global variables************/
std::default_random_engine rn;
//fstream fouter;



////////////***********fuc***//
bool compdis(dot a, dot b)
{
	return abs(a) < abs(b);
}
Warmap::Warmap()
{
}
void Warmap::Init_map(int a)
{
	
	for (int i = 0; i < Param_Y_Num; i++)
	{
		Y.push(Random_locate(Param_Area));
	}
	for (int i = 0; i < Param_Z_Num; i++)
	{
		Z.push(Random_locate(Param_Area));
	}
	ofstream out("./data/obj_locate.txt");
	if (out.is_open())
	{
		dot itery,iterz;
		for (int i = 0; i < Y.size(); i++)
		{
			itery = Y.front();
			iterz = Z.front();
			out << itery.real()<<"	"<<itery.imag()<<"	"<<iterz.real() << "	" << iterz.imag() << endl;
		
			Y.pop();
			Y.push(itery);
			Z.pop();
			Z.push(iterz);
		
		}
		out.close();
		cout << "generate object done" <<endl;
	}

	
	
	return;

}
double Warmap::distance(dot a, dot b)
	{
		dot c = a - b;
		return abs(c);
	}
dot Warmap::Random_locate(int bound)
{
	double x, y;
	std::uniform_real_distribution<double> dis(-bound, bound);	
	dot c;
	c.real(dis(rn));
	c.imag(dis(rn));
	//cout << c << endl;
	return  c;
}
Warmap::~Warmap()
{

}
