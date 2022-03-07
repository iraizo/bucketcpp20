#include <chrono>
#include <ctime>
#include <iostream>
const time_t &get_epoch =
    std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch())
        .count();

class Bucket {
private:
  int tokens, amount;
  time_t last_consumed, last_refill, rate;

public:
  Bucket(int capacity, time_t rate, int amount) {
    this->tokens = capacity; /* how many tokens are being stored as a maximum */
    this->rate =
        rate; /* the rate in milliseconds when refills will be happening */
    this->amount = amount; /* amount being refilled */
    this->last_refill = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now().time_since_epoch())
                            .count();
    this->last_consumed =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();
  }

  bool consume() {
    if (tokens != 0) {
      last_consumed = std::chrono::duration_cast<std::chrono::milliseconds>(
                          std::chrono::system_clock::now().time_since_epoch())
                          .count();
      tokens -= 1;
      return 0;
    }
    return 1;
  }

  void refill() {
    time_t epoch = std::chrono::duration_cast<std::chrono::milliseconds>(
                       std::chrono::system_clock::now().time_since_epoch())
                       .count();
    std::cout << difftime(epoch, last_refill) << std::endl;
    if (difftime(epoch, last_refill) > rate) {
      last_refill = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch())
                        .count();
      this->tokens = amount;
    }
    return;
  }

  void *handle(void *ptr) {
    refill();
    /*  accept the packet if tokens are available */
    if (!consume()) {
      return ptr;
    }
    return NULL;
  }
};
