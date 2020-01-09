#include "Kosaraju.h"

namespace graphs {

void DFS1(std::vector<std::vector<int> > &graph, std::vector<bool> &used, std::stack<int> &postponedVertexes, int vertex)
{
    used[vertex] = true;
    for(auto& otherVertex: graph[vertex])
        if(!used[otherVertex])
            DFS1(graph, used, postponedVertexes, otherVertex);
    postponedVertexes.push(vertex);
}

void DFS2(std::vector<std::vector<int> > &graph, int &componentIndex, std::vector<int> &components, int vertex)
{
    components[vertex] = componentIndex;
    for(auto& otherVertex: graph[vertex])
        if(components[otherVertex] < 0)
            DFS2(graph, componentIndex, components, otherVertex);
}

std::vector<int> kosaraju(std::vector<std::vector<int> > &graph)
{
    std::vector<std::vector<int>> hgraph(graph.size());
    std::stack<int> postponedVertexes;
    std::vector<int> components(graph.size(), -1);
    std::vector<bool> used(graph.size(), false);
    int componentIndex = 0;

    //creation of hgraph
    size_t vertexNumber = 0;
    for(auto& vertexBase: graph)
    {
        for(auto& vertex: vertexBase)
        {
            if(vertex < static_cast<int>(hgraph.size()))
                hgraph[vertex].push_back(vertexNumber);
        }
        vertexNumber++;
    }

    //creation of a backward path for each vertex
    for(size_t i = 0; i < graph.size(); i++)
        if(!used[i])
            DFS1(hgraph, used, postponedVertexes, i);


    //fill of components container
    for(size_t i = 0; i < postponedVertexes.size(); i++)
    {
        auto v = postponedVertexes.top();
        if(components[v] < 0)
        {
            DFS2(graph, componentIndex, components, v);
            componentIndex++;
        }
        postponedVertexes.pop();
    }

    return components;
}
}
