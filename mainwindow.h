#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QVector>
#include <QList>
#include <QCloseEvent>
#include "person.h"
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QListView>
#include <QTextStream>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNewBook_triggered();

    void on_actionOpen_triggered();

    void on_action_Save_triggered();

    void on_action_SaveAs_triggered();

    void on_action_Exit_triggered();

    void on_action_SortName_triggered();

    void on_action_SortZipCode_triggered();



    void on_pushButton_addContacct_clicked();

    void on_pushButton_editContact_clicked();

    void on_pushButton_deleteContact_clicked();

    void on_pushButton_exit_clicked();

    void on_listWidget_itemSelectionChanged();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_fillValues_clicked();



private:
    Ui::MainWindow *ui;

    QList<Person> persons;

    QFile currentFile;



};

#endif // MAINWINDOW_H
