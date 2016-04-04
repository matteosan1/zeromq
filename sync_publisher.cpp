#include <zmq.hpp>
#include <unistd.h>

#include <iostream>

#define SUBSCRIBERS_EXPECTED 1

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
    zmq::message_t request;
    syncservice.recv(&request);

    std::cout << "Added new subscriber" << std::endl;
    zmq::message_t reply(0);
    memcpy(reply.data(), "", 0);
    syncservice.send(reply);

    subscribers++;
  }

  int update_nbr;
  for (update_nbr=0; update_nbr<1; update_nbr++) {
    zmq::message_t message(7);
    memcpy(message.data(), "Rhubarb\0", 7);
    publisher.send(message);
  }
  zmq::message_t endmessage(3);
  memcpy(endmessage.data(), "END\0", 3);
  publisher.send(endmessage);

  sleep(1);
  return 0;
}
