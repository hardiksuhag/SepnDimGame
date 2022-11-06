# include <bits/stdc++.h>
using namespace std;

vector<int> dp;
int f(int n){
    if(dp[n]!=-1) return dp[n];
    if(n==1) return 1;
    if(n==2) return 1;
    int q = 0;
    // when the last node is connected to some i != (n-1)
    for(int i = 1; i<=(n-2); i++){  
        q += f(n-i-1)*i;
    }
    // now n is only connected to (n-1)..
    // now (n-1) cannot be connected to (n-2)
    for(int i = 1; i<=(n-3); i++){
        q += f(i)*(n - i - 2);
    }
    dp[n] = q;
    return q;
}

/*
f(10) = {1..8}
f(8)*1 + f(7)*2 + f(6)*3 + f(5)*4 + f(4)*5 + f(3)*6 + f(2)*7 + f(1)*8
f(9-i)*i

{1..7}
f(1)*7 + f(2)*6 + f(3)*5 + f(4)*4 + f(5)*3 + f(6)*2 + f(7)*1 + f(8)*0
f(i)*(8-i)

in total =>

f(10) = f(8)*1 + f(7)*3 + f(6)*5 + f(5)*7 + f(4)*9 + f(3)*11 + f(2)*13 + f(1)*15

*/

int g(int x){
    if(dp[x]!=-1) return dp[x];
    if(x==1) return 1;
    if(x==2) return 1;
    int q = 0;
    for(int i = 1; i<=(x-2); i++){
        q += g(x-i-1)*(2*i - 1);
    }
    dp[x] = q;
    return q;
}


/*

f(7) = f(5)*1 + f(4)*3 + f(3)*5 + f(2)*7 + f(1)*9
f(6) =          f(4)*1 + f(3)*3 + f(2)*5 + f(1)*7

f(7) - f(6) = f(5) + 2*( f(4) + f(3) + f(2) + f(1) )

f(8) - f(7) = f(6) + 2*( f(5) + f(4) + f(3) + f(2) + f(1) )

f(8) + f(6) - 2*f(7) = f(6) - f(5) + 2*f(5)

f(8) = 2*f(7) - f(5)

f(n) = 2*f(n-1) - f(n-3)

*/


int h(int n){
    if(n<4) return 1;
    if(n==4) return 4;
    if(dp[n]!=-1) return dp[n];
    dp[n] = ( 2*h(n-1) + h(n-3) );
    return dp[n];
}


int main(){

    int n; cin>>n;
    dp = vector<int> (n+5, -1);

    for(int i = 1; i<=n; i++){
        cout << h(i) << "\n";
    }

    return 0;
}


