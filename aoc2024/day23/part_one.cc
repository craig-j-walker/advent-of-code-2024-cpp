module;
#include <bits/types/error_t.h>
#include <cstdint>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/types.h>
#include <unordered_map>
#include <vector>

export module part_one;

using namespace std;

export namespace part_one {

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

uint64_t result(const string_view Input) {
  Graph g{};
  ParseInput(Input, g);
  set<set<string>> interconnected = g.GetTInterconnected();
  return interconnected.size();
}
} // namespace part_one