//Author：徐曉汎 學號：B102040019
//Date :Octb.24,2022
//Purpose：設計一個程式，可以處理兩個多項式之加法與乘法
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std ;
class Node{//自定義 node
private :
	int _coefficient ;//係數
	int _exponent ;//次方
	Node *_next ;//下一筆資料
public :
	Node(const Node &node );
	Node();
	Node( int coefficient , int exponent , Node * next = NULL );
	~Node();//解構
public :
	void RemoveAll();// 全部移除
	void AddNode( int coefficient , int exponent );// 加入
	void AddNode( const Node &node );//在 node 放資料
	Node operator + ( const Node &node );// 相加
	Node operator * ( const  Node &node );// 相除
	void operator = ( const Node &node );// 等於
	void Print() const ;//輸出
};
Node::Node( const Node &node ){//node
	_next = NULL ;
	(*this) = node ;
}
void Node::AddNode(const Node& node){//在 node 放資料
	AddNode( node._coefficient , node._exponent );
}
Node Node::operator+( const Node& node){//重載相加
	Node ret  = node ;
	Node *nn = _next ;
	while( nn != NULL ){
		ret.AddNode( nn->_coefficient , nn->_exponent );
		nn = nn->_next ;
	}
	return ret ;
}
Node Node::operator*( const Node& node){//重載相乘
	Node ret ;
	Node *A = _next ;
	while( A != NULL ){//若不為空
		Node *B = node._next ;
		while( B != NULL ){
			ret.AddNode( A->_coefficient * B->_coefficient , A->_exponent + B->_exponent );
			B = B->_next ;
		}
		A = A->_next ;
	}
	return ret ; 
}
void Node::operator=(const Node& node){//重載等於
	RemoveAll();
	Node *A = node._next ;
	while( A != NULL ){
		AddNode( A->_coefficient , A->_exponent );
		A = A->_next ;
	}
}
void Node::Print() const{//輸出
	Node *nn = _next ;
	if(_next == NULL )//若為 0
		cout << "0 0" << endl ;
	while( nn != NULL ){
		cout << nn->_coefficient << " " << nn->_exponent << endl ;
		nn = nn->_next ;
	}
}
Node::Node(){
	_next = NULL ;//空
	_coefficient = _exponent = 0 ;
}
Node::Node(int coefficient, int exponent, Node * next ){//node
	_next = next ;
	_coefficient = coefficient ;
	_exponent = exponent ;
}
Node::~Node(){//解構函數->移除
	RemoveAll();
}
void Node::RemoveAll(){//移除
	if( _next != NULL ){
		_next->RemoveAll();
		_next->_next = NULL ;
		delete _next ;
		_next = NULL ;
	}
}
void Node::AddNode(int coefficient, int exponent){//加入
	Node *nn ;
	Node *enn ;
	Node *nn2 ;
	if( _next == NULL ){//若為空
		_next = new Node( coefficient , exponent );
		return ;
	}
	nn = _next ;
	enn = NULL ;
	while( nn != NULL ){
		if( nn->_exponent == exponent ){//相同
			nn->_coefficient += coefficient ;
			if( nn->_coefficient == 0 ){//刪除運算後係數為 0 的項。
				if( enn == NULL )
					_next = nn->_next ;
				else
					enn->_next = nn->_next ;
				nn->_next = NULL ;
				delete nn ; 
			}
			return ;
		}
		if( nn->_exponent < exponent ){//次方若大於
			nn2 = new Node( coefficient , exponent , nn );
			if( enn == NULL )
				_next = nn2 ;
			else
				enn->_next = nn2 ;
			return ;
		}
		enn = nn ;
		nn = nn->_next ;
	}
	enn->_next = new Node( coefficient , exponent , NULL );//加到最後
}
class CaseData{//case的資料
public :
	Node a ;//第一個函式
	Node b ;//第二個函式
};
int main( const  int argc, const char *argv[]){
	CaseData * caseData[1024] = {0} ;
	CaseData * nowCase ;//現在case的資料
	int caseCount=0 ;//計次
	int i ;//計次變數
	int P , Q ;//每兩個函式
	int cc , ee ;//cc:每個函式的係數,ee:每個函式的次方
	int caseId = 0 ;//計次變數
	while( 1 ){
		nowCase = new CaseData ;
		caseId ++ ;// 數量
		Node &a = nowCase->a ;
		Node &b = nowCase->b ;
		cin >> P;
		for( i = 0 ; i < P ; ++i ){
			cin >> cc >> ee ;
			a.AddNode( cc , ee );
		}
		cin >> Q ;
		for( i = 0 ; i < Q ; ++i ){
			cin >> cc >> ee ;
			b.AddNode( cc , ee );
		}
		if( P == 0 )//輸入兩個 0 結束
			if( Q == 0 )
				break ;
		caseData[caseCount] = nowCase ;
		caseCount ++ ;
	}
	for( caseId = 0 ; caseId < caseCount ;){//幾個 case
		nowCase = caseData[caseId] ;
		caseId ++ ;//計次
		Node &a = nowCase->a ;
		Node &b = nowCase->b ;	
		Node c , d ;
		c = a + b ;//函式相加
		d = a * b ;//函式相乘
		cout << "Case "<< caseId << endl ;
		cout << "ADD" << endl ;
		c.Print();
		cout << "MULTIPLY" << endl ;
		d.Print();
		delete nowCase ;
	}
	system( "pause" );
	return 0;
}



