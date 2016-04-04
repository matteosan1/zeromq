#include <zmq.hpp>
#include <iostream>
#include <string>
#include "zhelpers.hpp"

int main(int argc, char* argv[]) {

  zmq::context_t context(1);

  zmq::socket_t subscriber(context, ZMQ_SUB);
  subscriber.connect("tcp://localhost:5561");
  subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

  zmq::socket_t syncclient(context, ZMQ_REQ);
  syncclient.connect("tcp://localhost:5562");

  s_send(syncclient, "");

  s_recv(syncclient);
  std::cout << "Connected to subscriber" << std::endl;
  
  int update_nbr = 0;
  while(1) {
    if (s_recv(subscriber).compare("END") == 0) {
      std::cout << "FINE" << std::endl;
      break;
    }

    update_nbr++;
  }

  std::cout << "Received " << update_nbr << "updates" << std::endl;

  return 0;
}
