#ifndef TABLEDATA_H
#define TABLEDATA_H

#include <QObject>
#include <QRegExp>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTableView>


class TableData: public QTableView
{
    Q_OBJECT
public:
    explicit TableData(QObject* parent = 0);
    void setTableModel(QMap<int, QStringList> exceltomap);
    QList<QMap<int, QStringList>> getMergeData();
    QStringList get_person_names();
    QMap<int, QStringList> getTableModel();
    QStringList remove_same_name(QStringList names_str);
    QList<QMap<int, QStringList>> set_name_split(QStringList names_str, QStringList new_names_str);
    QStringList getTableHeader();
private:
    QStringList headerlist;
    QStandardItem *item;
    QStandardItemModel *theModel;

    void remove_same_name();

};

#endif // TABLEDATA_H
