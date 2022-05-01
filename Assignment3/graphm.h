#pragma once

#include<iostream>
#include"nodedata.h"

class GraphM{

    private: 

    static const int MAXNODES = 100;
    static const int NOPATH = INT32_MAX;

    struct TableType {
        bool visited;          // whether node has been visited
        int dist;              // shortest distance from source known so far
        int path;              // previous node in path of min dist
    };

    NodeData* data[MAXNODES]; // data of nodes
    int cost[MAXNODES][MAXNODES]; // cost adj. matrix
    int size; // number of nodes in graph
    TableType travel[MAXNODES][MAXNODES]; // shortest path data
    
    public:

    /**
     * @brief Construct a new Graph
     * @details 
     * data is zero-initalized
     * cost is zero-initalized
     * size is zero-initalized
     * travelInfo is initialized: 
     *      dist to NOPATH
     *      visited is zero-initalized
     *      path is zero-initalized
     */
    GraphM();
    /**
     * @brief Deallocates NodeData
     */
    ~GraphM();

    /**
     * @brief Reads data from file and builds graph.
     * @param file File name to read information from.
     * @post Graph is constructed
     */
    void buildGraph(std::ifstream&);
    /**
     * @brief Inserts an edge between two nodes
     * @param from from Node
     * @param to to Node
     * @param weight Weight of edge beteween nodes
     */
    void insertEdge(int, int, int);
    /**
     * @brief Removes an edge between two nodes
     * @post Edge is set to -1
     * @param from from Node
     * @param to to Node
     */
    void removeEdge(int, int);
    /**
     * @brief Finds the shortest path between every node to every other node.
     * @post travelInfo is updated with shortest path information
     */
    void findShortestPath();
    /**
     * @brief Displays all nodes in the graph
     */
    void displayAll() const;
    /**
     * @brief Displays the shortest path between two nodes
     */
    void display(int, int) const;

};

