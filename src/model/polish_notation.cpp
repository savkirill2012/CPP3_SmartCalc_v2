#include "polish_notation.h"

#include "sstream"

PolishNotation::list PolishNotation::GetData() { return data_; }

bool PolishNotation::GetError() { return error_; }

void PolishNotation::SetStr(str str_to_set, str x_val) {
  x_val_.clear();

  int len = x_val.length();
  for (int i = 0; i < len; ++i) {
    if (!((x_val[i] >= '0' && x_val[i] <= '9') || x_val[i] == '.' ||
          (i == 0 && x_val[i] == '-' && x_val.length() > 1))) {
      x_val = "";
    }
  }

  if (x_val != "") {
    x_val_ = x_val;
  }

  data_.clear();
  error_ = 0;

  basic_str_ = str_to_set;
  _lexem_parser();
  _check_order();
  if (error_ == 0) {
    _change_x_val();
    if (error_ == 0) {
      _polish_notation();
    }
  }

  if (error_ == 0) {
    result_ = _convert_to_res();
  } else {
    result_ = "ERROR";
  }
}

PolishNotation::str PolishNotation::GetResult() { return result_; }

/**
 * @brief lexem parser
 */
void PolishNotation::_lexem_parser() {
  size len = basic_str_.size();
  str loc_str;
  for (size i = 0; i < len; ++i) {
    if (basic_str_[i] == '(' || basic_str_[i] == ')' || basic_str_[i] == ' ') {
      Node add_node;

      if (loc_str.size() != 0) {
        add_node.loc_str = loc_str;
        if (type_of_node_.find(loc_str) == type_of_node_.end()) {
          add_node.type = NUMBER;
          add_node.priority = 0;
        } else {
          add_node.type = type_of_node_[loc_str];
          add_node.priority = priority_of_node_[loc_str];
        }

        data_.push_back(add_node);
      }

      if (basic_str_[i] == '(' || basic_str_[i] == ')') {
        add_node.loc_str = basic_str_[i];
        add_node.type = type_of_node_[add_node.loc_str];
        add_node.priority = priority_of_node_[loc_str];
        data_.push_back(add_node);
      }

      loc_str.clear();
    } else {
      loc_str += basic_str_[i];
    }
  }

  // rewrigth
  if (loc_str.size() != 0) {
    Node add_node;
    add_node.loc_str = loc_str;
    if (type_of_node_.find(loc_str) == type_of_node_.end()) {
      add_node.type = NUMBER;
      add_node.priority = 0;
    } else {
      add_node.type = type_of_node_[loc_str];
      add_node.priority = priority_of_node_[loc_str];
    }

    data_.push_back(add_node);
  }
}

void PolishNotation::_check_order() {
  list::iterator start = data_.begin();
  list::iterator end = data_.end();
  operands prev_oper, cur_oper = start->type;
  // bool unar_flag = 0;
  std::list<list::iterator> massiv_itr_del;

  if (!(cur_oper == 1 || cur_oper == 3 || cur_oper >= 9)) {
    error_ = 1;
  } else {
    for (++start; start != end; ++start) {
      prev_oper = cur_oper;
      cur_oper = start->type;

      if ((prev_oper == NUMBER || prev_oper == CLOSE_BRACKET ||
           prev_oper == X || prev_oper == MX) &&
          (cur_oper >= 2 && cur_oper <= 8)) {
        continue;
      } else if (((prev_oper >= 2 && prev_oper <= 7) ||
                  prev_oper == OPEN_BRACKET) &&
                 (cur_oper == 1 || cur_oper >= 9)) {
        continue;
      } else if (prev_oper >= 10 && prev_oper <= 18 &&
                 (cur_oper == OPEN_BRACKET)) {
        continue;
      } else {
        error_ = 1;
        break;
      }
    }

    for (std::list<list::iterator>::iterator st = massiv_itr_del.begin(),
                                             end = massiv_itr_del.end();
         st != end; ++st) {
      data_.erase(*st);
    }

    --end;
    if (end->type != NUMBER && end->type != X && end->type != MX &&
        end->type != CLOSE_BRACKET) {
      error_ = 1;
    }
  }
}

void PolishNotation::_polish_notation() {
  std::stack<Node> stack;
  list::iterator start = data_.begin();
  list::iterator end = data_.end();
  list new_data;

  for (; start != end; ++start) {
    operands cur_type = start->type;
    if (cur_type == NUMBER || cur_type == X || cur_type == MX) {
      new_data.push_back(*start);
    } else if (cur_type == OPEN_BRACKET || (cur_type >= 10 && cur_type <= 18)) {
      stack.push(*start);
    } else if (cur_type == CLOSE_BRACKET) {
      Node tmp;
      if (stack.size() != 0) {
        tmp = stack.top();
        while (tmp.type != OPEN_BRACKET) {
          new_data.push_back(tmp);
          if (stack.size() == 1) {
            error_ = 1;
            break;
          }
          stack.pop();
          tmp = stack.top();
        }

        if (tmp.type == OPEN_BRACKET) {
          stack.pop();
        }
      } else {
        error_ = 1;
      }
    } else if (cur_type >= 2 && cur_type <= 7) {
      Node tmp;
      if (stack.size() != 0) {
        tmp = stack.top();
        if (tmp.priority > start->priority) {
          while (tmp.type != OPEN_BRACKET) {
            new_data.push_back(tmp);
            stack.pop();
            if (stack.size() != 0) {
              tmp = stack.top();
            } else {
              break;
            }
          }
        }
      }
      stack.push(*start);
    }

    if (error_ == 1) {
      break;
    }
  }

  while (stack.size() != 0) {
    if (stack.top().type == OPEN_BRACKET) {
      error_ = 1;
      break;
    }
    new_data.push_back(stack.top());
    stack.pop();
  }

  data_ = new_data;
}

void PolishNotation::_change_x_val() {
  std::stack<Node> stack;
  list::iterator start = data_.begin();
  list::iterator end = data_.end();
  list new_data;

  for (; start != end; start++) {
    if ((*start).type == X) {
      if (x_val_ != "") {
        (*start).type = NUMBER;
        (*start).loc_str = x_val_;
      } else {
        error_ = 1;
        break;
      }
    } else if ((*start).type == MX) {
      if (x_val_ != "") {
        (*start).type = NUMBER;
        if (x_val_[0] == '-') {
          (*start).loc_str = x_val_.erase(0, 1);
        } else {
          (*start).loc_str = "";
          (*start).loc_str = "-" + x_val_;
        }
      } else {
        error_ = 1;
        break;
      }
    }
  }
}

PolishNotation::str PolishNotation::_convert_to_res() {
  std::stack<Node> stack;

  for (list::iterator start = data_.begin(), end = data_.end(); start != end;
       ++start) {
    std::ostringstream out;
    out.precision(12);

    if ((*start).type == NUMBER) {
      stack.push(*start);
    } else if (start->type >= 10 && start->type <= 18) {
      // oper with 1 arg
      try {
        out << std::fixed
            << (funct_map_[start->type])(std::stod(stack.top().loc_str));
        stack.top().loc_str = std::move(out).str();
      } catch (...) {
        error_ = 1;
        return "Error";
      }
    } else {
      // oper with 2 args
      operands loc_oper = start->type;
      Node last_n = stack.top();
      stack.pop();
      if (loc_oper == MULTIPLICATION) {
        out << std::fixed
            << std::stod(stack.top().loc_str) * std::stod(last_n.loc_str);
      } else if (loc_oper == PLUS) {
        out << std::fixed
            << std::stod(stack.top().loc_str) + std::stod(last_n.loc_str);
      } else if (loc_oper == MINUS) {
        out << std::fixed
            << std::stod(stack.top().loc_str) - std::stod(last_n.loc_str);
      } else if (loc_oper == DIVISION) {
        out << std::fixed
            << std::stod(stack.top().loc_str) / std::stod(last_n.loc_str);
      } else if (loc_oper == POWER) {
        out << std::fixed
            << pow(std::stod(stack.top().loc_str), std::stod(last_n.loc_str));
      } else if (loc_oper == MOD) {
        out << std::fixed
            << fmod(std::stod(stack.top().loc_str), std::stod(last_n.loc_str));
      }
      stack.top().loc_str = std::move(out).str();
    }
  }

  try {
    double testval1 = std::stod(stack.top().loc_str);
    int testvall2 = std::stoi(stack.top().loc_str);
    double res = fabs(testval1 - testvall2);
    if (res < 0.00000000001) {
      stack.top().loc_str = std::to_string(std::stoi(stack.top().loc_str));
    } else {
      stack.top().loc_str = stack.top().loc_str.substr(
          0, stack.top().loc_str.find_last_not_of('0') + 1);
    }
  } catch (...) {
    error_ = 1;
    return "Error";
  }

  return stack.top().loc_str;
}
