/********************************************************************************
** Form generated from reading UI file 'HappyEliminate.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HAPPYELIMINATE_H
#define UI_HAPPYELIMINATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HappyEliminateClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QFrame *frame;
    QPushButton *btn_start;
    QLCDNumber *LCDnum;
    QPushButton *btn_auto;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *HappyEliminateClass)
    {
        if (HappyEliminateClass->objectName().isEmpty())
            HappyEliminateClass->setObjectName(QString::fromUtf8("HappyEliminateClass"));
        HappyEliminateClass->resize(518, 789);
        centralWidget = new QWidget(HappyEliminateClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMaximumSize(QSize(16777215, 80));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        btn_start = new QPushButton(frame);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));
        btn_start->setGeometry(QRect(50, 10, 91, 61));
        LCDnum = new QLCDNumber(frame);
        LCDnum->setObjectName(QString::fromUtf8("LCDnum"));
        LCDnum->setGeometry(QRect(270, 10, 181, 61));
        btn_auto = new QPushButton(frame);
        btn_auto->setObjectName(QString::fromUtf8("btn_auto"));
        btn_auto->setGeometry(QRect(162, 10, 91, 61));

        gridLayout_2->addWidget(frame, 1, 0, 1, 1);

        HappyEliminateClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(HappyEliminateClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 518, 26));
        HappyEliminateClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(HappyEliminateClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        HappyEliminateClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(HappyEliminateClass);

        QMetaObject::connectSlotsByName(HappyEliminateClass);
    } // setupUi

    void retranslateUi(QMainWindow *HappyEliminateClass)
    {
        HappyEliminateClass->setWindowTitle(QApplication::translate("HappyEliminateClass", "HappyEliminate", nullptr));
        btn_start->setText(QApplication::translate("HappyEliminateClass", "\345\274\200\345\247\213", nullptr));
        btn_auto->setText(QApplication::translate("HappyEliminateClass", "\346\211\230\347\256\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HappyEliminateClass: public Ui_HappyEliminateClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HAPPYELIMINATE_H
