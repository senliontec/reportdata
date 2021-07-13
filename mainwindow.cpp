#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setProgressbarUI();
    ui->statusbar->setSizeGripEnabled(false);
    ui->tabWidget->tabsClosable();
    ui->tabWidget->setTabsClosable(true);
    this->setWindowTitle(tr("excel处理"));
    this->setWindowState(Qt::WindowMaximized);
    this->setAttribute(Qt::WA_DeleteOnClose);
//    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(updateCurSheet(int)));
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(setCloseTab(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actOpen_Excel_triggered()
{
    ExcelHelper* excelhelper = new ExcelHelper(this);
    QList<QMap<int, QStringList>> exceltolist = excelhelper->openExcel();
    deleteTabPage();
    addTabPage(exceltolist);
}


void MainWindow::on_actSave_Excel_triggered()
{
    QList<QMap<int, QStringList>> sheets;
    ExcelHelper* excelhelper = new ExcelHelper(this);
    qDebug() << tabledatas.size();
    for (int i = 0; i < tabledatas.size(); i++) {
        QMap<int, QStringList> sheet =  tabledatas.at(i)->getTableModel();
        sheets.append(sheet);
    }
    excelhelper->saveExcel(sheets);
}

void MainWindow::on_actMerge_Excel_triggered()
{
    DataFilter* dlg = new DataFilter;
    int ret = dlg->exec();
    if (ret == QDialog::Accepted) {
        delete dlg;
    }
    if (ret == QDialog::Rejected) {
    }
}

void MainWindow::on_actOneMerge_Excel_triggered()
{
    QList<QStringList> names;
    for(int i = 0; i < tabledatas.size(); i++) {
        QStringList name = tabledatas.at(i)->getPersonNames();
        names.append(name);
    }
}

int MainWindow::getTabCurrentIndex()
{
    int index = ui->tabWidget->currentIndex();
    return  index;
}

void MainWindow::addTabPage(QList<QMap<int, QStringList>> exceltolist)
{
    for (int i = 0; i < exceltolist.size(); i++) {
        TableData* tabledata = new TableData();
        tabledata->setTableModel(exceltolist[i]);
        tabledatas.append(tabledata);
        ui->tabWidget->addTab(tabledata, QString::asprintf("Sheet %d", ui->tabWidget->count() + 1));
    }
}

//void MainWindow::updateCurSheet(int index)
//{
//    curtabledata = tabledatas.at(index);
//}

void MainWindow::setCloseTab(int index)
{
    ui->tabWidget->removeTab(index);
    delete tabledatas.at(index);
    tabledatas.removeAt(index);
}

void MainWindow::deleteTabPage()
{
    for(int i = 0; i < tabledatas.size(); i++) {
        ui->tabWidget->removeTab(i);
    }
    qDeleteAll(tabledatas);
    tabledatas.clear();
}


void MainWindow::setProgressbarUI()
{
    QLabel *  pLabel = new QLabel();
    pLabel->setText("请稍候...");
    QProgressBar* probar = new QProgressBar();
    probar->setFixedWidth(200);
    ui->statusbar->addPermanentWidget(pLabel);
    ui->statusbar->addPermanentWidget(probar);
    QLabel *versioninfo = new QLabel(this);
    versioninfo->setFrameStyle(QFrame::Box | QFrame::Sunken);
    versioninfo->setText(tr("<a href=\"https://github.com/ciss-projects-manager/reportdata.git\">版本更新</a>"));
    versioninfo->setOpenExternalLinks(true);
    ui->statusbar->addWidget(versioninfo);
}



