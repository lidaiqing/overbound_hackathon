Finding the Maximum Clique
==========================
Jeremy Li & Hari Sharma
1000795357 | 1000637643


Intuition
---------
The initial goal of our algorithm is to find a small clique (that is not necessarily maximal), to set a baseline for our algorithm. We begin by ordering the nodes by number of neighbouring nodes in ascending order. This heuristic is intuitive because it improves the chances of finding a clique at the beginning of algorithm. Suppose, instead, we try finding cliques that originate from a node with many neighbouring vertices. Naturally, in order to form a clique with those
many neighbours, many edges would be required, which is relatively unlikely. It is more probable to find a clique that includes a vertex with fewer neighbours - that is, the number of edges required to form the clique is much less, making it more likely to form a clique.

Once a baseline clique is found, the algorithm tries to form a clique using just the neighbouring vertices of the first node used to form the previous clique. That is, suppose v_1 is the first node that is adjacent to v_2 and v_3. Then, in the next step, the algorithm would use just the vertices v_2 and v_3 to find a clique "originating" from v_2. In essence, we want to build off of the neighbours of the vertices observed so far, in an attempt to find larger cliques. If any
larger clique is found, we simply replace the current largest clique. If, however, the number of neighbours of a particular v_i makes it impossible to form a clique larger than the current clique, we stop looking for a clique that includes v_i (we know that with v_i, we cannot form a larger clique than what we currently have). In this way, we avoid building every possible clique, and instead only build the cliques that may surpass our current clique by cardinality.

There were several heuristics that were initially used to order the original set of nodes. In fact, after some research, we found that for sparse graphs, unordered nodes work best. Nevertheless, we chose to order the nodes based on their number of neighbours since it gave us the optimal running time.

But of course, the solution just CLIQUED.


Data Structures
---------------
We read edges from the .clq file, and simultaneously store this information in a 2-dimensional matrix. Then, coordinates used to seek into the matrix represent the pair of nodes that may or may not be connected by an edge. Information about the connection between the nodes is stored within the cells of the matrix. We also read from a node file, and store this information in a collection, along with the type of the node (Issuer, Dealer, or Investor). We store several other
structures to keep track of how certain data is stored in collections, as a result of inconsistencies in the data files (nodes may start with node 0 or node 1). We then run the above algorithm on the data collections, and output the largest clique in the graph as a set of nodes to a text file.


---------------
Inspiration was drawn from Randy Carraghan's and Panos M. Pardalos' work on developing algorithm for finding a maximum clique.
---------------
