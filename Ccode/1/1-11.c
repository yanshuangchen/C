#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void result(int List[], int i, int j) {
    printf("最大子序列是: ");
    for (int t = i; t <= j; t++) {
        printf("%d ", List[t]);
    }
    printf("\n");
}

int Max3(int A, int B, int C) {
    /* 返回3个数中的最大值 */
    return A > B ? (A > C ? A : C) : (B > C ? B : C);
}

int DivideAndConquer(int List[], int left, int right) {
    /* 分治法求解List[left]到List[right]的最大子序列和 */
    int MaxLeftSum, MaxRightSum; /* 左右两半的结果 */
    int MaxLeftBorderSum, MaxRightBorderSum; /*跨越左右两半的结果*/

    int LeftBorderSum, RightBorderSum;
    int center, i;

    if (left == right) { /* 递归的终止条件，只有1个元素的序列 */
        if (List[left] > 0)
            return List[left];
        else
            return 0;
    }

    /* 进行"分"的步骤 */
    center = (left + right) / 2; /* 找到中分点 */
    /* 递归求得两边的最大子序列和 */
    MaxLeftSum = DivideAndConquer(List, left, center);
    MaxRightSum = DivideAndConquer(List, center + 1, right);

    /* 下面求跨越分界线的最大子序列和 */
    MaxLeftBorderSum = 0;
    LeftBorderSum = 0;
    for (i = center; i >= left; i--) { /* 从中线向左扫描 */
        LeftBorderSum += List[i];
        if (LeftBorderSum > MaxLeftBorderSum)
            MaxLeftBorderSum = LeftBorderSum;
    } /* 左边扫描结束 */

    MaxRightBorderSum = 0;
    RightBorderSum = 0;
    for (i = center + 1; i <= right; i++) { /* 从中线向右扫描 */
        RightBorderSum += List[i];
        if (RightBorderSum > MaxRightBorderSum)
            MaxRightBorderSum = RightBorderSum;
    } /* 右边扫描结束 */

    /* 返回治结果 */
    return Max3(MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum);
}

int MaxSubseqSum1(int List[], int N) {
    int ThisSum, MaxSum = 0;
    int start = 0, end = 0;

    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            ThisSum = 0;
            for (int k = i; k <= j; k++) {
                ThisSum += List[k];
            }
            if (ThisSum > MaxSum) {
                MaxSum = ThisSum;
                start = i;
                end = j;
            }
        }
    }

    printf("最大子序列的和为 %d\n", MaxSum);
    result(List, start, end);

    return MaxSum;
}

int MaxSubseqSum2(int List[], int N) {
    int i, j;
    int ThisSum, MaxSum = 0;

    for (i = 0; i < N; i++) {
        ThisSum = 0;
        for (j = i; j < N; j++) {
            ThisSum += List[j];
            if (ThisSum > MaxSum)
                MaxSum = ThisSum;
        }
    }
    return MaxSum;
}

int MaxSubseqSum3( int List[], int N )
{ 
	return DivideAndConquer( List, 0, N-1 );
}

int MaxSubseqSum4( int List[], int N )
{
	int i;
	int ThisSum, MaxSum;

	ThisSum = MaxSum = 0;
	for ( i=0; i<N; i++ ) {
		ThisSum += List[i]; 
		if ( ThisSum > MaxSum )
			MaxSum = ThisSum;
		else if ( ThisSum < 0 )
			ThisSum = 0; 
	} 
	return MaxSum;
}

double getCurrentTime() {
    LARGE_INTEGER frequency;
    if (!QueryPerformanceFrequency(&frequency)) {
        printf("无法获取高精度计时器的频率。\n");
        return 0.0;
    }

    LARGE_INTEGER counter;
    if (!QueryPerformanceCounter(&counter)) {
        printf("无法获取高精度计时器的计数。\n");
        return 0.0;
    }

    return (double)counter.QuadPart / (double)frequency.QuadPart * 1000000.0;
}

int main() {
    FILE *fp;
    fp = fopen("s2.csv", "w");
    if (fp == NULL) {
        printf("无法创建文件。\n");
        return 1;
    }

    fprintf(fp, "N,Time_Algorithm2,Time_Algorithm3,Time_Algorithm4\n");
    
    int N_values[] = {1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
    int N_count = sizeof(N_values) / sizeof(N_values[0]);
    
    int a[10000]; // 假设数组大小为10000
    
    // 测试不同N值的性能
    for (int i = 0; i < N_count; i++) {
        int N = N_values[i];
        
        // 初始化数组
        for (int j = 0; j < N; j++) {
            a[j] = 1;
        }
        
        // double start_time_algo1 = getCurrentTime();
        // MaxSubseqSum1(a, N);
        // double end_time_algo1 = getCurrentTime();
        // double elapsed_time_algo1 = end_time_algo1 - start_time_algo1;

		double start_time_algo2 = getCurrentTime();
        MaxSubseqSum2(a, N);
        double end_time_algo2 = getCurrentTime();
        double elapsed_time_algo2 = end_time_algo2 - start_time_algo2;

		double start_time_algo3 = getCurrentTime();
        MaxSubseqSum3(a, N);
        double end_time_algo3 = getCurrentTime();
        double elapsed_time_algo3 = end_time_algo3 - start_time_algo3;

		double start_time_algo4 = getCurrentTime();
        MaxSubseqSum4(a, N);
        double end_time_algo4 = getCurrentTime();
        double elapsed_time_algo4 = end_time_algo4 - start_time_algo4;

        fprintf(fp, "%d,%.2f,%.2f,%.2f\n", N, elapsed_time_algo2, elapsed_time_algo3, elapsed_time_algo4);
    }
    
    fclose(fp);
    
    return 0;
}