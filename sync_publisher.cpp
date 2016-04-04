#include <zmq.hpp>
#include "zhelpers.hpp"

#include <iostream>
#include <unistd.h>

#define SUBSCRIBERS_EXPECTED 10

int main(int argc, char* argv[]) {
  zmq::context_t context(1);

  zmq::socket_t publisher(context, ZMQ_PUB);

  int sndhwm = 0;
  publisher.setsockopt(ZMQ_SNDHWM, &sndhwm, sizeof(sndhwm));

  publisher.bind("tcp://*:5561");

  zmq::socket_t syncservice(context, ZMQ_REP);
  syncservice.bind("tcp://*:5562");

  int subscribers = 0;
  while (subscribers < SUBSCRIBERS_EXPECTED) {
    s_recv(syncservice);

    std::cout << "Added new subscriber" << std::endl;
    s_send(syncservice, "");

    subscribers++;
  }

  int update_nbr;
  for (update_nbr=0; update_nbr<1000000; update_nbr++) {
    s_send(publisher, "Rhubarb");
  }

  s_send(publisher, "END");

  sleep(1);
  return 0;
}
