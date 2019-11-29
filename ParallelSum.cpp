/* Sum an array with two threads in parallel */

#include <iostream>
#include <thread>
#include <mutex>

bool first = true;
const int NUM = 1000;
std::mutex mutex_lock;

int add(const int (&a)[NUM], const int (&b)[NUM], int &sum){
    int offset = 1;

    mutex_lock.lock();
    if (first == true){
        first = false;
        offset = 0;
    }
    mutex_lock.unlock();

    int res = 0;
    for (int i = 0; 2 * i + offset < NUM; i++){
        res += a[2 * i + offset] + b[2 * i + offset];
    }

    mutex_lock.lock();
    sum += res;
    mutex_lock.unlock();

    return 0;
}


int main() {
    int a[NUM], b[NUM];
    int sum = 0, regular_sum = 0;

    for (int i = 0; i < NUM; i++){
        a[i] = i;
        b[i] = i;
        regular_sum += a[i] + b[i];
    }

    std::thread worker1(add, std::ref(a), std::ref(b), std::ref(sum));
    std::thread worker2(add, std::ref(a), std::ref(b), std::ref(sum));

    worker1.join();
    worker2.join();

    std::cout << "Sum: " << regular_sum << std::endl;
    std::cout << "Parallel sum: " << sum << std::endl;

    return 0;
}
