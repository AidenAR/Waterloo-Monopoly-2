#include "subject.h"
#include <string>

using namespace std;

void Subject::attach(Observer *o) { observers.emplace_back(o); }

void Subject::notifyObservers() {
    for (auto &ob : observers) ob->notify(this);
}

