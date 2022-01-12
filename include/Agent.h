#ifndef AGENT_H_
#define AGENT_H_

#include <vector>


class Session;// foward decleration.
class Agent{
public:
    Agent();

    virtual Agent* clone() const=0;
    virtual void act(Session& session)=0; //this is an abstract method. (it has =0 which turns it to an abstarct method).
};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual Agent* clone() const ;
    virtual void act(Session& session);
};
//resource  = memeorry allocated on the heap


class Virus: public Agent{ //does not need rule of 3
public:
    Virus(int nodeInd);
    virtual Agent* clone() const ;
    virtual void act(Session& session);//will spread the virus to the lowest virus-free node neighbor.

    int getIndex();//returns the index the virus is on.
private:
    const int nodeInd;
    bool infected;
};

#endif
