#include "mainwindow.h"

#include "../controller/calc_controller.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  QFont font("Courier New");
  font.setStyleHint(QFont::Monospace);
  QApplication::setFont(font);
  QApplication::setStyle("Fusion");
  ui->setupUi(this);

  // num Buttons
  connect(ui->butt0, SIGNAL(clicked()), this, SLOT(add_to_lable()));
  connect(ui->butt1, SIGNAL(clicked()), this, SLOT(add_to_lable()));
  connect(ui->butt2, SIGNAL(clicked()), this, SLOT(add_to_lable()));
  connect(ui->butt3, SIGNAL(clicked()), this, SLOT(add_to_lable()));
  connect(ui->butt4, SIGNAL(clicked()), this, SLOT(add_to_lable()));
  connect(ui->butt5, SIGNAL(clicked()), this, SLOT(add_to_lable()));
  connect(ui->butt6, SIGNAL(clicked()), this, SLOT(add_to_lable()));
  connect(ui->butt7, SIGNAL(clicked()), this, SLOT(add_to_lable()));
  connect(ui->butt8, SIGNAL(clicked()), this, SLOT(add_to_lable()));
  connect(ui->butt9, SIGNAL(clicked()), this, SLOT(add_to_lable()));

  // brakets and point buttons
  connect(ui->buttCloseBrackets, SIGNAL(clicked()), this,
          SLOT(add_cb_to_lable()));
  connect(ui->buttOpenBrackets, SIGNAL(clicked()), this, SLOT(add_to_lable()));
  connect(ui->buttPoint, SIGNAL(clicked()), this, SLOT(add_to_lable()));

  // operation buttons
  connect(ui->buttPlus, SIGNAL(clicked()), this, SLOT(add_oper_to_lable()));
  connect(ui->buttMinus, SIGNAL(clicked()), this, SLOT(add_oper_to_lable()));
  connect(ui->buttMulti, SIGNAL(clicked()), this, SLOT(add_oper_to_lable()));
  connect(ui->buttDevide, SIGNAL(clicked()), this, SLOT(add_oper_to_lable()));
  connect(ui->buttMod, SIGNAL(clicked()), this, SLOT(add_oper_to_lable()));
  connect(ui->buttPow, SIGNAL(clicked()), this, SLOT(add_oper_to_lable()));

  // function buttons
  connect(ui->buttSin, SIGNAL(clicked()), this, SLOT(add_func_to_lable()));
  connect(ui->buttCos, SIGNAL(clicked()), this, SLOT(add_func_to_lable()));
  connect(ui->buttTan, SIGNAL(clicked()), this, SLOT(add_func_to_lable()));
  connect(ui->buttASin, SIGNAL(clicked()), this, SLOT(add_func_to_lable()));
  connect(ui->buttACos, SIGNAL(clicked()), this, SLOT(add_func_to_lable()));
  connect(ui->buttATan, SIGNAL(clicked()), this, SLOT(add_func_to_lable()));
  connect(ui->buttSqrt, SIGNAL(clicked()), this, SLOT(add_func_to_lable()));
  connect(ui->buttLog, SIGNAL(clicked()), this, SLOT(add_func_to_lable()));
  connect(ui->buttLn, SIGNAL(clicked()), this, SLOT(add_func_to_lable()));

  // x button
  connect(ui->buttX, SIGNAL(clicked()), this, SLOT(add_x_to_lable()));

  // unar button
  connect(ui->buttUnar, SIGNAL(clicked()), this, SLOT(add_unar_lable()));

  // clear button
  connect(ui->buttClear, SIGNAL(clicked()), this, SLOT(clear_lable()));

  // clear last obj
  connect(ui->buttRemove, SIGNAL(clicked()), this, SLOT(clear_last_char()));

  // equal button
  connect(ui->buttEqual, SIGNAL(clicked()), this, SLOT(get_res()));

  // plot func
  connect(ui->buttDraw, SIGNAL(clicked()), this, SLOT(graph_logic()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::add_to_lable() {
  QPushButton* button = (QPushButton*)sender();
  if (ui->label->text().right(1).toLower() == "r") {
    ui->label->clear();
  }

  if (ui->label->text().right(1) == "x") {
    ui->label->setText(ui->label->text() + " " + button->text());
  } else {
    ui->label->setText(ui->label->text() + button->text());
  }
}

void MainWindow::add_x_to_lable() {
  QPushButton* button = (QPushButton*)sender();
  if (ui->label->text().right(1).toLower() == "r") {
    ui->label->clear();
  }

  QString last_char = ui->label->text().right(1);
  if ((last_char >= "0" && last_char <= "9") || last_char == ".") {
    ui->label->setText(ui->label->text() + " " + button->text().toLower());
  } else {
    ui->label->setText(ui->label->text() + button->text().toLower());
  }
}

void MainWindow::add_cb_to_lable() {
  QPushButton* button = (QPushButton*)sender();
  if (ui->label->text().right(1).toLower() == "r") {
    ui->label->clear();
  }

  QString str = ui->label->text();
  if (str.right(2) == "x ") {
    str.remove(str[str.length() - 1]);
    ui->label->setText(str + button->text());
  } else {
    ui->label->setText(str + button->text());
  }
}

void MainWindow::add_oper_to_lable() {
  QPushButton* button = (QPushButton*)sender();
  if (ui->label->text().right(1).toLower() == "r") {
    ui->label->clear();
  }

  ui->label->setText(ui->label->text() + " " + button->text() + " ");
}

void MainWindow::add_func_to_lable() {
  QPushButton* button = (QPushButton*)sender();
  if (ui->label->text().right(1).toLower() == "r") {
    ui->label->clear();
  }

  QString last_char = ui->label->text().right(1);
  if ((last_char >= "0" && last_char <= "9") || last_char == "." ||
      last_char == 'x') {
    ui->label->setText(ui->label->text() + " " + button->text() + "(");
  } else {
    ui->label->setText(ui->label->text() + button->text() + "(");
  }
}

void MainWindow::clear_lable() { ui->label->setText(""); }

void MainWindow::clear_last_char() {
  QString str = ui->label->text();
  if (str.length() != 0) {
    QChar last_char = str[str.length() - 1];

    if ((last_char >= '0' && last_char <= '9') || last_char == ')' ||
        last_char == 'x' || last_char == '.') {
      str.resize(str.length() - 1);
    } else {
      int i = 1;
      if (str.length() - (1 + i) >= 0) {
        last_char = str[str.length() - (1 + i)];
        while (last_char != ' ' && last_char != '(' &&
               !((last_char >= '0' && last_char <= '9') || last_char == '.') &&
               str.length() - (1 + i) > 0) {
          i++;
          last_char = str[str.length() - (1 + i)];
        }

        if (str.length() - (1 + i) <= 0) {
          str = "";
        } else if (last_char == '(' ||
                   (last_char == ' ' && (str[str.length() - i] == '(' ||
                                         (str[str.length() - i] >= 'a' &&
                                          str[str.length() - i] <= 'z'))) ||
                   (last_char >= '0' && last_char <= '9') || last_char == '.') {
          str.resize(str.length() - (i));
        } else {
          str.resize(str.length() - (1 + i));
        }
      } else {
        str = "";
      }
    }
  }

  ui->label->setText(str);
}

void MainWindow::get_res() {
  std::string str = ui->label->text().toStdString();
  s21::CalcController controller;
  std::string x = ui->xLabel->text().toStdString();

  ui->label->setText(QString::fromStdString(controller.GetRes(str, x)));
}

void MainWindow::add_unar_lable() {
  QString str = ui->label->text();

  if (str.length() != 0) {
    QChar last_char = str[str.length() - 1];
    int i = 0;

    while (str.length() - i != 0 && ((last_char >= '0' && last_char <= '9') ||
                                     last_char == '.' || last_char == 'x')) {
      last_char = str[str.length() - (i + 1)];
      i++;
    }

    if (i == 0) {
      return;
    }

    if (last_char == '-') {
      last_char = str[str.length() - (i - 1)];

      while (i != 0) {
        str[str.length() - (i)] = last_char;
        i--;
        if (i != 0) {
          last_char = str[str.length() - (i - 1)];
        }
      }

      str.remove(str[str.length() - 1]);
      ui->label->setText(str);
      return;
    }

    if (str.length() - i == 0) {
      i++;
    }

    i--;
    last_char = str[str.length() - (i)];
    QChar next_char = last_char;
    last_char = '-';

    while (i != -1) {
      if (i != 0) {
        str[str.length() - (i)] = last_char;
        i--;
        last_char = next_char;
        if (i != 0) {
          next_char = str[str.length() - (i)];
        }
      } else {
        str += last_char;
        break;
      }
    }
  }

  ui->label->setText(str);
}

void MainWindow::graph_logic() {
  // plot logic
  if (ui->widget->graph(0)) {
    ui->widget->graph(0)->data()->clear();
  }
  double xBegin, xEnd, h, X;
  QVector<double> x, y;
  int error_flag = 0;

  h = 0.1;
  xBegin = ui->xMinLabel->text().toDouble();
  xEnd = ui->xMaxLabel->text().toDouble();

  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(ui->yMinLabel->text().toDouble(),
                              ui->yMaxLabel->text().toDouble());

  if (ui->label->text().trimmed().isEmpty()) {
    error_flag = 6;
  } else {
    for (X = xBegin; X < xEnd; X += h) {
      X = round(X * 10000000) / 10000000;
      x.push_back(X);
      s21::CalcController controller;
      std::string str = ui->label->text().toStdString();
      QString ret_val =
          QString::fromStdString(controller.GetRes(str, std::to_string(X)));
      if (controller.GetError() == 0) {
        y.push_back(ret_val.toDouble());
      } else {
        error_flag = 1;
        break;
      }
    }
  }

  if (error_flag == 0) {
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
  } else {
    ui->label->setText("Error");
  }
}
