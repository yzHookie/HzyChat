#ifndef REGISTER_DIALOG_H
#define REGISTER_DIALOG_H

#include <QDialog>

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
private:
    void ShowTip(QString tip, bool ok);
    Ui::RegisterDialog *ui;
};

#endif // REGISTER_DIALOG_H
