#ifndef OBSERVER_H
#define OBSERVER_H

#include <algorithm>
#include <vector>
//#include <windows.h>
//#include <chrono>
//#include <thread>

using std::vector;

class Observer
{
public:
    virtual void update() = 0;
};

class Observable
{
private:
    vector<Observer*> observers;
public:
    void addObserver(Observer* obs)
    {
        observers.push_back(obs);
    }
    void removeObserver(Observer* obs)
    {
        observers.erase(std::remove(begin(observers), end(observers),obs), observers.end());
    }
protected:
    void notify()
    {
        for(auto obs:observers)
        {
            //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            obs->update();
        }
    }
};

#endif // OBSERVER_H
