#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>

struct Edge {
	int from, to, cap, flow, index;
	Edge(int from, int to, int cap, int flow, int index) :
		from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel {
	int N;
	std::vector< std::vector<Edge> > G;
	std::vector<long long> excess;
	std::vector<int> dist, active, count;
	std::queue<int> Q;

	PushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(N << 1) {}

	void AddEdge(int from, int to, int cap) {
		G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
		if (from == to) ++G[from].back().index;
		G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
	}

	void Enqueue(int v) { 
		if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); } 
	}

	void Push(Edge &e) {
		int amt = int(std::min(excess[e.from], (long long)(e.cap - e.flow)));
		if (dist[e.from] <= dist[e.to] || amt == 0) return;
		e.flow += amt;
		G[e.to][e.index].flow -= amt;
		excess[e.to] += amt;		
		excess[e.from] -= amt;
		Enqueue(e.to);
	}
	
	void Gap(int k) {
		for (int v = 0; v < N; ++v) {
			if (dist[v] < k) continue;
			--count[dist[v]];
			dist[v] = std::max(dist[v], N+1);
			++count[dist[v]];
			Enqueue(v);
		}
	}

	void Relabel(int v) {
		--count[dist[v]];
		dist[v] = N << 1;
		for (size_t i = 0; i < G[v].size(); ++i)
			if (G[v][i].cap - G[v][i].flow > 0) dist[v] = std::min(dist[v], dist[G[v][i].to] + 1);
		++count[dist[v]];
		Enqueue(v);
	}

	void Discharge(int v) {
		for (size_t i = 0; excess[v] > 0 && i < G[v].size(); ++i) Push(G[v][i]);
		if (excess[v] > 0) {
			if (count[dist[v]] == 1) 
	Gap(dist[v]); 
			else
	Relabel(v);
		}
	}

	long long GetMaxFlow(int s, int t) {
		count[0] = N-1;
		count[N] = 1;
		dist[s] = N;
		active[s] = active[t] = true;
		for (size_t i = 0; i < G[s].size(); ++i) {
			excess[s] += G[s][i].cap;
			Push(G[s][i]);
		}
		
		while (!Q.empty()) {
			int v = Q.front();
			Q.pop();
			active[v] = false;
			Discharge(v);
		}
		
		long long totflow = 0;
		for (size_t i = 0; i < G[s].size(); ++i) totflow += G[s][i].flow;
		return totflow;
	}
};

int main(int argc, char *argv[]) {
	int N, M, n, A, B, W;
	scanf("%d%d", &N, &M);
	PushRelabel dual_core_cpu(N + 2);
	for (n = 1; n <= N; ++n) {
		scanf("%d%d", &A, &B);
		dual_core_cpu.AddEdge(n, N + 1, A);
		dual_core_cpu.AddEdge(0, n, B);
	}
	while (M--) {
		scanf("%d%d%d", &A, &B, &W);
		dual_core_cpu.AddEdge(A, B, W);
		dual_core_cpu.AddEdge(B, A, W);
	}
	printf("%lld\n", dual_core_cpu.GetMaxFlow(0, N + 1));
	return 0;
}
