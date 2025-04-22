#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>

class Graph {
public:
    std::unordered_map<int, std::vector<int>> adjList;

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);  // ����ͼ��Ҫ˫�����
    }

    std::vector<int> findShortestPath(int theSource, int theDestination) {
        std::unordered_map<int, bool> visited;
        std::unordered_map<int, int> parent;
        std::queue<int> q;

        q.push(theSource);
        visited[theSource] = true;
        parent[theSource] = -1;  // ��ʾ��ʼ�ڵ�û�и��ڵ�

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == theDestination) {
                // ����·��
                return buildPath(parent, theSource, theDestination);
            }

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                }
            }
        }

        // ����޷��ҵ�·�������ؿ�·��
        return std::vector<int>();
    }

private:
    std::vector<int> buildPath(const std::unordered_map<int, int>& parent, int theSource, int theDestination) {
        std::stack<int> pathStack;
        int current = theDestination;

        while (current != -1) {
            pathStack.push(current);
            current = parent.at(current);
        }

        std::vector<int> path;
        while (!pathStack.empty()) {
            path.push_back(pathStack.top());
            pathStack.pop();
        }

        return path;
    }
};

int main() {
    Graph g;

    // ���ͼ�ı�
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 6);
    g.addEdge(4, 6);
    g.addEdge(5, 6);

    int theSource = 0;
    int theDestination = 6;

    std::vector<int> shortestPath = g.findShortestPath(theSource, theDestination);

    if (!shortestPath.empty()) {
        std::cout << "Shortest path from " << theSource << " to " << theDestination << ": ";
        for (int vertex : shortestPath) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "No path found from " << theSource << " to " << theDestination << std::endl;
    }

    return 0;
}


