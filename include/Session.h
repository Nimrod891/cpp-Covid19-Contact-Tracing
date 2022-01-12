#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "Graph.h"


class Agent;
enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
    virtual ~Session();//DESTRUCTOR
    Session(const  Session& other);//COPY
    Session(Session&& other);//MOVE (rvalue)
    const Session& operator=(const Session& other);//assigment
    const Session& operator=( Session&& other);//MOVE ASSIGMENT
    void simulate();
    void addAgent(const Agent& agent);//u cant know where this agent came from. it could have came from the stack therefore copying agent is manditory
    void setGraph(const Graph& graph);
    Graph getGraph() const;
    void enqueueInfected(int nodeInd);
    int dequeueInfected();
    TreeType getTreeType() const;
    void Output();
    void isolateNode(int nodeInd);
    int getCycleCount() const;

private:
    Graph g ;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> infectedQ;
    int cycleCounter;
};



#endif
