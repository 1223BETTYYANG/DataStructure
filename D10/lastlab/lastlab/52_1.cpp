#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    int vertices;
    vector<vector<int> > adjacencyMatrix;
    Graph(int n) : vertices(n), adjacencyMatrix(n, vector<int>(n, 0)) {}
    void addEdge(int u, int v) {
        adjacencyMatrix[u][v] = 1;
        adjacencyMatrix[v][u] = 1;
    }
    vector<vector<int> > transitiveClosure() 
	{
        vector<vector<int> > tc(vertices, vector<int>(vertices, 0));

        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                tc[i][j] = adjacencyMatrix[i][j];
            }
        }
        // 使用构建标记策略更新传递闭包
        for (int k = 0; k < vertices; ++k)
		{
            for (int i = 0; i < vertices; ++i) 
			{
                for (int j = 0; j < vertices; ++j) 
				{
                    tc[i][j] = tc[i][j] || (tc[i][k] && tc[k][j]);
                }
            }
        }

        return tc;
    }
};

int main() 
{
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
  //  g.addEdge(2, 3);
   
    vector<vector<int> > tc = g.transitiveClosure();

    // 输出传递闭包
    cout << "Transitive Closure Matrix:" << endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << tc[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
