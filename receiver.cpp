#include "zmq.h"

int main() {
  void *context = zmq_ctx_new();
  void *responder = zmq_socket(context, ZMQ_PAIR);
  int rc = zmq_bind(responder, "tcp://*:5555");

  printf("Receiver: Started\n");
  char buffer[128];
  while (true) {
    int num = zmq_recv(responder, buffer, 128, 0);
    if (num > 0) {
      buffer[num] = '\0';
      printf("Receiver: Received (%s)\n", buffer);
    }
  }

  return 0;
}
