This is part of the third assignment for the course COL333: Artificial Intelligence in Semester I, 2023-24 at IIT Delhi.

run1.sh converts the problem of finding two independent complete subgraphs to SAT.\n
run2.sh converts the solution of SAT produced after running minisat (which is what we used for testing, but should work with other SAT solvers given the output format is consistent) to the list of nodes in each complete subgraph.\n
run3.sh converts the problem of finding the maximum sized independent subgraph to SAT and internally calls minisat (command can be found in p2dp.cpp) to solve it and returns the nodes in the subgraph.
