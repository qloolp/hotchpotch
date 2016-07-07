#include "BP.h"
#include <iomanip>
#include <fstream>
using namespace std;





int main()
{
	int size = 85;                   //训练集样本数
	int ts = 15;                     //测试集样本数

	int inNode = 4;
	int midNode = 10;
	int outNode = 1;

	int indexA;
	int indexB;




	ifstream ft("train.txt");
	ifstream fs("test.txt");
	BP bp = BP(inNode,midNode,outNode);              
	
	double** srcIn = new double*[size];
	double** srcOut = new double*[size];
	double** result = new double*[size];
	double temp;


	for(int i=0; i<size; i++)
	{
		srcIn[i] = new double[inNode];
		srcOut[i] = new double[outNode];
		result[i] = new double[outNode];
		for(int j=0; j<inNode; j++)
			ft>>srcIn[i][j];
		for(int j=0; j<outNode; j++)
			ft>>srcOut[i][j];
	}
	ft.close();


	bp.normalize(srcIn,size,inNode);
	bp.normalize(srcOut,size,outNode);



	//随机化样本顺序
	  
	srand(time(NULL));
	for(int i=0; i<size; i++)
	{
		indexA = rand()%size;
		indexB = rand()%size;
		for(int i=0; i<inNode; i++)
		{
			temp = srcIn[indexA][i];
			srcIn[indexA][i] = srcIn[indexB][i];
			srcIn[indexB][i] = temp;
		}
		temp = srcOut[indexA][0];
		srcOut[indexA][0] = srcOut[indexB][0];
		srcOut[indexB][0] = temp;
	}


	bp.train(srcIn,srcOut,size);


	for(int i=0; i<ts; i++)
	{
		for(int j=0; j<inNode; j++)
			fs>>srcIn[i][j];
		for(int j=0; j<outNode; j++)
			fs>>srcOut[i][j];

	}
	fs.close();

	bp.normalize(srcIn,ts,inNode);
	bp.normalize(srcOut,ts,outNode);



	bp.test(srcIn,result,ts);

	for(int i=0; i<ts; i++)
	{
		if(result[i][0]<0.0)
			cout<<-1<<endl;
		else
			cout<<1<<endl;
	}

	cin.get();
	return 0;
}