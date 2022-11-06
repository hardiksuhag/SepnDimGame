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

	static int comp(pair<int,int> &a, pair<int,int> &b){
		if((a.second - a.first) < (b.second - b.first)) return 0; // 0 for larger first 
		return 1;
	}

	vector<pair<int,int>> moves(){
		vector<pair<int,int>> q = {};
		for(int i = 0; i<n; i++){
			for(int j = i+1; j<n; j++){
				if(possible({i,j})) q.push_back({i,j});
			}
		}
		sort(q.begin(), q.end(), comp);
		return q;
	}
	graph copy(pair<int,int> m){
		graph gnew = graph(this->edges);
		gnew.connect(m);
		return gnew;
	}
	void connect(pair<int,int> m){
		edges[m.first][m.second] = 1;
		edges[m.second][m.first] = 1;
	}
	vector<int> hash(){
		int cnt = 0;
		vector<int> q(nax, 0);
		for(int i = 0; i<n; i++){
			for(int j = i+1; j<n; j++){
				if(edges[i][j]) q[cnt] = 1;
				cnt ++;
			}
		}
		return q;
	}
};

map<vector<int>,int> dp;
map<vector<int>,pair<int,int>> best_move;

int winner(graph g){
	vector<int> curr_hash = g.hash();
	if(dp.count(curr_hash)) return dp[curr_hash];

	if(g.moves().size()==0) { // when no move is left on the board
		dp[curr_hash] = 2;
		best_move[curr_hash] = {-1,-1};
		return 2;
	}

	pair<int,int> prev;
	for(pair<int,int> m: g.moves()){
		if(winner(g.copy(m)) == 2){
			dp[curr_hash] = 1;
			best_move[curr_hash] = {m.first, m.second};
			return 1;
		}
		prev = m;
	}

	dp[curr_hash] = 2;
	best_move[curr_hash] = prev;
	return 2;
}

int32_t main(){

dp = {};
best_move = {};


int n; cin>>n;
cout << winner(graph(n)) << endl;
cout << "Total number of valid graphs are :: " << dp.size() << endl;


graph game(n);

int player = 1;

for(int i = 0; i<n; i++) cout << (i+1) << " "; cout << endl;

while(1){
	if(player==1){ // computer
		pair<int,int> comp = best_move[game.hash()];
		cout << "Computer plays :: " << comp.first + 1 << "-" << comp.second + 1 << endl;
		game.connect(comp);
	}else{ // human
		cout << "Enter your move here :: ";
		int u, v; cin>>u>>v;
		u--; v--;
		game.connect({u,v});
	}
	if(game.moves().size()==0) {
		cout << "Player " << player << " wins!!\n";
		break;
	}
	player = 3 - player;
}


return 0;
}


