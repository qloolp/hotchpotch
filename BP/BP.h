#ifndef _BP_
#define _BP_

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;


class BP
{
private:
	 
	int inNodeCount;                     //输入层节点数
	int midNodeCount;                    //隐藏层节点数
	int outNodeCount;                    //输出层节点数

	double** midWeight;                   //隐藏层权值
	double** outWeight;                   //输出层权值

	double** detaMidW;                     //隐藏层权值增量
	double** detaOutW;                     //输出层权值增量

	double* midThreshold;                 //隐藏层阈值
	double* outThreshold;                 //输出层阈值

	double error;                         //精度
	double studyRate;                     //学习效率
	double alpha;                         //动量

	double sigmoid(double x);             //传递函数：双曲正切函数
	double diffSigmoid(double x);         //传递函数导数
	double turn(double* in, double* out);
public:
	BP(int inc, int mnc, int onc);
	void normalize(double** data, int r, int c);
	void train(double** in, double** out, int size);
	void test(double** in, double** out, int size);
};

BP::BP(int inc, int mnc, int onc)
{
	inNodeCount = inc;
	midNodeCount = mnc;
	outNodeCount = onc;

	studyRate = 0.5;
	error = 0.0;
	alpha = 0.5;

	midWeight = new double*[midNodeCount];               //申请隐藏层权值存储空间
	detaMidW = new double*[midNodeCount];                 //申请隐藏层权值增量存储空间

	for(int i=0; i<midNodeCount; i++)
	{
		midWeight[i] = new double[inNodeCount];
		detaMidW[i] = new double[inNodeCount];
	}

	outWeight = new double*[outNodeCount];              //申请输出层权值存储空间
	detaOutW = new double*[outNodeCount];                //申请输出层权值增量存储空间
	for(int i=0; i<outNodeCount; i++)
	{
		outWeight[i] = new double[midNodeCount];
		detaOutW[i] = new double[midNodeCount];
	}

	midThreshold = new double[midNodeCount];            //申请隐藏层阈值存储空间
	outThreshold = new double[outNodeCount];            //申请输出层阈值存储空间


	srand(time(NULL));
	for(int i=0; i<midNodeCount; i++)
	{
		midThreshold[i] = 1;                    //初始化隐藏层阈值
		for(int j=0; j<inNodeCount; j++)
		{
			midWeight[i][j] = 2*rand()/RAND_MAX-1;                //初始化隐藏层权值
			detaMidW[i][j] = 0.0;
		}
	}

	for(int i=0; i<outNodeCount; i++)                           
	{
		outThreshold[i] = 1;                   //初始化输出层阈值
		for(int j=0; j<midNodeCount; j++)
		{
			outWeight[i][j] = 2*rand()/RAND_MAX;                 //初始化输出层权值
			detaOutW[i][j] = 0.0;
		}
	}
}


void BP::normalize(double** data, int r, int c)           //数据规整化：-a~a
{
	double max;
	double min;
	double b;
	double k;
	double a = 1;
	for(int i=0; i<c; i++)
	{
		max = data[0][i];
		min = data[0][i];
		for(int j=0; j<r; j++)
		{
			if(data[j][i]<min)
				min = data[j][i];
			if(data[j][i]>max)
				max = data[j][i];
		}

		for(int j=0; j<r; j++)
		{
			k = 2.0*a/(max-min);
			b = -a*(max+min)/(max-min);
			data[j][i] = data[j][i]*k+b;
		}
	}
}

double BP::sigmoid(double x)        //f(x)=a*tanh(b*x)         
{
	return  1.7159*tanh(2.0/3.0*x);
}

double BP::diffSigmoid(double x)       
{
	double a = 1.7159;
	double b = 2.0/3.0;
	return -a*b*(pow(tanh(b*x),2)-1);
}


double BP::turn(double* in, double* out)                               //in:输入数据，out:期望输出数据，返回值:单次训练误差
{
	double* inMid = new double[midNodeCount];                         //申请隐藏层神经元输入存储空间
	double* inOut = new double[outNodeCount];                         //申请输出层神经元输入存储空间          
	double* Omid = new double[midNodeCount];                          //申请隐藏层输出空间
	double* Oout = new double[outNodeCount];                          //申请输出层输出空间
	double* detaMid = new double[midNodeCount];                       //申请隐藏层梯度存储空间
	double* detaOut = new double[outNodeCount];                       //申请输出层梯度存储空间
	double e = 0.0;

	
	for(int i=0; i<midNodeCount; i++)                                 //计算隐藏层输出值
	{
		inMid[i] = 0.0;
		for(int j=0; j<inNodeCount; j++)
			inMid[i] += midWeight[i][j]*in[j];
		Omid[i] = sigmoid(inMid[i]-midThreshold[i]); 
	}

	for(int i=0; i<outNodeCount; i++)                                //计算输出层输出值
	{
		inOut[i] = 0.0;
		for(int j=0; j<midNodeCount; j++)
			inOut[i] += outWeight[i][j]*Omid[j];
		Oout[i] = sigmoid(inOut[i]-midThreshold[i]); 
	}


	for(int i=0; i<outNodeCount; i++)                               
	{
		detaOut[i] = (out[i]-Oout[i])*diffSigmoid(inOut[i]);                       //计算输出层梯度
	}

	for(int i=0; i<outNodeCount; i++)                               
	{
		for(int j=0; j<midNodeCount; j++)                          
		{
			detaOutW[i][j] = alpha*detaOutW[i][j]+studyRate*detaOut[i]*Omid[j];              //计算输出层权值增量
			outWeight[i][j] += detaOutW[i][j];                                               //更新输出层权值
		}
	}


	for(int i=0; i<midNodeCount; i++)                               //计算隐藏层梯度
	{
		detaMid[i] = 0.0;
		for(int j=0; j<outNodeCount; j++)
			detaMid[i] += detaOut[j]*outWeight[j][i];
		detaMid[i] *= diffSigmoid(in[i]);
	}

	for(int i=0; i<midNodeCount; i++)                              //更新隐藏层权值
	{
		for(int j=0; j<inNodeCount; j++)
		{
			detaMidW[i][j] = detaMidW[i][j]*alpha+studyRate*detaMid[i]*in[j];
			midWeight[i][j] += detaMidW[i][j];
		}
	}

	for(int i=0; i<outNodeCount; i++)
	{
		e += pow(out[i]-Oout[i],2);
	}
	e = 0.5*e;

	delete[] inMid;                      //释放空间
	delete[] inOut;
	delete[] Omid;
	delete[] Oout;
	delete[] detaMid;
	delete[] detaOut;

	return e;
}

void BP::train(double** in, double** out, int size)
{
	int times = 0;
	int MAX_TIMES = 200;               //最大训练次数

	error = 0.0;

	double* dataIn;
	double* dataOut;

	while(true)
	{

		for(int i=0; i<size; i++)
		{
			dataIn = in[i];
			dataOut = out[i];
			error += turn(dataIn, dataOut);
		}

		error *= 1.0/(double)size;                    //样本集均方误差
		cout<<"Times:"<<++times<<"   Error:"<<error<<endl;

		if(times>MAX_TIMES)
		{
			break;

		}
		else
		{
			error = 0.0;
		}

	}

	cout<<"Complete train!"<<endl;
}


void BP::test(double** in, double** out, int size)
{
	double* inMid = new double[midNodeCount];                         //申请隐藏层神经元输入存储空间
	double* inOut = new double[outNodeCount];                         //申请输出层神经元输入存储空间          
	double* Omid = new double[midNodeCount];                          //申请隐藏层输出空间


	for(int i=0; i<size; i++)
	{
		for(int j=0; j<midNodeCount; j++)                                 //计算隐藏层输出值
		{
			inMid[j] = 0.0;
			for(int k=0; k<inNodeCount; k++)
				inMid[j] += midWeight[j][k]*in[i][k];
			Omid[j] = sigmoid(inMid[j]-midThreshold[j]); 
		}

		for(int j=0; j<outNodeCount; j++)                                //计算输出层输出值
		{
			inOut[j] = 0.0;
			for(int k=0; k<midNodeCount; k++)
				inOut[j] += outWeight[j][k]*Omid[k];
			out[i][j] = sigmoid(inOut[j]-outThreshold[j]);
		}
	}

	delete[] inMid;
	delete[] inOut;
	delete[] Omid;
}


#endif

