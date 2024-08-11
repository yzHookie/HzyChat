#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
/******************************************************************************
 *
 * @file       mainwindow.h
 * @brief      主窗口
 *
 * @author     hzy
 * @date       2024/08/09
 * @history
 *****************************************************************************/
namespace Ui {
class MainWindow;
}

class LoginDialog;
class RegisterDialog;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void SlotSwitchRegisterWindow();
private:
    Ui::MainWindow *ui;
    LoginDialog *login_dialog_;
    RegisterDialog *register_dialog_;
};

#endif // MAINWINDOW_H
