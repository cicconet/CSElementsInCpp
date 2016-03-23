//
//  main.cpp
//  GraphTraversal
//
//  tutorial: https://www.youtube.com/watch?v=zLZhSSXAwxI
//

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

// depth-first traversal
void dft(int * graph, int nNodes, int root) {
    stack<int> s;
    int * visited = (int *)calloc(nNodes, sizeof(int));
    
    s.push(root);
    visited[root] = 1;
    cout << root << endl;
    
    while(!s.empty()) {
        int i = s.top();
        int j;
        for(j = 0; j < nNodes; j++) {
            if (graph[i*nNodes+j] == 1 && visited[j] == 0) {
                break;
            }
        }
        if (j < nNodes) { // there's a connected node not visited
            s.push(j);
            visited[j] = 1;
            cout << j << endl;
        } else {
            s.pop();
        }
    }
    
    free(visited);
}

// breadth-first traversal
void bft(int * graph, int nNodes, int root) {
    queue<int> q;
    
    int * visited = (int *)calloc(nNodes, sizeof(int));
    
    q.push(root);
    visited[root] = 1;
    cout << root << endl;
    
    while(!q.empty()) {
        int i = q.front();
        q.pop();
        
        for (int j = 0; j < nNodes; j++) {
            if (graph[i*nNodes+j] == 1 && visited[j] == 0) {
                q.push(j);
                cout << j << endl;
                visited[j] = 1;
            }
        }
    }
    
    free(visited);
}

int main(int argc, const char * argv[]) {
    // graph (adjacency list representation)
    int G[64] = {0, 1, 0, 1, 0, 0, 1, 0,
                 1, 0, 0, 0, 1, 1, 0, 0,
                 0, 0, 0, 0, 0, 1, 0, 1,
                 1, 0, 0, 0, 0, 1, 0, 0,
                 0, 1, 0, 0, 0, 0, 1, 0,
                 0, 1, 1, 1, 0, 0, 0, 0,
                 1, 0, 0, 0, 1, 0, 0, 0,
                 0, 0, 1, 0, 0, 0, 0, 0};
    
    int root = 0;
    
    cout << "depth-first traversal from node index " << root << endl;
    dft(G, 8, root);
    
    cout << "breadth-first traversal from node index " << root << endl;
    bft(G, 8, root);
    
    return 0;
}
