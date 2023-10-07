#include <thread>
#include <iostream>
#include <boost/lockfree/spsc_queue.hpp>

boost::lockfree::spsc_queue<int> q{500};
int sum = 0;

void produce()
{
    for (int i = 1; i <= 500; i++)
        q.push(i);
}

void consume()
{
    int i;
    while (q.pop(i))
        sum += i;
}

int main()
{
    std::thread th1{produce};
    std::thread th2{consume};
    th1.join();
    th2.join();
    consume();
    std::cout << "Sum of Queue: " << sum << std::endl;
}