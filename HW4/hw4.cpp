//Author：徐曉汎 學號：B102040019
//Date :Octb.12,2022
//Purpose：一個n*n的西洋棋盤上，騎士(knight)置於某位置(x,y)，撰寫一個程式以便找出此騎士(n2-1)次移動的順序，而每個格子只拜訪過一次。實作方式使用recursion，而不使用stack。
//輸出 n=1~6
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std ;
int _count = 0 ;//初始化
int _map[6][6] ;// 已走過的地圖，最大6*6就好
int inMap( int x , int y , int W , int H ){// 是否在地圖中
	if( x >= 0 ) if(y >= 0 )
		if( x < W ) if( y < H )
			return true ;
	return false ;
};
int move2( int x , int y , int W, int H , int pos ){//下一步怎麼移動
	static const int nextCount = 8 ;// 下一步有八個方位
	static const int mX[] = {-2, -1, 1, 2, 2, 1, -1, -2};
	static const int mY[] = {1, 2, 2, 1, -1, -2, -2, -1} ;
	int nx , ny ;// nx：下一步'i'的方向,ny：下一步'j'的方向
	_map[y][x] = pos ;// 標示每一步
	if( pos == ( W * H )){//如果跑完 n*n
		return 1 ;
	}
	for(int i = 0 ; i <nextCount ; ++i ){// 八個方向
		nx = x + mX[i] ;// 下一步'i'的方向
		ny = y + mY[i] ;// 下一步'j'的方向
		if( inMap( nx , ny , W , H )) // 是否在地圖內
			if( _map[ny][nx] == 0 ){// 是否有移過
				if( move2( nx , ny , W , H , pos + 1 ))// 往下一格(遞迴)
					return 1 ;
			}
	}
	_map[y][x] = 0 ;// 標示
	return 0 ;
}
int main( const  int argc, const char *argv[]){
	int W, H ; //W,H:n的邊長
	int x , y ;//loop 用
	int isTrue ;//如果正確移動
	int ww , hh ;//loop 用
	for( int ii = 1 ; ii <= 6 ; ++ii ){//n=1~6
		printf( "\n\n" );
		printf( "# -------------------------------------------\n\n" );
		printf( "%d x %d \n\n" , ii , ii );
		isTrue = 0 ;//如果正確移動
		memset( _map , 0 , sizeof( _map ));//矩陣初始化
		_count = 0 ;
		W = H = ii ;//矩陣 n*n
		for( y = 0 ; y < H ; ++y ){
			for( x = 0 ; x < W ; ++x ){
				isTrue = move2(0,0, W , H , 1 );//從座標（1,1）開始
				if( isTrue )
					break ;
			}
			if(isTrue )
				break ;
		}
		if( isTrue ){// 判斷是否有走完
			for( ww = 0 ; ww < W ; ++ww ){
				for( hh = 0 ; hh < H ; ++hh ){
					printf( "%2d " , _map[hh][ww] );
				}
				printf( "\n" );
			}
		}
        else{ // 沒走完
			printf( "no solution\n" );
		}
	}
	return 0;
} 



