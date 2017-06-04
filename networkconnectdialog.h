#ifndef NETWORKCONNECTDIALOG_H
#define NETWORKCONNECTDIALOG_H

#include <QDialog>

namespace Ui {
class NetworkConnectDialog;
}

class NetworkConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkConnectDialog(QWidget *parent = 0);
    ~NetworkConnectDialog();

private slots:
    void on_CreateButton_released();
    void on_JoinButton_released();

signals:
    void CreateButtonReleased();
    void JoinButtonReleased();

private:
    Ui::NetworkConnectDialog *ui;
};

#endif // NETWORKCONNECTDIALOG_H
