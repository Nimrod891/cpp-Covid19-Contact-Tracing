//TODO: learn inheritance in c++ so we can no how to make the constructor of the child classes.

#include "../include/Tree.h"
#include "../include/Session.h"

//TREE//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Tree::Tree(const Tree &other): node(other.node),children() {
    int size= other.children.size();
     for(int i=0; i<size;i++)
         children.push_back(other.children[i]->clone());
}

Tree::~Tree() noexcept {
    int size =children.size();
    for(int i=0; i<size;i++)
        delete children[i];
    // children.clear(); Maybe we don't need it because it's on the stack
}

Tree::Tree(Tree &&other):node(other.node) ,children(other.children){
    int size =other.children.size();
    for(int i=0; i<size; i++)
        other.children[i]= nullptr;
}

const Tree & Tree::operator=(Tree &&other) {
    int size =children.size();
    for(int i=0; i<size;i++) {
        if(children[i] != nullptr)
            delete children[i];
    }
    children.clear();
    node = other.node;
    children= other.children;
    size =other.children.size();
    for(int i=0; i<size; i++)
        other.children[i]= nullptr;
    return *this;
}




const Tree & Tree::operator=(const Tree &other) {
    if(this != &other) {
        int size =children.size();
        for (int i = 0; i < size; i++) {
            if (children[i] != nullptr)
                delete children[i];
        }
        children.clear();
        node = other.node;
        size =other.children.size();
        for(int i=0; i<size;i++)
            children.push_back(other.children[i]);
    }
    return *this;
}
Tree::Tree(int rootLabel): node(rootLabel),children(){}

Tree*  Tree::BFSaddChild(const Tree& child){
    Tree* clone = child.clone();
    children.push_back(clone);
    return  clone;
}

Tree * Tree::createTree(const Session &session, int rootLabel)
{
    Tree* result;
    switch (session.getTreeType()) {
        case Cycle:
            result = new CycleTree(rootLabel, session.getCycleCount());
            break;
        case MaxRank:
            result = new MaxRankTree(rootLabel);
            break;
        case Root:
            result = new RootTree(rootLabel);
            break;
    }
    return result;
}

int Tree::size() const { return children.size();}


int Tree::getLable() const
{
    return node;
}


std::vector<Tree *> Tree::getChildern() const
{
    return children;
}

//CYCLE TREE////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CycleTree::traceTree() {
    int countDown=currCycle;
    Tree*a=this;
    while(countDown>0){
        if(!a->getChildern().empty())
            a=a->getChildern().front();
        countDown--;
    }

    return a->getLable();
}

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel),currCycle(currCycle) {}

Tree * CycleTree::clone() const {return new CycleTree(*this);}




//MAXRANGE TREE////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MaxRankTree::traceTree()
{
    std::queue<Tree*> Q;
    Tree* t=clone();
    Q.push(t);
    int maxchildren=children.size();
    int node=getLable();
    while(!Q.empty()) {
        Tree *a = Q.front();
        Q.pop();
        if (maxchildren < a->size()) {
            maxchildren = a->size();
            node = a->getLable();
        }
        for (int i = 0; i < a->size(); i++) {
            Q.push(a->getChildern()[i]);
        }
    }
    delete(t);
    return node;
}



MaxRankTree::MaxRankTree(int rootLabel) :Tree(rootLabel){}

Tree * MaxRankTree::clone() const {return new MaxRankTree(*this);}

//ROOT TREE////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RootTree::traceTree() { return getLable();}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

Tree * RootTree::clone() const {return new RootTree(*this);}