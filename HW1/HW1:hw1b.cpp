//Author：徐曉汎 學號：B102040019
//Date :Sept.14,2022
//Purpose：印出1～N之間所有整數之階層 (factorial)，N<=50。
#include <iostream>
using namespace std;
#define s 80//階層存放的矩陣大小
#define N 20//輸入多少數字的矩陣大小
int main(){
    int i=0,w,input[N],num[s];//i:計次輸入多少數字,n:判斷輸入是否為 0,input[N]=存放輸入多少數字,num[s]:存放階層
    cout <<"輸入："<<endl;
    while(1){//存放輸入多少數字並輸出（不包含 0)
        cin>>w;
        if(w==0) break;//輸入 0 則結束輸入
        input[i]=w,i++;
    }
    cout <<"輸出："<<endl;
    for(int j=0;j<i;j++){//輸出分幾部分,j:計次
        for(int n=1;n<=input[j];n++){//每部分有n個數字,n:計次
            cout<<n<<"!=";
            int a,digit=0,decimal;//a:計次,digit:儲存當前結果的位數(從1開始),decimal：進位 
            num[0]=1;
            for(int g=1;g<=n;g++){//每個數字的階層（與 1,2,3...,n相乘）,g:當前乘到幾階層
                for(a=0,decimal=0;a<=digit;a++){//讓num[]的每位與g相乘
                    num[a] = num[a] * g + decimal ; 
                    decimal = num[a] / 10 ; //進位
                    num[a] = num[a] % 10 ;  
                }
                while(decimal>0){//若最後還需要進位時
                    num[a]=decimal%10;
                    decimal= decimal/ 10 ;
                    a++;
                }
                digit=a-1;//當前有幾位數
            }
            for(int g=digit;g>=0;g--) cout<<num[g];//輸出每個數字的階層
            cout<<endl;
        }
        cout<<endl;
    }
    }







