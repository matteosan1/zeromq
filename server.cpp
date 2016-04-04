#include "zmq.h"

#include <string.h>

#ifndef _WIN32
#include "unistd.h"
#else
#include "windows.h"
#endif

int main() {
  
  char buffer[32];
  
  void *context = zmq_ctx_new();
  void *requester = zmq_socket(context, ZMQ_PAIR);
  int rc = zmq_connect(requester, "tcp://localhost:5555");

  printf("Sender: Started\n");

  for (int i = 0; i < 10; ++i) {
#ifndef _WIN32
    sleep(1000);
#else
    Sleep(1000);
#endif
    sprintf(buffer, "Message %d", i + 1);
    printf("Sender: Sending (%s)\n", buffer);
    int rc = zmq_send(requester, buffer, strlen(buffer), 0);
  }
  
  zmq_close(requester);
  zmq_ctx_destroy(context);
  
  return 0;
}
