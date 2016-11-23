-module(example1).
-export([start/0, stop/0]).
-export([sum_list/1, mul_matrix/2]).

start() ->
    register(example1, 
	     spawn(fun() ->
		     process_flag(trap_exit, true),
		     Port = open_port({spawn, "./example1"}, [{packet, 4}]),
		     loop(Port)
		   end)).

stop() ->
    ?MODULE ! stop.

sum_list(L) -> call_port({sum_list, L}).
mul_matrix(A, B) -> call_port({mul_matrix, A, B}).

call_port(Msg) ->
    ?MODULE ! {call, self(), Msg},
    receive
	{?MODULE, Result} ->
	    Result
    end.

loop(Port) ->
    receive
	{call, Caller, Msg} ->
	    Port ! {self(), {command, encode(Msg)}},
	    receive
		{Port, {data, Data}} ->
		    Caller ! {?MODULE, decode(Data)}
	    end,
	    loop(Port);
	stop ->
	    Port ! {self(), close},
	    receive
		{Port, closed} ->
		    exit(normal)
	    end;
	{'EXIT', Port, Reason} ->
	    exit({port_terminated, Reason})
    end.
	
encode({sum_list, L}) -> [1, length(L)] ++ lists:foldl(fun(X, Acc) -> Acc ++ lists:reverse(binary:bin_to_list(<<X:64/float>>)) end, [], L);
encode({mul_matrix, A, B}) ->
  M = length(A),
  K = length(B),
  A0 = lists:nth(1, A),
  B0 = lists:nth(1, B),
  K = length(A0),
  N = length(B0),
  [2, M, K, N] ++ lists:foldl(fun(X, Acc) -> Acc ++ lists:reverse(binary:bin_to_list(<<X:64/float>>)) end, [], lists:flatten(A) ++ lists:flatten(B)).

decode([Int]) -> Int;
decode([1|L]) -> <<X:64/float>> = binary:list_to_bin(lists:reverse(L)),
  X;
decode([2|L]) -> 
  [_|[N|T]] = L,
  C1 = unflatten(8, T, []),
  C2 = lists:map(fun(X) -> <<Y:64/float>> = binary:list_to_bin(lists:reverse(X)), Y end, C1),
  unflatten(N, C2, []).

unflatten(_, [], L) -> L;
unflatten(N, L1, L2) -> 
  {L3, L4} = lists:split(N, L1),
  unflatten(N, L4, L2 ++ [L3]).

