#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>

// Atomic variables to ensure thread-safe operations
std::atomic<bool> chopping(true);                   // Indicates whether chopping should continue
std::atomic<unsigned int> vegetable_count(0);       // Counter for chopped vegetables

// Function simulating vegetable chopping
void vegetable_chopper(const char* name) {
    while (chopping) {
        vegetable_count++;  // Increment vegetable count atomically
    }
    printf("%s chopped %u vegetables.\n", name, vegetable_count.load());
    // Use load() to safely obtain the current value of vegetable_count
}

int main() {
    // Create threads for Olivia and Barron
    std::thread olivia(vegetable_chopper, "Olivia");
    std::thread barron(vegetable_chopper, "Barron");

    // Display an informative message
    printf("Barron and Olivia are chopping vegetables...\n");

    // Wait for 1 second before stopping vegetable chopping
    std::this_thread::sleep_for(std::chrono::seconds(1));
    chopping = false;  // Stop vegetable chopping

    // Wait for both threads to finish their execution
    barron.join();
    olivia.join();
    
    return 0;
}
