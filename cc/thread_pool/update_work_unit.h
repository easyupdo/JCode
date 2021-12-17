#ifndef _UPDATE_WORK_UNIT_H_
#define _UPDATE_WORK_UNIT_H_

#include <iostream>

#include "work_unit.h"

class UpdateWorkUnit : public WorkUnit {
 public:
  UpdateWorkUnit() = default;
  explicit UpdateWorkUnit(const std::string &work_str) : str_(work_str){}
  virtual ~UpdateWorkUnit() {}

  void Run() override { std::cout << str_ << std::endl; }

 private:
  std::string str_{};
};

#endif  //_UPDATE_WORK_UNIT_H_