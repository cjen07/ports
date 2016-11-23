# ports
## commands
    g++ -o example1 example1.c erl_comm.c example1_driver.c -llapack
    erl
    1> c(example1).
    2> example1:start().
    3> example1:sum_list([1.2,3.4,-2,1]).
    4> example1:mul_matrix([[1.2,3.1],[-0.5,2.7]], [[1.7,-2.5],[1.5,4.8]]).
## logs
- 11.22 success with sending doubles and recieving a double
- 11.22 success with sending two matrix and getting the multiplication
- 11.23 success with adjustment from packet:2 to packet: 4 with buf[8000000]
- 11.23 failure with endless sending time of large matrix muliplication (1389*256)
