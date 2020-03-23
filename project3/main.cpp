//
// Created by student on 09.12.2017.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <list>
#include <array>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;

//Nodes are vertices, keeps all info about towns
class Node{

    int node;
    int weight;
    vector<int> thief;
    vector<int> jeweler;

public:
    Node(int n){
        node = n;
    }

    Node(int n, int w){
        node = n;
        weight = w;
    }

    Node(int n, vector<int> j){
        node = n;
        jeweler = j;
    }

    int getN(){ return node; }
    int getW(){ return weight; }
    vector<int> getT(){ return thief;}
    vector<int> getJ(){ return jeweler;}
    void setT(int num){
        thief.push_back(num);
    }
    void setJ(int num){
        jeweler.push_back(num);
    }

    bool operator<(const Node &rhs) const {
        return this->weight < rhs.weight;
    }

    bool operator>(const Node &rhs) const {
        return rhs.weight < this->weight;
    }

    bool operator<=(const Node &rhs) const {
        return (!(rhs.weight < this->weight));
    }

    bool operator>=(const Node &rhs) const {
        return !(this->weight < rhs.weight);
    }

    bool operator==(const Node &rhs) const {
        return node == rhs.node &&
               weight == rhs.weight &&
               thief == rhs.thief ;
    }

    bool operator!=(const Node &rhs) const {
        return !(rhs == *this);
    }

    ~Node() {}

};

class Graph{

    int v;  //number of vertices
    vector<int> *nodes; //it keeps jewelers of all vertices
    list<Node> *adjlist;  //it is the list of edges

public:
    Graph(int vNumber);

    void addJeweler(vector<string> numbers);

    void addEdge(vector<string> words);

    bool checkRoad(vector<int> thieves, vector<int> jewelers);

    queue<int> path(int _towns, int _jewelers);

    ~Graph();
};

Graph::Graph(int vNumber) {
    this->v = vNumber;
    nodes = new vector<int>[v+1];
    adjlist = new list<Node>[v+1];
}

//adds jewelers in its town
void Graph::addJeweler(vector<string> numbers) {
    int a = stoi(numbers[1]);
    for(int i=0; i<a; i++){
        nodes[stoi(numbers[0])].push_back(stoi(numbers[i+2]));
    }
}

//adds edges to list
void Graph::addEdge(vector<string> words) {
    Node v1(stoi(words[1]), stoi(words[2]));
    int a = stoi(words[3]);
    for(int i=0; i<a; i++){
        v1.setT(stoi(words[i+4]));
    }
    adjlist[stoi(words[0])].push_back(v1);
}

//checks the road and returns true if AliBaba can go
bool Graph::checkRoad(vector<int> thieves, vector<int> jewelers) {
    for(int i= 0; i<thieves.size(); i++){
        int j = thieves[i];
        if(find(jewelers.begin(), jewelers.end(), j) == jewelers.end()){
            return false;
        }
    }
    return true;
}


//gives the shortest path
queue<int> Graph::path(int _towns, int _jewelers) {
    Node AliBaba(1, nodes[1]);
    queue<int> shortestPath; //keeps the towns id for shortest path
    queue<int> a, b;
    stack<int> reverse;
    a.push(-1);
    shortestPath.push(1);
    //if first town has no road
    if(adjlist[1].empty()) {
        return a;
    }
    else {
        priority_queue<Node, vector<Node>, greater<Node>> q;  //it keeps adj edges of current node
        queue<Node> q2;
        int current = 1;
        while (current != _towns) {

            int s = adjlist[current].size();
            while (s!=0){
                Node c= adjlist[current].front();
                q.push(c);
                adjlist[current].pop_front();
                adjlist[current].push_back(c);
                s--;
            }

            Node vertex = q.top();
            while(!checkRoad(vertex.getT(), AliBaba.getJ())){
                if(!q.empty()){
                    q.pop();
                    q2.push(vertex);
                    vertex = q.top();
                } else {
                    return a;
                }
            }
            q.pop();

            if(!q.empty()){
                Node v= q.top();
                while (v.getW() == vertex.getW()){
                    if((v.getN() == _towns) && checkRoad(v.getT(), AliBaba.getJ())){
                        vertex = v;
                        break;
                    }
                    else{
                        q.pop();
                        if(!q.empty())
                            v = q.top();
                        else{
                            q.push(v);
                            break;
                        }
                    }
                }
            }

            int n= current;
            current = vertex.getN();
            if(!nodes[current].empty()){
                for(int i=0; i!= nodes[current].front();){
                    i=nodes[current].back();
                    AliBaba.setJ(i);
                    nodes[current].pop_back();
                }
                AliBaba.setJ(nodes[current].front());
            }

            while (find(adjlist[n].begin(), adjlist[n].end(), vertex) == adjlist[n].end()){
                n = reverse.top();
                reverse.pop();
                if(n != shortestPath.back())
                    shortestPath.push(n);
            }

            shortestPath.push(current);
            reverse.push(current);

            while (!q2.empty()){
                Node v= q2.front();
                q.push(v);
                q2.pop();
            }
        }
    }

    return shortestPath;
}

Graph::~Graph() {
    if(!adjlist->empty()) {
        delete adjlist;
    }
}

template <class Container>
void split(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

int main(int argc, char* argv[]) {
    // below reads the input file
    // in your next projects, you will implement that part as well
    if (argc != 3) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }

    cout << "input file: " << argv[1] << endl;
    cout << "output file: " << argv[2] << endl;

    ifstream infile(argv[1]);
    string line;
    getline(infile, line);
    vector<string> words;
    split(line, words);
    int towns = stoi(words[0]);
    int roads = stoi(words[1]);
    int thieves = stoi(words[2]);
    int jewelers = stoi(words[3]);


    Graph middleEast(towns);
    //reads the jewekers from file
    for(int i=0; i<jewelers; i++){
        vector<string> words1;
        getline(infile, line);
        split(line, words1);
        middleEast.addJeweler(words1);
    }
    //reads the roads froma file
    for(int i=0; i<roads; i++){
        vector<string> words2;
        getline(infile, line);
        split(line, words2);
        middleEast.addEdge(words2);
    }

    ofstream myfile(argv[2]);
    queue<int> s = middleEast.path(towns, jewelers);
    //prints the file
    while(!s.empty()){
        myfile << s.front() << " ";
        s.pop();
    }
    myfile.close();

    return 0;
}
