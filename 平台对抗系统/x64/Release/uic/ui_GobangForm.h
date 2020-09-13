/********************************************************************************
** Form generated from reading UI file 'GobangForm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOBANGFORM_H
#define UI_GOBANGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GobangForm
{
public:
    QGridLayout *gridLayout;
    QGridLayout *grid_chess;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QLabel *label_white;
    QPushButton *btn_start;
    QPushButton *btn_peace;
    QPushButton *btn_regret;
    QLabel *label_black;
    QPushButton *btn_giveup;

    void setupUi(QWidget *GobangForm)
    {
        if (GobangForm->objectName().isEmpty())
            GobangForm->setObjectName(QString::fromUtf8("GobangForm"));
        GobangForm->resize(705, 560);
        gridLayout = new QGridLayout(GobangForm);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        grid_chess = new QGridLayout();
        grid_chess->setSpacing(6);
        grid_chess->setObjectName(QString::fromUtf8("grid_chess"));

        gridLayout->addLayout(grid_chess, 0, 0, 1, 1);

        frame = new QFrame(GobangForm);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMaximumSize(QSize(150, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_white = new QLabel(frame);
        label_white->setObjectName(QString::fromUtf8("label_white"));
        label_white->setMinimumSize(QSize(140, 140));
        label_white->setMaximumSize(QSize(140, 140));

        gridLayout_3->addWidget(label_white, 5, 0, 1, 1);

        btn_start = new QPushButton(frame);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));

        gridLayout_3->addWidget(btn_start, 1, 0, 1, 1);

        btn_peace = new QPushButton(frame);
        btn_peace->setObjectName(QString::fromUtf8("btn_peace"));

        gridLayout_3->addWidget(btn_peace, 3, 0, 1, 1);

        btn_regret = new QPushButton(frame);
        btn_regret->setObjectName(QString::fromUtf8("btn_regret"));

        gridLayout_3->addWidget(btn_regret, 2, 0, 1, 1);

        label_black = new QLabel(frame);
        label_black->setObjectName(QString::fromUtf8("label_black"));
        label_black->setMinimumSize(QSize(140, 140));
        label_black->setMaximumSize(QSize(140, 140));

        gridLayout_3->addWidget(label_black, 0, 0, 1, 1);

        btn_giveup = new QPushButton(frame);
        btn_giveup->setObjectName(QString::fromUtf8("btn_giveup"));

        gridLayout_3->addWidget(btn_giveup, 4, 0, 1, 1);


        gridLayout->addWidget(frame, 0, 1, 1, 1);


        retranslateUi(GobangForm);

        QMetaObject::connectSlotsByName(GobangForm);
    } // setupUi

    void retranslateUi(QWidget *GobangForm)
    {
        GobangForm->setWindowTitle(QApplication::translate("GobangForm", "GobangForm", nullptr));
        label_white->setText(QApplication::translate("GobangForm", "\347\231\275\345\255\220", nullptr));
        btn_start->setText(QApplication::translate("GobangForm", "\345\274\200\345\247\213", nullptr));
        btn_peace->setText(QApplication::translate("GobangForm", "\346\261\202\345\222\214", nullptr));
        btn_regret->setText(QApplication::translate("GobangForm", "\346\202\224\346\243\213", nullptr));
        label_black->setText(QApplication::translate("GobangForm", "\351\273\221\345\255\220", nullptr));
        btn_giveup->setText(QApplication::translate("GobangForm", "\350\256\244\350\264\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GobangForm: public Ui_GobangForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOBANGFORM_H
