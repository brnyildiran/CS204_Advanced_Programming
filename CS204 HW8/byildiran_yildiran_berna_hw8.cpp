#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <random> 
#include <time.h>
#include <iomanip> 
#include <chrono>
#include <sstream>
#include "HW8DynIntQueue.h"
using namespace std;
/*
 *********************************************************
 Dynamic Queue Code for Cashiers by Using Threads
 by Berna Yildiran
 *********************************************************
*/

HW8DynIntQueue myShopQueue;
mutex myMute, insideMute;
int i = 1; //Counter variable that shared by all functions

string whatTimeIsIt() //Time function that gets current time of the system
{
	stringstream ss;
	time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
	struct tm *ptm = new struct tm;  //creating the time struct to be used in thread
	localtime_s(ptm, &tt);  //converting the time structures   

	ss << std::put_time(ptm,"%X");//displaying the time
	return ss.str();
}

int random_range(const int & min, const int & max) //Random range
{
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

void EnqueueCustomer(int customerAmount, int min_arrival, int max_arrival) //Enqueue
{
	for( i ; i <= customerAmount; i++) //Enqueue customers according to total_customer_count
	{
		myMute.lock();
		myShopQueue.enqueue(i);
		myMute.unlock();

		insideMute.lock();
		cout << "New customer with ID " << i << " has arrived (queue size is "
			 << myShopQueue.getCurrentSize() << "): " << whatTimeIsIt() << endl;
		insideMute.unlock();

		int RandomCheckout = random_range(min_arrival, max_arrival);
		this_thread::sleep_for(chrono::seconds(RandomCheckout));
	}
}


void DequeueCustomer(int customerAmount,int cashierID, int threshold, int min_checkout, int max_checkout) 
//Dequeue used by both Cashiers
{
	int RandomCheckout = random_range(min_checkout, max_checkout);
	this_thread::sleep_for(chrono::seconds(RandomCheckout));

	int current;

	for(int i =1 ; i <= customerAmount; i++) //Dequeue customers according to total_customer_count
	{
		myMute.lock();
		if (cashierID == 1 && !myShopQueue.isEmpty()) //If there is customer and Cashier 1
		{  
			myShopQueue.dequeue(current);
			myMute.unlock();

			insideMute.lock();
			cout << "Cashier " << cashierID << " started transaction with customer " << current
				<< " (queue size is " << myShopQueue.getCurrentSize() << "): " << whatTimeIsIt() << endl;
			insideMute.unlock();

			int RandomCheckout = random_range(min_checkout, max_checkout);
			this_thread::sleep_for(chrono::seconds(RandomCheckout));

			insideMute.lock();
			cout << "Cashier " << cashierID << " finished transaction with customer " << current << " " << whatTimeIsIt() << endl;
			insideMute.unlock();
		}
		else if(cashierID == 2 && myShopQueue.getCurrentSize() >= threshold && !myShopQueue.isEmpty()) 
		// If there is customer AND number of customer waiting in the queue is more than threshold of Cahier 2 AND Cashier 2
		{
			myShopQueue.dequeue(current);
			myMute.unlock();

			insideMute.lock();
			cout << "Cashier " << cashierID << " started transaction with customer " << current
				<< " (queue size is " << myShopQueue.getCurrentSize() << "): " << whatTimeIsIt() << endl;
			insideMute.unlock();

			int RandomCheckout = random_range(min_checkout, max_checkout);
			this_thread::sleep_for(chrono::seconds(RandomCheckout));

			insideMute.lock();
			cout << "Cashier " << cashierID << " finished transaction with customer " << current << " " << whatTimeIsIt() << endl;
			insideMute.unlock();
		}
		else
		//For Cashier 2 in the situation of customer number is smaller than threshold of Cashier2
		{
			myMute.unlock();
			i--;
		}
	}
}


int main()
{
	int total_customer_count, cashier2_threshold;
	int min_arrival, max_arrival;
	int max_checkout_time, min_checkout_time;

	cout << "Please enter the total number of customers: ";
	cin >> total_customer_count;

	cout << "Please enter the number of customers waiting in the queue to open the second cashier: ";
	cin >> cashier2_threshold;

	cout << "Please enter the inter-arrival time range between two customers: " << endl;
	cout << "Min: ";
	cin >> min_arrival;
	cout << "Max: ";
	cin >> max_arrival;

	cout << "Please enter the checkout time range of cashiers: " << endl;
	cout << "Min: ";
	cin >> min_checkout_time;
	cout << "Max: ";
	cin >> max_checkout_time;

	cout << "Simulation starts " << whatTimeIsIt() << endl; //Displaying the time

	thread CustomerArrival(&EnqueueCustomer,total_customer_count, min_arrival, max_arrival);
	thread Cashier_1(&DequeueCustomer, total_customer_count, 1, cashier2_threshold, min_checkout_time, max_checkout_time); //Serve customer all the time
	thread Cashier_2(&DequeueCustomer, total_customer_count, 2, cashier2_threshold, min_checkout_time, max_checkout_time); //Serves customer after threshold

	CustomerArrival.join();
	Cashier_1.join();
	Cashier_2.join();
	cout << "End of the simulation ends: " << whatTimeIsIt() << endl;

	return 0;
}