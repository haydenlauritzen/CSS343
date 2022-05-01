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

    /**
     * @brief Default Constructor
     * @details 
     * size is set to 0
     * data is zero-initalized to a size of MAXNODES
     */
    GraphL();
    /**
     * @brief Deconstructor
     * @details Deallocates NodeData and EdgeNodes
     */
    ~GraphL();

    /**
     * @brief Populates the graph with data nodes and edges.
     * @param file std::ifstream& containing input file 
     */
    void buildGraph(std::ifstream&);
    /**
     * @brief Displays the entire Graph
     */
    void displayGraph() const;
    /**
     * @brief Runs the Depth First Search algoritm
     * @post All GraphNodes are marked as visited.
     */
    void depthFirstSearch();

};