#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void add_to_lable();
  void add_cb_to_lable();
  void add_oper_to_lable();
  void add_func_to_lable();
  void add_x_to_lable();
  void clear_lable();
  void clear_last_char();
  void add_unar_lable();
  void get_res();
  void graph_logic();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
