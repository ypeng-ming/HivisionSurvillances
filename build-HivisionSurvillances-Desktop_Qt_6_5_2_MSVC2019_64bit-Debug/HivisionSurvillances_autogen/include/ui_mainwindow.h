/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayoutVideo;
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QLineEdit *usernamebox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    QLineEdit *passwordbox;
    QPushButton *loginBtn;
    QGridLayout *gridLayout_3;
    QPushButton *downBtn;
    QPushButton *leftBtn;
    QPushButton *upBtn;
    QPushButton *rightBtn;
    QPushButton *leftupBtn;
    QPushButton *leftdownBtn;
    QPushButton *rightdownBtn;
    QPushButton *rightupBtn;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *zoominBtn;
    QPushButton *zoomoutBtn;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *focusnearBtn;
    QPushButton *focusfarBtn;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setMaximumSize(QSize(16777215, 9));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayoutVideo = new QGridLayout();
        gridLayoutVideo->setObjectName("gridLayoutVideo");

        gridLayout_2->addLayout(gridLayoutVideo, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);

        verticalFrame = new QFrame(centralwidget);
        verticalFrame->setObjectName("verticalFrame");
        verticalFrame->setMaximumSize(QSize(200, 16777215));
        verticalLayout = new QVBoxLayout(verticalFrame);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_6 = new QLabel(verticalFrame);
        label_6->setObjectName("label_6");

        horizontalLayout->addWidget(label_6, 0, Qt::AlignHCenter);

        usernamebox = new QLineEdit(verticalFrame);
        usernamebox->setObjectName("usernamebox");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(usernamebox->sizePolicy().hasHeightForWidth());
        usernamebox->setSizePolicy(sizePolicy);
        usernamebox->setMinimumSize(QSize(140, 0));
        usernamebox->setMaximumSize(QSize(150, 22));

        horizontalLayout->addWidget(usernamebox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_7 = new QLabel(verticalFrame);
        label_7->setObjectName("label_7");

        horizontalLayout_2->addWidget(label_7, 0, Qt::AlignHCenter);

        passwordbox = new QLineEdit(verticalFrame);
        passwordbox->setObjectName("passwordbox");
        sizePolicy.setHeightForWidth(passwordbox->sizePolicy().hasHeightForWidth());
        passwordbox->setSizePolicy(sizePolicy);
        passwordbox->setMinimumSize(QSize(140, 0));
        passwordbox->setMaximumSize(QSize(96, 22));

        horizontalLayout_2->addWidget(passwordbox);


        verticalLayout->addLayout(horizontalLayout_2);

        loginBtn = new QPushButton(verticalFrame);
        loginBtn->setObjectName("loginBtn");
        loginBtn->setMaximumSize(QSize(96, 16777215));

        verticalLayout->addWidget(loginBtn, 0, Qt::AlignRight);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        downBtn = new QPushButton(verticalFrame);
        downBtn->setObjectName("downBtn");

        gridLayout_3->addWidget(downBtn, 2, 1, 1, 1);

        leftBtn = new QPushButton(verticalFrame);
        leftBtn->setObjectName("leftBtn");

        gridLayout_3->addWidget(leftBtn, 1, 0, 1, 1);

        upBtn = new QPushButton(verticalFrame);
        upBtn->setObjectName("upBtn");

        gridLayout_3->addWidget(upBtn, 0, 1, 1, 1);

        rightBtn = new QPushButton(verticalFrame);
        rightBtn->setObjectName("rightBtn");

        gridLayout_3->addWidget(rightBtn, 1, 2, 1, 1);

        leftupBtn = new QPushButton(verticalFrame);
        leftupBtn->setObjectName("leftupBtn");

        gridLayout_3->addWidget(leftupBtn, 0, 0, 1, 1);

        leftdownBtn = new QPushButton(verticalFrame);
        leftdownBtn->setObjectName("leftdownBtn");

        gridLayout_3->addWidget(leftdownBtn, 2, 0, 1, 1);

        rightdownBtn = new QPushButton(verticalFrame);
        rightdownBtn->setObjectName("rightdownBtn");

        gridLayout_3->addWidget(rightdownBtn, 2, 2, 1, 1);

        rightupBtn = new QPushButton(verticalFrame);
        rightupBtn->setObjectName("rightupBtn");

        gridLayout_3->addWidget(rightupBtn, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        zoominBtn = new QPushButton(verticalFrame);
        zoominBtn->setObjectName("zoominBtn");

        horizontalLayout_3->addWidget(zoominBtn);

        zoomoutBtn = new QPushButton(verticalFrame);
        zoomoutBtn->setObjectName("zoomoutBtn");

        horizontalLayout_3->addWidget(zoomoutBtn);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        focusnearBtn = new QPushButton(verticalFrame);
        focusnearBtn->setObjectName("focusnearBtn");

        horizontalLayout_4->addWidget(focusnearBtn);

        focusfarBtn = new QPushButton(verticalFrame);
        focusfarBtn->setObjectName("focusfarBtn");

        horizontalLayout_4->addWidget(focusfarBtn);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addWidget(verticalFrame, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201", nullptr));
        loginBtn->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        downBtn->setText(QCoreApplication::translate("MainWindow", "\344\270\213\347\247\273", nullptr));
        leftBtn->setText(QCoreApplication::translate("MainWindow", "\345\267\246\347\247\273", nullptr));
        upBtn->setText(QCoreApplication::translate("MainWindow", "\344\270\212\347\247\273", nullptr));
        rightBtn->setText(QCoreApplication::translate("MainWindow", "\345\217\263\347\247\273", nullptr));
        leftupBtn->setText(QCoreApplication::translate("MainWindow", "\345\267\246\344\270\212\347\247\273", nullptr));
        leftdownBtn->setText(QCoreApplication::translate("MainWindow", "\345\235\220\344\270\213\347\247\273", nullptr));
        rightdownBtn->setText(QCoreApplication::translate("MainWindow", "\345\217\263\344\270\213\347\247\273", nullptr));
        rightupBtn->setText(QCoreApplication::translate("MainWindow", "\345\217\263\344\270\212\347\247\273", nullptr));
        zoominBtn->setText(QCoreApplication::translate("MainWindow", "Zoom in", nullptr));
        zoomoutBtn->setText(QCoreApplication::translate("MainWindow", "Zoom out", nullptr));
        focusnearBtn->setText(QCoreApplication::translate("MainWindow", "Focus Near", nullptr));
        focusfarBtn->setText(QCoreApplication::translate("MainWindow", "Foucs Far", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
