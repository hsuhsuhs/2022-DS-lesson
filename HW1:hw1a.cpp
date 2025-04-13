//Author：徐曉汎 學號：B102040019
//Date :Sept.13,2022
//Purpose：製作N階(N為奇數 1,3,5,7,9)的魔方陣
#include <iostream>
#include <iomanip>
using namespace std;
int main(){
    int N; // N階層魔方陣
    N = 1; //從一階層開始
    while (N <= 9){ //輸出 1,3,5,7,9 階魔方陣
        cout << N << "階魔方陣:\n"<< endl;
        int i, j, i_change,j_change, num, square[9][9] = {0};
        // i:當前‘列’的位置,j:當前‘行’的位置,i_change:超過矩陣範圍時，‘列’須轉換的變數,j_change:超過矩陣範圍時，‘行’須轉換的變數,num:魔方陣裡面的數字,
        // square[9][9]:魔方陣範圍,並初始化
        i = 0, j = (N / 2), square[i][j] = 1; //魔方陣第一列中間放 1
        for (num = 2; num <= N * N; num++){//將數字從 2 ~ N*N 放到魔方陣
            i_change = i,j_change=j; //給超過矩陣範圍的‘列’,‘行’變數初始值
            i--;//上一列
            j--;//上一行 (num+1的位置往左上角放置)
            if (i < 0) i = N - 1; //如果擺放位置往左上角的‘列’超出範圍
            if (j < 0) j = N - 1; //如果擺放位置往左上角的‘行’超出範圍
            if (square[i][j] != 0) i = i_change + 1,j=j_change; //如果擺放位置往左上角已經存放東西,則往下放
            square[i][j] = num;
        }
        for (i = 0; i < N; i++){ //輸出魔方陣
            for (j = 0; j < N; j++){
                cout << setw(2) << square[i][j] << " ";
            }
            cout << endl;
        }
        N += 2;
        cout <<endl;
    }
    return 0;
}
