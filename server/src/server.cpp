#include <zmq.hpp>
#include <iostream>
#define within(num) (int) ((float)((num) * random ()) / (RAND_MAX + 1.0))

int main ()
{
    srandom ((unsigned) time (NULL));

    zmq::context_t context(1);
    zmq::socket_t server(context, ZMQ_REP);
    server.bind("tcp://*:5555");

    int cycles = 0;
    while (1) {
		zmq::message_t query;
		server.recv(query, zmq::recv_flags::none);
        std::string request =query.to_string();
        cycles++;

        // Simulate various problems, after a few cycles
        if (cycles > 3 && within (3) == 0) {
            std::cout << "I: simulating a crash" << std::endl;
            break;
        }
        else
        if (cycles > 3 && within (3) == 0) {
            std::cout << "I: simulating CPU overload" << std::endl;
            sleep (2);
        }
    	std::cout << "I: normal request (" << request << ")" << std::endl;
        sleep (1); // Do some heavy work
		zmq::message_t reply{request +" reply from server"};
        server.send(reply, zmq::send_flags::none);
    }
    return 0;
}