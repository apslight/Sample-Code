//=======================================================================
// Author: Aditya Pratap Singh
// Email:  adityapratap.singh28@gmail.com
//=======================================================================

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <iostream>

using namespace boost;

// refer this link for explanation
// (https://docs.google.com/presentation/d/1AegT_Z502fJt2Zj9RfUs7QrjAR-GR25J1J4gxTHzipE/edit#slide=id.g3475b13dfa_0_356)
int main()
{

  typedef adjacency_list < vecS, vecS, undirectedS,
                           no_property, property < edge_weight_t, int > > 
                           Graph;
  typedef graph_traits < Graph >::edge_descriptor 
                         Edge;
  typedef graph_traits < Graph >::vertex_descriptor 
                         Vertex;
  typedef std::pair<int, int> 
                    add_E;

  const int num_nodes = 8;  // Number of node in Graph

  // Example Edges Data. Define the 15 edges of the graph. {0, 1} means an undirected edge between vertices 0 and 1.
  add_E edge_array[] = { 
                            add_E(0, 1), add_E(0, 5), add_E(0, 7), 
                       	    add_E(1, 5), add_E(1, 7), add_E(1, 2), add_E(1, 4), 
                            add_E(2, 5), add_E(2, 3), 
		            add_E(3, 5), add_E(3, 4), add_E(3, 6), 
                            add_E(4, 6), add_E(4, 5),
                            add_E(6, 7)  
  };

  // For each of the 15 edges, define the associated edge weight. weights[i] is the weight for the edge.
  int weights[] = { 8, 10, 4, 7, 9, 4, 10, 3, 3, 18, 25, 2, 7, 2, 3 };
  
  std::size_t num_edges = sizeof(edge_array) / sizeof(add_E);

  // Create a Graph with 15 edge
  #if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
    Graph g(num_nodes);
    property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, g);
    for (std::size_t j = 0; j < num_edges; ++j) {
      Edge e; bool inserted;
      boost::tie(e, inserted) = add_edge(edge_array[j].first, edge_array[j].second, g);
      weightmap[e] = weights[j];
    }
#else
  Graph g(edge_array, edge_array + num_edges, weights, num_nodes);
#endif
  property_map < Graph, edge_weight_t >::type weight = get(edge_weight, g);
  std::vector < Edge > spanning_tree;

  // Spanning of Tree using kruskal Algorithm

  kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));
  
  // Output
  float total_weight = 0;

  std::cout << "Print the edges in the MST:" << std::endl;
  for (std::vector < Edge >::iterator ei = spanning_tree.begin();
       ei != spanning_tree.end(); ++ei) {
    std::cout << source(*ei, g) << " <--> " << target(*ei, g)
      << " with weight of " << weight[*ei]
      << std::endl;
    total_weight += weight[*ei];
  }
  
  // Total Spanning cost
  std::cout << "Total Spanning = " << total_weight << std::endl ;

  return EXIT_SUCCESS;
}
