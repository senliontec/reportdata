#include "tabledata.h"
#include <QDebug>
TableData::TableData(QObject* parent)
    : QTableView()
{
    theModel = new QStandardItemModel(this);
    this->setModel(theModel);
}

void TableData::setTableModel(QMap<int, QStringList> exceltomap)
{
    QStandardItem* item;
    // 设置表头
    QStringList headerlist = exceltomap[0];
    for (int i = 0; i < headerlist.size(); i++) {
        item = new QStandardItem(headerlist[0]);
        theModel->setHorizontalHeaderItem(i, item);
    }
    // 设置数据区
    for (int i = 1; i < exceltomap.size(); i++) {
        QStringList rowlist = exceltomap[i];
        for (int j = 0; j < rowlist.size(); j++) {
            item = new QStandardItem(rowlist[j]);
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            theModel->setItem(i - 1, j, item);
        }
    }
}

QMap<int, QStringList> TableData::getTableModel()
{
    QStandardItem* item;
    // 获取表头文字
    QMap<int, QStringList> sheet;
    for(int i = 0; i < theModel->columnCount(); i++) {
        item = theModel->horizontalHeaderItem(i);
        headerlist.append(item->text());
    }
    sheet.insert(0, headerlist);
    // 获取数据区文字
    for (int i = 0; i < theModel->rowCount(); i++ ) {
        QStringList rowlist;
        for (int j = 0; j < theModel->columnCount(); j++) {
            item = theModel->item(i, j);
            rowlist.append(item->text());
        }
        sheet.insert(i + 1, rowlist);
    }
    return sheet;
}

QStringList TableData::getPersonNames()
{
    QStringList nameslist;
    int index = headerlist.indexOf("姓名");
    for(int i = 0; i < theModel->rowCount(); i++) {
        QStandardItem* item = theModel->item(i, index);
        nameslist.append(item->text());
    }
    return nameslist;
}


