#include "dijkstras.h"

int main() {
    Graph myGraph;
    file_to_graph("src/large.txt", myGraph);

    int source = 3;
    vector<int> previous(myGraph.numVertices, -1);
    vector<int> distances = dijkstra_shortest_path(myGraph, source, previous);

    cout << "From vertex: " << source << endl;
    for (int i = 0; i < distances.size(); ++i) {
        cout << "Distance"  << i << ":" << distances[i] << endl;
    }

    return 0;
}