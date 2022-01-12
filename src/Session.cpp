

#include "../include/Session.h"
#include "../include/json.hpp"
#include "../include/Agent.h"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void Session::isolateNode(int nodeInd) {

    std::vector<std::vector<int>> edges = g.getEdges();
    int x =edges.size();
    for(int i=0 ; i<x; i++)
        edges[nodeInd][i]=0;

    for (int j = 0; j <x ; j++)
        edges[j][nodeInd] =0;
    g.setEdges(edges);
}

///will get the path of the json file as a string and build Session
Session::Session(const std::string &path):g{{}}, cycleCounter(0), treeType(),agents(),infectedQ() {
    std::ifstream input(path);
    json j;
    input>>j;

    Graph g(j["graph"]);

    for(auto& elem : j["agents"] )
    {
        if(elem[0]=="V")
        {
            agents.push_back(new Virus(elem[1]));
            g.putVirus(elem[1]);
        }
        else
        {
            agents.push_back(new ContactTracer());
        }
    }
    setGraph(g);

    if(j["tree"]=="M"){
        treeType=MaxRank;
    }
    else if(j["tree"]=="C"){
        treeType = Cycle;
    }
    else
        treeType =Root;

}

//the main function which run a loop. each loop is a cycle (further explained in other functions).
void Session::simulate()
{
    int startSize=agents.size();
    for(int i=0; i<startSize;i++)
        agents[i]->act(*this);
    int before =0;
    while(!getGraph().isAllInfected() || getGraph().getNumber() != before ) {
        startSize=agents.size();
        cycleCounter++;
        for(int i=0; i<startSize;i++)
            agents[i]->act(*this);
        before= getGraph().getNumber();

    }

}


void Session::setGraph(const Graph &graph) {
    g=graph;
}


void Session::enqueueInfected(int nodeInd) {
infectedQ.push(nodeInd);
}

int Session::dequeueInfected() {
    if(!infectedQ.empty()) {
        int node = infectedQ.front();
        infectedQ.pop();
        return  node;
    }
    return  -1;
}

TreeType Session::getTreeType() const {
    return treeType;
}

void Session::Output()
{
    json j;
    j["graph"]= getGraph().getEdges();
    std::vector<int> v;
    std::vector<bool> b(getGraph().getInfected());
    int size =b.size();
    for(int i=0; i<size;i++)
    {
        if(b[i])
            v.push_back(i);
    }
    j["infected"] = v;
    std::ofstream output("output.json");
    output << j;
    output.close();
}

///////////////////////////////////////////////////////RULE OF 5 //////////////////////////////////////////////////////////////////////////////////////////////////////////////
Session::Session(const Session &other) :g(other.getGraph()),agents(),infectedQ(other.infectedQ),cycleCounter(other.cycleCounter),treeType(other.treeType) {
    int size = other.agents.size();
    for (int i = 0; i < size; i++)
        agents.push_back(other.agents[i]->clone());//if we wouldnt clone we would have had the same pointers.
}

Session::Session(Session &&other):g(other.getGraph()) {
    treeType=other.treeType;
    infectedQ= other.infectedQ;
    agents=other.agents;
    cycleCounter=other.cycleCounter;
    int size =other.agents.size();
    for(int i=0; i<size;i++)
        other.agents[i]= nullptr;
}

Session::~Session() {
    int size =agents.size();
    for(int i=0; i<size;i++)
        delete agents[i];
}

const Session & Session::operator=(Session &&other) {
    int size =agents.size();
    for(int i=0; i<size;i++)
        delete agents[i];
    agents.clear();
    treeType= other.treeType;
    g= other.g;
    infectedQ= other.infectedQ;
    agents=other.agents;
    cycleCounter=other.cycleCounter;
    size =other.agents.size();
    for(int i=0; i<size;i++)
        other.agents[i]= nullptr;
    return *this;

}

const Session & Session::operator=(const Session &other){
if(this != &other)
{
    treeType= other.treeType;
    g= other.g;
    infectedQ= other.infectedQ;
    cycleCounter=other.cycleCounter;
    int size =other.agents.size();
    for(int i=0; i<size;i++)
        agents.push_back(other.agents[i]->clone());
}
    return *this;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Session::addAgent(const Agent &agent)
{
    Agent* clone = agent.clone();
    agents.push_back(clone);

}

Graph Session::getGraph() const {return g;}
int Session::getCycleCount() const {return cycleCounter;}


