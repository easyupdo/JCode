all:
	g++ main.cc -o main -std=c++14 -g

hash:
	g++ hash_chaining_main.cc -o hash_chaining_main -std=c++14 -g

shm:
	rm -rf shm
	g++ shared_mem.cc -o shm -std=c++14 -g

msg:
	g++ message_queues.cc -o msg -std=c++14 -g

sem:
	g++ semaphore.cc -o sem -std=c++14 -g

test:
	g++ test.cc -o test -std=c++14 -g

cv:
	g++ condition_variable.cc -o cv -std=c++14 -g -lpthread

poxis_shm:
	g++ shared_mem_poxis.cc -o poxis_shm -std=c++14 -g -lrt

poxis_sem:
	g++ semaphore_poxis.cc -o poxis_sem -std=c++14 -g -lrt -lpthread

singleton:
	g++ singleton.cc -o singleton -std=c++14 -g -lpthread

log_test:
	g++ ./log/log_test.cc -o log_test -std=c++14 -g

socket_client:
	g++ ./socket/socket_client.cc -o socket_client -g -std=c++14 -L ./log -I ./log

socket_server:
	g++ ./socket/socket_server.cc -o socket_server -g -std=c++14 -L ./log -I ./log

feture:
	g++ ./feturec++17/feture.cc -o feture -g -std=c++17 

raii_demo:
	g++ ./raii/raii_demo.cc -o raii_demo -g -std=c++17

test_vector:
	g++ ./test_vector.cc -o test_vector -g -std=c++11 -lpthread

throw:
	g++ ./throw.cc -o throw -g -std=c++11

boost_ptree:
	g++ ./boost_ptree.cc -o boost_ptree -std=c++17 -l stdc++fs -g

temp:
	g++ ./temp.cc -o temp -std=c++17 -g