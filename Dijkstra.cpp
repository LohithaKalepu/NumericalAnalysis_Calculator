#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>

using namespace std;

const int MAX_NODES = 10000; //maximum nodes in a graph
const int INF_VAL = 1e9; // globally declare infinity value to avoid overflow issues
bool visited[MAX_NODES]; // keep track of visted nodes

int num_vertices, start_vertex, end_vertex;
list <pair<int, int>> neighbor_list[MAX_NODES]; //create list of neighbors for a node
int dist[MAX_NODES]; 
int prev_vertex[MAX_NODES];

//initialize values
void init(int source) {
    for (int i = 0; i <= num_vertices; i++) {
        dist[i] = INF_VAL;
        prev_vertex[i] = -1;
        visited[i] = false;
    }
    dist[source] = 0;
}

//get the nearest node method
int get_closest() {
    //assume minimum distance is 0, and no node selected yet
    int min_val = INF_VAL;
    int min_node = -1;
    //for every node from 1 to num nodes, return the non-visited node with minimum distance
    for (int i = 1; i <= num_vertices; i++) {
        //check for unvisited nodes with smaller distance, then update the smallest distance 
        if (!visited[i] && dist[i] < min_val) {
            min_val = dist[i];
            min_node = i;
        }
    }
    return min_node;
}

// dijkstra algorithm
void D_algorithm() {
    //for all nodes, find the closest distance
    for (int i = 0; i < num_vertices; i++) {
        int closest = get_closest();
        //if no node is left, exit
        if (closest == -1) break; 
        //mark the node as visited
        visited[closest] = true;
        //for all the nodes that are directly connected by an edge
        for (auto neighbor : neighbor_list[closest]) {
            //values to update distance
            int node = neighbor.first;
            int weight = neighbor.second;
            //if the current min. distance (dist[node]) is greater than going through dist[closest], then, we found a shorter path. 
            if (dist[node] > dist[closest] + weight) {
                //update
                dist[node] = dist[closest] + weight;
                prev_vertex[node] = closest;
            }
        }
    }
}

// main method
int main() {
    //read file, if cannot read file, return error
    ifstream read_file("graph.txt");
    if (!read_file) {
        cout << "Error: Cannot Open File!" << endl;
        return 1;
    }
    //read the file dividing the numbers into their types
    read_file >> num_vertices;
    read_file >> start_vertex >> end_vertex;

    string line;
    getline(read_file, line); 
    while (getline(read_file, line)) {
        // u = start, v = end, w = weight
        int u,v, w;
        stringstream ss(line);
        ss >> u >> v >> w;
        neighbor_list[u].push_back(make_pair(v, w));
        neighbor_list[v].push_back(make_pair(u, w));
    }


    read_file.close();
    init(start_vertex);
    D_algorithm();

    //create empty vector to store the path
    vector<int> shortest_path;
    //start from the destination
    int node = end_vertex;
    //and keep going until there is no parent node left
    while (node != -1) {
        //add the current node at the beginning
        shortest_path.push_back(node); 
        //then move to the previous node
        node = prev_vertex[node];
    }
    //reverse for the correct order
    reverse(shortest_path.begin(), shortest_path.end());

    //print the output
    cout << "[";
    //for every node in the path
    for (int i = 0; i < shortest_path.size(); i++) {
        //print the node at i
        cout << shortest_path[i];
        //then, print ,
        if (i != shortest_path.size() - 1) cout << ",";
    }
    cout << "] ";
    //print the shortest
    cout << "[" << dist[end_vertex] << "]" << endl;
}
