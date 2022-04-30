#include"graphm.h"
#include<cstring>
#include<algorithm> 
#include<stack>

GraphM::GraphM() : data{}, size(0), travel{} {
    for(int i = 0; i < MAXNODES; ++i) {
        for(int j = 0; j < MAXNODES; ++j) {
            cost[i][j] = NOPATH;
        }
    }
    for(int i = 0; i < MAXNODES; ++i) {
        for(int j = 0; j < MAXNODES; ++j) {
            // Initalize all TableType values
            // travelInfo[i][j].visited = false;
            travel[i][j].dist = NOPATH;
            // travelInfo[i][j].path = 0;
        }
    }
}

GraphM::~GraphM() {
    for(int i = 0; i < this->size; ++i) {
        delete data[i];
    }
}

void GraphM::buildGraph(std::ifstream& file) {
    std::string line;
    if(file.eof()) return;
    do {
        std::getline(file, line);
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
    } while(line == "");
    // First line will be number of number of nodes
    this->size = std::stoi(line);
    // Next this->size lines will be NodeData
    for(int i = 0; i < this->size; ++i) {
        std::getline(file, line);
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        // Graph will handle deallocation of memory
        NodeData* newData = new NodeData(line);
        this->data[i] = newData; 
    }
    // Rest of text will include branches
    while(!file.eof()) {
        const int NODESIZE = 3; 
        int node[NODESIZE]{};
        std::string num;
        // Stream next three ints
        for(int i = 0; i < NODESIZE; ++i) {
            file >> num;
            node[i] = stoi(num);
        }
        // Normalize inputs to be zero-indexed
        --node[0];
        --node[1];
        // 0 0 0 will terminate, equivalent to -1 -1 0 after zero-indexing
        if(node[0] == -1 && node[1] == -1 && node[2] == 0) break;
        insertEdge(node[0], node[1], node[2]);
    }
}

void GraphM::insertEdge(int from, int to, int weight) {
    this->cost[from][to] = weight;
}

void GraphM::removeEdge(int from, int to) {
    this->cost[from][to] = NOPATH;
}

void GraphM::findShortestPath() {
    for(int source = 0; source < this->size; ++source) {
        this->travel[source][source].dist = 0;
        // begin search for start -> all other nodes
        for(int i = 0; i < this->size; ++i) { // node being processed
            int from;
            int cheapest = NOPATH;
            // pick cheapest node next
            for(int j = 0; j < this->size; ++j) {
                if(!this->travel[source][j].visited && this->travel[source][j].dist < cheapest) {
                    cheapest = this->travel[source][j].dist;
                    from = j;
                } 
            }
            this->travel[source][from].visited = true;
            for(int to = 0; to < this->size; ++to) { // path from processed node
                if(from == to) continue; // unnessary to process cost to self
                if(this->cost[from][to] != NOPATH && this->travel[source][to].visited == false) {
                    int newCost = this->travel[source][from].dist + this->cost[from][to];
                    int currentCost = this->travel[source][to].dist;
                    // if cheaper path, update cost
                    if(newCost < currentCost) {
                        this->travel[source][to].dist = newCost;
                        this->travel[source][to].path = from;
                    }
                }
            }
        }
    }
}

void GraphM::displayAll() const {
    std::cout << "Description               From node  To node  Dijkstra's  Path\n";
    std::cout << "----------------------------------------------------------------" << std::endl;
    for(int i = 0; i < this->size; ++i) {
        std::cout << *this->data[i] << std::endl;
        for(int j = 0; j < this->size; ++j) {
            if(i == j) continue;
            std::cout << "                               " << i+1 << "       " << j+1; 
            if(this->travel[i][j].dist == GraphM::NOPATH) {
                std::cout << "      " << "---" << "         ";
                std::cout << i << std::endl;
                continue;
            }
            std::cout << "      " << this->travel[i][j].dist << "          ";
            int prev = this->travel[i][j].path;
            std::stack<int> path;
            while(prev != i) {
                path.push(prev+1);
                prev = this->travel[i][prev].path;
            }
            path.push(i+1);
            while(!path.empty()) {
                std::cout << path.top() << ' ';
                path.pop();
            }
            std::cout << j+1 << std::endl;
        }
    }
    std::cout << "----------------------------------------------------------------" << std::endl;
}

void GraphM::display(int from, int to) const {
    if(from > this->size || to > this->size) { 
        std::cout << "Node is not in Graph.\n";
        return;
    }
    // If no path was present
    std::stack<int> data;
    if(this->travel[from-1][to-1].dist == GraphM::NOPATH) {
        std::cout << "      " << "---" << "         ";
        std::cout << from-1 << std::endl;
        std::cout << *this->data[from-1] << std::endl;
        return;
    }
    // Otherwise print out of the path
    std::cout << "      " << this->travel[from-1][to-1].dist << "          ";
    int prev = this->travel[from-1][to-1].path;
    std::stack<int> path;
    while(prev != from-1) {
    path.push(prev+1);
    prev = this->travel[from-1][prev].path;
    }
    path.push(from);
    data = path;
    while(!path.empty()) {
        std::cout << path.top() << ' ';
        path.pop();
    }
    std::cout << '\n';
    // Print out the NodeData path
    while(!data.empty()) {
        std::cout << *this->data[data.top()] << std::endl;
        data.pop();
    }
}
