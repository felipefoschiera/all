#include <cstdio>
#include <vector>
#define MAXN 100009
#define MAXLOGN 20
using namespace std;
typedef long long ll;

ll comp(ll a, ll b) { return a + b; }

typedef pair<int, ll> ii;
vector<ii> adjList[MAXN];
int level[MAXN], N;
int P[MAXN][MAXLOGN];
ll D[MAXN][MAXLOGN];

void depthdfs(int u){
    for(auto i : adjList[u]){
        int v = i.first;
        ll w = i.second;
        if(v == P[u][0]) continue;
        P[v][0] = u; D[v][0] = w;
        level[v] = 1 + level[u];
        depthdfs(v);
    }
}

void computeP(int root) {
	level[root] = 0;
	P[root][0] = root; D[root][0] = 0;
	depthdfs(root);
	for(int j = 1; j < MAXLOGN; j++)
		for(int i = 0; i < N; i++) {
			P[i][j] = P[P[i][j-1]][j-1];
			D[i][j] = comp(D[P[i][j-1]][j-1], D[i][j-1]);
		}
}

ll LCA(int u, int v){
    if(level[u] > level[v]) swap(u, v);
    int d = level[v] - level[u];
    ll ans = 0;
    for(int i = 0; i < MAXLOGN; i++){
        if(d & (1 << i)){
            ans = comp(ans, D[v][i]);
            v = P[v][i];
        }
    }
    if(u == v) return ans;
    for(int i = MAXLOGN-1; i >= 0; i--)
        while(P[u][i] != P[v][i]){
            ans = comp(ans, D[v][i]);
            ans = comp(ans, D[u][i]);
            u = P[u][i]; v = P[v][i];
        }
    ans = comp(ans, D[v][0]);
    ans = comp(ans, D[u][0]);
    return ans;
}

int main(){
    while(scanf("%d", &N), N){
        for(int i = 0; i < N; i++) adjList[i].clear();
        int u;
        ll w;
        for(int i = 1; i < N; i++){
            scanf("%d %lld", &u, &w);
            adjList[i].push_back({u, w});
            adjList[u].push_back({i, w});
        }
        computeP(0);
        int Q, a, b;
        scanf("%d", &Q);
        while(Q--){
            scanf("%d %d", &a, &b);
            printf("%lld%c", LCA(a, b), (Q == 0 ? '\n' : ' '));
        }
    }
    return 0;
}