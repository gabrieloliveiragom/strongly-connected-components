#include <list>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void explore_rec(int current, stack<int>* explored, bool* visited, list<int>* neighbors){
    visited[current] = true;
    for (list<int>::iterator i = neighbors[current].begin(); i != neighbors[current].end(); ++i){
        if(!visited[*i]){
            cout << "\t" << *i << endl;
            explore_rec(*i,  explored, visited, neighbors);
        }//was not explored
    }

    explored->push(current);
}

void explore(stack<int>* order, stack<int>* explored, bool* visited, list<int>* neighbors){
    int curr;
    while(!order->empty()) {
        curr = order->top();
        order->pop();
        if(!visited[curr]){
            cout << curr << endl;
            explore_rec(curr, explored, visited, neighbors);
        }
    }
}

// void find_SCC(istream input, ostream output){
//     istream input;
//     input.open(filename);

// }

list<int>* read_edges(int n_vertices, istream& in){
    list<int>* neighbors = new list<int>[n_vertices];

    int dest;
    string line;
    for(unsigned i = 0; i < n_vertices; ++i) {
        getline(in, line);
        stringstream estream(line);
        while(estream >> dest){
            neighbors[i].push_front(dest);
        }
    }
    return neighbors;
}

list<int>* rev_edges(int n_vertices, list<int>* neighbors){
    list<int>* neighbors_rev = new list<int>[n_vertices];
    for(unsigned i = 0; i < n_vertices; ++i) {
        for (list<int>::iterator j = neighbors[i].begin(); j != neighbors[i].end(); ++j){
            neighbors_rev[*j].push_front(i);
        }
    }
    return neighbors_rev;
}

int main(int argc, char const *argv[]){
    int n_vertices;
    cin >> n_vertices >> std::ws;

    list<int>* neighbors = read_edges(n_vertices, cin);
    list<int>* neighbors_rev = rev_edges(n_vertices, neighbors);

    stack<int> explored;
    stack<int> order;

    bool* visited = new bool[n_vertices];

    // int dest;
    // string line;
    // for(unsigned i = 0; i < n_vertices; ++i) {
    //     getline(cin, line);
    //     stringstream estream(line);
    //     while(estream >> dest){
    //         neighbors[i].push_front(dest);
    //         neighbors_rev[dest].push_front(i);
    //     }
    // }

    for(unsigned i = 0; i < n_vertices; ++i) {
        order.push(n_vertices-i-1);
    }

    explore(&order, &explored, visited, neighbors);

    for(unsigned i = 0; i < n_vertices; ++i) {
        visited[i] = false;
    }

    explore(&explored, &order, visited, neighbors_rev);

    return 0;
}
