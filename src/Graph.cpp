//
// Created by A-PC on 08/11/2020.
//

#include "../include/Graph.h"
#include "../include/Tree.h"
#include "../include/Session.h"
Graph::Graph(std::vector<std::vector<int>> matrix):edges(matrix),infected(std::vector<bool>(matrix.size(), false)), virusExists(std::vector<bool>(matrix.size(), false)){}


void Graph::infectNode(int nodeInd)
{
   infected[nodeInd]= true;
   number_infected++;
}

std::vector<std::vector<int>> Graph::getEdges() const {return  edges;}
std::vector<bool> Graph::getInfected() const { return  infected;}
int Graph::getNumber() const {return number_infected;}

void Graph::putVirus(int nodeInd) {
    virusExists[nodeInd]=true;
}

bool Graph::isInfected(int nodeInd)
{
    return infected[nodeInd];
}

void Graph::setNumber(int num) { number_infected = num;}
void Graph::setEdges(std::vector<std::vector<int>> newEdges) { edges=newEdges;}

int Graph::virusfreeneighbor(int nodeInd)
{
    int x =edges[nodeInd].size();
    for(int i=0; i<x;i++)
    {
        if(edges[nodeInd][i]==1)
        {
            if(!isVirusExist(i)) //not yet sick but has a virus
                return i;
        }
    }
    return -1;
}

Tree* Graph::bfsAlgorithm(int nodeInd, const Session& session)
{
std::vector<bool> visited(edges.size(), false);
Tree* t = Tree::createTree(session,nodeInd);
std::queue<Tree*> Q;
Q.push(t);

visited[t->getLable()]= true;
while (!Q.empty())
{
    //Tree* v = Q.front();
    //Q.pop();
     int x= edges.size();
    for(int i=0; i<x;i++)
    {
        if(edges[Q.front()->getLable()][i]==1 && !visited[i]) {
            Tree *child = Tree::createTree(session, i);//move
            Q.push(Q.front()->BFSaddChild(*child));
            visited[i] = true;
            delete (child);
        }
    }
    Q.front()= nullptr;
    Q.pop();
}
    return t;
}

bool Graph::isVirusExist(int nodeInd) {
    return virusExists[nodeInd];
}

bool Graph::isAllInfected() {
    int x =edges.size();
    bool flag=true;
    for (int i=0; i<x; i++){
        if(isInfected(i) && virusfreeneighbor(i)!=-1)
            flag=false; // if the node is infected and has a healthy neighbor we are NOT done yet
        if(!isInfected(i))
            for(int j=0; j<x;j++) // if the node is healthy I want to check if all its neighbors are healthy
            {
                if(edges[i][j]==1)
                {
                    if(isInfected(j))//if the neighbor is infected, we are NOT done yet
                        flag=false;
                }
            }


    }
    return flag;
   // return number_infected==infected.size();
}







