#pragma once

#include<iostream>
#include"nodedata.h"

class GraphL {
    private:

    static const int MAXNODES = 100;

    struct GraphNode {
        struct EdgeNode {
            int toNode; // adj. node idx
            EdgeNode* next; // next edge in list
        };
        EdgeNode* head; // first edge in list
        NodeData* data; // data of node
        bool visited; // if node has been visited in a df
    };

    GraphNode data[MAXNODES]; // array of GraphNodes
    int size; // size of graph / num of graph nodes

    /**
     * @brief Inserts an edge from the 'from' index to the 'to' index 
     * @pre Indexes are zero-indexed
     * @param from  
     * @param to 
     */
    void insertEdge(int, int);

    public:

    GraphL();
    GraphL(std::ifstream&);
    ~GraphL();

    void buildGraph(std::ifstream&);
    void displayGraph() const;
    void depthFirstSearch();

};