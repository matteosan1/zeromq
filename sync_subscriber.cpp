#include <zmq.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

  zmq::context_t context(1);

  zmq::socket_t subscriber(context, ZMQ_SUB);
  subscriber.connect("tcp://localhost:5561");
  subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

  zmq::socket_t syncclient(context, ZMQ_REQ);
  syncclient.connect("tcp://localhost:5562");

  zmq::message_t message(0);
  memcpy(message.data(), "", 0);
  syncclient.send(message);

  zmq::message_t request;
  syncclient.recv(&request);
  std::cout << "Connected to subscriber" << std::endl;
  
  int update_nbr = 0;
  while(1) {
    subscriber.recv(&request);
    std::cout << "received " << *(static_cast<std::string*>(request.data())) << std::endl;
    //if (strcmp((static_cast<std::string*>(request.data())), "ENDSocket-Type") == 0) {
    if (*(static_cast<std::string*>(request.data())) == "ENDSocket-Type") {
      std::cout << "FINE" << std::endl;
      break;
    }

    update_nbr++;
  }

  std::cout << "Received " << update_nbr << "updates" << std::endl;

  return 0;
}
