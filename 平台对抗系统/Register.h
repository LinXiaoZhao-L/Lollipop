#pragma once
#pragma execution_character_set("utf-8")

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>

#include <QtWidgets/QMainWindow>
#include "ui_Register.h"
#include "PlayerForm.h"

class Register : public QMainWindow
{
    Q_OBJECT

public:
    Register(QWidget *parent = Q_NULLPTR);

    void login();

private slots:
    void on_Register_clicked();
    void on_Close_clicked();
    void doProBack(QString);

private:
    Ui::RegisterClass ui;
    PlayerForm* playerForm;

    void Init();

signals:
    void SendUserNo(QString User);
};

#endif // MAINWINDOW_H