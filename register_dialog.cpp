#include "register_dialog.h"
#include "ui_register_dialog.h"
#include "global.h"
RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->err_tip->setProperty("state", "normal");
    global::repolish(ui->err_tip);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}
