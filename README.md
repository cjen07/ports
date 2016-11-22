# ports
## commands
    g++ -o example1 example1.c erl_comm.c example1_driver.c -llapack
    erl
    1> c(complex1).
    2> complex1:start().
    3> complex1:sum_list([1.2,3.4,-2,1]).
    4> complex1:mul_matrix([[1.2,3.1],[-0.5,2.7]], [[1,7,-2.5],[1.5,4.8]).
## logs
- 11.22 success with sending doubles and recieving a double
- 11.22 success with sending two matrix and getting the multiplication
