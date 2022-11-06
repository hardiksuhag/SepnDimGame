# include <bits/stdc++.h>
using namespace std;

/*
f(n) = 2*f(n-1) + f(n-3)
M = [
    [0, 1, 0],
    [0, 0, 1],
    [1, 0, 2]
]
F(n) = [f(n-2), f(n-1), f(n)] (transpose)

M * F(n-1) = F(n)

can use binary exponentiation
*/

struct mat{
    vector<vector<int>> val;
    int n;
    mat(int n){
        this->n = n;
        val = vector<vector<int>> (n, vector<int> (n, 0));
        for(int i = 0; i<n; i++) val[i][i] = 1;
    }
    mat(vector<vector<int>> x){
        val = x;
        n = x.size();
        assert(x[0].size()==n);
    }
    void set(int k){
        for(int i = 0; i<n; i++) for(int j = 0; j<n; j++) val[i][j] = k;
    }
    mat operator * (mat that){
        assert(this->n == that.n);
        mat prod(that.n);
        prod.set(0);
        for(int i = 0; i<n; i++){
            for(int k = 0; k<n; k++){
                for(int j = 0; j<n; j++){
                    prod.val[i][j] += this->val[i][k] * that.val[k][j];
                }
            }
        }
        return prod;
    }
};

int f(int n){
    if(n==1) return 1;
    // M**n x [1,1,4] 
    // n==0 :: [1,1,4]
    // n==1 :: [1,4,9]
    // n==2 :: [4,9,19]
    n--;
    mat l(3);
    mat r({{0,1,0}, {0,0,1}, {1,0,2}});
    while(n){
        if(n%2){
            n--;
            l = l*r;
        }else{
            n/=2;
            r = r*r;
        }
    }
    return (l.val[0][0]*1 + l.val[0][1]*1 + l.val[0][2]*4);
}

int main(){
    int n; cin>>n;
    // beware of out of bound errors
    cout << f(n) << "\n";
    return 0;
}

