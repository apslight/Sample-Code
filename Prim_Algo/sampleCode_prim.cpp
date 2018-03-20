//=======================================================================
// Author: Aditya Pratap Singh
// Email:  adityapratap.singh28@gmail.com
//=======================================================================

#include <boost/config.hpp>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

using namespace boost;

// refer this link for explanation
// (https://docs.google.com/presentation/d/1N62Il1MMHPkYjkxsV8pFGHblHNCvHOobIljEWIektFk/edit#slide=id.g314108e333_0_48)

int main()
{
  typedef std::pair < int, int > 
                      add_E;
  typedef adjacency_list < vecS, vecS, undirectedS, property<vertex_distance_t, int>, 
                           property < edge_weight_t, int > > 
                           Graph;
  
  const int num_nodes = 17;  // Number of node in Graph
 
  // Example Edges Data. Define the 18 edges of the graph. {0, 1} means an undirected edge between vertices 0 and 1.
  add_E edges[] = { 
                       add_E(1, 2), add_E(2, 3), add_E(3, 4), 
                       add_E(2, 5), add_E(3, 6), add_E(4, 9), add_E(5, 6), 
                       add_E(6, 9), add_E(7, 8), 
		       add_E(8, 5), add_E(5, 10), add_E(6, 11), 
                       add_E(9, 12), add_E(10, 11),
                       add_E(11, 12), add_E(10, 13), add_E(14, 15), add_E(16, 17) 
  };

 
  // For each of the 18 edges, define the associated edge weight. weights[i] is the weight for the edges.
  // All edge have weight 1 beacuse of undirected graph  
  int weights[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
   
  //As pgRouting Node Start from 1 but boost start from 0
  int size = sizeof(weights) / sizeof(int);
  for (std::size_t j = 0; j != size; ++j){
        edges[j].first--;
        edges[j].second--;
  }

  // Create a Graph with 15 edge
  #if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
  	Graph g(num_nodes);
  	property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, g); 
  	for (std::size_t i = 0; i < sizeof(edges) / sizeof(add_E); ++i) {
    		graph_traits<Graph>::edge_descriptor e; 
                bool inserted;
    		boost::tie(e, inserted) = add_edge(edges[i].first, edges[i].second, g);
    		weightmap[e] = weights[i];
  	}
  #else
  	Graph g(edges, edges + sizeof(edges) / sizeof(add_E), weights, num_nodes);
  #endif
  	std::vector < graph_traits < Graph >::vertex_descriptor >
          p(num_vertices(g));


// Spanning of Tree using Prim Algorithm
 
  #if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
  	property_map<Graph, vertex_distance_t>::type distance = get(vertex_distance, g);
  	property_map<Graph, vertex_index_t>::type indexmap = get(vertex_index, g);
  	prim_minimum_spanning_tree
   	 (g, *vertices(g).first, &p[0], distance, weightmap, indexmap, default_dijkstra_visitor());
  #else
   	prim_minimum_spanning_tree(g, &p[0]);
  #endif


// Output of Example Code
  float total_weight = 0; 
  for (std::size_t i = 0; i != p.size(); ++i)
    if (p[i] != i){
        std::cout << "parent[" << i+1 << "] = " << p[i]+1 ;
        for (std::size_t j = 0; j != size; ++j){
          if((edges[j].first==i && edges[j].second==p[i]) || edges[j].first==p[i] && edges[j].second==i){
             std::cout<< " with weight = " << weights[j] <<std::endl; total_weight += weights[j]; break; 
         }
      }
    }
    else
        std::cout << "parent[" << i+1 << "] = no parent" << std::endl;
  
  std::cout << "Total Spanning = " << total_weight << std::endl;
  
  return EXIT_SUCCESS;
}


