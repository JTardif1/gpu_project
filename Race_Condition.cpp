#include <iostream>
#include <cstdlib>
#include <cmath>
#include <omp.h>
void main()
{
	int nthreads;
	int size = 123456;
	int mnt = omp_get_max_threads();
	float* a = new float[size];
	for (int i = 0; i < size; i++)
		a[i] = 1.0f;
	float mag = 0.0f;

	double start = omp_get_wtime();

#pragma omp parallel
	{
		int tid = omp_get_thread_num();
		int nt = omp_get_num_threads();
		if (tid == 0) nthreads = nt;
		float sum = 0.0f;
		for (int i = tid; i < size; i += nt)
		{
			sum += a[i] * a[i];
			//#pragma omp critical
			mag += sum;
		}
	}

	mag = std::sqrt(mag);
	std::cout << "mag = " << mag << "\n";
	std::cout << "num of threads = " << nthreads;
}