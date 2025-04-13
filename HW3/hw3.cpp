//Author：徐曉汎 學號：B102040019
//Date :Octb.5,2022
//Purpose：一個n*n的西洋棋盤上，騎士(knight)置於某位置(x,y)，撰寫一個程式以便找出此騎士(n2-1)次移動的順序，而每個格子只拜訪過一次。實作方式使用stack，而不使用recursion。
//輸出 n=1~6
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <list>
#include <iomanip>
using namespace std ;
int n ;
typedef struct _STACK_POS{// stack 結構
	int x ; // x : i 座標
	int y ; // y : j 座標
	int index ;// 第幾步
}STACK_POS ;
STACK_POS _stack[6*6] ;//n最大是 6，步數最多 36 步
int _count = 0 ;//stack的容量初始化
int _map[6][6] ;// 已走過的地圖的範圍
void push( int x , int y , int index ){//將資料放入堆疊頂端，x : i 座標，y : j 座標，index：方向
	STACK_POS &p = _stack[_count] ;
	p.x = x ;
	p.y = y ;
	p.index = index ;
	_count ++ ;
}
STACK_POS pop(){//將堆疊頂端資料移除
	_count -- ;
	return _stack[_count] ;
}
STACK_POS& peek(){//傳回頂端的物件但不移除它
	return _stack[_count-1] ;
}
bool empty(){//判斷是否為空
	return _count == 0 ;
}
bool notEmpty(){//判斷是否不為空
	return _count > 0 ;
}
int inMap( int x , int y , int n ){// 是否在地圖中
	if( x >= 0 ) if(y >= 0 )
		if( x < n ) if( y < n )
			return true ;
	return false ;
}
int move( int startX , int startY , int n ){//下一步怎麼移動
	static const int nextCount = 8 ;// 下一步有八個方位
	static const int mX[] = {-2, -1, 1, 2, 2, 1, -1, -2, };
	static const int mY[] = {1, 2, 2, 1, -1, -2, -2, -1, } ;
	int ww , hh ;//loop 用
	int nx , ny ;// nx：下一步'i'的方向,ny：下一步'j'的方向
	int pos = 0 ;//步數初始化
	memset( _map , 0 , sizeof( _map ));//初始化	
	pos ++ ;
	_map[startY][startX] = pos ;//記錄步數
	push( startX , startY , 0  );// 先 push 0 0 0
	while( notEmpty() ){//不是空的
		STACK_POS& p = peek();// 都走完了
		if( p.index == nextCount ){//8個方位都走完
			_map[p.y][p.x] = 0 ;
			pos -- ;
			pop();//移掉
		}
		else{// 下一步的位置
			nx = p.x + mX[p.index] ;// 下一步'i'的方向
			ny = p.y + mY[p.index] ;// 下一步'j'的方向
			p.index ++ ;//不同方向一直試
			if( inMap( nx , ny , n )) // 是否在地圖內
				if( _map[ny][nx] == 0 ){// 是否有移過
					pos ++ ;//計次
					_map[ny][nx] = pos ;// 下一步 
					push( nx , ny , 0 );// 下一步
					if( pos == ( n * n ))//如果有解法
						return 1 ;
				}
		}
	}
	return 0;
}
int main( const  int argc, const char *argv[]){
	cout<<"n=1\n\n 1\n------------------"<<endl;//"n=1"只有一開始直接 push 進去的起點，沒有其他解法
	for(n=2;n<=6;++n){
		int x , y ;//變數
		int isTrue=1 ;//如果正確移動
		int ww , hh ;//loop 用
		cout <<"n="<<n<<"\n"<<endl;
		for( y = 0 ; y < n ; y++ ){//跑回圈進函式
			for( x = 0 ; x < n ; x++ ){
				isTrue = move( 0  , 0  , n  );
				if( isTrue )
					break ;
			}
			if(isTrue ) break ;
		}
		if( isTrue ){// 判斷是否走完
			for( ww = 0 ; ww < n ; ww++ ){
			    for( hh = 0 ; hh < n ; hh++ ){
				    cout << setw(2) << _map[hh][ww] << " ";
			    }
			    cout << endl;
		    }
		}
		else{// 沒走完
			cout<<"no solution"<<endl;
		}
        cout<<"--------------------"<<endl;
	}
	return 0;
}
	
