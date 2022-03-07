#include "bucket.h"
#include <chrono>
#include <cstdio>
#include <iostream>
#include <thread>

int main() {
  Bucket bucket(25, 5000, 25);
  void *packet = (void *)0x1337;
  for (;;) {
    void *packet = (void *)0x1337;
    if (bucket.handle(packet) == packet) {
      printf("Packet received\n");
    } else {
      printf("Packet deleted: %p\n", packet);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
  }

  return 0;
}
