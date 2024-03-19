#ifndef POLISH_NOTATION_
#define POLISH_NOTATION_

#include <math.h>

#include <iostream>
#include <list>
#include <map>
#include <stack>
#include <string>

enum operands {
  NUMBER = 1,      // 1
  PLUS,            // 2
  MINUS,           // 3
  MULTIPLICATION,  // 4
  DIVISION,        // 5
  POWER,           // 6
  MOD,             // 7
  CLOSE_BRACKET,   // 8
  OPEN_BRACKET,    // 9
  COS,             // 10
  SIN,             // 11
  TAN,             // 12
  ACOS,            // 13
  ASIN,            // 14
  ATAN,            // 15
  SQRT,            // 16
  LN,              // 17
  LOG,             // 18
  X,               // 19
  MX               // 20
};

struct Node {
  using str = std::string;

  str loc_str;
  operands type;
  int priority;
};

/**
 * Main function
 */
class PolishNotation {
 public:
  using str = std::string;
  using list = std::list<Node>;
  using size = std::size_t;
  using map = std::map<char, int>;

  str GetResult();
  list GetData();
  bool GetError();
  void SetStr(str str_to_set, str x_val = "");
  // void SetX(str x_val);

 private:
  str basic_str_;
  list data_;
  bool error_ = 0;
  str result_;
  str x_val_;

  std::map<str, operands> type_of_node_ = {{"^", POWER},
                                           {"+", PLUS},
                                           {"mod", MOD},
                                           {"-", MINUS},
                                           {"*", MULTIPLICATION},
                                           {"/", DIVISION},
                                           {"cos", COS},
                                           {"sin", SIN},
                                           {"tan", TAN},
                                           {"asin", ASIN},
                                           {"acos", ACOS},
                                           {"atan", ATAN},
                                           {"sqrt", SQRT},
                                           {"ln", LN},
                                           {"log", LOG},
                                           {"(", OPEN_BRACKET},
                                           {")", CLOSE_BRACKET},
                                           {"x", X},
                                           {"-x", MX}};

  std::map<str, int> priority_of_node_ = {
      {"^", 3},    {"+", 1},    {"mod", 2},  {"-", 1},   {"*", 2},
      {"/", 2},    {"cos", 4},  {"sin", 4},  {"tan", 4}, {"asin", 4},
      {"acos", 4}, {"atan", 4}, {"sqrt", 4}, {"ln", 4},  {"log", 4},
      {"(", -1},   {")", 5},    {"x", 0}};

  std::map<operands, double (*)(double)> funct_map_ = {
      {COS, &cos},   {SIN, &sin},   {TAN, &tan},  {ACOS, &acos}, {ASIN, &acos},
      {ATAN, &atan}, {SQRT, &sqrt}, {LN, &log10}, {LOG, &log}};

  void _lexem_parser();
  void _check_order();
  void _polish_notation();
  void _change_x_val();
  str _convert_to_res();
};

#endif