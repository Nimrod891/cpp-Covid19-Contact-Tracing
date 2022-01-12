//
// Created by A-PC on 08/11/2020.
//
#include "../include/Agent.h"
#include "../include/Session.h"
#include "../include/Tree.h"

//AGENT
Agent::Agent() {}



//CONTACT TRACER
ContactTracer::ContactTracer() {}


void ContactTracer::act(Session &session)
{
    int node=session.dequeueInfected();
    if(node!=-1) {
        Tree *tree = session.getGraph().bfsAlgorithm(node, session);
        int isolate = tree->traceTree();
        session.isolateNode(isolate);
        delete (tree);
    }
}
Agent * ContactTracer::clone() const {return new ContactTracer(*this);}



//VIRUS
void Virus::act(Session &session) {
    Graph g = session.getGraph();
    if (infected == false) {
        infected = true;
        session.enqueueInfected(nodeInd);
        g.infectNode(nodeInd);
    }
    int virus = g.virusfreeneighbor(nodeInd);

    if (virus != -1) {

        Virus * v=new Virus(virus);
        session.addAgent(*v);//we need virus on the heap so it will live after the activation frame.
        g.putVirus(virus);
        delete (v);

    }
    session.setGraph(g);
}

Agent * Virus::clone() const {return new Virus(*this);}


Virus::Virus(int nodeInd):nodeInd(nodeInd),infected(false){}
