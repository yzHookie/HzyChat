#include "register_dialog.h"
#include "ui_register_dialog.h"
#include "util.h"
#include <QRegularExpression>

static QRegularExpression regex;

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    connect(ui->verify_code_button, &QPushButton::clicked, this, &RegisterDialog::OnGetCodeClicked);

    ui->err_tip->setProperty("state", "normal");
    util::repolish(ui->err_tip);
    regex.setPattern(R"(\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::OnGetCodeClicked() {
    QString email = ui->email_edit->text();

    bool match = regex.match(email).hasMatch();
    if (match) {
        // 发送 http 验证码
    } else {
        ShowTip("邮箱地址格式不正确", false);
    }

}

void RegisterDialog::ShowTip(QString tip, bool ok) {
    if (ok) {
        ui->err_tip->setProperty("state", "normal");
    } else {
        ui->err_tip->setProperty("state", "err");
    }
    ui->err_tip->setText(tip);
    util::repolish(ui->err_tip);
}
