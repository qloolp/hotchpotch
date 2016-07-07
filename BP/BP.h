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
	 
	int inNodeCount;                     //�����ڵ���
	int midNodeCount;                    //���ز�ڵ���
	int outNodeCount;                    //�����ڵ���

	double** midWeight;                   //���ز�Ȩֵ
	double** outWeight;                   //�����Ȩֵ

	double** detaMidW;                     //���ز�Ȩֵ����
	double** detaOutW;                     //�����Ȩֵ����

	double* midThreshold;                 //���ز���ֵ
	double* outThreshold;                 //�������ֵ

	double error;                         //����
	double studyRate;                     //ѧϰЧ��
	double alpha;                         //����

	double sigmoid(double x);             //���ݺ�����˫�����к���
	double diffSigmoid(double x);         //���ݺ�������
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

	midWeight = new double*[midNodeCount];               //�������ز�Ȩֵ�洢�ռ�
	detaMidW = new double*[midNodeCount];                 //�������ز�Ȩֵ�����洢�ռ�

	for(int i=0; i<midNodeCount; i++)
	{
		midWeight[i] = new double[inNodeCount];
		detaMidW[i] = new double[inNodeCount];
	}

	outWeight = new double*[outNodeCount];              //���������Ȩֵ�洢�ռ�
	detaOutW = new double*[outNodeCount];                //���������Ȩֵ�����洢�ռ�
	for(int i=0; i<outNodeCount; i++)
	{
		outWeight[i] = new double[midNodeCount];
		detaOutW[i] = new double[midNodeCount];
	}

	midThreshold = new double[midNodeCount];            //�������ز���ֵ�洢�ռ�
	outThreshold = new double[outNodeCount];            //�����������ֵ�洢�ռ�


	srand(time(NULL));
	for(int i=0; i<midNodeCount; i++)
	{
		midThreshold[i] = 1;                    //��ʼ�����ز���ֵ
		for(int j=0; j<inNodeCount; j++)
		{
			midWeight[i][j] = 2*rand()/RAND_MAX-1;                //��ʼ�����ز�Ȩֵ
			detaMidW[i][j] = 0.0;
		}
	}

	for(int i=0; i<outNodeCount; i++)                           
	{
		outThreshold[i] = 1;                   //��ʼ���������ֵ
		for(int j=0; j<midNodeCount; j++)
		{
			outWeight[i][j] = 2*rand()/RAND_MAX;                 //��ʼ�������Ȩֵ
			detaOutW[i][j] = 0.0;
		}
	}
}


void BP::normalize(double** data, int r, int c)           //���ݹ�������-a~a
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


double BP::turn(double* in, double* out)                               //in:�������ݣ�out:����������ݣ�����ֵ:����ѵ�����
{
	double* inMid = new double[midNodeCount];                         //�������ز���Ԫ����洢�ռ�
	double* inOut = new double[outNodeCount];                         //�����������Ԫ����洢�ռ�          
	double* Omid = new double[midNodeCount];                          //�������ز�����ռ�
	double* Oout = new double[outNodeCount];                          //�������������ռ�
	double* detaMid = new double[midNodeCount];                       //�������ز��ݶȴ洢�ռ�
	double* detaOut = new double[outNodeCount];                       //����������ݶȴ洢�ռ�
	double e = 0.0;

	
	for(int i=0; i<midNodeCount; i++)                                 //�������ز����ֵ
	{
		inMid[i] = 0.0;
		for(int j=0; j<inNodeCount; j++)
			inMid[i] += midWeight[i][j]*in[j];
		Omid[i] = sigmoid(inMid[i]-midThreshold[i]); 
	}

	for(int i=0; i<outNodeCount; i++)                                //������������ֵ
	{
		inOut[i] = 0.0;
		for(int j=0; j<midNodeCount; j++)
			inOut[i] += outWeight[i][j]*Omid[j];
		Oout[i] = sigmoid(inOut[i]-midThreshold[i]); 
	}


	for(int i=0; i<outNodeCount; i++)                               
	{
		detaOut[i] = (out[i]-Oout[i])*diffSigmoid(inOut[i]);                       //����������ݶ�
	}

	for(int i=0; i<outNodeCount; i++)                               
	{
		for(int j=0; j<midNodeCount; j++)                          
		{
			detaOutW[i][j] = alpha*detaOutW[i][j]+studyRate*detaOut[i]*Omid[j];              //���������Ȩֵ����
			outWeight[i][j] += detaOutW[i][j];                                               //���������Ȩֵ
		}
	}


	for(int i=0; i<midNodeCount; i++)                               //�������ز��ݶ�
	{
		detaMid[i] = 0.0;
		for(int j=0; j<outNodeCount; j++)
			detaMid[i] += detaOut[j]*outWeight[j][i];
		detaMid[i] *= diffSigmoid(in[i]);
	}

	for(int i=0; i<midNodeCount; i++)                              //�������ز�Ȩֵ
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

	delete[] inMid;                      //�ͷſռ�
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
	int MAX_TIMES = 200;               //���ѵ������

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

		error *= 1.0/(double)size;                    //�������������
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
	double* inMid = new double[midNodeCount];                         //�������ز���Ԫ����洢�ռ�
	double* inOut = new double[outNodeCount];                         //�����������Ԫ����洢�ռ�          
	double* Omid = new double[midNodeCount];                          //�������ز�����ռ�


	for(int i=0; i<size; i++)
	{
		for(int j=0; j<midNodeCount; j++)                                 //�������ز����ֵ
		{
			inMid[j] = 0.0;
			for(int k=0; k<inNodeCount; k++)
				inMid[j] += midWeight[j][k]*in[i][k];
			Omid[j] = sigmoid(inMid[j]-midThreshold[j]); 
		}

		for(int j=0; j<outNodeCount; j++)                                //������������ֵ
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

