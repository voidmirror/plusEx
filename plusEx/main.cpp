//#include <iostream>
//#include <string>
//#include <cstdlib>
//#include <map>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//class Calendar {
//	int year;
//	multimap<int, string> events;
//
//	Calendar& operator=(const Calendar& c) {
//		year = c.year;
//		for (auto element : c.events) {
//			events.insert(element);
//		}
//	}
//private:
//
//public:
//	vector <string> dayEvent(int day) {
//		vector <string> ev;
//		for (auto element : events) {
//			ev.push_back(element.second);
//		}
//	}
//};
//
//void cycle(vector <int> v, int step) {
//	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
//	{
//		if (abs(*it - step) / step * 100 > 0.1) {
//			cout << *it << " ";
//		}
//	}
//}
//
//void cycleLambda(vector <int> v, int step) {
//	for_each(begin(v), end(v), [](int n) {cout << n << endl; });
//}
//
//int main() {
//	vector <int> v = { 1, 2, 3, 4, 5 };
//	cycle(v, 100);
//	cycleLambda(v, 100);
//}


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mu;
std::condition_variable cond;
int count = 1;

void PrintOdd()
{
	for (; count < 100;)
	{
		std::unique_lock<std::mutex> locker(mu);
		cond.wait(locker, [](){ return (count % 2 == 1); });
		std::cout << "From Odd:    " << count << std::endl;
		count++;
		locker.unlock();
		cond.notify_all();
	}

}

void PrintEven()
{
	for (; count < 100;)
	{
		std::unique_lock<std::mutex> locker(mu);
		cond.wait(locker, [](){ return (count % 2 == 0); });
		std::cout << "From Even: " << count << std::endl;
		count++;
		locker.unlock();
		cond.notify_all();
	}
}

int main()
{
	std::thread t1(PrintOdd);
	std::thread t2(PrintEven);
	t1.join();
	t2.join();
	return 0;
}