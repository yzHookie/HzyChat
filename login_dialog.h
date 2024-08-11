#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>
/******************************************************************************
 *
 * @file       login_dialog.h
 * @brief      登录窗口
 *
 * @author     hzy
 * @date       2024/08/09
 * @history
 *****************************************************************************/

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
signals:
    void SwitchRegister();
private:
    Ui::LoginDialog *ui;
};

#endif // LOGIN_DIALOG_H
