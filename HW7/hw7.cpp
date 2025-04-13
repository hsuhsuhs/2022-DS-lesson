//Author：徐曉汎 學號：B102040019
//Date :Nov.16,2022
//Purpose：測試五種排序(sorting)演算法的執行效率
/*/// ------------------------------------------------------------------------------------
19
2,1,2
2. insertion sort
1. heap sort
2. radix sort
/*/// ------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <iomanip>


//
// =========================================================
// 二值交換
void swap(  size_t *arr , int a, int b)
{
	size_t temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void swap(  size_t &a, size_t &b)
{
	size_t temp = a ;
	a = b ;
	b = temp;
}

// ======================================================================
// heap tree
void Heapify(size_t a[],int size, int root)
{
    int largest=root; //設root為最大
    int l=2*root+1; //left child=2*root+1
    int r=2*root+2; //right child=2*root+2
 
    //if left child > root
    if(l<size&&a[l]>a[largest])
        largest=l;

    //if right child > 目前最大值
    if(r<size&&a[r]>a[largest])
        largest=r;
 
    // If largest 不是 root
    if(largest!=root)
    {
        swap(a[root],a[largest]); //將最大值與root互換
        Heapify(a,size, largest); //recursive
    }
}

//heap sort
void Heapsort(size_t a[],int size)
{
    // Build heap
    for(int i=size/2-1;i>=0;i--)
        Heapify(a,size, i);

    for (int i=size-1;i>0;i--)
    {
        swap(a[0],a[i]); //將heap正確位置與最末位交換
        Heapify(a,i,0);
    }
}
//

// ======================================================================
// 插入排序法
void InsertionSort( size_t s[] , int size)
{
	int i, j, key;

	for(i=1;i<size;i++)
	{
		key=s[i];
		j=i-1; //前後比較
		while(key<s[j]&&j>=0) //後面的數比較小進行互換
		{
			s[j+1]=s[j];
			j--;
		}
		s[j+1]=key;
	}
}

//======================================================================
//找陣列a中的最大值
size_t GetMax(size_t a[], int size)
{
	int i ;
	size_t max=a[0]; //設a[0]為最大值
    for( i=1;i<size;i++) //用迴圈找到最大值
        if(a[i]>max)
            max=a[i];
    return max;
}

//由個位數開始排序至最高位數
void CountSort(size_t a[],size_t size,size_t exp) //exp=10的i次方
{  
	size_t *result = new size_t[size]  ;
	int i , count[12]={0};
    //計算數字出現次數
    for(i=0;i<size;i++)
        count[(a[i]/exp)%10]++;
    //更改位置
    for(i=1;i<10;i++)
        count[i]+=count[i-1];
 
    //最後輸出的位置
    for(i=size-1;i>=0;i--)
    {
        result[count[(a[i]/exp)%10]-1]=a[i];
        count[(a[i]/exp)%10]--;
    }
    for (i =0;i<size;i++)
        a[i]=result[i];

	delete result;
}

// ======================================================================
// GetMax
void RadixSort(size_t a[], int size)
{
    size_t exp,i;
    i=GetMax(a,size);
    for( exp = 1 ;( i/exp )>0; ( exp*=10) )
        CountSort(a,size,exp);
}

//
void randBuf( size_t *buf , size_t bufSize )
{
	size_t i ;
	for( i = 0 ; i < bufSize ; ++i )
		buf[i] = rand() + ( rand() << 16 );
}

// 印，最多只印 20 個--->印太多會跑很久，想說跑 20 用來確認sort的完整性
void printfBuf( size_t *buf , size_t bufSize )
{
	size_t i ;
	if( bufSize > 20 )
		bufSize = 20 ;
	for( i = 0 ; i < bufSize ; ++i )
		printf( "\n%12u" , buf[i] );
	printf("\n" );
}

// ==================================================================
// c qsort
int compare(const void *a, const void *b)//這函式是 qsort 所需的比較函式
{
	size_t c = *(size_t *)a;
	size_t d = *(size_t *)b;
	if(c < d) {return -1;}//傳回 -1 代表 a < b
	else if (c == d) {return 0;} //傳回   0 代表 a = b
	else return 1;  //傳回  1 代表 a>b
}
// ==================================================================
// output
void outputFile( const char *sortName ,  size_t *buf , int count )
{
	int i ;
	char fileName[1024] ;
	sprintf( fileName , "%s-%d.txt" , sortName , count );
	FILE * output = fopen( fileName , "w" );
	fprintf( output , "%s\n" , sortName );
	for( i = 0 ; i < count ; ++i )
		fprintf( output , "%u\n" , buf[i] );
	fclose( output );
}
// ==================================================================
// 排序
int runSort( size_t *outData , size_t *inValue , size_t bufSize )
{
	clock_t  clockBegin, clockEnd;  
	size_t i ;
	//   size_t bufSize = 100000 ;
	size_t *buf = (size_t*)malloc( sizeof( size_t ) * bufSize );

	// 1. 印要排序的資料
	printf("\n\n" );
	printf( " -----------------------------------------------------------\n\n\n" );
	printf( "run sort buf Size: %u\n " , bufSize );


	printf( "sort value buffer : " );
	printfBuf( inValue, bufSize );

	//
	// =================================================
	// 2. InsertionSort
	// a. 複製要排虧的資料
	memcpy( buf , inValue , sizeof( size_t )*bufSize );
	// b. 記錄開始時間
	clockBegin = clock();
	printf("\n" );
	printf( "InsertionSort start: %u ..." , clockBegin ) ;
	// c. 排序
	InsertionSort( buf , bufSize );
	// d. 取結束時間
	clockEnd = clock();  
	outData[0] =  clockEnd -  clockBegin ;
	// e. 記算結果
	printf( " down:%u, runTime = %u\n ", clockEnd , clockEnd -  clockBegin ) ;
	// f. 印排序後的數值(只印20 個)
	printfBuf( buf, bufSize );
	// g. 輸出成檔案
	outputFile( "InsertionSort" , buf , bufSize );
	//
	// =================================================
	// 3. Heapsort
	memcpy( buf , inValue , sizeof( size_t )*bufSize );
	clockBegin = clock();
	printf("\n" );
	printf( "Heapsort start: %u ..." , clockBegin ) ;
	size_t *bufTemp = (size_t*)malloc( sizeof( size_t ) * bufSize );
	Heapsort( buf , bufSize );
	free( bufTemp );
	clockEnd = clock();
	outData[1] =  clockEnd -  clockBegin ;
	printf( " down:%u, runTime = %u\n ", clockEnd , clockEnd -  clockBegin ) ;
	printfBuf( buf, bufSize );
	outputFile( "Heapsort" , buf , bufSize );

	// =================================================
	// 4. RadixSort
	memcpy( buf , inValue , sizeof( size_t )*bufSize );
	clockBegin = clock();
	printf("\n" );
	printf( "RadixSort start: %u ..." , clockBegin ) ;
	RadixSort( buf , bufSize  );
	clockEnd = clock();  
	outData[2] =  clockEnd -  clockBegin ;
	printf( " down:%u, runTime = %u\n ", clockEnd , clockEnd -  clockBegin ) ;
	printfBuf( buf, bufSize );
	outputFile( "RadixSort" , buf , bufSize );

	// =================================================
	// 5. c qsort
	memcpy( buf , inValue , sizeof( size_t )*bufSize );
	clockBegin = clock();
	printf("\n" );
	printf( "qsort start: %u ..." , clockBegin ) ;
	qsort((void *)buf, bufSize, sizeof(size_t), compare);
	clockEnd = clock();  
	outData[3] =  clockEnd -  clockBegin ;
	printf( " down:%u, runTime = %u\n ", clockEnd , clockEnd -  clockBegin ) ;
	printfBuf( buf, bufSize );
	outputFile( "qsort" , buf , bufSize );
	//
	// =================================================
	// 6. c++ sort
	memcpy( buf , inValue , sizeof( size_t )*bufSize );
	clockBegin = clock();
	printf("\n" );
	printf( "qsort start: %u ..." , clockBegin ) ;
	std::sort(buf, buf+bufSize); //sort(第一筆,最後一筆)
	qsort((void *)buf, bufSize, sizeof(size_t), compare);
	clockEnd = clock();  
	outData[4] =  clockEnd -  clockBegin ;
	printf( " down:%u, runTime = %u\n ", clockEnd , clockEnd -  clockBegin ) ;
	printfBuf( buf, bufSize );
	outputFile( "cpp_sort" , buf , bufSize );

	// 7. 移除暫存
	delete buf ;
	return 0 ;

}

int main()
{
	int i ;
	static const size_t runCount = 8 ; // 測次總回合數
	size_t bufCount = 500000 ; // 排序的最大數量
	size_t outData[runCount][6] = {} ; // 排序結果
	// 排序次數
	size_t sortCount[] = { 100 , 500 , 1000 , 5000 , 10000 , 50000 , 100000 , 500000 };
//	size_t sortCount[] = { 20 , 1000 , 5000 , 20000 , 50000 , 100000 , 200000 , 300000 , 400000 , 500000 };
	size_t *values ;//= new size_t[bufCount] ; // 測資值

	// 亂數種子
	srand(time(0));
	// 0 產生亂數測資(input，只做一
	if( 1 )
	{
		// 亂數產生 500000 筆
		FILE *output = fopen( "input.txt" , "w" );
		// 產生很大的亂數
		fprintf( output , "%u\n" , bufCount );
		for( i = 0 ; i < bufCount ; ++i )
		{
			fprintf( output , "%u\n" , 
				rand()% 10000 * 10000 + rand()% 10000  
			);
		}
		fclose( output );

	} // 讀入
	// 1. 載入測資，input.txt 有 500000 筆資料
	{
		FILE *input = fopen( "input.txt" , "r" );
		fscanf( input , "%u" , &bufCount );
		values = new size_t[bufCount] ; // 測資值
		for( i = 0 ; i < bufCount ; ++i )
			fscanf( input , "%u" , values + i );
		fclose( input );
	}

	// 2. 開始排序
	for( i = 0 ; i < runCount ; ++i )
	{
		runSort( outData[i] , values , sortCount[i] ) ;
	}

	printf("\n\n" );
	printf( " -----------------------------------------------------------\n\n\n" );
	printf( "total:\n\n"  );

	printf( "%14s %14s %14s %14s %14s %14s\n" ,"run count" , "insertion" , "heap sort" , "radix sort" , "c qsort" , "c++ sort" );
	// 3. 輸出結束
	for( i = 0 ; i < runCount ; ++i )
	{

		//	printf( "%14u %14u %14u %14u %14u\n" , sortCount[i]  ,
		printf( "%14u %14.3lf %14.3lf %14.3lf %14.3lf %14.3lf\n" , sortCount[i] 
			, outData[i][0] / 1000.0
			, outData[i][1] / 1000.0
			, outData[i][2] / 1000.0
			, outData[i][3] / 1000.0
			, outData[i][4] / 1000.0 );
	}

	delete values;

	return 0 ;
}