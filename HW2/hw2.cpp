//Author: 徐曉汎 學號：B102040019
//Date :Sept.15,2022
//Purpose：以C++製作一個「集合」類別 (set class)，使其能進行「聯集」、「交集」、「差集」、「包含」、「屬於」等五種運算。
#include <iostream>
using namespace std;
#define max 256//字元總數
class Tset{//集合類別
    private:
        bool array[max];//儲存相應位置的字元是否重複出現。
    public:
        Tset() {
		    for (int i = 0; i < max; i++){//初始化以防集合亂掉
			    this->array[i] = false;
	        }
        }
        Tset operator+(const Tset &set){//聯集
                Tset res=*this;//回傳聯集
                for(int i=0;i<max;i++) if(set.array[i]) res.array[i]=true;
                    return res;
                
        }
        Tset operator*(const Tset &set){//交集
                Tset res;//回傳交集
                for(int i=0;i<max;i++) if(this->array[i]&&set.array[i]) res.array[i]=true;
                    return res;
                
        }
        Tset operator-(const Tset &set){//差集
                Tset res;//回傳差集
                for(int i=0;i<max;i++) if(this->array[i]&&!set.array[i]) res.array[i]=true;
                    return res;
                
        }
        bool operator>=(const Tset& set) {//A是否包含Ｂ
		for (int i = 0; i < max; i++) if (set.array[i] && !this->array[i]) return false;
		return true;
	    }
        bool operator<=(const Tset& set) {//Ｂ是否包含Ａ
		for (int i = 0; i < max; i++) if (this->array[i] && !set.array[i]) return false;
		return true;
	    }
	    friend istream& operator>>(istream&, Tset&);
	    friend ostream& operator<<(ostream&, const Tset&);
}set[50];
istream& operator>>(istream& input, Tset& set) {//重載輸入，換行代表下一個集合
	char character = getchar();
	while ( character == '\n')
		character = getchar();
	if (character != 'EOF') {
		for (int i = 0; i < max; i++)
			set.array[i] = false;
		do {
			set.array[character] = true, character = getchar();
		} while (character != '\n' && character != 'EOF');
	}
	return input;
}

ostream& operator<<(ostream& output, const Tset& set){//重載輸出
	for (int i = -1; i < max; i++)
		if (set.array[i]) putchar(i);
	return output;
}
int main(){
    int n;//測試資料計次
    cin>>n;
    for(int i=0;i<n*3;i=i+3){//每 3 個輸入一循環
        cin>>set[i]>>set[i+1]>>set[i+2];
    }
    cout<<endl;
    for (int i = 0; i < n*3; i=i+3){//每 3 個輸出一循環
        Tset A=set[i],B=set[i+1],C,D;//老師規定的 21 ~ 23 行
        C=A+B;//聯集
        D=A*B;//交集
        cout<<"Test Case "<<(i+3)/3<<":"<<endl;
		cout << "A: {" <<A<< "}"<<endl;
        cout << "B: {" <<B<< "}"<<endl;
        cout << "A+B: {" <<C<< "}"<<endl;
        cout << "A*B: {" <<D<< "}"<<endl;
        cout << "A-B: {" <<(A-B)<< "}"<<endl;
        cout << "B-A: {" <<(B-A)<< "}"<<endl;
        if (A>=B) cout <<"A contains B"<<endl;
		else cout << "A does not contain B"<<endl;
        if (A<=B) cout <<"B contains A"<<endl;
		else cout << "B does not contain A"<<endl;
        if(set[i]>=set[i+2]) cout <<"'"<<set[i+2] << "' is in A"<<endl;//直接用包含於判斷字元是否存在
        else cout<<"'"<<set[i+2] << "' is not in A"<<endl;
        if(set[i+1]>=set[i+2]) cout <<"'"<<set[i+2]  << "' is in B"<<endl;
        else cout<<"'"<<set[i+2] << "' is not in B\n"<<endl;
        cout<<endl;
    }  
}