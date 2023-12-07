#ifndef SCP_3DVIEWER_V2_OBSERVER_H
#define SCP_3DVIEWER_V2_OBSERVER_H

#include "scp_enums.h"

namespace scp {

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
}  // namespace scp
#endif  // SCP_3DVIEWER_V2_OBSERVER_H