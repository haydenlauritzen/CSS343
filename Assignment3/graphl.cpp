#include"graphl.h"
#include<cstring> // string parsing
#include<algorithm> // string parsing

GraphL::GraphL() : data{}, size(0) {}

GraphL::GraphL(std::ifstream& file) {
    buildGraph(file);
}

GraphL::~GraphL() {
    for(int i = 0; i < this->size; ++i) {
        // Deallocate NodeData
        delete this->data[i].data;
        // Deallocate EdgeNodes
        auto delete_edges = [](GraphNode::EdgeNode*& cur, auto&& delete_edges) mutable {
            if(cur == nullptr) return;
            delete_edges(cur->next, delete_edges);
            delete cur;
        };
        delete_edges(this->data[i].head, delete_edges);
    }
}

void GraphL::buildGraph(std::ifstream& file) {
    std::string line;
    // Filter out empty lines and carriage returns if present.
    if(file.eof()) return;
    do {
        std::getline(file, line);
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        if(file.eof()) return;
    } while(line == "");
    // First line will be number of number of nodes
    this->size = std::stoi(line);
    // Next this->size lines will be NodeData
    for(int i = 0; i < this->size; ++i) {
        std::getline(file, line);
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        // Graph will handle deallocation of NodeData
        NodeData* newData = new NodeData(line);
        this->data[i].data = newData;
    }
    // Rest of text will include branches
    while(!file.eof()) {
        const int NODESIZE = 2; 
        int node[NODESIZE]{};
        std::string num;
        // Stream next two ints
        for(int i = 0; i < NODESIZE; ++i) {
            file >> num;
            // Normalize inputs to be zero-indexed
            node[i] = stoi(num)-1;
        }
        // 0 0 will terminate, equivalent to -1 -1 after zero-indexing
        if(node[0] == -1 && node[1] == -1) break;
        insertEdge(node[0], node[1]);
    }
}

void GraphL::insertEdge(int from, int to) {
    // First edge 
    if(this->data[from].head == nullptr) {
        // Graph will handle deallocation of GraphNodes
        this->data[from].head = new GraphNode::EdgeNode();
        this->data[from].head->toNode = to;
        this->data[from].head->next = nullptr;
    }
    // Succeeding edges
    else {
        GraphNode::EdgeNode* temp = this->data[from].head;
        // Graph will handle deallocation of GraphNodes
        this->data[from].head = new GraphNode::EdgeNode();
        this->data[from].head->toNode = to;
        this->data[from].head->next = temp;
    }
    
}

void GraphL::displayGraph() const {
    std::cout << "----------------------------------------------------------------\n";
    std::cout << "Graph:\n";
    for(int i = 0; i < this->size; ++i) {
        std::cout << "Node " << i+1 << "        " << *this->data[i].data;
        GraphNode::EdgeNode* cur = this->data[i].head;
        while(cur != nullptr) {
            std::cout << "\n  edge " << i+1 << " " << cur->toNode+1;
            cur = cur->next;
        }
        std::cout << '\n';
    }
    std::cout << "----------------------------------------------------------------" << std::endl;
}

void GraphL::depthFirstSearch() {
    std::cout << "Depth-first ordering: ";
    auto h_depthFirstSearch = [&](GraphNode* cur, int idx, auto&& h_depthFirstSearch) {
        // Base Case, visited node
        if(cur->visited) return;
        cur->visited = true;
        std::cout << idx+1 << " ";
        GraphNode::EdgeNode* adj = cur->head;
        while(adj != nullptr) {
            h_depthFirstSearch(&(this->data[adj->toNode]), adj->toNode, h_depthFirstSearch);
            adj = adj->next;
        }
    };
    h_depthFirstSearch(&(this->data[0]), 0, h_depthFirstSearch);
    std::cout << std::endl;
}

