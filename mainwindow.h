#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QThread>
#include <QDebug>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QMainWindow>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>

#define SERIAL_ASSISTANT_VERSION  "1.0"

enum {
    SerialAssisant, BlueTooth, GeneralUpComp
};

#define PID_UI_COUNT  6

namespace Ui {
    class MainWindow;
    class PID_UI;
    class CammadUI;
    class SwitchUI;
    class CustomArgUI;
    class ArgWatchUI;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSerialPort serial;
    bool isSerialOpen;
    int currentTabe;

    QThread *thread;

    Ui::MainWindow *ui;

private slots:
    void on_portSearchPushButton_clicked();

    void on_openSerialPushButton_clicked();

    void on_sendPushButton_clicked();

    void readData();

    void on_cleanOutputPushButton_clicked();

    void on_cleanInputPushButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_useGeneralCheckBox_stateChanged(int arg1);

    void on_cmd0PushButton_clicked();
    void on_cmd1PushButton_clicked();
    void on_cmd2PushButton_clicked();
    void on_cmd3PushButton_clicked();
    void on_cmd4PushButton_clicked();
    void on_cmd5PushButton_clicked();
    void on_cmd6PushButton_clicked();
    void on_cmd7PushButton_clicked();
    void on_cmd8PushButton_clicked();

    void on_switch0OpenRadioButton_clicked();
    void on_switch0CloseRadioButton_clicked();
    void on_switch1OpenRadioButton_clicked();
    void on_switch1CloseRadioButton_clicked();
    void on_switch2OpenRadioButton_clicked();
    void on_switch2CloseRadioButton_clicked();
    void on_switch3OpenRadioButton_clicked();
    void on_switch3CloseRadioButton_clicked();

    void on_pid0GetPushButton_clicked();
    void on_pid0SetPushButton_clicked();

    void on_pid1GetPushButton_clicked();
    void on_pid1SetPushButton_clicked();
    void on_pid2GetPushButton_clicked();
    void on_pid2SetPushButton_clicked();
    void on_pid3GetPushButton_clicked();
    void on_pid3SetPushButton_clicked();
    void on_pid4GetPushButton_clicked();
    void on_pid4SetPushButton_clicked();
    void on_pid5GetPushButton_clicked();
    void on_pid5SetPushButton_clicked();
    void on_custom0GetPushbutton_clicked();
    void on_custom0SetPushbutton_clicked();
    void on_custom2GetPushbutton_clicked();
    void on_custom1GetPushbutton_clicked();
    void on_custom1SetPushbutton_clicked();
    void on_custom2SetPushbutton_clicked();

    void on_custom3GetPushbutton_clicked();

    void on_custom3SetPushbutton_clicked();

    void on_custom4GetPushbutton_clicked();

    void on_custom4SetPushbutton_clicked();

    void on_custom5GetPushbutton_clicked();

    void on_custom5SetPushbutton_clicked();

    void on_custom6GetPushbutton_clicked();

    void on_custom6SetPushbutton_clicked();

    void on_custom7GetPushbutton_clicked();

    void on_custom7SetPushbutton_clicked();

    void on_custom8GetPushbutton_clicked();

    void on_custom8SetPushbutton_clicked();

    void on_custom9GetPushbutton_clicked();

    void on_custom9SetPushbutton_clicked();

    void on_nameOrCmdSetPushButton_clicked();

    void on_generalHelpPushButton_clicked();

    void on_rememberCurrentPushButton_clicked();

    void on_saveAsCfgPushButton_clicked();

    void on_loadCfgPushButton_clicked();

    void on_setDefalufCfgPushButton_clicked();

private:

};

class PID_UI
{
public:
    MainWindow *window;

    QLineEdit *kpLineEdit;
    QLineEdit *kiLineEdit;
    QLineEdit *kdLineEdit;
    QLineEdit *nameLineEdit;
    QPushButton *setPushButton;
    QPushButton *getPushButton;

    float kp, ki, kd;

    bool getPIDByUI(void)
    {
        bool ok1, ok2, ok3;

        float v1 = kpLineEdit->text().toFloat(&ok1);
        float v2 = kiLineEdit->text().toFloat(&ok2);
        float v3 = kdLineEdit->text().toFloat(&ok3);

        if (ok1 && ok2 && ok3)
        {
            kp = v1;
            ki = v2;
            kd = v3;
            qDebug() << QString("kp: %1, ki: %2, kd: %3").arg(double(kp)).arg(double(ki)).arg(double(kd));
            return true;
        }

        QMessageBox::warning(window, "错误", "存在无效的PID值");
        return false;
    }

    void setPIDByValue(void)
    {
        kpLineEdit->setText(QString("%1").arg(double(kp)));
        kiLineEdit->setText(QString("%1").arg(double(ki)));
        kdLineEdit->setText(QString("%1").arg(double(kd)));
    }
};

class CustomArgUI
{
public:
    MainWindow *window;

    QLineEdit *argLineEdit;
    QLineEdit *nameLineEdit;
    QPushButton *setPushButton;
    QPushButton *getPushButton;

    float value;

    bool getArgByUI(void)
    {
        bool ok;

        float v = argLineEdit->text().toFloat(&ok);

        if (ok)
        {
            value = v;
            qDebug() << QString("arg: %1").arg(double(value));
            return true;
        }

        QMessageBox::warning(window, "错误", "无效的参数值");
        return false;
    }

    void setArgByValue(void)
    {
        argLineEdit->setText(QString("%1").arg(double(value)));
    }
};

class ArgWatchUI
{
public:
    MainWindow *window;

    QLineEdit *argLineEdit;
    QLineEdit *nameLineEdit;

    float value;

    void setArgByValue(void)
    {
        argLineEdit->setText(QString("%1").arg(double(value)));
    }
};

class MyThread : QThread
{
    void run()
    {

    }
};

#endif // MAINWINDOW_H
