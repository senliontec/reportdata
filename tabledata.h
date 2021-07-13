#ifndef TABLEDATA_H
#define TABLEDATA_H

#include <QObject>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTableView>


class TableData: public QTableView
{
    Q_OBJECT
public:
    explicit TableData(QObject* parent = 0);
    void setTableModel(QMap<int, QStringList> exceltomap);
    QStringList getPersonNames();
    QMap<int, QStringList> getTableModel();
    void getMergeData(QList<QStringList>names);
private:
    QStringList headerlist;
    QStandardItem *item;
    QStandardItemModel *theModel;

    void remove_same_name();

};

#endif // TABLEDATA_H
