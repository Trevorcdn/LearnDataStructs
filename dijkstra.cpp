#include <iostream>
#include <vector>
#include <string>
#include <list>
 
#include <limits> // for numeric_limits
 
#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
using namespace std;

typedef int vertex_t;
typedef double weight_t;
 
const weight_t max_weight = numeric_limits<double>::infinity();

/*Each node will have a neighbor struct that points to which other nodes it is
  connected to and how far apart they are.
  For example, adjacency_list[0].push_back(neighbor(4, 10));
  In this case, target = 4 and weight = 10 so node0 and node4 are connected with
  weight= 10;
  Otherwords, target = which nodes are connected with which nodes
*/
struct neighbor {
    vertex_t target; 
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) { }
};
 
 
void DijkstraComputePaths(vertex_t source,const vector<vector<neighbor>> &adjacency_list,  
                          vector<weight_t> &min_distance, vector<vertex_t> &previous)
{
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight); //init all distance as INF
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1); //init all paths from start/cur node as -1
    set<pair<weight_t, vertex_t> > vertex_queue;
    vertex_queue.insert(make_pair(min_distance[source], source));
 
    while (!vertex_queue.empty()){
        
        weight_t dist = vertex_queue.begin()->first;
        vertex_t u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());
 
        // Visit each edge exiting u
	    for(auto& neighbor_iter : adjacency_list[u])
        {
            vertex_t v = neighbor_iter.target;
            weight_t weight = neighbor_iter.weight;
	        if(dist + weight < min_distance[v]) {
	          vertex_queue.erase(make_pair(min_distance[v], v));//delete to update new value
	          min_distance[v] = dist + weight;
	          previous[v] = u;
	          vertex_queue.insert(make_pair(min_distance[v], v));
	        }
 
        }
    }
}
 
 
list<vertex_t> DijkstraGetShortestPathTo(vertex_t vertex, const std::vector<vertex_t> &previous)
{
    list<vertex_t> path;
    for ( ; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    for(auto& p : path)
      cout<< p << " ";
    cout<<endl;
    return path;
}
 
 
int main()
{
    // remember to insert edges both ways for an undirected graph
    vector<vector<neighbor>> adjacency_list(5);
    // 0 = a
    adjacency_list[0].push_back(neighbor(1, 1));
    adjacency_list[0].push_back(neighbor(4, 10));
    // 1 = b
    adjacency_list[1].push_back(neighbor(0, 1));
    adjacency_list[1].push_back(neighbor(2, 4));
    // 2 = c
    adjacency_list[2].push_back(neighbor(1, 4));
    adjacency_list[2].push_back(neighbor(3, 7));
    // 3 = d
    adjacency_list[3].push_back(neighbor(2, 7));
    adjacency_list[3].push_back(neighbor(4, 2));
    // 4 = e
    adjacency_list[4].push_back(neighbor(0, 10));
    adjacency_list[4].push_back(neighbor(3, 2));
  
 
    vector<weight_t> min_distance;
    vector<vertex_t> previous;
    DijkstraComputePaths(4, adjacency_list, min_distance, previous);
    cout << "Distance from 4 to 1 is: " << min_distance[1] << std::endl;
    list<vertex_t> path = DijkstraGetShortestPathTo(1, previous);
 
    return 0;
}