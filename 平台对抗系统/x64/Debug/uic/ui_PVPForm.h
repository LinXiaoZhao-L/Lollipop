/********************************************************************************
** Form generated from reading UI file 'PVPForm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PVPFORM_H
#define UI_PVPFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PVPForm
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_black;
    QLabel *Black_Name;
    QPushButton *btn_start;
    QPushButton *btn_regret;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *Rblack;
    QRadioButton *Rwhite;
    QPushButton *btn_peace;
    QPushButton *btn_giveup;
    QLabel *White_Name;
    QLabel *label_white;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *tEdit_Msg;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_Send;
    QPushButton *btn_Empty;
    QTextEdit *tEdit_Send;

    void setupUi(QWidget *PVPForm)
    {
        if (PVPForm->objectName().isEmpty())
            PVPForm->setObjectName(QString::fromUtf8("PVPForm"));
        PVPForm->resize(1068, 627);
        gridLayoutWidget = new QWidget(PVPForm);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(180, 20, 611, 591));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        layoutWidget = new QWidget(PVPForm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 21, 152, 591));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_black = new QLabel(layoutWidget);
        label_black->setObjectName(QString::fromUtf8("label_black"));
        label_black->setMinimumSize(QSize(150, 150));
        label_black->setMaximumSize(QSize(150, 150));

        verticalLayout->addWidget(label_black);

        Black_Name = new QLabel(layoutWidget);
        Black_Name->setObjectName(QString::fromUtf8("Black_Name"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(16);
        Black_Name->setFont(font);
        Black_Name->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(Black_Name);

        btn_start = new QPushButton(layoutWidget);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));

        verticalLayout->addWidget(btn_start);

        btn_regret = new QPushButton(layoutWidget);
        btn_regret->setObjectName(QString::fromUtf8("btn_regret"));

        verticalLayout->addWidget(btn_regret);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        Rblack = new QRadioButton(layoutWidget);
        Rblack->setObjectName(QString::fromUtf8("Rblack"));
        Rblack->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_2->addWidget(Rblack);

        Rwhite = new QRadioButton(layoutWidget);
        Rwhite->setObjectName(QString::fromUtf8("Rwhite"));

        horizontalLayout_2->addWidget(Rwhite);


        verticalLayout->addLayout(horizontalLayout_2);

        btn_peace = new QPushButton(layoutWidget);
        btn_peace->setObjectName(QString::fromUtf8("btn_peace"));

        verticalLayout->addWidget(btn_peace);

        btn_giveup = new QPushButton(layoutWidget);
        btn_giveup->setObjectName(QString::fromUtf8("btn_giveup"));

        verticalLayout->addWidget(btn_giveup);

        White_Name = new QLabel(layoutWidget);
        White_Name->setObjectName(QString::fromUtf8("White_Name"));
        White_Name->setFont(font);
        White_Name->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(White_Name);

        label_white = new QLabel(layoutWidget);
        label_white->setObjectName(QString::fromUtf8("label_white"));
        label_white->setMinimumSize(QSize(150, 150));
        label_white->setMaximumSize(QSize(150, 150));

        verticalLayout->addWidget(label_white);

        layoutWidget1 = new QWidget(PVPForm);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(800, 20, 252, 591));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tEdit_Msg = new QTextEdit(layoutWidget1);
        tEdit_Msg->setObjectName(QString::fromUtf8("tEdit_Msg"));
        tEdit_Msg->setMinimumSize(QSize(250, 0));
        tEdit_Msg->setMaximumSize(QSize(250, 16777215));

        verticalLayout_2->addWidget(tEdit_Msg);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btn_Send = new QPushButton(layoutWidget1);
        btn_Send->setObjectName(QString::fromUtf8("btn_Send"));

        horizontalLayout->addWidget(btn_Send);

        btn_Empty = new QPushButton(layoutWidget1);
        btn_Empty->setObjectName(QString::fromUtf8("btn_Empty"));

        horizontalLayout->addWidget(btn_Empty);


        verticalLayout_2->addLayout(horizontalLayout);

        tEdit_Send = new QTextEdit(layoutWidget1);
        tEdit_Send->setObjectName(QString::fromUtf8("tEdit_Send"));
        tEdit_Send->setMinimumSize(QSize(250, 100));
        tEdit_Send->setMaximumSize(QSize(250, 100));

        verticalLayout_2->addWidget(tEdit_Send);


        retranslateUi(PVPForm);

        QMetaObject::connectSlotsByName(PVPForm);
    } // setupUi

    void retranslateUi(QWidget *PVPForm)
    {
        PVPForm->setWindowTitle(QApplication::translate("PVPForm", "PVPForm", nullptr));
        label_black->setText(QApplication::translate("PVPForm", "\351\273\221\345\255\220\345\233\276\346\240\207", nullptr));
        Black_Name->setText(QApplication::translate("PVPForm", "\351\273\221\345\255\220\347\216\251\345\256\266", nullptr));
        btn_start->setText(QApplication::translate("PVPForm", "\345\274\200\345\247\213", nullptr));
        btn_regret->setText(QApplication::translate("PVPForm", "\346\202\224\346\243\213", nullptr));
        Rblack->setText(QApplication::translate("PVPForm", "\351\273\221\345\255\220", nullptr));
        Rwhite->setText(QApplication::translate("PVPForm", "\347\231\275\345\255\220", nullptr));
        btn_peace->setText(QApplication::translate("PVPForm", "\346\261\202\345\222\214", nullptr));
        btn_giveup->setText(QApplication::translate("PVPForm", "\350\256\244\350\264\237", nullptr));
        White_Name->setText(QApplication::translate("PVPForm", "\347\231\275\345\255\220\347\216\251\345\256\266", nullptr));
        label_white->setText(QApplication::translate("PVPForm", "\347\231\275\345\255\220\345\233\276\346\240\207", nullptr));
        btn_Send->setText(QApplication::translate("PVPForm", "\345\217\221\351\200\201", nullptr));
        btn_Empty->setText(QApplication::translate("PVPForm", "\346\270\205\347\251\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PVPForm: public Ui_PVPForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PVPFORM_H
