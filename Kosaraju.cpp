#include "Kosaraju.h"

namespace graphs {

void DFS1recursion(std::vector<std::vector<int> > &graph, std::vector<bool> &used, std::stack<int> &postponedVertexes, int vertex)
{
    used[vertex] = true;
    for(auto& otherVertex: graph[vertex])
        if(!used[otherVertex])
            DFS1recursion(graph, used, postponedVertexes, otherVertex);
    postponedVertexes.push(vertex);
}

void DFS2recursion(std::vector<std::vector<int> > &graph, int &componentIndex, std::vector<int> &components, int vertex)
{
    components[vertex] = componentIndex;
    for(auto& otherVertex: graph[vertex])
        if(components[otherVertex] < 0)
            DFS2recursion(graph, componentIndex, components, otherVertex);
}

void hgraphCreation(std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& hgraph)
{
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
}

std::vector<int> kosarajuRecursion(std::vector<std::vector<int> > &graph)
{
    std::vector<std::vector<int>> hgraph(graph.size());
    std::stack<int> postponedVertexes;
    std::vector<int> components(graph.size(), -1);
    std::vector<bool> used(graph.size(), false);
    int componentIndex = 0;

    //creation of hgraph
    hgraphCreation(graph, hgraph);

    //creation of a backward path for each vertex
    for(size_t i = 0; i < graph.size(); i++)
        if(!used[i])
            DFS1recursion(hgraph, used, postponedVertexes, i);

    //fill of components container
    for(size_t i = 0; i < postponedVertexes.size(); i++)
    {
        auto v = postponedVertexes.top();
        if(components[v] < 0)
        {
            DFS2recursion(graph, componentIndex, components, v);
            componentIndex++;
        }
        postponedVertexes.pop();
    }

    return components;
}

void DFS1iterative(std::vector<std::vector<int> > &graph, std::vector<bool> &used, std::stack<int> &postponedVertexes, int vertex)
{
    used[vertex] = true;
    std::stack<int> localStack;
    localStack.push(vertex);
    postponedVertexes.push(vertex);

    while(!localStack.empty())
    {
        auto top = localStack.top();
        localStack.pop();
        for(auto& otherVertex: graph[top])
            if(!used[otherVertex])
            {
                used[otherVertex] = true;
                localStack.push(otherVertex);
                postponedVertexes.push(otherVertex);
            }
    }
}

void DFS2iterative(std::vector<std::vector<int> > &graph, int &componentIndex, std::vector<int> &components, int vertex)
{
    components[vertex] = componentIndex;
    std::stack<int> localStack;
    localStack.push(vertex);

    while(!localStack.empty())
    {
        auto top = localStack.top();
        localStack.pop();
        for(auto& otherVertex: graph[top])
            if(components[otherVertex] < 0)
            {
                components[otherVertex] = componentIndex;
                localStack.push(otherVertex);
            }
    }
}

std::vector<int> kosarajuIterative(std::vector<std::vector<int> > &graph)
{
    std::vector<std::vector<int>> hgraph(graph.size());
    std::stack<int> postponedVertexes;
    std::vector<int> components(graph.size(), -1);
    std::vector<bool> used(graph.size(), false);
    int componentIndex = 0;

    //creation of hgraph
    hgraphCreation(graph, hgraph);

    //creation of a backward path for each vertex
    for(size_t i = 0; i < graph.size(); i++)
        if(!used[i])
            DFS1iterative(hgraph, used, postponedVertexes, i);

    //fill of components container
    for(size_t i = 0; i < postponedVertexes.size(); i++)
    {
        auto v = postponedVertexes.top();
        if(components[v] < 0)
        {
            DFS2iterative(graph, componentIndex, components, v);
            componentIndex++;
        }
        postponedVertexes.pop();
    }

    return components;
}

}
