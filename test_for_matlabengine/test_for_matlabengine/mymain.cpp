//测试相关MATLAB引擎函数
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

			y[i] = sin(x[i]) + j * log(x[i]); // 产生－之间的随机数赋给 xx[i];

			j *= -1;
			
		}

	}
	Engine *ep; // 定义 Matlab 引擎指针。

	if (!(ep = engOpen(NULL))) // 测试是否启动 Matlab 引擎成功。

	{

		cout << "Can't start Matlab engine!" << endl;

		exit(1);

	}

	// 定义 mxArray ，为行， N 列的实数数组。

	mxArray *xx = mxCreateDoubleMatrix(1, N, mxREAL);

	mxArray *yy = mxCreateDoubleMatrix(1, N, mxREAL); // 同上。

	memcpy(mxGetPr(xx), x, N*sizeof(double)); // 将数组 x 复制到 mxarray 数组 xx 中。

	memcpy(mxGetPr(yy), y, N*sizeof(double)); // 将数组 x 复制到 mxarray 数组 yy 中。

	engPutVariable(ep, "xx", xx); // 将 mxArray 数组 xx 写入到 Matlab 工作空间，命名为 xx 。

	engPutVariable(ep, "yy", yy); // 将 mxArray 数组 yy 写入到 Matlab 工作空间，命名为 yy 。

	// 向 Matlab 引擎发送画图命令。 plot 为 Matlab 的画图函数，参见 Matlab 相关文档。

	engEvalString(ep, "plot(xx, yy); ");

	mxDestroyArray(xx); // 销毁 mxArray 数组 xx 和 yy 。

	mxDestroyArray(yy);

	cout << "Press any key to exit!" << endl;

	cin.get();

	engClose(ep); // 关闭 Matlab 引擎。

	//engClose(p);
}