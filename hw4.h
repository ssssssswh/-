//图数据结构
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Graph {
private:
    unordered_map<int, vector<int>> adjList;

public:
    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    void printGraph() {
        for (auto node : adjList) {
            cout << node.first << " -> ";
            for (auto neighbor : node.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};
 

（2）实现BFS和DFS算法
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

class Graph {
    // same implementation as above
};

vector<int> bfsTraversal(Graph graph, int start) {
    vector<int> visited;
    unordered_set<int> visitedSet;
    queue<int> q;
    q.push(start);
    visitedSet.insert(start);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        visited.push_back(node);
        for (int neighbor : graph[node]) {
            if (visitedSet.find(neighbor) == visitedSet.end()) {
                q.push(neighbor);
                visitedSet.insert(neighbor);
            }
        }
    }
    return visited;
}

vector<int> dfsTraversal(Graph graph, int start) {
    vector<int> visited;
    unordered_set<int> visitedSet;
    stack<int> s;
    s.push(start);
    visitedSet.insert(start);
    while (!s.empty()) {
        int node = s.top();
        s.pop();
        visited.push_back(node);
        for (int neighbor : graph[node]) {
            if (visitedSet.find(neighbor) == visitedSet.end()) {
                s.push(neighbor);
                visitedSet.insert(neighbor);
            }
        }
    }
    return visited;
}
int main() {
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    cout << "BFS Traversal: ";
    vector<int> bfs = bfsTraversal(g, 2);
    for (int node : bfs) {
        cout << node << " ";
    }
    cout << endl;

    cout << "DFS Traversal: ";
    vector<int> dfs = dfsTraversal(g, 2);
    for (int node : dfs) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}


（3）最短路径算法：
#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 1005;

int n, m, s, t;
int vis[maxn], dist[maxn];
vector<pair<int, int>> adj[maxn];

void dijkstra() {
    memset(vis, 0, sizeof(vis));
    memset(dist, INF, sizeof(dist));
    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({ 0, s });
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto e : adj[u]) {
            int v = e.first, w = e.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({ dist[v], v });
            }
        }
    }
}

int main() {
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w });
    }
    dijkstra();
    cout << dist[t] << endl;
    return 0;
}

样例：
5 7 1 5
1 2 2
1 3 4
2 3 1
2 4 7
3 4 3
3 5 5
4 5 1
结果： 8

  
最小支撑树算法：
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1005;

struct Edge {
    int u, v, w;
    bool operator<(Edge e) const {
        return w < e.w;
    }
} e[maxn * maxn];

int n, m;
int fa[maxn];

int Find(int x) {
    return fa[x] == x ? x : fa[x] = Find(fa[x]);
}

void Kruskal() {
    sort(e, e + m);
    for (int i = 1; i <= n; i++) fa[i] = i;
    int cnt = 0, ans = 0;
    for (int i = 0; i < m && cnt < n - 1; i++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        int fu = Find(u), fv = Find(v);
        if (fu == fv) continue;
        fa[fu] = fv;
        ans += w;
        cnt++;
    }
    cout << ans << endl;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }
    Kruskal();
    return 0;
}
样例：
5 7
1 2 2
1 3 4
2 3 1
2 4 7
3 4 3
3 5 5
4 5 1
结果：9
