#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

struct Node {
    int value;
    std::vector<Node*> neighbors;

    Node(int val) : value(val) {}
};

struct Graph {
    std::vector<Node*> nodes;

    Node* addNode(int value) {
        Node* newNode = new Node(value);
        nodes.push_back(newNode);
        return newNode;
    }

    void addEdge(Node* from, Node* to) {
        from->neighbors.push_back(to);
    }

    int sumNeighbors(Node* node) {
        int sum = 0;
        for (Node* neighbor : node->neighbors) {
            sum += neighbor->value;
        }
        return sum;
    }

    void DFS(Node* start, std::unordered_set<Node*>& visited) {
        if (!start || visited.count(start)) return;
        std::cout << start->value << " ";
        visited.insert(start);
        for (Node* neighbor : start->neighbors) {
            DFS(neighbor, visited);
        }
    }

    void BFS(Node* start) {
        if (!start) return;
        std::queue<Node*> q;
        std::unordered_set<Node*> visited;
        q.push(start);
        visited.insert(start);
        while (!q.empty()) {
            Node* current = q.front(); q.pop();
            std::cout << current->value << " ";
            for (Node* neighbor : current->neighbors) {
                if (!visited.count(neighbor)) {
                    q.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }
    }
};

void testGraph() {
    Graph graph;
    Node* n1 = graph.addNode(1);
    Node* n2 = graph.addNode(2);
    Node* n3 = graph.addNode(3);
    Node* n4 = graph.addNode(4);

    graph.addEdge(n1, n2);
    graph.addEdge(n1, n3);
    graph.addEdge(n2, n4);
    graph.addEdge(n3, n4);

    std::cout << "Sum of neighbors of node 1: " << graph.sumNeighbors(n1) << "\n";
    std::cout << "DFS traversal: ";
    std::unordered_set<Node*> visited;
    graph.DFS(n1, visited);
    std::cout << "\nBFS traversal: ";
    graph.BFS(n1);
    std::cout << "\n";
}

int main() {
    testGraph();
    return 0;
}
