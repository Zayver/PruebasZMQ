#include <iostream>
#include <thread>
#include <chrono>
#include <zmq.hpp>
using namespace std::chrono_literals;
int main (int argc, char *argv[])
{
    //  Prepare our context and sockets
    zmq::context_t context(8);
    zmq::socket_t frontend (context, ZMQ_ROUTER);
    zmq::socket_t backend (context, ZMQ_DEALER);

    frontend.bind("tcp://*:5559");
    backend.bind("tcp://*:5560");

    //  Initialize poll set
    zmq::pollitem_t items [] = {
        { frontend, 0, ZMQ_POLLIN, 0 },
        { backend, 0, ZMQ_POLLIN, 0 }
    };
    
    //  Switch messages between sockets
    while (1) {
        zmq::message_t message;

        zmq::poll (&items [0], 2, -1s);
        
        if (items [0].revents & ZMQ_POLLIN) {
            while (1) {
                //  Process all parts of the message
                frontend.recv(message, zmq::recv_flags::none);
                auto more = frontend.get(zmq::sockopt::rcvmore);
                backend.send(message, more? zmq::send_flags::sndmore: zmq::send_flags::none);
                
                if (!more)
                    break;      //  Last message part
            }
        }
        if (items [1].revents & ZMQ_POLLIN) {
            while (1) {
                //  Process all parts of the message
                backend.recv(message);
                auto more = backend.get(zmq::sockopt::rcvmore);
                frontend.send(message, more? zmq::send_flags::sndmore : zmq::send_flags::none);
                // more = backend.get(zmq::sockopt::rcvmore); // new syntax
                //frontend.send(message, more? zmq::send_flags::sndmore : zmq::send_flags::none);

                if (!more)
                    break;      //  Last message part
            }
        }
    }
    return 0;
}