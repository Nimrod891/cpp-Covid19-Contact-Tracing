#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include <queue>

class Session;
class Tree{
public:

    virtual Tree* clone() const=0 ;
    Tree(int rootLabel);
    Tree* BFSaddChild(const Tree& child);
    void addChild(const Tree& child);
    static Tree* createTree(const Session& session, int rootLabel);
    int getLable() const;
    int size() const;
    virtual ~Tree();//DESTRUCTOR
    Tree(const  Tree& other);//COPY
    Tree(Tree&& other);//MOVE (rvalue)
    const Tree& operator=(const Tree& other);//assigment
    const Tree& operator=( Tree&& other);//MOVE ASSIGMENT
    std::vector<Tree*> getChildern() const;//TODO: make it so the function is nor bad.

    virtual int traceTree()=0;

protected:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    virtual Tree* clone() const;
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    virtual Tree* clone() const;
    MaxRankTree(int rootLabel);
    virtual int traceTree();
};

class RootTree: public Tree{
public:
    virtual Tree* clone() const;
    RootTree(int rootLabel);
    virtual int traceTree();
};
#endif
