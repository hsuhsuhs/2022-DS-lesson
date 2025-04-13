//Author：徐曉汎 學號：B102040019
//Date :Dec.1,2022
//Purpose：以Huffman 演算法製作一個檔案壓縮與解壓縮之軟體
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <time.h>
// 
typedef struct _CHAR_COUNT
{
	unsigned int _count ; // 字元數目 (比較用
	unsigned char _char ;// 字元
	char _code[256] ;// 最長有 256 個 (大小寫，符號都可以用
	unsigned int _keyCode ;// 編號
	unsigned char _keyCount ;// 長度
	struct _CHAR_COUNT *left ;// 左
	struct _CHAR_COUNT *right ;//右
}CHAR_COUNT , *LPCHAR_COUNT ;

// min heap
typedef struct _HEAP
{
	LPCHAR_COUNT *buf ;
	int bufSize ;
	int bufIndex ;
}HEAP , *LPHEAP ;

void heapInit( LPHEAP heap )
{

	memset( heap , 0 , sizeof(HEAP ));
	// 第 0 號不用，所以自建一個
	heap->bufSize = 1 ;
	heap->buf = (LPCHAR_COUNT*)malloc( sizeof( LPCHAR_COUNT ));

}
void heapDel( LPHEAP heap )
{
	free( heap->buf );
	memset( heap , 0 , sizeof(HEAP ));
}

// 更新大小
void heapResize( LPHEAP pHeap )
{
	// 目前索引 < 最大索引時，直接結束
	if( pHeap->bufIndex < pHeap->bufSize )
		return ;

	// 建原來 2 倍大小的
	int s = pHeap->bufSize * 2 ;
	int index = pHeap->bufIndex ; 
	LPCHAR_COUNT *temp = (LPCHAR_COUNT*)malloc( sizeof( LPCHAR_COUNT ) * s );
	memcpy( temp , pHeap->buf , sizeof( LPCHAR_COUNT ) * pHeap->bufSize );
	free( pHeap->buf );
	pHeap->buf = temp ;
	pHeap->bufSize = s ;

}

// 加入點
LPCHAR_COUNT heapAdd( LPHEAP pHeap , LPCHAR_COUNT value )
{
	int now, p ;
	LPCHAR_COUNT temp ;
	LPCHAR_COUNT * heap ;

	// 索引 + 1 
	pHeap->bufIndex ++ ;
	heapResize( pHeap );
	heap = pHeap->buf ;
	// 放到最後
	now = pHeap->bufIndex ;
	heap[pHeap->bufIndex ] = value ;
	while(now > 1)
	{
		// 往前排，排到索引 1 的位置
		// 上層的位置
		p = now / 2;
		// 比上層大，結束 
		if(heap[now]->_count  > heap[p]->_count  )
			break;
		// 交換
		temp = heap[now];
		heap[now] = heap[p];
		heap[p] = temp;
		now = p;
	}
	return value ;
}
// 是否是空的
int heapIsEmpty( LPHEAP pHeap )
{
	return pHeap->bufIndex == 0 ;
}

// 取得，最上層就是最大的了
LPCHAR_COUNT heapGet( LPHEAP pHeap )
{

	LPCHAR_COUNT * heap ;
	int index ;
	LPCHAR_COUNT temp ;
	int fb ;

	heap = pHeap->buf ;
	// 取得
	LPCHAR_COUNT ret = heap[1] ;
	int now, child ;
	// 最後一個取代第一個
	heap[1] = heap[pHeap->bufIndex];
	pHeap->bufIndex -- ;
	index = pHeap->bufIndex ;
	now = 1;
	// 往下沈(沈到下層(左右)比目前數量大為止)( 
	while(now * 2 <= index)
	{
		fb = 1;
		// 下層的左邊比自己大
		if( heap[2*now]->_count  < heap[now]->_count  ) 
			fb = 0;
		//          未到最下層          並且 下層的右邊比自己大    
		else if(((2 * now + 1)<= index )&&( heap[2* now + 1]->_count  < heap[now]->_count ))
			fb = 0;
		if( fb ) 
			break;
		// 交換的位置
		child = 2* now;
		if(((2 * now + 1) <= index ) &&
			( heap[2 * now + 1]->_count  < heap[2 * now]->_count ))
			child = 2 * now + 1;
		temp = heap[child];
		heap[child] = heap[now];
		heap[now] = temp;
		now = child;
	}
	return ret;
}
// ====================================================================
// 存取資料用
class OP_FILD
{
private :
	FILE *_file ;
	unsigned int _index ;
	unsigned char _data ;
	long long int _pos ;
	long long int _size ;
	int _isRead ;
public :
	OP_FILD( FILE * file , int size , int isRead )
	{
		_file = file ;
		_index = 0 ;
		_data = 0 ;
		_size = size ;
		_pos = 0 ;
		_isRead = isRead ;
	}
	void end()
	{
		if( _isRead == 0 )
		{
			fwrite(  &_data , sizeof( _data ) , 1 , _file );
		}
	}
	//
	int isEOF()const
	{
		return _pos >= _size ;
	}
	// get
	int pop()
	{
		int ret = 0 ;
		if( _index == 0 )
		{
			fread(  &_data , sizeof( _data ) , 1 , _file );
		}
		ret = ( _data >> _index )& 0x01 ;

		_index ++ ;
		_pos ++ ; 
		if( _index >= ( sizeof( _data )* 8))
			_index = 0 ;
		return ret ; 
	}
	//out
	void push( int value )
	{
		if( value != 0 )
			_data |= ( 0x01  << _index ) ;
		_pos ++ ;
		_index ++ ;
		if( _index >= ( sizeof( _data ) * 8 ))
		{
			fwrite(  &_data , sizeof( _data ) , 1 , _file );
			_index = 0 ;
			_data = 0 ;
		}
	}
	// 存放
	void push( LPCHAR_COUNT pData )
	{
		int i ;
		for( i = 0 ; pData->_code[i] ; ++i )
			push( pData->_code[i] == '1' );

	}
};

// 取樹高 ( 順便建 code 
int treeHeight( LPCHAR_COUNT node , const char *code , const char *addCode )
{
	int i ;
	if( node == NULL )
		return 0 ;
	strcpy( node->_code , code );
	strcat( node->_code , addCode );
	node->_keyCode = 0 ;
	node->_keyCount = 0 ;
	for( i = 0 ; node->_code[i] ; ++i )
	{
		if( node->_code[i] == '1' )
			node->_keyCode |= (( 0x80 )>> ( i ));
		node->_keyCount ++ ;
	}
	int a = treeHeight( node->left ,  node->_code , "0" );
	int b = treeHeight( node->right ,  node->_code , "1" );
	return (( a > b )? a : b ) + 1 ;
}

void treePrintHuffman(LPCHAR_COUNT node)
{
	if( node == NULL )
		return  ;
	printf( "%4d(%12u): %s\n" , node->_char , node->_count , node->_code );

	treePrintHuffman( node->left  );
	treePrintHuffman( node->right );
}

// 
unsigned char treeDecodedResult(LPCHAR_COUNT node, OP_FILD *load )
{
	if( node == NULL )
		return 0 ;
	if( node->left == NULL )
		if( node->right == NULL )// 最低了
			return node->_char ;
	int lr = load->pop();
	if( lr == 0 )// 左
		return treeDecodedResult( node->left , load );

	return treeDecodedResult( node->right , load );

}

//刪除
void treeDelete(LPCHAR_COUNT node)
{
	if( node == NULL )
		return  ;
	treeDelete( node->left  );
	treeDelete( node->right );
	free( node );
}

void printStuff( size_t srcSize , size_t toSize , LPCHAR_COUNT tree , LPCHAR_COUNT pHuffman[] )
{
	size_t i ;
	// 印code
	for( i = 0 ; i < 256 ; ++i )
		printf( " %4d -> %8u: %s\n" , i , pHuffman[i]->_count , pHuffman[i]->_code );
	//
	// 編碼
	printf( "Huffman Code:\n" );
	treePrintHuffman( tree );

	printf( "src  size: %u\n" , srcSize );
	printf( "dest size: %u\n" , toSize );
	if( srcSize > 0 )
		printf( "compression: %.2lf%%\n" , ((double)toSize * 100.0 )/(double) srcSize );

}

// 壓縮
int compressionMain( const  int argc, const char *argv[])
{
	HEAP heap ;
	size_t i ;
	int ch ;
	LPCHAR_COUNT data , tree ;
	size_t chBuf[256]  ;
	size_t total  ;
	LPCHAR_COUNT a , b ;
	char strBuff[1024] ;
	char c ;
	unsigned char value ;
	LPCHAR_COUNT pHuffman[256] = {0} ;// 最後編碼

	FILE *input = fopen( argv[3] , "rb" );
	if( input == NULL )
	{
		printf( "fopen input error: %s\n", argv[3]  );
		return 0 ;
	}

	FILE *output = fopen( argv[5] , "wb" );
	if( output == NULL )
	{
		printf( "fopen output error: %s\n", argv[5]  );
		return 0 ;
	}
	//
	memset( chBuf , 0 , sizeof(chBuf ));
	// 初始
	heapInit( &heap );
	// 輸入
	total = 0  ;

	while( 1 )
	{
		if( feof( input ))
			break ;
		fread( &value , sizeof( value ) , 1 , input );

		chBuf[value] ++ ;
		total ++ ;

		if(( total % 1000000 ) == 0 )
			printf( "." );
	}

	// 建 heap
	printf( "symbol: \n" );
	total = 0 ;
	for( i = 0 ; i < 256 ; ++i )
	{
		if( chBuf[i] > 0 )
		{
			data = (LPCHAR_COUNT)malloc( sizeof( CHAR_COUNT ));
			memset( data , 0 , sizeof( CHAR_COUNT ));
			data->_char = (unsigned char) i ;
			data->_count = chBuf[i] ;
			heapAdd( &heap ,  data );
			printf( "  %4d: %d\n" , data->_char , data->_count );
			total += data->_count ;

			pHuffman[i] = data ;
		}
	}
	printf( "\n" );
	//printf( "add total: %d\n\n" , total );
	// 數量取出
	// 取二個
	while( heap.bufIndex > 1 )// 還可以合
	{
		data = (LPCHAR_COUNT)malloc( sizeof( CHAR_COUNT ));
		memset( data , 0 , sizeof( CHAR_COUNT ));
		// 串到新點 (二個最小的，且 left <= right 
		data->left = a = heapGet( &heap );
		data->right = b = heapGet( &heap );
		// 數值合計
		data->_count = a->_count + b->_count ;
		// 加入
		heapAdd( &heap ,  data );


	}
	// 畫
	tree = heapGet( &heap );
	//
	printf( "Level: %d\n" , treeHeight( tree , "" , "" ));

	i = 0 ;
	// 存檔頭資料
	fwrite( &total , sizeof( total ) , 1 , output );
	fwrite( chBuf , sizeof( chBuf ) , 1 , output );
	// 回到頭
	fseek( input , 0 , SEEK_SET );

	printf( "Compression Result:\n" );

	// 加密 compression
	OP_FILD save( output , total , false );
	i = 0 ;
	while( 1 )
	{
		if( feof( input ))
			break ;
		fread( &value , sizeof( value ) , 1 , input );
		save.push( pHuffman[value] );

		if(( i % 1000000 ) == 0 )
			printf( "  %2d%%\n" , (( i * 100 ) / total ));
		i ++ ;

	}

	// 印資訊
	printStuff( ftell( input  ) , ftell( output ), tree , pHuffman );
	//
	save.end();
	fclose( output );
	fclose( input );
	printf( "\n" );
	heapDel( &heap );
	//
	treeDelete( tree );

	return 0;
}

// 解壓縮
int decodedMain( const  int argc, const char *argv[])
{

	HEAP heap ;
	size_t i ;
	int ch ;
	LPCHAR_COUNT data , tree ;
	size_t chBuf[256]  ;
	size_t total  ;
	LPCHAR_COUNT a , b ;
	char strBuff[1024] ;
	char c ;
	unsigned char value ;
	LPCHAR_COUNT pHuffman[256] = {0} ;// 最後編碼

	FILE *input = fopen( argv[3] , "rb" );
	if( input == NULL )
	{
		printf( "fopen input error: %s\n", argv[3]  );
		return 0 ;
	}

	FILE *output = fopen( argv[5] , "wb" );
	if( output == NULL )
	{
		printf( "fopen output error: %s\n", argv[5]  );
		return 0 ;
	}
	//
	memset( chBuf , 0 , sizeof(chBuf ));
	// 初始
	heapInit( &heap );
	// 輸入
	// 取檔頭資料
	fread( &total , sizeof( total ) , 1 , input );
	fread( chBuf , sizeof( chBuf ) , 1 , input );
	OP_FILD load( input , total , true );

	// 建 heap
	printf( "symbol: \n" );
	total = 0 ;
	for( i = 0 ; i < 256 ; ++i )
	{
		if( chBuf[i] > 0 )
		{
			data = (LPCHAR_COUNT)malloc( sizeof( CHAR_COUNT ));
			memset( data , 0 , sizeof( CHAR_COUNT ));
			data->_char = (unsigned char) i ;
			data->_count = chBuf[i] ;
			//	chBuf[i]._char = (unsigned char) i ;
			heapAdd( &heap ,  data );
			printf( "  %4d: %d\n" , data->_char , data->_count );
			total += data->_count ;

			pHuffman[i] = data ;
		}
	}

	printf( "\n" );
	// 數量取出

	printf( "Decoded Result:\n" );
	// 取二個
	while( heap.bufIndex > 1 )// 還可以合
	{
		data = (LPCHAR_COUNT)malloc( sizeof( CHAR_COUNT ));
		memset( data , 0 , sizeof( CHAR_COUNT ));
		// 串到新點 (二個最小的，且 left <= right 
		data->left = a = heapGet( &heap );
		data->right = b = heapGet( &heap );
		// 數值合計
		data->_count = a->_count + b->_count ;
		// 加入
		heapAdd( &heap ,  data );


	}
	// 畫
	tree = heapGet( &heap );
	//
	printf( "Level: %d\n" , treeHeight( tree , "" , "" ));


	i = 0 ;
	// 存檔頭資料
	for( i = 0 ; i < total ; ++i )
	{
		value = treeDecodedResult( tree , &load );
		fwrite( &value , sizeof( value ) , 1 , output );

		if(( i % 1000000 ) == 0 )
			printf( "  %2d%%\n" , (( i * 100 ) / total ));
	}
	// 印資訊
	printStuff( ftell( output ), ftell( input  ) , tree , pHuffman );

	fclose( output );
	fclose( input );

	printf( "\n" );

	heapDel( &heap );
	//
	treeDelete( tree );

	return 0;
}

//
int main( const  int argc, const char *argv[])
{
	//
	if( argc < 5 )
	{
		printf( "argc error: %d\n", argc );
	}else
	{
		// 加壓
		if( strcmp( argv[1] , "-c" ) == 0 )
			compressionMain( argc , argv );
		// 解壓
		else if( strcmp( argv[1] , "-u" ) == 0 )
			decodedMain( argc , argv );
		else
			printf( "argv[2] error\n" );

	}
	system( "pause" );
	return 0 ;
}