/********************************************************************************
** Form generated from reading UI file 'HappyEForm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HAPPYEFORM_H
#define UI_HAPPYEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HappyEForm
{
public:
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout;
    QFrame *frame;
    QPushButton *btn_start;
    QLCDNumber *LCDnum;
    QPushButton *btn_auto;

    void setupUi(QWidget *HappyEForm)
    {
        if (HappyEForm->objectName().isEmpty())
            HappyEForm->setObjectName(QString::fromUtf8("HappyEForm"));
        HappyEForm->resize(514, 780);
        gridLayout_5 = new QGridLayout(HappyEForm);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        gridLayout_5->addLayout(gridLayout, 0, 0, 1, 1);

        frame = new QFrame(HappyEForm);
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

        gridLayout_5->addWidget(frame, 1, 0, 1, 1);


        retranslateUi(HappyEForm);

        QMetaObject::connectSlotsByName(HappyEForm);
    } // setupUi

    void retranslateUi(QWidget *HappyEForm)
    {
        HappyEForm->setWindowTitle(QApplication::translate("HappyEForm", "HappyEForm", nullptr));
        btn_start->setText(QApplication::translate("HappyEForm", "\345\274\200\345\247\213", nullptr));
        btn_auto->setText(QApplication::translate("HappyEForm", "\346\211\230\347\256\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HappyEForm: public Ui_HappyEForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HAPPYEFORM_H
