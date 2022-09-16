//
//  Lazy Pirate client
//  Use zmq_poll to do a safe request-reply
//  To run, start piserver and then randomly kill/restart it
//
#include <zmq.hpp>

#include <sstream>
#include <iostream>
#include <chrono>
using namespace std::chrono_literals;

auto const REQUEST_TIMEOUT = 2500ms ;   //  msecs, (> 1000!)
auto const REQUEST_RETRIES = 3;       //  Before we abandon

//  Helper function that returns a new configured socket
//  connected to the Hello World server
//
static zmq::socket_t  s_client_socket (zmq::context_t & context) {
    std::cout << "I: connecting to server..." << std::endl;
    zmq::socket_t client = zmq::socket_t (context, zmq::socket_type::req);
    client.connect ("tcp://localhost:5555");

    //  Configure socket to not wait at close time
    int linger = 0;
    client.set(zmq::sockopt::linger, linger);
    return client;
}

int main () {
    zmq::context_t context (1);

    zmq::socket_t client = s_client_socket (context);

    int sequence = 0;
    int retries_left = REQUEST_RETRIES;

    while (retries_left) {
        std::stringstream request;
        request << ++sequence;
        zmq::message_t msm{request.str()};

        client.send(msm, zmq::send_flags::none);
        sleep (1);

        bool expect_reply = true;
        while (expect_reply) {
            //  Poll socket for a reply, with timeout
            zmq::pollitem_t items[] = {
                { client, 0, ZMQ_POLLIN, 0 } };
            zmq::poll (&items[0], 1, REQUEST_TIMEOUT);

            //  If we got a reply, process it
            if (items[0].revents & ZMQ_POLLIN) {
                zmq::message_t reply;
                client.recv(reply, zmq::recv_flags::none);
                //  We got a reply from the server, must match sequence
                std::string reply_str = reply.to_string() ;
                if (stoi(reply_str) == sequence) {
                    std::cout << "I: server replied OK (" << reply << ")" << std::endl;
                    retries_left = REQUEST_RETRIES;
                    expect_reply = false;
                }
                else {
                    std::cout << "E: malformed reply from server: " << reply << std::endl;
                }
            }
            else
            if (--retries_left == 0) {
                std::cout << "E: server seems to be offline, abandoning" << std::endl;
                expect_reply = false;
                break;
            }
            else {
                std::cout << "W: no response from server, retrying..." << std::endl;
                //  Old socket will be confused; close it and open a new one
                client = s_client_socket (context);
                //  Send request again, on new socket
                client.send(msm, zmq::send_flags::none);
            }
        }
    }
    return 0;
}