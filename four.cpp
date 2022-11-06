# include <bits/stdc++.h>
using namespace std;

int main(){
	vector<int> a = {1,1,1};
	int m; cin>>m;
	assert(m>3);
	while(a.size()<m){
		int q = 0;
		int coeff = 1;
		int n = a.size();
		for(int j = 0; j<n; j++){
			q += a[n - j - 1]*coeff;	
			if(j%2) coeff+=3;
			else coeff-=1;
		}
		a.push_back(q);
	}
	for(int x: a) cout << x << "\n";
	return 0;
}

