//Name: Jake Tremblay
//Student ID: 200633568
//Email: tremb008@cougars.csusm.edu

#include <iostream>

using namespace std;

struct Edge{
    int adj_vtx;    //index of adjacent vertex
    Edge * next;    //linked list of next edges

    Edge(){
        adj_vtx = -1;
        next = NULL;
    }
};

class linkedList{
    public:
        Edge *head;
        Edge *rear;

    linkedList(){
        head = NULL;
        rear = NULL;
    }

    //if the list is not empty, rear->next points to null, rear pointer to temp
    void pushBack(int data){
        Edge * temp = new Edge(); 
        temp->adj_vtx = data;
        temp->next = NULL;

        if(this->head == NULL){       
            head = temp;
            rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }
    }
};

class queue{
     Edge *front, *back;
     int size;

     public:

        queue(){
            front = new Edge();
            back = new Edge();

            front->adj_vtx = -1;
            front->next = NULL;

            back->adj_vtx = -1;
            back->next = NULL;

            size = 0;
        }

        //updating only the rear when we add
        void enqueue(int data){
            Edge *temp = new Edge();
            temp->adj_vtx = data;
            temp->next = back;

            if(front->adj_vtx == -1) {front->adj_vtx = 0;}
            back->adj_vtx += 1;

            back = temp;
            size++;  
        }

        //updating only the head when we remove
        Edge *dequeue(){
            if(front > 0){
                Edge *temp = new Edge();
                temp = front;
                
                front = front->next;
                size--;
                return temp;
            } else {
                return NULL; //or return some error
            }
        }

        bool empty(){
            if(size <= 0){
                return true;
            }
            return false;
        }

        Edge *peekFront(){
            return front;
        }

        Edge *peekBack(){
            return back;
        }
};

class Graph{
    int vertices; 
    linkedList ** adj;   //had issue with Edge ** implementation because Edge doesnt have pushBack functionality
    void DFSUtil(int v, bool visited[]);
    public:

        Graph(int v);
        void addEdge(int v, int w); //v is vertex to add to, w is weight of edge
        void BFS(int s); //traverse from source s
        void DFS(int v); //traverse the vertices reachable from v
        bool hasCycle(); //returns true if there is a cycle
};

Graph::Graph(int v){
    vertices = v;
    adj = new linkedList*[v]; //linked list of linked list pointers 
    for(int i=0; i < v; ++i){
        adj[i] = new linkedList();  //init all elements of each sub list up to v edges
    }
}

//adj[v] is a pointer to linked list, we push w (data) 
//graph is undirected, thus for all w in v, v in w 
void Graph::addEdge(int v, int w){  
    adj[v]->pushBack(w);
    adj[w]->pushBack(v);
}

//part 1 of DFS, creates 'visited list' and calls DFSUtil using the list of unvisited vertices
void Graph::DFS(int v){
    bool * visited = new bool[vertices];
    for(int i = 0; i < vertices; i++){
        visited[i] = false;
    }
    DFSUtil(v, visited);
}

//part 2 of DFS, sets vertex we are looking at to visited, prints its value, then recursively call DFSUtil on each adj vertice for given v
void Graph::DFSUtil(int v, bool visited[]){
    visited[v] = true;

    cout << v << " ";

    for(int i = 0; i < vertices; i++){ //not sure how to loop through a list of lists without iterators from STL
        if(!visited[i]){
            if(adj[i]->head != NULL){
                DFSUtil(i, visited);
            }
        }
    }
}

//BFS uses queue
void Graph::BFS(int s){
    bool *visited = new bool[vertices];

    queue * BFS_queue = new queue();

    for(int i = 0; i < vertices; i ++){
        visited[i] = false;
    }    

    if(adj[s]->head != NULL){
        BFS_queue->enqueue(s);
    } else {
        cout << "Source not found in graph." << endl;
        return;
    }
    
    while(!BFS_queue->empty()){
        visited[s] = true;

        s = BFS_queue->dequeue()->adj_vtx;

        cout << s << " ";  

        for(int i = 0; i < vertices; i++){
            if(!visited[i]){
                if(adj[i]->head != NULL){
                    visited[i] = true;
                    BFS_queue->enqueue(i);
                }
            }
        }
    }

}

int main(){
    Graph * testGraph = new Graph(10);

    testGraph->addEdge(1, 2);
    testGraph->addEdge(1, 3);
    testGraph->addEdge(1, 5);
    testGraph->addEdge(2, 4);
    
    testGraph->DFS(2);  //not sure if dfs works or not, but it compiles and runs
    cout<<endl;
    testGraph->BFS(0); //having issues with queue working properly
    
    return 0;
}