# Sample-Code
Sample code of GSoC'18 proposal using the Boost Graph Library.

# How to run code..??
Install boost:
```
sudo apt-get install libboost-all-dev 
```
### Download the code and compile it:
```
git clone https://github.com/apslight/Sample-Code.git 
g++ sample_code.cpp -o sample_code -Wall
```
### Run:
```
./sample_code
```
### Description:

* [prim_minimum_spanning_tree](http://www.boost.org/doc/libs/1_53_0/libs/graph/doc/prim_minimum_spanning_tree.html)

* [kruskal_minimum_spanning_tree](http://www.boost.org/doc/libs/1_53_0/libs/graph/doc/kruskal_min_spanning_tree.html)

* [stoer_wagner_min_cut](http://www.boost.org/doc/libs/1_53_0/libs/graph/doc/stoer_wagner_min_cut.html)

## Prim Algorithms:
   Sample code:
   
   ![prim_sample code](/images/prim_input_graph.png)
   
   Output:
   
   ![prim_output](/images/prim_output.jpg)
   
 ## Kruskal Algorithms:
   Sample code:
   
   ![kruskal_sample_code](/images/kruskal_sample_code.jpg)
   
   Output:
   
   ![kruskal_output.jpg](/images/kruskal_output.jpg) 
   
 ## Min - Cut:
   Sample code:
   
   ![mn_cut_sample_code](/images/min_cut_input.jpg)
   
   Output:
   
   ![mincut_output.jpg](/images/min_cut_output.jpg) 
   
