#ifndef CALC_CONTROLLER_
#define CALC_CONTROLLER_

#include "../model/polish_notation.h"

namespace s21 {
class CalcController {
 public:
  std::string GetRes(std::string func, std::string x) {
    loc_.SetStr(func, x);
    return loc_.GetResult();
  };

  bool GetError() { return loc_.GetError(); };

 private:
  PolishNotation loc_;
};
}  // namespace s21

#endif
