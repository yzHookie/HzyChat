#include "register_dialog.h"
#include "ui_register_dialog.h"
#include "util.h"
#include "http_mgr.h"
#include <QRegularExpression>
#include <QJsonObject>
#include <QJsonDocument>
static QRegularExpression regex;

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    connect(ui->verify_code_button, &QPushButton::clicked, this, &RegisterDialog::OnGetCodeClicked);
    connect(HttpMgr::GetInstance().get(), &HttpMgr::SigReqModFinish, this, &RegisterDialog::SlotReqModFinish);
    ui->err_tip->setProperty("state", "normal");
    util::repolish(ui->err_tip);
    regex.setPattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    connect(HttpMgr::GetInstance().get(), &HttpMgr::SigReqModFinish, this, &RegisterDialog::SlotReqModFinish);

    InitHttpHandlers();
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
        QJsonObject json_obj;
        json_obj["email"] = email;
        HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix + "/get_varifycode"), json_obj, ReqId::ID_GET_VARIFY_CODE, Modules::REGISTERMOD);
    } else {
        ShowTip("邮箱地址格式不正确", false);
    }

}

void RegisterDialog::SlotReqModFinish(ReqId id, QString res, ErrorCodes err) {
    if (err != ErrorCodes::SUCCESS) {
        ShowTip(tr("网络请求错误"), false);
        return;
    }

    // 序列化后才能发给后台
    QJsonDocument json_doc = QJsonDocument::fromJson(res.toUtf8());
    if (json_doc.isNull() || !json_doc.isObject()) {
        ShowTip(tr("json解析失败"), false);
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
    // 处理获取验证码回包的逻辑
    handlers_.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& json_obj) {
        int error = json_obj["error"].toInt();
        if (error != ErrorCodes::SUCCESS) {
            ShowTip(tr("参数错误"), false);
            return;
        }
        auto email = json_obj["email"].toString();
        ShowTip(tr("验证码已经发送到邮箱，注意查收"), true);
        qDebug() << "email is " << email;
    });
}
