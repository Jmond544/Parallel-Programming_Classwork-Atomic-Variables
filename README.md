# Classwork: obtain the same number of Vegetable_count:

We have the source code of the program that counts the number of vegetables chopped by two threads. But we see that the number of vegetables is different for each thread. We need to fix the program so that the number of vegetables is the same for each thread.

The file of the original program is [here](./Original_Code.cpp).

```c++
#include <thread>
#include <iostream>
#include <chrono>

bool chopping = true;

void vegetable_chopper(const char* name) {
    unsigned int vegetable_count = 0;
    while (chopping) {
        vegetable_count++;
    }
    printf("%s chopped %u vegetables.\n", name, vegetable_count);
}

int main() {
    std::thread olivia(vegetable_chopper, "Olivia");
    std::thread barron(vegetable_chopper, "Barron");

    printf("Barron and Olivia are chopping vegetables...\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    chopping = false;
    barron.join();
    olivia.join();
}
```

## Solution

The solution is [here](./Adapted_code.cpp).

### Explanation

The solution that I propose is to use the `std::atomic` library. This library allows us to create atomic variables, that is, variables that can be accessed by several threads at the same time without having to worry about the order of access.

### Diferences

- **Atomic Variables:** In the new code, atomic variables (`std::atomic<bool>` chopping and `std::atomic<unsigned int> vegetable_count`) are used to ensure thread-safe operations. This prevents race conditions and ensures that operations, such as updating `vegetable_count`, occur atomically and without interruptions from other threads.

- **Use of `load()`:** In the new code, the `load()` function is used on `vegetable_count` before printing its value. This ensures that we obtain the current value of `vegetable_count` safely, avoiding potential inconsistencies if another thread is modifying the variable simultaneously.

```c++
#include <thread>
#include <chrono>
#include <atomic>
#include <iostream>

std::atomic<bool> chopping(true);
std::atomic<unsigned int> vegetable_count(0);

void vegetable_chopper(const char* name) {
    while (chopping) {
        vegetable_count++;
    }
    printf("%s chopped %u vegetables.\n", name, vegetable_count.load());
}

int main() {
    std::thread olivia(vegetable_chopper, "Olivia");
    std::thread barron(vegetable_chopper, "Barron");

    printf("Barron and Olivia are chopping vegetables...\n");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    chopping = false;

    barron.join();
    olivia.join();

    return 0;
}
```

## Result:

