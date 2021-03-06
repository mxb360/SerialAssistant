# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'mainwindow.ui'
#
# Created by: PyQt5 UI code generator 5.11.3
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1053, 814)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.tabWidget = QtWidgets.QTabWidget(self.centralwidget)
        self.tabWidget.setGeometry(QtCore.QRect(0, 0, 1041, 781))
        self.tabWidget.setObjectName("tabWidget")
        self.serialTab = QtWidgets.QWidget()
        self.serialTab.setObjectName("serialTab")
        self.outPutTextEdit = QtWidgets.QTextEdit(self.serialTab)
        self.outPutTextEdit.setGeometry(QtCore.QRect(10, 10, 711, 521))
        self.outPutTextEdit.setStyleSheet("color: rgb(0, 255, 21);\n"
"background-color: rgb(0, 0, 0);")
        self.outPutTextEdit.setReadOnly(True)
        self.outPutTextEdit.setObjectName("outPutTextEdit")
        self.dataSendGoupBox = QtWidgets.QGroupBox(self.serialTab)
        self.dataSendGoupBox.setGeometry(QtCore.QRect(730, 520, 291, 211))
        self.dataSendGoupBox.setTitle("")
        self.dataSendGoupBox.setObjectName("dataSendGoupBox")
        self.sendPushButton = QtWidgets.QPushButton(self.dataSendGoupBox)
        self.sendPushButton.setGeometry(QtCore.QRect(20, 30, 261, 41))
        self.sendPushButton.setObjectName("sendPushButton")
        self.saveInputPushButton = QtWidgets.QPushButton(self.dataSendGoupBox)
        self.saveInputPushButton.setGeometry(QtCore.QRect(150, 80, 131, 28))
        self.saveInputPushButton.setObjectName("saveInputPushButton")
        self.cleanInputPushButton = QtWidgets.QPushButton(self.dataSendGoupBox)
        self.cleanInputPushButton.setGeometry(QtCore.QRect(20, 80, 121, 28))
        self.cleanInputPushButton.setObjectName("cleanInputPushButton")
        self.sendNewLineCheckBox = QtWidgets.QCheckBox(self.dataSendGoupBox)
        self.sendNewLineCheckBox.setGeometry(QtCore.QRect(160, 120, 91, 19))
        self.sendNewLineCheckBox.setObjectName("sendNewLineCheckBox")
        self.hexSendCheckBox = QtWidgets.QCheckBox(self.dataSendGoupBox)
        self.hexSendCheckBox.setGeometry(QtCore.QRect(10, 120, 111, 19))
        self.hexSendCheckBox.setObjectName("hexSendCheckBox")
        self.timingSendCheckBox = QtWidgets.QCheckBox(self.dataSendGoupBox)
        self.timingSendCheckBox.setGeometry(QtCore.QRect(10, 140, 171, 19))
        self.timingSendCheckBox.setObjectName("timingSendCheckBox")
        self.periodLineEdit = QtWidgets.QLineEdit(self.dataSendGoupBox)
        self.periodLineEdit.setGeometry(QtCore.QRect(180, 140, 51, 21))
        self.periodLineEdit.setText("")
        self.periodLineEdit.setObjectName("periodLineEdit")
        self.label_6 = QtWidgets.QLabel(self.dataSendGoupBox)
        self.label_6.setGeometry(QtCore.QRect(240, 140, 41, 16))
        self.label_6.setObjectName("label_6")
        self.echoCheckBox = QtWidgets.QCheckBox(self.dataSendGoupBox)
        self.echoCheckBox.setGeometry(QtCore.QRect(10, 160, 171, 16))
        self.echoCheckBox.setObjectName("echoCheckBox")
        self.snedNowCheckBox = QtWidgets.QCheckBox(self.dataSendGoupBox)
        self.snedNowCheckBox.setGeometry(QtCore.QRect(10, 180, 161, 19))
        self.snedNowCheckBox.setObjectName("snedNowCheckBox")
        self.serialGroupBox = QtWidgets.QGroupBox(self.serialTab)
        self.serialGroupBox.setGeometry(QtCore.QRect(730, -10, 291, 351))
        self.serialGroupBox.setTitle("")
        self.serialGroupBox.setObjectName("serialGroupBox")
        self.groupBox = QtWidgets.QGroupBox(self.serialGroupBox)
        self.groupBox.setGeometry(QtCore.QRect(10, 10, 271, 101))
        self.groupBox.setTitle("")
        self.groupBox.setObjectName("groupBox")
        self.portSearchPushButton = QtWidgets.QPushButton(self.groupBox)
        self.portSearchPushButton.setGeometry(QtCore.QRect(120, 30, 141, 28))
        self.portSearchPushButton.setObjectName("portSearchPushButton")
        self.portComboBox = QtWidgets.QComboBox(self.groupBox)
        self.portComboBox.setGeometry(QtCore.QRect(10, 60, 251, 31))
        self.portComboBox.setObjectName("portComboBox")
        self.label = QtWidgets.QLabel(self.groupBox)
        self.label.setGeometry(QtCore.QRect(10, 40, 72, 15))
        self.label.setObjectName("label")
        self.openSerialPushButton = QtWidgets.QPushButton(self.serialGroupBox)
        self.openSerialPushButton.setGeometry(QtCore.QRect(10, 300, 271, 41))
        self.openSerialPushButton.setObjectName("openSerialPushButton")
        self.groupBox_2 = QtWidgets.QGroupBox(self.serialGroupBox)
        self.groupBox_2.setGeometry(QtCore.QRect(10, 100, 271, 191))
        self.groupBox_2.setTitle("")
        self.groupBox_2.setObjectName("groupBox_2")
        self.baudComboBox = QtWidgets.QComboBox(self.groupBox_2)
        self.baudComboBox.setGeometry(QtCore.QRect(120, 30, 141, 31))
        self.baudComboBox.setObjectName("baudComboBox")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.baudComboBox.addItem("")
        self.label_10 = QtWidgets.QLabel(self.groupBox_2)
        self.label_10.setGeometry(QtCore.QRect(10, 160, 72, 15))
        self.label_10.setObjectName("label_10")
        self.label_7 = QtWidgets.QLabel(self.groupBox_2)
        self.label_7.setGeometry(QtCore.QRect(10, 40, 72, 15))
        self.label_7.setObjectName("label_7")
        self.baudComboBox_4 = QtWidgets.QComboBox(self.groupBox_2)
        self.baudComboBox_4.setGeometry(QtCore.QRect(120, 150, 141, 31))
        self.baudComboBox_4.setObjectName("baudComboBox_4")
        self.baudComboBox_4.addItem("")
        self.baudComboBox_4.addItem("")
        self.baudComboBox_4.addItem("")
        self.baudComboBox_3 = QtWidgets.QComboBox(self.groupBox_2)
        self.baudComboBox_3.setGeometry(QtCore.QRect(120, 110, 141, 31))
        self.baudComboBox_3.setObjectName("baudComboBox_3")
        self.baudComboBox_3.addItem("")
        self.baudComboBox_3.addItem("")
        self.baudComboBox_3.addItem("")
        self.baudComboBox_3.addItem("")
        self.baudComboBox_2 = QtWidgets.QComboBox(self.groupBox_2)
        self.baudComboBox_2.setGeometry(QtCore.QRect(120, 70, 141, 31))
        self.baudComboBox_2.setObjectName("baudComboBox_2")
        self.baudComboBox_2.addItem("")
        self.baudComboBox_2.addItem("")
        self.baudComboBox_2.addItem("")
        self.label_9 = QtWidgets.QLabel(self.groupBox_2)
        self.label_9.setGeometry(QtCore.QRect(10, 120, 72, 15))
        self.label_9.setObjectName("label_9")
        self.label_8 = QtWidgets.QLabel(self.groupBox_2)
        self.label_8.setGeometry(QtCore.QRect(10, 80, 72, 15))
        self.label_8.setObjectName("label_8")
        self.groupBox_2.raise_()
        self.groupBox.raise_()
        self.openSerialPushButton.raise_()
        self.dataRecvGroupBox = QtWidgets.QGroupBox(self.serialTab)
        self.dataRecvGroupBox.setGeometry(QtCore.QRect(730, 330, 291, 201))
        self.dataRecvGroupBox.setTitle("")
        self.dataRecvGroupBox.setObjectName("dataRecvGroupBox")
        self.cleanOutputPushButton = QtWidgets.QPushButton(self.dataRecvGroupBox)
        self.cleanOutputPushButton.setGeometry(QtCore.QRect(150, 30, 131, 28))
        self.cleanOutputPushButton.setObjectName("cleanOutputPushButton")
        self.saveOutputPushButton = QtWidgets.QPushButton(self.dataRecvGroupBox)
        self.saveOutputPushButton.setGeometry(QtCore.QRect(10, 30, 131, 28))
        self.saveOutputPushButton.setObjectName("saveOutputPushButton")
        self.hexOutputCheckBox = QtWidgets.QCheckBox(self.dataRecvGroupBox)
        self.hexOutputCheckBox.setGeometry(QtCore.QRect(10, 70, 121, 19))
        self.hexOutputCheckBox.setObjectName("hexOutputCheckBox")
        self.wordWrapCheckBox = QtWidgets.QCheckBox(self.dataRecvGroupBox)
        self.wordWrapCheckBox.setGeometry(QtCore.QRect(150, 70, 91, 19))
        self.wordWrapCheckBox.setObjectName("wordWrapCheckBox")
        self.timeStampCheckBox = QtWidgets.QCheckBox(self.dataRecvGroupBox)
        self.timeStampCheckBox.setGeometry(QtCore.QRect(10, 130, 101, 21))
        self.timeStampCheckBox.setObjectName("timeStampCheckBox")
        self.saveOutputPushButton_2 = QtWidgets.QPushButton(self.dataRecvGroupBox)
        self.saveOutputPushButton_2.setGeometry(QtCore.QRect(70, 160, 141, 28))
        self.saveOutputPushButton_2.setObjectName("saveOutputPushButton_2")
        self.hexOutputCheckBox_2 = QtWidgets.QCheckBox(self.dataRecvGroupBox)
        self.hexOutputCheckBox_2.setGeometry(QtCore.QRect(10, 100, 121, 19))
        self.hexOutputCheckBox_2.setObjectName("hexOutputCheckBox_2")
        self.hexOutputCheckBox_3 = QtWidgets.QCheckBox(self.dataRecvGroupBox)
        self.hexOutputCheckBox_3.setGeometry(QtCore.QRect(150, 100, 121, 19))
        self.hexOutputCheckBox_3.setObjectName("hexOutputCheckBox_3")
        self.timeStampCheckBox_2 = QtWidgets.QCheckBox(self.dataRecvGroupBox)
        self.timeStampCheckBox_2.setGeometry(QtCore.QRect(150, 130, 111, 21))
        self.timeStampCheckBox_2.setObjectName("timeStampCheckBox_2")
        self.inputTxtEdit = QtWidgets.QTextEdit(self.serialTab)
        self.inputTxtEdit.setGeometry(QtCore.QRect(10, 540, 711, 191))
        self.inputTxtEdit.setObjectName("inputTxtEdit")
        self.tabWidget.addTab(self.serialTab, "")
        self.flyCtrlTab = QtWidgets.QWidget()
        self.flyCtrlTab.setObjectName("flyCtrlTab")
        self.tabWidget.addTab(self.flyCtrlTab, "")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1053, 25))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)

        self.retranslateUi(MainWindow)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.outPutTextEdit.setHtml(_translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'SimSun\'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>"))
        self.sendPushButton.setText(_translate("MainWindow", "发送（Ctrl+Enter）"))
        self.saveInputPushButton.setText(_translate("MainWindow", "保存数据"))
        self.cleanInputPushButton.setText(_translate("MainWindow", "清除发送"))
        self.sendNewLineCheckBox.setText(_translate("MainWindow", "发送新行"))
        self.hexSendCheckBox.setText(_translate("MainWindow", "十六进制"))
        self.timingSendCheckBox.setText(_translate("MainWindow", "定时发送: 发送周期:"))
        self.label_6.setText(_translate("MainWindow", "毫秒"))
        self.echoCheckBox.setText(_translate("MainWindow", "在接收窗口显示回显"))
        self.snedNowCheckBox.setText(_translate("MainWindow", "立刻发送按键数据"))
        self.portSearchPushButton.setText(_translate("MainWindow", "端口搜索"))
        self.label.setText(_translate("MainWindow", "端口选择："))
        self.openSerialPushButton.setText(_translate("MainWindow", "打开串口"))
        self.baudComboBox.setItemText(0, _translate("MainWindow", "1200"))
        self.baudComboBox.setItemText(1, _translate("MainWindow", "2400"))
        self.baudComboBox.setItemText(2, _translate("MainWindow", "4800"))
        self.baudComboBox.setItemText(3, _translate("MainWindow", "9600"))
        self.baudComboBox.setItemText(4, _translate("MainWindow", "19200"))
        self.baudComboBox.setItemText(5, _translate("MainWindow", "38400"))
        self.baudComboBox.setItemText(6, _translate("MainWindow", "43000"))
        self.baudComboBox.setItemText(7, _translate("MainWindow", "57600"))
        self.baudComboBox.setItemText(8, _translate("MainWindow", "76800"))
        self.baudComboBox.setItemText(9, _translate("MainWindow", "115200"))
        self.baudComboBox.setItemText(10, _translate("MainWindow", "128000"))
        self.baudComboBox.setItemText(11, _translate("MainWindow", "230400"))
        self.baudComboBox.setItemText(12, _translate("MainWindow", "256000"))
        self.baudComboBox.setItemText(13, _translate("MainWindow", "460800"))
        self.baudComboBox.setItemText(14, _translate("MainWindow", "921600"))
        self.baudComboBox.setItemText(15, _translate("MainWindow", "1382400"))
        self.baudComboBox.setItemText(16, _translate("MainWindow", "自定义"))
        self.label_10.setText(_translate("MainWindow", "奇偶校验："))
        self.label_7.setText(_translate("MainWindow", "波特率："))
        self.baudComboBox_4.setItemText(0, _translate("MainWindow", "无"))
        self.baudComboBox_4.setItemText(1, _translate("MainWindow", "奇校验"))
        self.baudComboBox_4.setItemText(2, _translate("MainWindow", "偶校验"))
        self.baudComboBox_3.setItemText(0, _translate("MainWindow", "8"))
        self.baudComboBox_3.setItemText(1, _translate("MainWindow", "7"))
        self.baudComboBox_3.setItemText(2, _translate("MainWindow", "6"))
        self.baudComboBox_3.setItemText(3, _translate("MainWindow", "5"))
        self.baudComboBox_2.setItemText(0, _translate("MainWindow", "1"))
        self.baudComboBox_2.setItemText(1, _translate("MainWindow", "1.5"))
        self.baudComboBox_2.setItemText(2, _translate("MainWindow", "2"))
        self.label_9.setText(_translate("MainWindow", "数据位："))
        self.label_8.setText(_translate("MainWindow", "停止位："))
        self.cleanOutputPushButton.setText(_translate("MainWindow", "清除接收"))
        self.saveOutputPushButton.setText(_translate("MainWindow", "保存接收窗口"))
        self.hexOutputCheckBox.setText(_translate("MainWindow", "十六进制显示"))
        self.wordWrapCheckBox.setText(_translate("MainWindow", "自动换行"))
        self.timeStampCheckBox.setText(_translate("MainWindow", "换行断帧"))
        self.saveOutputPushButton_2.setText(_translate("MainWindow", "接收窗口设置..."))
        self.hexOutputCheckBox_2.setText(_translate("MainWindow", "RTS"))
        self.hexOutputCheckBox_3.setText(_translate("MainWindow", "DTR"))
        self.timeStampCheckBox_2.setText(_translate("MainWindow", "换行断帧"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.serialTab), _translate("MainWindow", "串口助手"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.flyCtrlTab), _translate("MainWindow", "飞控上位机"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())

