/********************************************************************************
** Form generated from reading UI file 'Register.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *Edit_PassWord;
    QLabel *label_2;
    QLineEdit *Edit_Account;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_Register;
    QPushButton *btn_Close;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RegisterClass)
    {
        if (RegisterClass->objectName().isEmpty())
            RegisterClass->setObjectName(QString::fromUtf8("RegisterClass"));
        RegisterClass->resize(518, 352);
        centralWidget = new QWidget(RegisterClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 70));
        label->setMaximumSize(QSize(16777215, 70));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font.setPointSize(26);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(100, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font1.setPointSize(16);
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        Edit_PassWord = new QLineEdit(centralWidget);
        Edit_PassWord->setObjectName(QString::fromUtf8("Edit_PassWord"));
        Edit_PassWord->setMinimumSize(QSize(250, 50));
        Edit_PassWord->setMaximumSize(QSize(330, 16777215));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(16);
        Edit_PassWord->setFont(font2);

        gridLayout->addWidget(Edit_PassWord, 1, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(100, 30));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        Edit_Account = new QLineEdit(centralWidget);
        Edit_Account->setObjectName(QString::fromUtf8("Edit_Account"));
        Edit_Account->setMinimumSize(QSize(250, 50));
        Edit_Account->setMaximumSize(QSize(330, 16777215));
        Edit_Account->setFont(font2);

        gridLayout->addWidget(Edit_Account, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btn_Register = new QPushButton(centralWidget);
        btn_Register->setObjectName(QString::fromUtf8("btn_Register"));
        btn_Register->setMinimumSize(QSize(0, 70));
        btn_Register->setFont(font1);

        horizontalLayout->addWidget(btn_Register);

        btn_Close = new QPushButton(centralWidget);
        btn_Close->setObjectName(QString::fromUtf8("btn_Close"));
        btn_Close->setMinimumSize(QSize(0, 70));
        btn_Close->setFont(font1);

        horizontalLayout->addWidget(btn_Close);


        gridLayout_2->addLayout(horizontalLayout, 2, 0, 1, 1);

        RegisterClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RegisterClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 518, 26));
        RegisterClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RegisterClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        RegisterClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RegisterClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        RegisterClass->setStatusBar(statusBar);

        retranslateUi(RegisterClass);

        QMetaObject::connectSlotsByName(RegisterClass);
    } // setupUi

    void retranslateUi(QMainWindow *RegisterClass)
    {
        RegisterClass->setWindowTitle(QApplication::translate("RegisterClass", "Register", nullptr));
        label->setText(QApplication::translate("RegisterClass", "\345\271\263\345\217\260\345\257\271\346\212\227\347\263\273\347\273\237", nullptr));
        label_3->setText(QApplication::translate("RegisterClass", "\345\257\206\347\240\201", nullptr));
        label_2->setText(QApplication::translate("RegisterClass", "\346\230\265\347\247\260/\350\264\246\345\217\267", nullptr));
        btn_Register->setText(QApplication::translate("RegisterClass", "\347\231\273\345\275\225/\346\263\250\345\206\214", nullptr));
        btn_Close->setText(QApplication::translate("RegisterClass", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterClass: public Ui_RegisterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
