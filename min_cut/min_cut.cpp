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

// refer this link for explanation
// (https://docs.google.com/presentation/d/1N3ItzKnjSG0RVbgaBLUBMgwIOSzsYCRPdFHX02cg9lo/edit#slide=id.g3141adc0ff_0_272)
int main()
{

  typedef adjacency_list< vecS, vecS, undirectedS,
                          no_property, property< edge_weight_t, int> > undirected_graph;
  typedef graph_traits< undirected_graph>::vertex_descriptor vertex_descriptor;
  typedef property_map< undirected_graph, edge_weight_t>::type weight_map_type;
  typedef property_traits<weight_map_type>::value_type weight_type;
  
  // Define the 12 edges of the graph. {0, 1} means an undirected edge between vertices 0 and 1.
  edge_t edges[] = { 
                      { 0, 1}, { 0, 4}, { 1, 4}, { 1, 5}, { 1, 2}, 
                      { 2, 6}, { 2, 3}, { 3, 6}, { 3, 7}, { 4, 5}, 
                      { 5, 6}, { 6, 7} 
  };
  

  // For each of the 12 edges, define the associated edge weight. weights[i] is the weight for the edge
  // that is described by edges[i].
  weight_type weights[] = { 2, 3, 2, 2, 3, 2, 4, 2, 2, 3, 1, 3 };
  
  // Construct the graph object. 
  // 8 is the number of vertices, which are numbered from 0 through 7, 
  // and 12 is the number of edges.
  undirected_graph g(edges, edges + 12, weights, 8, 12);
  
  // define a property map, `parities`, that will store a boolean value for each vertex.
  // Vertices that have the same parity after `stoer_wagner_min_cut` runs are on the same side of the min-cut.
  BOOST_AUTO(parities, make_one_bit_color_map(num_vertices(g), get(vertex_index, g)));
  
  // run the Stoer-Wagner algorithm to obtain the min-cut weight. `parities` is also filled in.
  int w = stoer_wagner_min_cut(g, get(edge_weight, g), parity_map(parities));
  
  // The minimum cut of graph with weight 4.
  std::cout << "The min-cut weight of G is " << w << ".\n" << std::endl;
 
  // Print of disjoint set which get seperated
  std::cout << "One set of vertices consists of:" << std::endl;
  std::size_t i;
  for (i = 0; i < num_vertices(g); ++i) {
    if (get(parities, i))
      std::cout << i << std::endl;
  }
  std::cout << std::endl;
  
  std::cout << "The other set of vertices consists of:" << std::endl;
  for (i = 0; i < num_vertices(g); ++i) {
    if (!get(parities, i))
      std::cout << i << std::endl;
  }
  std::cout << std::endl;
  
  return EXIT_SUCCESS;
}
