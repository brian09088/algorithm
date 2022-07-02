#include <algorithm>
#include <iostream>
using namespace std;

const int MAXV = 1000;
const int INF = 1;

int adjacency[MAXV][MAXV], visited[MAXV], weight[MAXV];
int contract[MAXV];

void add_edge(const int source, const int dest);
void init(const int vertex_num);
int random_min_cut(int& s, int& t, const int vertex_num);
int min_cut(const int vertex_num);

int main() {
	int vertex_num, source, dest;
	cin >> vertex_num;
	init(vertex_num);
    while(cin >> source >> dest){
		add_edge(source,dest);
    }
	int answer = min_cut(vertex_num);
	cout << answer << endl;
	return 0;
}

void add_edge(const int source, const int dest) {
	const int weight = 1;
	adjacency[source][dest] += weight;
	adjacency[dest][source] += weight;
}

void init(const int vertex_num) {
	for(int i = 0; i < vertex_num; i++)
		for(int j = 0; j < vertex_num; j++)
			adjacency[i][j] = 0;
}

int random_min_cut(int& s, int& t,const int vertex_num) {
	int ret = 0;
	s = t = -1;
	for(int i = 0; i < vertex_num; i++)
		visited[i] = weight[i] = 0;
	for(int i = 0; i < vertex_num; i++) {
		int mx = -INF, u = t;
		for(int j = 0; j < vertex_num; j++) {
			if(!contract[j] && !visited[j] && weight[j] > mx) {
				mx = weight[j], u = j;
			}
		}
		if(u == t)
			break;
		s = t, t = u, ret = mx;
		visited[u] = 1;
		for(int j = 0; j < vertex_num; j++) {
			if(!contract[j] && !visited[j])
				weight[j] += adjacency[u][j];
		}
	}
	return ret;
}

int min_cut(const int vertex_num) {
	for(int i = 0; i < vertex_num; i++)
		contract[i] = 0;
	int ret = INF;
	for(int i = 0; i < vertex_num - 1; i++) {
		int s, t;
		int min_cut_result = random_min_cut(s, t, vertex_num);
		ret = min(ret, min_cut_result);
		if(ret == 0)
			return ret;
		contract[t] = 1;
		for(int j = 0; j < vertex_num; j++) {  // contract(s, t)
			if(!contract[j]) {
				adjacency[s][j] += adjacency[t][j];
				adjacency[j][s] += adjacency[j][t];
			}
		}
	}
	return ret;
}
