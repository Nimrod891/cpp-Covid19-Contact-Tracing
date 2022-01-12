#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>

class Session;
class Tree;
class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);

    std::vector<std::vector<int>> getEdges() const;
    std::vector<bool> getInfected() const;
    int getNumber() const;

    void setNumber(int num);
    void setEdges(std::vector<std::vector<int>> newEdges);
    void putVirus(int nodeInd);

    void infectNode(int nodeInd);// infect the node with the same index
    bool isInfected(int nodeInd);
    bool isVirusExist(int nodeInd);

    int virusfreeneighbor(int nodeInd);
    Tree* bfsAlgorithm(int nodeInd, const Session& session); //will execute bfs algorithm and return a tree.

    bool isAllInfected();



private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> infected;
    int number_infected=0;
    std::vector<bool> virusExists;
};


#endif
