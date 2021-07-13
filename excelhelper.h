#ifndef EXCELHELPER_H
#define EXCELHELPER_H

#include <QDir>
#include <QFileDialog>
#include <QList>
#include <QMap>
#include <QObject>
#include <QStandardItemModel>
#include <QVariant>
#include <QWidget>

#include "xlsxdocument.h"
#include "xlsxcellrange.h"
#include "xlsxworkbook.h"
#include "xlsxworksheet.h"

class ExcelHelper : public QObject
{
    Q_OBJECT

public:
    ExcelHelper(QWidget* parent);
    QList<QMap<int, QStringList>> openExcel();
    void readAllSheetsData();
    void saveExcel(QList<QMap<int, QStringList>> listtoexcel);
    void oneMergeSaveExcel(QList<QStringList> sheets_tableheader,
                           QList<QList<QMap<int, QStringList>>> sheets_names_split);

private:
    QString open_filename;
    void wirte_cell_data();
    void add_sheet();
    void select_sheet();
    void cell_colors();
    void get_all_sheel();
    void merge_write_excel(QStringList tableheader, QString filename, QMap<int, QStringList> names);
    QString get_open_filename();
    QString get_save_filename();
    void write_excel(QString filename, QList<QMap<int, QStringList>>sheets);
    QList<QMap<int, QStringList>> read_excel(QString filename);

};

#endif // EXCELHELPER_H
