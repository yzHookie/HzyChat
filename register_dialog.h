#ifndef REGISTER_DIALOG_H
#define REGISTER_DIALOG_H

#include <QDialog>
#include "global.h"
/******************************************************************************
 *
 * @file       register_dialog.h
 * @brief      注册窗口
 *
 * @author     hzy
 * @date       2024/08/09
 * @history
 *****************************************************************************/
namespace Ui {
class RegisterDialog;
}
class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();
public slots:
    void slot_get_code_clicked();
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
private:
    void ShowTip(QString tip, bool ok);
    void InitHttpHandlers();
    Ui::RegisterDialog *ui;

    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers_;
};

#endif // REGISTER_DIALOG_H
