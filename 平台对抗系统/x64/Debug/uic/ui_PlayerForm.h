/********************************************************************************
** Form generated from reading UI file 'PlayerForm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERFORM_H
#define UI_PLAYERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerForm
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QPushButton *btn_PVP;
    QPushButton *btn_PVE_GB;
    QPushButton *btn_PVE_HE;
    QPushButton *btn_Refresh;
    QPushButton *btn_Rank;
    QPushButton *btn_SignOut;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_PVP;
    QLabel *label_PVE_GB;
    QLabel *label_PVE_HE;
    QTableView *SHOW;

    void setupUi(QWidget *PlayerForm)
    {
        if (PlayerForm->objectName().isEmpty())
            PlayerForm->setObjectName(QString::fromUtf8("PlayerForm"));
        PlayerForm->resize(665, 526);
        gridLayout = new QGridLayout(PlayerForm);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(PlayerForm);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(0, 300));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font.setPointSize(24);
        tabWidget->setFont(font);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        btn_PVP = new QPushButton(tab);
        btn_PVP->setObjectName(QString::fromUtf8("btn_PVP"));
        btn_PVP->setMinimumSize(QSize(0, 80));
        QFont font1;
        font1.setPointSize(18);
        btn_PVP->setFont(font1);

        gridLayout_2->addWidget(btn_PVP, 0, 0, 1, 1);

        btn_PVE_GB = new QPushButton(tab);
        btn_PVE_GB->setObjectName(QString::fromUtf8("btn_PVE_GB"));
        btn_PVE_GB->setMinimumSize(QSize(0, 80));
        btn_PVE_GB->setFont(font1);

        gridLayout_2->addWidget(btn_PVE_GB, 0, 1, 1, 1);

        btn_PVE_HE = new QPushButton(tab);
        btn_PVE_HE->setObjectName(QString::fromUtf8("btn_PVE_HE"));
        btn_PVE_HE->setMinimumSize(QSize(0, 80));
        btn_PVE_HE->setFont(font1);

        gridLayout_2->addWidget(btn_PVE_HE, 0, 2, 1, 1);

        btn_Refresh = new QPushButton(tab);
        btn_Refresh->setObjectName(QString::fromUtf8("btn_Refresh"));
        btn_Refresh->setMinimumSize(QSize(0, 80));
        btn_Refresh->setFont(font1);

        gridLayout_2->addWidget(btn_Refresh, 1, 0, 1, 1);

        btn_Rank = new QPushButton(tab);
        btn_Rank->setObjectName(QString::fromUtf8("btn_Rank"));
        btn_Rank->setMinimumSize(QSize(0, 80));
        btn_Rank->setFont(font1);

        gridLayout_2->addWidget(btn_Rank, 1, 1, 1, 1);

        btn_SignOut = new QPushButton(tab);
        btn_SignOut->setObjectName(QString::fromUtf8("btn_SignOut"));
        btn_SignOut->setMinimumSize(QSize(0, 80));
        btn_SignOut->setFont(font1);

        gridLayout_2->addWidget(btn_SignOut, 1, 2, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font2.setPointSize(18);
        label->setFont(font2);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font2);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font3.setPointSize(16);
        label_3->setFont(font3);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_PVP = new QLabel(tab_2);
        label_PVP->setObjectName(QString::fromUtf8("label_PVP"));
        label_PVP->setFont(font2);
        label_PVP->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_PVP);

        label_PVE_GB = new QLabel(tab_2);
        label_PVE_GB->setObjectName(QString::fromUtf8("label_PVE_GB"));
        label_PVE_GB->setFont(font2);
        label_PVE_GB->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_PVE_GB);

        label_PVE_HE = new QLabel(tab_2);
        label_PVE_HE->setObjectName(QString::fromUtf8("label_PVE_HE"));
        label_PVE_HE->setFont(font3);
        label_PVE_HE->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_PVE_HE);


        gridLayout_3->addLayout(verticalLayout_2, 0, 1, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1, Qt::AlignTop);

        SHOW = new QTableView(PlayerForm);
        SHOW->setObjectName(QString::fromUtf8("SHOW"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(SHOW->sizePolicy().hasHeightForWidth());
        SHOW->setSizePolicy(sizePolicy1);
        SHOW->setMaximumSize(QSize(16777215, 200));

        gridLayout->addWidget(SHOW, 1, 0, 1, 1);


        retranslateUi(PlayerForm);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PlayerForm);
    } // setupUi

    void retranslateUi(QWidget *PlayerForm)
    {
        PlayerForm->setWindowTitle(QApplication::translate("PlayerForm", "PlayerForm", nullptr));
        btn_PVP->setText(QApplication::translate("PlayerForm", "\347\275\221\347\273\234\345\257\271\346\210\230", nullptr));
        btn_PVE_GB->setText(QApplication::translate("PlayerForm", "\344\272\224\345\255\220\346\243\213\344\272\272\346\234\272", nullptr));
        btn_PVE_HE->setText(QApplication::translate("PlayerForm", "\345\274\200\345\277\203\346\266\210\346\266\210\344\271\220", nullptr));
        btn_Refresh->setText(QApplication::translate("PlayerForm", "\345\234\250\347\272\277\344\272\272\346\225\260", nullptr));
        btn_Rank->setText(QApplication::translate("PlayerForm", "\346\216\222\350\241\214\346\246\234", nullptr));
        btn_SignOut->setText(QApplication::translate("PlayerForm", "\347\231\273\345\207\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("PlayerForm", "Game", nullptr));
        label->setText(QApplication::translate("PlayerForm", "PVP\346\210\230\347\273\251/Rank", nullptr));
        label_2->setText(QApplication::translate("PlayerForm", "PVE\350\264\245\345\234\272/Rank", nullptr));
        label_3->setText(QApplication::translate("PlayerForm", "\346\266\210\346\266\210\344\271\220\346\234\200\351\253\230\345\210\206/Rank", nullptr));
        label_PVP->setText(QApplication::translate("PlayerForm", "0", nullptr));
        label_PVE_GB->setText(QApplication::translate("PlayerForm", "0", nullptr));
        label_PVE_HE->setText(QApplication::translate("PlayerForm", "0", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("PlayerForm", "Home", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayerForm: public Ui_PlayerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERFORM_H
