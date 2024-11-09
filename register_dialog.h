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
    void OnGetCodeClicked();
    void SlotReqModFinish(ReqId id, QString res, ErrorCodes err);
private:
    void ShowTip(QString tip, bool ok);
    /**
     * @brief 注册处理回包的逻辑
     */
    void InitHttpHandlers();
    Ui::RegisterDialog *ui;
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers_;
};

#endif // REGISTER_DIALOG_H
