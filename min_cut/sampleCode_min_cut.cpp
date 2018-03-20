//=======================================================================
// Author: Aditya Pratap Singh
// Email:  adityapratap.singh28@gmail.com
//=======================================================================

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/one_bit_color_map.hpp>
#include <boost/graph/stoer_wagner_min_cut.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/typeof/typeof.hpp>

using namespace boost;

//Structure for the edge 
struct edge_t
{
  unsigned long first;
  unsigned long second;
};

// Sample Data link(http://docs.pgrouting.org/2.5/en/sampledata.html#network-for-queries-marked-as-undirected-and-cost-and-reverse-cost-columns-are-used)
int main()
{

  typedef adjacency_list< vecS, vecS, undirectedS,
                          no_property, property< edge_weight_t, int> > undirected_graph;
  typedef graph_traits< undirected_graph>::vertex_descriptor vertex_descriptor;
  typedef property_map< undirected_graph, edge_weight_t>::type weight_map_type;
  typedef property_traits<weight_map_type>::value_type weight_type;
  
  // Define the 16 edges of the graph. {0, 1} means an undirected edge between vertices 0 and 1.
  // unconnected edges are not included as min cut is 0 for such graph.
  edge_t edges[] = { 
		       {1, 2}, {2, 3}, {3, 4}, 
                       {2, 5}, {3, 6}, {4, 9}, {5, 6}, 
                       {6, 9}, {7, 8}, 
		       {8, 5}, {5, 10}, {6, 11}, 
                       {9, 12}, {10, 11},
                       {11, 12}, {10, 13}
                       
  };
  


  // For each of the 16 edges, define the associated edge weight. weights[i] is the weight for the edge
  // that is described by edges[i].
  weight_type weights[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

  //As pgRouting Node Start from 1 but boost start from 0
  int size = sizeof(weights) / sizeof(int);
  for (std::size_t j = 0; j != size; ++j){
        edges[j].first--;
        edges[j].second--;
  }
  
  
  // Construct the graph object. 
  // 13 is the number of vertices, which are numbered from 0 through 12, 
  // and 16 is the number of edges.
  undirected_graph g(edges, edges + 16, weights, 13, 16);
  
  // define a property map, `parities`, that will store a boolean value for each vertex.
  // Vertices that have the same parity after `stoer_wagner_min_cut` runs are on the same side of the min-cut.
  BOOST_AUTO(parities, make_one_bit_color_map(num_vertices(g), get(vertex_index, g)));
  
  // run the Stoer-Wagner algorithm to obtain the min-cut weight. `parities` is also filled in.
  int w = stoer_wagner_min_cut(g, get(edge_weight, g), parity_map(parities));
  
  // The minimum cut of graph with weight 1.
  std::cout << "The min-cut weight of G is " << w << ".\n" << std::endl;
 
  // Print of disjoint set which get seperated
  std::cout << "One set of vertices consists of:" << std::endl;
  std::size_t i;
  for (i = 0; i < num_vertices(g); ++i) {
    if (get(parities, i))
      std::cout << i+1 << std::endl;
  }
  std::cout << std::endl;
  
  std::cout << "The other set of vertices consists of:" << std::endl;
  for (i = 0; i < num_vertices(g); ++i) {
    if (!get(parities, i))
      std::cout << i+1 << std::endl;
  }
  std::cout << std::endl;
  
  return EXIT_SUCCESS;
}
