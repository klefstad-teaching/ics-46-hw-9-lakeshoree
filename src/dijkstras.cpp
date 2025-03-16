#include "dijkstras.h"
#include "algorithm"
using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {

    int numVertices = G.size(); // based off slides
    vector<int> distance(numVertices, INF);
    vector<bool> visited(numVertices, false);

    distance[source] = 0;
    previous[source] = -1; // same as undefined

    priority_queue<pair<int,int>, vector<pair<int, int>>, greater<pair<int,int>>> minHeap; //using greater to ensure min heap
    minHeap.push({0,source});
    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                minHeap.push({distance[v], v});
            }
        }
    }

    return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;

    for (int i = destination; i != -1; i = previous[i]) {
        path.push_back(i);
    }

    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {

    if (v.empty()) {
        return;
    }

    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << ' ';
    }

    cout << "\nTotal cost is " << total << endl;



}


