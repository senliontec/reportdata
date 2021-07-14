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
        item = new QStandardItem(headerlist[i]);
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

QList<QMap<int, QStringList>> TableData::getMergeData()
{
    QStringList names_str = get_person_names();
    QStringList new_names_str = remove_same_name(names_str);
    QList<QMap<int, QStringList>> sheet_names_split = set_name_split(names_str, new_names_str);
    return sheet_names_split;
}

QList<QMap<int, QStringList>> TableData::set_name_split(QStringList names_str, QStringList new_names_str)
{
    QStandardItem* item;
    QList<QMap<int, QStringList>> sheet_names_split;
    for (int i = 0; i < new_names_str.size(); i++) {
        QMap<int, QStringList> rows_map;
        for (int j = 0; j < names_str.size(); j++) {
            if (new_names_str.at(i) == names_str.at(j)) {
                QStringList row_list;
                for (int c = 0; c < theModel->columnCount(); c++) {
                    item = theModel->item(j, c);
                    row_list.append(item->text());
                }
                rows_map.insert(j, row_list);
            }
        }
        sheet_names_split.append(rows_map);
    }
    return sheet_names_split;
}

QStringList TableData::get_person_names()
{
    QStringList names_str;
    for(int i = 0; i < theModel->rowCount(); i++) {
        QStandardItem* item = theModel->item(i, 1); // TODO 使用索引
        if (!item->text().isEmpty()) {
            names_str.append(item->text());
        }
    }
    return names_str;
}

QStringList TableData::remove_same_name(QStringList names_str)
{
    names_str.removeDuplicates();
    return names_str;
}

QStringList TableData::getTableHeader()
{
    return headerlist;
}


