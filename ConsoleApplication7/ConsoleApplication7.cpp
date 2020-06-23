// ConsoleApplication7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>           // std::cout
#include <thread>             // std::thread, std::this_thread::yield
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

std::mutex mtx;
std::condition_variable cv;

bool hmmm = 1;

bool should_i_do_it() {
	return hmmm;
}

void print() {
	std::unique_lock<std::mutex> lck(mtx);
	cv.wait(lck, should_i_do_it);
	std::cout << "Ok, I did it" << std::endl;
}


int main()
{
	std::thread consumer_thread(print);

	// produce 10 items when needed
	
	while (should_i_do_it()) {
		std::this_thread::yield();
		std::unique_lock<std::mutex> lck(mtx);
	}

		cv.notify_all();
	

	consumer_thread.join();

	return 0;
}
