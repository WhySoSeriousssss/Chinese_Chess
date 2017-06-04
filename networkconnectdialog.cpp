#include "networkconnectdialog.h"
#include "ui_networkconnectdialog.h"

NetworkConnectDialog::NetworkConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkConnectDialog)
{
    ui->setupUi(this);
}

NetworkConnectDialog::~NetworkConnectDialog()
{
    delete ui;
}

void NetworkConnectDialog::on_CreateButton_released()
{
    accept();
    emit CreateButtonReleased();
}

void NetworkConnectDialog::on_JoinButton_released()
{
    accept();
    emit JoinButtonReleased();
}
