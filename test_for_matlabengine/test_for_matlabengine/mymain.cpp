//�������MATLAB���溯��
#include<engine.h>
#include<iostream>
#include<omp.h>

using std::cout;
using std::endl;
using std::cin;

int main()
{
	
	
	const int N = 50;

	double x[N], y[N];

	int j = 1;
#pragma omp parallel
	{
#pragma omp for
		for (int i = 0; i < N; i++)

		{

			x[i] = (i + 1);

			y[i] = sin(x[i]) + j * log(x[i]); // ������֮������������ xx[i];

			j *= -1;
			
		}

	}
	Engine *ep; // ���� Matlab ����ָ�롣

	if (!(ep = engOpen(NULL))) // �����Ƿ����� Matlab ����ɹ���

	{

		cout << "Can't start Matlab engine!" << endl;

		exit(1);

	}

	// ���� mxArray ��Ϊ�У� N �е�ʵ�����顣

	mxArray *xx = mxCreateDoubleMatrix(1, N, mxREAL);

	mxArray *yy = mxCreateDoubleMatrix(1, N, mxREAL); // ͬ�ϡ�

	memcpy(mxGetPr(xx), x, N*sizeof(double)); // ������ x ���Ƶ� mxarray ���� xx �С�

	memcpy(mxGetPr(yy), y, N*sizeof(double)); // ������ x ���Ƶ� mxarray ���� yy �С�

	engPutVariable(ep, "xx", xx); // �� mxArray ���� xx д�뵽 Matlab �����ռ䣬����Ϊ xx ��

	engPutVariable(ep, "yy", yy); // �� mxArray ���� yy д�뵽 Matlab �����ռ䣬����Ϊ yy ��

	// �� Matlab ���淢�ͻ�ͼ��� plot Ϊ Matlab �Ļ�ͼ�������μ� Matlab ����ĵ���

	engEvalString(ep, "plot(xx, yy); ");

	mxDestroyArray(xx); // ���� mxArray ���� xx �� yy ��

	mxDestroyArray(yy);

	cout << "Press any key to exit!" << endl;

	cin.get();

	engClose(ep); // �ر� Matlab ���档

	//engClose(p);
}