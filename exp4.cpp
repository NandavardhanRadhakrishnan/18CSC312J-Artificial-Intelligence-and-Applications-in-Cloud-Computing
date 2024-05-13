// DFS BFS

#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    map<int, bool> visited;
    map<int, list<int>> adj;
    
    
    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
    }
    
    
    void DFS(int v)
    {
        visited[v] = true;
        cout << v << " ";
        for (auto i : adj[v])
            if (!visited[i])
                DFS(i);
    }


    void BFS(int s)
    {
        queue<int> queue;
        visited[s] = true;
        queue.push(s);
        while (!queue.empty())
        {
            s = queue.front();
            cout << s << " ";
            queue.pop();
            for (auto i : adj[s]){
                if (!visited[i])
                {
                    visited[i] = true;
                    queue.push(i);
                }
            }
        }
    }
};


int main()
{
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    cout << "Following is Depth First Traversal"
            " (starting from vertex 2) \n";
    g.DFS(2);
    return 0;
}
