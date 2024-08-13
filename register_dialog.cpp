#include "register_dialog.h"
#include "ui_register_dialog.h"
#include "util.h"
#include "http_mgr.h"

#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
static QRegularExpression regex;

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    connect(ui->verify_code_button, &QPushButton::clicked, this, &RegisterDialog::slot_get_code_clicked);
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish);
    ui->err_tip->setProperty("state", "normal");
    util::repolish(ui->err_tip);
    regex.setPattern(R"(\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");

    InitHttpHandlers();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::slot_get_code_clicked() {
    QString email = ui->email_edit->text();

    bool match = regex.match(email).hasMatch();
    if (match) {
        // 发送 http 验证码
    } else {
        ShowTip("邮箱地址格式不正确", false);
    }

}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err) {
    if (err != ErrorCodes::SUCCESS) {
        ShowTip(tr("网络请求错误"), false);
        return;
    }
    QJsonDocument json_doc = QJsonDocument::fromJson(res.toUtf8());
    if (json_doc.isNull()) {
        ShowTip(tr("json 解析失败"), false);
        return;
    }
    if (!json_doc.isObject()) {
        ShowTip(tr("json 解析失败"), false);
        return;
    }
    handlers_[id](json_doc.object());
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

void RegisterDialog::InitHttpHandlers() {
    // 注册获取验证码回包逻辑
    handlers_.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& json_obj) {
        int error = json_obj["error"].toInt();
        if (error != ErrorCodes::SUCCESS) {
            ShowTip(tr("参数错误"), false);
            return;
        }
        auto email = json_obj["email"].toString();
        ShowTip(tr("验证码已经发送到邮箱，请注意查收"), true);
        qDebug() << "email is " << email;
    });
}
