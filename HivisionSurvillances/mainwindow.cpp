#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "HCNetSDK.h"
#include "videobox.h"
#include "qapplication.h"
#include <QMessageBox>
#include "qlabel.h"
#include "qmenu.h"
#include "qcursor.h"
#include "qlist.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initForm();
    ui->passwordbox->setEchoMode(QLineEdit::Password);
    ui->usernamebox->setText("admin");
    ui->passwordbox->setText("naura44444444");
}

MainWindow::~MainWindow()
{
    delete ui;
}



bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        //双击最大化再次双击还原
        QLabel *widget = (QLabel *) watched;
        if (!max)
        {
            max = true;
            box->hide_video_all();
            ui->gridLayout->addWidget(widget, 0, 0);
            widget->setVisible(true);
        }
        else
        {
            max = false;
            box->show_video_all();
        }
        return true;
    }
    else if (event->type() == QEvent::MouseButtonPress)
    {
        //鼠标右键的地方弹出菜单
        if (qApp->mouseButtons() == Qt::RightButton)
        {
            menu->exec(QCursor::pos());
        }
    }
    return QWidget::eventFilter(watched, event);
}

void MainWindow::initForm()
{
    max = false;
    //安装事件过滤器
    //this->installEventFilter(this);
    //实例化子对象
    QWidgetList widgets;
    for (int i = 0; i < 64; ++i)
    {
        //这里用QLabel做演示可以改成自己的窗体类比如视频监控窗体
        QLabel *label = new QLabel;
        label->installEventFilter(this);
        label->setFrameShape(QLabel::Box);
        label->setAlignment(Qt::AlignCenter);
        label->setText(QString("Channel %1").arg(i + 1));
        widgets << label;
    }
    //实例化盒子
    box = new VideoBox(this);
    //关联信号槽
    connect(box, SIGNAL(changeVideo(int, QString, bool)), this, SLOT(changeVideo(int, QString, bool)));
    //可以改成 1_4 5_8 1_36 等
    box->setVideoType("1_8");
    box->setLayout(ui->gridLayoutVideo);
    box->setWidgets(widgets);
    box->setMenuFlag("Arrangement");
    box->setActionFlag("Survillance");
    box->show_video_all();
    //实例化菜单
    menu = new QMenu(this);
    //先安排自己的菜单
    //这里关联到一个槽函数处理,也可以关联到不同的槽函数
    menu->addAction("Switch full Screen Model", this, SLOT(doAction()));
    menu->addAction("Start looping pics", this, SLOT(doAction()));
    menu->addSeparator();
    //把菜单加到盒子上,并控制布局切换菜单是否可用(默认9个布局切换菜单)
    QList<bool> enable;
    enable << true << true << true << true << true << true << true << true << true;
    box->initMenu(menu, enable);
}

void MainWindow::doAction()
{
    //判断是哪个动作触发的
    QAction *action = (QAction *)sender();
    ui->label->setText(QString("Triggered menu: %1").arg(action->text()));
}

void MainWindow::changeVideo(int type, const QString &videoType, bool videoMax)
{
    QString info = QString("Main menu: %1  Submenu: %2").arg(type).arg(videoType);
    ui->label->setText(info);
}

void MainWindow::on_loginBtn_clicked()
{
    long lUserID = 0;
    long lUserID1 = 0;
    if (ui->loginBtn->text() == "Login")
    {
        bool isInit = NET_DVR_Init();
        if (isInit)
        {
            qDebug() << "SDK Initialized!";
            NET_DVR_SetConnectTime(2000, 3);
            NET_DVR_SetReconnect(10000, true);
            NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
            NET_DVR_USER_LOGIN_INFO struLoginInfo1 = {0};
            if (ui->usernamebox->text().isEmpty() ||
                    ui->usernamebox->text().isNull())
            {
                QMessageBox::critical(this, "ERROR", "Input UserName!");
                return;
            }
            if (ui->passwordbox->text().isEmpty() ||
                    ui->passwordbox->text().isNull())
            {
                QMessageBox::critical(this, "ERROR", "Input Password!");
                return;
            }
            QString ip = "192.168.161.250";
            strcpy_s(struLoginInfo.sDeviceAddress, ip.toStdString().data());
            strcpy_s(struLoginInfo.sUserName,
                     ui->usernamebox->text().toStdString().data());
            strcpy_s(struLoginInfo.sPassword,
                     ui->passwordbox->text().toStdString().data());
            struLoginInfo.wPort = 8000;
            struLoginInfo.bUseAsynLogin = 0;
            QString ip1 = "192.168.161.253";
            strcpy_s(struLoginInfo1.sDeviceAddress, ip1.toStdString().data());
            strcpy_s(struLoginInfo1.sUserName,
                     ui->usernamebox->text().toStdString().data());
            strcpy_s(struLoginInfo1.sPassword,
                     ui->passwordbox->text().toStdString().data());
            struLoginInfo1.wPort = 8001;
            struLoginInfo1.bUseAsynLogin = 0;
            NET_DVR_DEVICEINFO_V40 struDeviceInfo = {0};
            NET_DVR_DEVICEINFO_V40 struDeviceInfo1 = {0};
            lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfo);
            lUserID1 = NET_DVR_Login_V40(&struLoginInfo1, &struDeviceInfo1);
            if (lUserID < 0 || lUserID1 < 0)
            {
                qDebug() << "login error: " << NET_DVR_GetLastError();
                NET_DVR_Cleanup();
                return;
            }
            else
            {
                qDebug() << "login success";
                HWND hWND = (HWND)box->widgets.at(0)->winId();
                NET_DVR_PREVIEWINFO structPlayInfo;
                structPlayInfo.hPlayWnd = hWND;
                structPlayInfo.lChannel = 1;
                structPlayInfo.dwStreamType = 0;
                structPlayInfo.dwLinkMode = 0;
                structPlayInfo.bBlocked = 1;
                m_lPlayHandle =
                    NET_DVR_RealPlay_V40(lUserID, &structPlayInfo, nullptr, nullptr);
                HWND hWND1 = (HWND)box->widgets.at(1)->winId();
                NET_DVR_PREVIEWINFO structPlayInfo1;
                structPlayInfo1.hPlayWnd = hWND1;
                structPlayInfo1.lChannel = 1;
                structPlayInfo1.dwStreamType = 0;
                structPlayInfo1.dwLinkMode = 0;
                structPlayInfo1.bBlocked = 1;
                m_lPlayHandle1 =
                    NET_DVR_RealPlay_V40(lUserID1, &structPlayInfo1, nullptr, nullptr);
                if (m_lPlayHandle < 0 || m_lPlayHandle1 < 0)
                {
                    qDebug() << "preview error: " << NET_DVR_GetLastError();
                    NET_DVR_Logout(lUserID);
                    NET_DVR_Cleanup();
                    return ;
                }
            }
        }
        else
        {
            qDebug() << "SDK init failed: " << NET_DVR_GetLastError();
        }
        ui->loginBtn->setText("Logout");
    }
    else
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        NET_DVR_Logout(lUserID);
        NET_DVR_Cleanup();
        box->widgets.at(0)->setMask(box->widgets.at(0)->rect());
        box->widgets.at(1)->setMask(box->widgets.at(1)->rect());
        ui->loginBtn->setText("Login");
    }
    return ;
}


void MainWindow::on_leftupBtn_pressed()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, UP_LEFT, 0))
    {
        if (NET_DVR_GetLastError() == 3)
        {
            QMessageBox::critical(this, "ERROR", "Start Preview First!");
            return ;
        }
        else
        {
            QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
            QMessageBox::critical(this, "ERROR", errorMessage);
            return ;
        }
    }
}


void MainWindow::on_leftupBtn_released()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, UP_LEFT, 1))
    {
        QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
        QMessageBox::critical(this, "ERROR", errorMessage);
        return ;
    }
}


void MainWindow::on_upBtn_pressed()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, TILT_UP, 0))
    {
        if (NET_DVR_GetLastError() == 3)
        {
            QMessageBox::critical(this, "ERROR", "Start Preview First!");
            return ;
        }
        else
        {
            QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
            QMessageBox::critical(this, "ERROR", errorMessage);
            return ;
        }
    }
}


void MainWindow::on_upBtn_released()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, TILT_UP, 1))
    {
        QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
        QMessageBox::critical(this, "ERROR", errorMessage);
        return ;
    }
}


void MainWindow::on_rightupBtn_pressed()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, UP_RIGHT, 0))
    {
        if (NET_DVR_GetLastError() == 3)
        {
            QMessageBox::critical(this, "ERROR", "Start Preview First!");
            return ;
        }
        else
        {
            QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
            QMessageBox::critical(this, "ERROR", errorMessage);
            return ;
        }
    }
}


void MainWindow::on_rightupBtn_released()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, UP_RIGHT, 1))
    {
        QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
        QMessageBox::critical(this, "ERROR", errorMessage);
        return ;
    }
}


void MainWindow::on_rightBtn_pressed()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, PAN_RIGHT, 0))
    {
        if (NET_DVR_GetLastError() == 3)
        {
            QMessageBox::critical(this, "ERROR", "Start Preview First!");
            return ;
        }
        else
        {
            QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
            QMessageBox::critical(this, "ERROR", errorMessage);
            return ;
        }
    }
}


void MainWindow::on_rightBtn_released()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, PAN_RIGHT, 1))
    {
        QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
        QMessageBox::critical(this, "ERROR", errorMessage);
        return ;
    }
}


void MainWindow::on_rightdownBtn_pressed()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, DOWN_RIGHT, 0))
    {
        if (NET_DVR_GetLastError() == 3)
        {
            QMessageBox::critical(this, "ERROR", "Start Preview First!");
            return ;
        }
        else
        {
            QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
            QMessageBox::critical(this, "ERROR", errorMessage);
            return ;
        }
    }
}


void MainWindow::on_rightdownBtn_released()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, DOWN_RIGHT, 1))
    {
        QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
        QMessageBox::critical(this, "ERROR", errorMessage);
        return ;
    }
}


void MainWindow::on_downBtn_pressed()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, TILT_DOWN, 0))
    {
        if (NET_DVR_GetLastError() == 3)
        {
            QMessageBox::critical(this, "ERROR", "Start Preview First!");
            return ;
        }
        else
        {
            QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
            QMessageBox::critical(this, "ERROR", errorMessage);
            return ;
        }
    }
}


void MainWindow::on_downBtn_released()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, TILT_DOWN, 1))
    {
        QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
        QMessageBox::critical(this, "ERROR", errorMessage);
        return ;
    }
}


void MainWindow::on_leftdownBtn_pressed()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, DOWN_LEFT, 0))
    {
        if (NET_DVR_GetLastError() == 3)
        {
            QMessageBox::critical(this, "ERROR", "Start Preview First!");
            return ;
        }
        else
        {
            QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
            QMessageBox::critical(this, "ERROR", errorMessage);
            return ;
        }
    }
}


void MainWindow::on_leftdownBtn_released()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, DOWN_LEFT, 1))
    {
        QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
        QMessageBox::critical(this, "ERROR", errorMessage);
        return ;
    }
}


void MainWindow::on_leftBtn_pressed()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, PAN_LEFT, 0))
    {
        if (NET_DVR_GetLastError() == 3)
        {
            QMessageBox::critical(this, "ERROR", "Start Preview First!");
            return ;
        }
        else
        {
            QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
            QMessageBox::critical(this, "ERROR", errorMessage);
            return ;
        }
    }
}


void MainWindow::on_leftBtn_released()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, PAN_LEFT, 1))
    {
        QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
        QMessageBox::critical(this, "ERROR", errorMessage);
        return ;
    }
}


void MainWindow::on_zoominBtn_pressed()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, ZOOM_IN, 0))
    {
        if (NET_DVR_GetLastError() == 3)
        {
            QMessageBox::critical(this, "ERROR", "Start Preview First!");
            return ;
        }
        else
        {
            QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
            QMessageBox::critical(this, "ERROR", errorMessage);
            return ;
        }
    }
}


void MainWindow::on_zoominBtn_released()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, ZOOM_IN, 1))
    {
        QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
        QMessageBox::critical(this, "ERROR", errorMessage);
        return ;
    }
}


void MainWindow::on_zoomoutBtn_pressed()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, ZOOM_OUT, 0))
    {
        if (NET_DVR_GetLastError() == 3)
        {
            QMessageBox::critical(this, "ERROR", "Start Preview First!");
            return ;
        }
        else
        {
            QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
            QMessageBox::critical(this, "ERROR", errorMessage);
            return ;
        }
    }
}


void MainWindow::on_zoomoutBtn_released()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, ZOOM_OUT, 1))
    {
        QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
        QMessageBox::critical(this, "ERROR", errorMessage);
        return ;
    }
}


void MainWindow::on_focusnearBtn_pressed()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, FOCUS_NEAR, 0))
    {
        if (NET_DVR_GetLastError() == 3)
        {
            QMessageBox::critical(this, "ERROR", "Start Preview First!");
            return ;
        }
        else
        {
            QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
            QMessageBox::critical(this, "ERROR", errorMessage);
            return ;
        }
    }
}


void MainWindow::on_focusnearBtn_released()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, FOCUS_NEAR, 1))
    {
        QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
        QMessageBox::critical(this, "ERROR", errorMessage);
        return ;
    }
}


void MainWindow::on_focusfarBtn_pressed()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, FOCUS_FAR, 0))
    {
        if (NET_DVR_GetLastError() == 3)
        {
            QMessageBox::critical(this, "ERROR", "Start Preview First!");
            return ;
        }
        else
        {
            QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
            QMessageBox::critical(this, "ERROR", errorMessage);
            return ;
        }
    }
}


void MainWindow::on_focusfarBtn_released()
{
    if (!NET_DVR_PTZControl(m_lPlayHandle, FOCUS_FAR, 1))
    {
        QString errorMessage = "Error Occurred! Error Code: " + QString::fromStdString(std::to_string(NET_DVR_GetLastError()));
        QMessageBox::critical(this, "ERROR", errorMessage);
        return ;
    }
}

