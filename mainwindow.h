#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QTableView>
#include <QStandardItem>
#include <QProgressBar>
#include <QPushButton>
#include <QWidget>


#include "excelhelper.h"
#include "tabledata.h"
#include "datafilter.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    ExcelHelper* excelhelper;
    QList<TableData*> tabledatas;
    TableData* curtabledata;
    int getTabCurrentIndex();
    void addTabPage(QList<QMap<int, QStringList>> exceltolist);
    void deleteTabPage();
    void setProgressbarUI();
    void setSearchUI();

private slots:
    void on_actOpen_Excel_triggered();

    void on_actSave_Excel_triggered();

    void setCloseTab(int index);

    void on_actMerge_Excel_triggered();

    void on_actOneMerge_Excel_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
