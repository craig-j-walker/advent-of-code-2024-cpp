module;
#include <algorithm>
#include <bits/types/error_t.h>
#include <cstdint>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

export module part_two;

using namespace std;

export namespace part_two {

// Define the graph using an adjacency list
class Graph {
public:
  // Add an edge between two vertices
  void addEdge(const string &src, const string &dest) {
    adjList[src].push_back(dest);
    adjList[dest].push_back(src); // For undirected graph
  }

  // Print the graph
  void printGraph() const {
    for (const auto &pair : adjList) {
      cout << pair.first << " -> ";
      for (const auto &vertex : pair.second) {
        cout << vertex << " ";
      }
      cout << endl;
    }
  }

  set<set<string>> GetInterconnected() const {
    set<set<string>> interconnected{};
    for (const auto &vertex : adjList) {
      for (const auto &vertex2 :
           vertex.second) { // all vertices connected to vertex
        for (const auto &vertex3 :
             adjList.find(vertex2)
                 ->second) { // all vertices connected to vertex2
          for (const auto &other :
               adjList.find(vertex3)
                   ->second) { // all vertices connected to vertex3
            if (other == vertex.first) {
              interconnected.insert(set<string>{other, vertex2, vertex3});
            }
          }
        }
      }
    }
    return interconnected;
  }

  set<set<string>> GetTInterconnected() const {
    set<set<string>> interconnected = GetInterconnected();
    set<set<string>> tInterconnected{};
    for (const auto &party : interconnected) {
      for (const auto &computer : party) {
        if (computer.starts_with("t")) {
          tInterconnected.insert(party);
          break;
        }
      }
    }
    return tInterconnected;
  }

  void bronKerbosch(unordered_set<string> &R, unordered_set<string> &P,
                    unordered_set<string> &X,
                    unordered_map<string, vector<string>> &graph,
                    vector<string> &max_clique) {
    if (P.empty() && X.empty()) {
      if (R.size() > max_clique.size()) {
        max_clique.assign(R.begin(), R.end());
      }
      return;
    }

    unordered_set<string> P_copy = P;
    for (const string &v : P_copy) {
      unordered_set<string> R_new = R;
      R_new.insert(v);

      unordered_set<string> P_new;
      for (const string &neighbor : graph[v]) {
        if (P.find(neighbor) != P.end()) {
          P_new.insert(neighbor);
        }
      }

      unordered_set<string> X_new;
      for (const string &neighbor : graph[v]) {
        if (X.find(neighbor) != X.end()) {
          X_new.insert(neighbor);
        }
      }

      bronKerbosch(R_new, P_new, X_new, graph, max_clique);

      P.erase(v);
      X.insert(v);
    }
  }

  set<string> findMaximumClique() {
    unordered_set<string> R, P, X;
    for (const auto &pair : adjList) {
      P.insert(pair.first);
    }
    vector<string> max_clique;
    set<string> clique;
    bronKerbosch(R, P, X, adjList, max_clique);
    for (const auto &mc : max_clique) {
      clique.insert(mc);
    }
    return clique;
  }

private:
  unordered_map<string, vector<string>> adjList;
};

void ParseInput(const string_view Input, Graph &G) {
  stringstream ss((string(Input)));
  string line;

  while (getline(ss, line, '\n')) {
    G.addEdge(line.substr(0, 2), line.substr(3, 2));
  }
}

string result(const string_view Input) {
  Graph g{};
  ParseInput(Input, g);
  set<string> mostInterconnected = g.findMaximumClique();
  string password;

  for (const auto &connection : mostInterconnected) {
    password += connection;
  }
  return password;
}
} // namespace part_two