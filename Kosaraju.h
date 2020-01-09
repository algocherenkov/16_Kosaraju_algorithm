#pragma once
#include <vector>
#include <stack>

namespace graphs {
    void DFS1(std::vector<std::vector<int>>& graph, std::vector<bool>& used, std::stack<int>& postponedVertexes, int vertex);

    void DFS2(std::vector<std::vector<int>>& graph, int& componentIndex, std::vector<int>& components, int vertex);

    std::vector<int> kosaraju(std::vector<std::vector<int>>& graph);
}


