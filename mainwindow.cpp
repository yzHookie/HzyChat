#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login_dialog.h"
#include "register_dialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    login_dialog_ = new LoginDialog(this);
    register_dialog_ = new RegisterDialog(this);
    register_dialog_->hide();

    setCentralWidget(login_dialog_);

    connect(login_dialog_, &LoginDialog::SwitchRegister, this, &MainWindow::SlotSwitchRegisterWindow);
    login_dialog_->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    register_dialog_->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotSwitchRegisterWindow()
{
    register_dialog_->show();
    login_dialog_->hide();
    this->setCentralWidget(register_dialog_);
}
