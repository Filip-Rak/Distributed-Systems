/*
 * Assignment: Reaching all nodes of connected Graph
 * Author: Filip Rak
 * Description:
 *   The program identifies nodes that can reach all other nodes in
 *   in a directed graph using depth-first search (DFS).
 *
 * Input:
 *   The program reads a file containing an adjacency matrix representing the graph.
 *   - Each line corresponds to a node.
 *   - Values are space-separated integers (0 or 1), indicating edges.
 *
 * Example input (graph with 3 nodes, forming a cycle):
 *   0 1 0
 *   0 0 1
 *   1 0 0
 *
 * Output:
 *   A list of node indices that can reach all other nodes.
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

// Returns a set of all reacheable nodes from the starting node
std::unordered_set<int> dfs_reachable_nodes(int start_node, const std::vector<std::vector<int>>& graph)
{
    std::unordered_set<int> visited;
    std::stack<int> stack;
    stack.push(start_node);

    while (!stack.empty())
    {
        int current = stack.top();
        stack.pop();

        visited.insert(current);
        for (int neighbor = 0; neighbor < graph[current].size(); neighbor++)
        {
            if (visited.find(neighbor) == visited.end() && graph[current][neighbor] == 1)
                stack.push(neighbor);
        }
    }

    return visited;
}

// Reads an adjency matrix from a given file
// Format: N x N matrix of 0s and 1s, space-separated, one row per line.
std::vector<std::vector<int>> load_adjency_matrix(const std::string& filename)
{
    std::vector<std::vector<int>> graph;
    std::ifstream file(filename);

    if (!file.good())
        throw std::runtime_error("Failed to open file: " + filename);

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<int> connections;
        std::stringstream ss(line);

        int buffer;
        while (ss >> buffer)
            connections.push_back(buffer);

        graph.push_back(connections);
    }

    file.close();
    return graph;
}

int main()
{
    /* Load The Graph */
    std::cout << "Adjacency matrix filename with extension: ";
    std::string filename; std::cin >> filename;

    std::vector<std::vector<int>> graph;
    try
    {
        graph = load_adjency_matrix(filename);
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << "\n";
        return 0;
    }

    /* Find & print all fully valid entry nodes */
    std::cout << "Nodes that can reach all other nodes: ";
    for (int i = 0; i < graph.size(); i++)
    {
        auto res = dfs_reachable_nodes(i, graph);
        if (res.size() == graph.size())
            std::cout << i << " ";
    }

    std::cout << "\n";
    return 0;
}