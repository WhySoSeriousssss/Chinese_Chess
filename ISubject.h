#ifndef ISUBJECT_H
#define ISUBJECT_H

#include "IObserver.h"
#include <list>

class ISubject {
public:
    ISubject() {

    }

    ~ISubject() {

    }

    void Attach(IObserver* observer) {
        _observers.push_back(observer);

    }

    void Detach(IObserver* observer) {
        _observers.remove(observer);
    }

    void Notify() {
        for (auto i = _observers.begin(); i != _observers.end(); i++) {
            (*i)->Update();
        }
    }

private:
    std::list<IObserver *> _observers;
};

#endif // ISUBJECT_H
