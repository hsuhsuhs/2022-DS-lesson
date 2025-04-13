//Author：徐曉汎 學號：B102040019
//Date :Nov.11,2022
//Purpose：給予一串數字，找出所有出現次數為奇數之數字
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _NODE//node結構
{
	int value ;
	struct _NODE *nLeft ;
	struct _NODE *nRight ; 
}NODE , *LPNODE  ;


LPNODE nowNode( int value )//現在node
{
	LPNODE ret ;
	ret = (LPNODE)malloc( sizeof( NODE ));
	memset( ret , 0 , sizeof( NODE ));
	ret->value = value ;
	return ret ; 
}

LPNODE delNode(LPNODE node )//刪除
{
	LPNODE ret ;
	LPNODE left = node->nLeft ;
	LPNODE right = node->nRight ;
	free( node );
	// 左右其中一個沒有，回傳另一個
	if( left == NULL )
		return right ;
	if( right == NULL )
		return left ;
	// 左邊加到右邊
	ret = left ;
	while( left->nRight )
		left = left->nRight ;
	left->nRight = right ;
	return ret ; 
}

LPNODE addNode( LPNODE node , int value )//插入
{
	if( node == NULL )
		return nowNode( value ) ;
	if( node->value > value )//較小者
		node->nLeft = addNode( node->nLeft , value );//左
	else if( node->value < value )//較大者
		node->nRight = addNode( node->nRight , value );//右
	else if( node->value == value )
		return delNode( node );
	return node ;

}
// 畫左線(輸出)
void printLeft( LPNODE node )
{
	if( node == NULL )
		return ;
	printLeft( node->nLeft );
	if( node->nLeft != NULL )
		printf( " %d" , node->nLeft->value );
	else
		printf( " 0" );
	printLeft( node->nRight );
}
// 取數量
int nodeCount( LPNODE node )
{
	if( node == NULL )
		return 0 ;
	return 1 + nodeCount( node->nLeft )
		+ nodeCount( node->nRight );
}

// 中序遍歷：順序是左子節點、根節點、右子節點，根排在中間。
void inorderTraversal( LPNODE node )
{
	if( node == NULL )
		return ;
	inorderTraversal( node->nLeft );
	printf( " %d" , node->value );
	inorderTraversal( node->nRight );
}
// 畫右線(輸出)
void printRight( LPNODE node )
{
	if( node == NULL )
		return ;
	printRight( node->nLeft );
	if( node->nRight != NULL )
		printf( " %d" , node->nRight->value );
	else
		printf( " 0" );
	printRight( node->nRight );

}

LPNODE findValue( LPNODE node , int value )
{
	if( node == NULL )
		return NULL ;
	if( node->value == value )
		return node ;
	if( node->value > value )
		return findValue( node->nLeft , value );
	return findValue( node->nRight , value );
}
// 移除
LPNODE freeRoot( LPNODE node )
{
	if( node == NULL )return NULL ;
	freeRoot( node->nLeft );
	freeRoot( node->nRight );
	free( node );
	return NULL ;
}

int main()
{
	int r ; 
	int i , k  ;//計算次數
	NODE *root = NULL ;
	char *strBuf[1024] ;
	char ch[1024] ;
	char *str ;
	for( i = 0 ; ; ++i )
	{
		strBuf[i] = (char*) malloc( 1024 );
		root = NULL ; 
		ch[0] = 0 ;
		if( fgets( ch , sizeof( ch ) , stdin ) == NULL )
			break ;
		strBuf[i] = (char*)malloc( strlen( ch ) + 10 );
		strcpy( strBuf[i] , ch );
		strtok(  strBuf[i] , "\r\n" );
		
	}
	for( k = 0 ; k < i ; ++k )//輸入
	{
		root = NULL ;
		strcpy( ch , strBuf[k] );
		strtok(  ch , "\r\n" );
		str = strtok( ch , " " );
		while( str != NULL )
		{
			sscanf( str , "%d" , &r );
			if(r < 0 )//輸入 -1 時
				break ;
			root = addNode( root , r );
			str = strtok( NULL , " " );
		}
		if( k > 0 )//沒輸入 -1 時
			printf( "\n" );
		///輸出全部
		printf( "node: " );
		inorderTraversal( root );
		printf("\n" );

		printf( "left: " );
		printLeft( root );
		printf("\n" );

		printf( "right: " );
		printRight( root );
		printf("\n" );

		root = freeRoot( root ) ;
	}
	system( "pause" );
	return 0 ;
}