#ifndef S21_3DVIEWER_V2_OBSERVER_H
#define S21_3DVIEWER_V2_OBSERVER_H

#include "s21_enums.h"

namespace s21 {

class Observer {
 public:
  virtual ~Observer(){};
  virtual void UpdateObserver(EventType event) = 0;
};

class Observable {
 public:
  virtual ~Observable(){};
  virtual void AddObserver(Observer* observer) = 0;
  virtual void RemoveObserver(Observer* observer) = 0;
  virtual void Notify(EventType event) = 0;
};
}  // namespace s21
#endif  // S21_3DVIEWER_V2_OBSERVER_H