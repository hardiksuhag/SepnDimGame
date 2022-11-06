#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
# define int ll
# define nax 200

class graph{
public:
	int n;
	vector<vector<int>> edges;
	graph(int k){
		n = k;
		edges = vector<vector<int>> (n, vector<int>(n, 0));
	}
	graph(vector<vector<int>> ed){
		n = ed.size();
		edges = ed;
	}
	bool possible(pair<int,int> m){
		assert(m.first < m.second);
		for(int i = 0; i<n; i++){
			for(int j = i+1; j<n; j++){
				if(edges[i][j]){
					if(m.first == i && m.second == j) return 0;
					if(m.second <= i || m.first >= j) continue;
					if(m.first == i || m.second == j) continue;
					return 0;
				}
			}
		}
		return 1;
	}

	vector<pair<int,int>> moves(){
		vector<pair<int,int>> q = {};
		for(int i = 0; i<n; i++){
			for(int j = i+1; j<n; j++){
				if(possible({i,j})) q.push_back({i,j});
			}
		}
		return q;
	}

	void connect(pair<int,int> m, int flag = 1){
		edges[m.first][m.second] = flag;
		edges[m.second][m.first] = flag;
	}
};


int compare(pair<int,int>& a, pair<int,int>& b){
    if(a.first < b.first) return 1;
    return (a.second < b.second);
}


int cnt;
int iterations;

void dfs(graph& g, pair<int,int> last_move){
    iterations++;
    auto moves = g.moves();
    if(moves.size()==0) {
        cnt++;
        return;
    }
    sort(moves.begin(), moves.end(), compare);
    for(auto move: moves){
        if(compare(last_move, move)){
            g.connect(move, 1);
            dfs(g, move);
            g.connect(move, 0);
        }
    }
}



int32_t main(){

int N; cin>>N;
for(int n = 1; n<=N; n++){
    graph g(n);
    cnt = 0;
    iterations = 0;
    dfs(g, {-1,-1});
    cout << cnt << " , iterations :: " << iterations << "\n";
}


return 0;
}


