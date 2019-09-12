#include <QDebug>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sap.h"

static MainWindow *main_window;
static PID_UI pid_ui[MAX_PID_SIZE];
static CustomArgUI custom_arg_ui[MAX_CUSTOM_ARG_SIZE];
static ArgWatchUI arg_watch_ui[MAX_ARG_WATCH_SIZE];

#define PID_UI_SET(n)                                       \
    pid_ui[n].window = main_window;                         \
    pid_ui[n].nameLineEdit = ui->pid##n##NameLineEdit;      \
    pid_ui[n].kpLineEdit = ui->pid##n##KpLineEdit;          \
    pid_ui[n].kiLineEdit = ui->pid##n##KiLineEdit;          \
    pid_ui[n].kdLineEdit = ui->pid##n##KdLineEdit;          \
    pid_ui[n].getPushButton = ui->pid##n##GetPushButton;    \
    pid_ui[n].setPushButton = ui->pid##n##SetPushButton;    \
    sap_bind_pid(n, &pid_ui[n].kp, &pid_ui[n].ki, &pid_ui[n].kd);

#define CUSTOM_ARG_UI_SET(n)                                        \
    custom_arg_ui[n].window = main_window;                          \
    custom_arg_ui[n].nameLineEdit = ui->custom##n##NameLineEdit;    \
    custom_arg_ui[n].argLineEdit = ui->custom##n##ValueLineEdit;    \
    custom_arg_ui[n].setPushButton = ui->custom##n##SetPushbutton;  \
    custom_arg_ui[n].getPushButton = ui->custom##n##GetPushbutton;  \
    sap_bind_custom_arg(n, &custom_arg_ui[n].value);

#define ARG_WATCH_UI_SET(n)                                         \
    arg_watch_ui[n].window = main_window;                          \
    arg_watch_ui[n].nameLineEdit = ui->arg##n##NameLineEdit;       \
    arg_watch_ui[n].argLineEdit = ui->arg##n##ValueLineEdit;       \
    sap_bind_arg_watch(n, &arg_watch_ui[n].value);

#define SERIAL_CHECK                                        \
    if (!main_window->isSerialOpen)                                 \
    {                                                               \
        QMessageBox::warning(main_window, "错误", "串口未打开！");    \
        return;                                                     \
    }

#define USE_GENERAL_CHECK                                           \
    if (!main_window->ui->useGeneralCheckBox->checkState())         \
    {                                                               \
        QMessageBox::warning(main_window, "错误", "请先启用通用上位机！");  \
        return;                                                     \
    }

#define GENERAL_CHECK       \
    SERIAL_CHECK            \
    USE_GENERAL_CHECK

#define ThisIsUnrealizedFunc  QMessageBox::information(this, "信息", "该功能尚未实现，敬请期待！");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    isSerialOpen = false;
    currentTabe = 0;
    main_window = this;

    ui->setupUi(this);
    setWindowTitle("多功能串口助手 V" SERIAL_ASSISTANT_VERSION);
    ui->tabWidget->setCurrentIndex(0);
    ui->baudComboBox->setCurrentIndex(3);

    PID_UI_SET(0);
    PID_UI_SET(1);
    PID_UI_SET(2);
    PID_UI_SET(3);
    PID_UI_SET(4);
    PID_UI_SET(5);

    CUSTOM_ARG_UI_SET(0);
    CUSTOM_ARG_UI_SET(1);
    CUSTOM_ARG_UI_SET(2);
    CUSTOM_ARG_UI_SET(3);
    CUSTOM_ARG_UI_SET(4);
    CUSTOM_ARG_UI_SET(5);
    CUSTOM_ARG_UI_SET(6);
    CUSTOM_ARG_UI_SET(7);
    CUSTOM_ARG_UI_SET(8);
    CUSTOM_ARG_UI_SET(9);

    ARG_WATCH_UI_SET(0);
    ARG_WATCH_UI_SET(1);
    ARG_WATCH_UI_SET(2);
    ARG_WATCH_UI_SET(3);
    ARG_WATCH_UI_SET(4);
    ARG_WATCH_UI_SET(5);
    ARG_WATCH_UI_SET(6);
    ARG_WATCH_UI_SET(7);
    ARG_WATCH_UI_SET(8);
    ARG_WATCH_UI_SET(9);

    thread = new QThread(this);
    thread->create([&]{qDebug() << "error";});
}

MainWindow::~MainWindow()
{
    delete ui;
}


// 搜索串口
void MainWindow::on_portSearchPushButton_clicked()
{
    ui->portComboBox->clear();
    for (QSerialPortInfo info : QSerialPortInfo::availablePorts())
        ui->portComboBox->addItem(info.portName() + ": " + info.description());
}

// 打开串口
void MainWindow::on_openSerialPushButton_clicked()
{
    // 串口已经被本程序打开，关闭它
    if (isSerialOpen)
    {
        serial.close();
        ui->openSerialPushButton->setText("打开串口");
        ui->openSerialPushButton->setStyleSheet("color: black");
        isSerialOpen = false;
        qDebug() << "串口已关闭！";
        return;
    }

    // 获取界面的串口配置信息并设置串口
    QString portName = ui->portComboBox->currentText();
    if (portName == "")
    {
        QMessageBox::warning(nullptr, "错误", "暂无可用串口！请尝试“搜索串口”");
        return;
    }

    int parity = ui->checkBitComboBox->currentIndex();
    serial.setPortName(portName.split(":")[0]);
    serial.setBaudRate(ui->baudComboBox->currentText().toInt());
    serial.setStopBits(QSerialPort::StopBits(ui->stopBitComboBox->currentIndex() + 1));
    serial.setDataBits(QSerialPort::DataBits(ui->dataBitComboBox->currentText().toInt()));
    serial.setParity(QSerialPort::Parity(parity ? parity + 1 : 0));
    //serial.getSerial().setReadBufferSize(10000);

    // 尝试打开串口
    if (serial.open(QIODevice::ReadWrite))
    {
        qDebug() << "打开串口成功！";
        ui->openSerialPushButton->setText("关闭串口");
        ui->openSerialPushButton->setStyleSheet("color: red");
        isSerialOpen = true;

        QObject::connect(&serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    }
    else
        QMessageBox::warning(nullptr, "错误", "串口打开失败！该串口不存在或者被占用。");
}

// 发送数据
void MainWindow::on_sendPushButton_clicked()
{
    if (!isSerialOpen)
    {
        QMessageBox::warning(nullptr, "错误", "串口未打开！");
        return;
    }

    QString string = ui->inputTxtEdit->toPlainText();

    if (ui->sendNewLineCheckBox->checkState())
        string += "\r\n";
    if (string == "")
        return;

    if (ui->hexSendCheckBox->checkState())
    {

    }


    qDebug() << "发送：" + string;
    serial.write(string.toLatin1());
}

// 接收处理
void MainWindow::readData()
{
    QByteArray buf = serial.readAll();

    /* 串口助手*/
    if (currentTabe == SerialAssisant)
    {
        QString s;

        if (ui->hexOutputCheckBox->checkState())
        {
            for (int b: buf)
                s += QString("%1").arg(b, 2, 16, QLatin1Char('0')) + " ";
        }
        else
            s = QString(buf);

        ui->outPutTextEdit->setText(ui->outPutTextEdit->toPlainText() + s);
        ui->outPutTextEdit->moveCursor(QTextCursor::End);
    }

    if (currentTabe == GeneralUpComp)
    {
        for (char b : buf)
            sap_get_one_byte(static_cast<unsigned char>(b));
    }
}

/*********************** 串口助手界面按键事件 *************************************/

// 清除接收
void MainWindow::on_cleanOutputPushButton_clicked()
{
    ui->outPutTextEdit->clear();
}

// 清除发送
void MainWindow::on_cleanInputPushButton_clicked()
{
    ui->inputTxtEdit->clear();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    currentTabe = index;
    qDebug() << QString("切换到界面%1").arg(index);

    switch (currentTabe)
    {
    case SerialAssisant:
        on_portSearchPushButton_clicked();
        break;
    case BlueTooth:
        ui->bluetoothSerialLineEdit->setText(isSerialOpen ? serial.portName() : "(串口未打开)");
        ui->bluetoothBaudLineEdit->setText(isSerialOpen ? QString("%1").arg(serial.baudRate()) : "");
        //ui->useBluetoothCheckBox->setDisabled(!isSerialOpen);
        //ui->BluetoothGroupBox->setDisabled(!isSerialOpen || !ui->useBluetoothCheckBox->checkState());
        break;
    case GeneralUpComp:
        ui->generalSerialLineEdit->setText(isSerialOpen ? serial.portName() : "(串口未打开)");
        ui->generalBaudLineEdit->setText(isSerialOpen ? QString("%1").arg(serial.baudRate()) : "");
        //ui->useGeneralCheckBox->setDisabled(!isSerialOpen);
        //ui->generalGroupBox->setDisabled(!isSerialOpen || !ui->useGeneralCheckBox->checkState());
        break;
    }
}

void MainWindow::on_useGeneralCheckBox_stateChanged(int arg1)
{
    (void)arg1;
    if (arg1)
    {
        qDebug() << "error";

        thread->start();
    }
    //ui->generalGroupBox->setDisabled(!isSerialOpen || !arg1);
}

/*********************** 通用上位机界面数据解析回调 *************************************/
void sap_send_byte(unsigned char byte)
{
    char p = static_cast<char>(byte);
    main_window->serial.write(&p, 1);
}

void sap_cammand_handler(int cammand_index)
{
    //qDebug() << "接收到命令(" << cammand_index << ")";
    QMessageBox::information(main_window, "", QString("接收到命令(%1)").arg(cammand_index));
}

void sap_switch_handler(int switch_index, int switch_state)
{
    //qDebug() << "接收到开关命令(" << switch_index << ", " << (switch_state ? "开" : "关") << ")";
    QMessageBox::information(main_window, "", QString("接收到开关命令(%1，%2)").arg(switch_index).arg(switch_state ? "开" : "关"));
}

void sap_get_recv_data_frame(unsigned char *frame, int len)
{
    switch (frame[2])
    {
    case PID_Set:
        pid_ui[frame[3]].setPIDByValue();
        break;
    case CustomSet:
        custom_arg_ui[frame[3]].setArgByValue();
        break;
    case ArgWatch:
        qDebug() << "argwatch";
        arg_watch_ui[frame[3]].value = *(float *)(frame + 4);
        arg_watch_ui[frame[3]].setArgByValue();
        break;
    }

    if (!main_window->ui->showRecvDataCheckBox->checkState())
        return;

    QString s = "接收：";
    for (int i = 0; i < len; i++)
        s += QString("%1").arg(frame[i], 2, 16, QLatin1Char('0')) + " ";;
    main_window->ui->generalOutputTextEdit->insertHtml("<html><font color=green>"+ s + "<br></font></html>");
    main_window->ui->generalOutputTextEdit->moveCursor(QTextCursor::End);
}

void sap_get_send_data_frame(unsigned char *frame, int len)
{
    if (!main_window->ui->showSendDataCheckBox->checkState())
        return;

    QString s = "发送：";
    for (int i = 0; i < len; i++)
        s += QString("%1").arg(frame[i], 2, 16, QLatin1Char('0')) + " ";;
    main_window->ui->generalOutputTextEdit->insertHtml("<html><font color=red>"+ s + "<br></font></html>");
    main_window->ui->generalOutputTextEdit->moveCursor(QTextCursor::End);

    //main_window->ui->generalOutputTextEdit->append(s);
}


/*********************** 通用上位机界面按键事件 *************************************/

/* 批量定义on_cmdPushButton_clicked槽函数
 */
#define DEFINE_on_cmdPushButton_clicked(n)          \
void MainWindow::on_cmd##n##PushButton_clicked()    \
{                                                   \
    GENERAL_CHECK                                   \
    sap_send_cammad(0);                             \
}
DEFINE_on_cmdPushButton_clicked(0)
DEFINE_on_cmdPushButton_clicked(1)
DEFINE_on_cmdPushButton_clicked(2)
DEFINE_on_cmdPushButton_clicked(3)
DEFINE_on_cmdPushButton_clicked(4)
DEFINE_on_cmdPushButton_clicked(5)
DEFINE_on_cmdPushButton_clicked(6)
DEFINE_on_cmdPushButton_clicked(7)
DEFINE_on_cmdPushButton_clicked(8)
#undef DEFINE_on_cmdPushButton_clicked

/* 批量定义on_switchOpenRadioButton_clicked槽函数
 * 批量定义on_switchCloseRadioButton_clicked槽函数
 */
#define DEFINE_on_switchOpenAndCloseRadioButton_clicked(n)      \
void MainWindow::on_switch##n##OpenRadioButton_clicked()        \
{                                                               \
    GENERAL_CHECK                                               \
    sap_send_switch(n, main_window->ui->switch0OpenRadioButton->isChecked());   \
}                                                               \
void MainWindow::on_switch##n##CloseRadioButton_clicked()       \
{                                                               \
    GENERAL_CHECK                                               \
    sap_send_switch(n, main_window->ui->switch0OpenRadioButton->isChecked());   \
}
DEFINE_on_switchOpenAndCloseRadioButton_clicked(0)
DEFINE_on_switchOpenAndCloseRadioButton_clicked(1)
DEFINE_on_switchOpenAndCloseRadioButton_clicked(2)
DEFINE_on_switchOpenAndCloseRadioButton_clicked(3)
#undef DEFINE_on_switchOpenAndCloseRadioButton_clicked

/* 批量定义on_pidGetPushButton_clicked槽函数
 * 批量定义on_pidGetSetPushButton_clicked槽函数
 */
#define DEFINE_on_pidGetAndSetPushButton_clicked(n)             \
void MainWindow::on_pid##n##GetPushButton_clicked()             \
{                                                               \
    GENERAL_CHECK                                               \
    sap_send_request(PID_Get, n);                               \
}                                                               \
void MainWindow::on_pid##n##SetPushButton_clicked()             \
{                                                               \
    GENERAL_CHECK                                               \
    if (pid_ui[n].getPIDByUI())                                 \
        sap_send_pid(n);                                        \
}
DEFINE_on_pidGetAndSetPushButton_clicked(0)
DEFINE_on_pidGetAndSetPushButton_clicked(1)
DEFINE_on_pidGetAndSetPushButton_clicked(2)
DEFINE_on_pidGetAndSetPushButton_clicked(3)
DEFINE_on_pidGetAndSetPushButton_clicked(4)
DEFINE_on_pidGetAndSetPushButton_clicked(5)
#undef DEFINE_on_pidGetAndSetPushButton_clicked

/* 批量定义on_customGetPushbutton_clicked槽函数
 * 批量定义on_customSetPushbutton_clicked槽函数
 */
#define DEFINE_on_customGetAndSetPushbutton_clicked(n)          \
void MainWindow::on_custom##n##GetPushbutton_clicked()          \
{                                                               \
    GENERAL_CHECK                                               \
    sap_send_request(CustomGet, n);                             \
}                                                               \
void MainWindow::on_custom##n##SetPushbutton_clicked()          \
{                                                               \
    GENERAL_CHECK                                               \
    if (custom_arg_ui[n].getArgByUI())                          \
        sap_send_arg(CustomSet, n);                             \
}
DEFINE_on_customGetAndSetPushbutton_clicked(0)
DEFINE_on_customGetAndSetPushbutton_clicked(1)
DEFINE_on_customGetAndSetPushbutton_clicked(2)
DEFINE_on_customGetAndSetPushbutton_clicked(3)
DEFINE_on_customGetAndSetPushbutton_clicked(4)
DEFINE_on_customGetAndSetPushbutton_clicked(5)
DEFINE_on_customGetAndSetPushbutton_clicked(6)
DEFINE_on_customGetAndSetPushbutton_clicked(7)
DEFINE_on_customGetAndSetPushbutton_clicked(8)
DEFINE_on_customGetAndSetPushbutton_clicked(9)
#undef on_customGetAndSetPushbutton_clicked

void MainWindow::on_nameOrCmdSetPushButton_clicked()
{
    ThisIsUnrealizedFunc
}

void MainWindow::on_generalHelpPushButton_clicked()
{
    ThisIsUnrealizedFunc
}

void MainWindow::on_rememberCurrentPushButton_clicked()
{
    ThisIsUnrealizedFunc
}

void MainWindow::on_saveAsCfgPushButton_clicked()
{
    ThisIsUnrealizedFunc
}

void MainWindow::on_loadCfgPushButton_clicked()
{
    ThisIsUnrealizedFunc
}

void MainWindow::on_setDefalufCfgPushButton_clicked()
{
    ThisIsUnrealizedFunc
}
