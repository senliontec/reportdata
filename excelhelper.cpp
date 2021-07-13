#include "excelhelper.h"
#include <QDebug>
#include <exception>
ExcelHelper::ExcelHelper(QWidget* parent)
{
    QWidget* parentwidget = parent;
}

QList<QMap<int, QStringList>> ExcelHelper::openExcel()
{
    open_filename = this->get_open_filename();
    QList<QMap<int, QStringList>> exceltolist = this->read_excel(open_filename);
    return exceltolist;
}

void ExcelHelper::saveExcel(QList<QMap<int, QStringList>> sheets)
{
    QString filename = this->get_save_filename();
    write_excel(filename, sheets);
}

void ExcelHelper::oneMergeSaveExcel(QList<QStringList>sheets_tableheader,
                                    QList<QList<QMap<int, QStringList>>> sheets_names_split)
{
    QDir dir;
    QString curpath = dir.currentPath();
    dir.cd(curpath);
    if (!dir.exists("test")) {
        dir.mkdir("test");
    }
    QString filename = curpath + "/" + "test/";
    sheets_names_split.removeAt(1); // TODO
    for (int sheet = 0; sheet < sheets_names_split.size(); sheet++) {
        QList<QMap<int, QStringList>> sheet_names_split = sheets_names_split[sheet];
        QStringList tableheader = sheets_tableheader[sheet];
        for (int i = 0; i < sheet_names_split.size(); i++) {
            QMap<int, QStringList> names = sheet_names_split[i];
            QString savefile = filename + names.constBegin().value().at(1) + ".xlsx";
            merge_write_excel(tableheader, savefile, names);
        }
    }
}


void ExcelHelper::merge_write_excel(QStringList tableheader, QString filename, QMap<int, QStringList> names)
{
    QXlsx::Document xlsxW;
    QMap<int, QStringList>::iterator iter = names.begin();
    // 写入表头
    qDebug() << "tablehedader" << tableheader;
    for(int i = 0; i < tableheader.size(); i++) {
        xlsxW.write(1, i + 1, tableheader[i]);
    }
    // 写入数据区
    int rownum = 0;
    while (iter != names.end()) {
        QStringList rowlist = iter.value();
        ++rownum;
        for (int j = 0; j < rowlist.size(); j++) {
            QString value = rowlist[j];
            xlsxW.write(rownum + 1, j + 1, value);
        }
        iter++;
    }
    xlsxW.saveAs(filename);
}

void ExcelHelper::write_excel(QString filename, QList<QMap<int, QStringList>> sheets)
{
    QXlsx::Document xlsxW;
    for (int s = 0; s < sheets.size(); s++) {
        QMap<int, QStringList> table = sheets[s];
        QString num = QString::asprintf("Sheet %d", s + 1);
        xlsxW.addSheet(num);
        for (int i = 0; i < table.size() ; i++) {
            QStringList rowlist = table[i];
            for (int j = 0; j < rowlist.size(); j++) {
                QString value = rowlist[j];
                xlsxW.write(i + 1, j + 1, value);
            }
        }
    }
    xlsxW.saveAs(filename);
}

QList<QMap<int, QStringList>> ExcelHelper::read_excel(QString filename)
{
    QString value;
    QList<QMap<int, QStringList>> exceltolist;
    QXlsx::Document xlsxR(filename.toUtf8());
    QXlsx::Workbook *workBook = xlsxR.workbook();
    int sheetcount = workBook->sheetCount();
    for (int i = 0; i < sheetcount; i++) {
        QMap<int, QStringList> exceltomap;
        QString sheetname = workBook->sheet(i)->sheetName();
        QXlsx::Worksheet *workSheet = static_cast<QXlsx::Worksheet*>(workBook->sheet(i));
        for (int i = 1; i <= workSheet->dimension().rowCount(); i++) {
            QStringList rowlist;
            for (int j = 1; j <= workSheet->dimension().columnCount(); j++) {
                QXlsx::Cell *cell = workSheet->cellAt(i, j);
                if (cell == NULL) {
                    value = "";
                } else {
                    value = cell->value().toString();
                }
                rowlist.append(value);
            }
            exceltomap.insert(i - 1, rowlist);
        }
        exceltolist.append(exceltomap);
    }
    return exceltolist;
}

QString ExcelHelper::get_open_filename()
{
    QString curpath = QDir::currentPath();
    QString dlgtitle = tr("请选择Excel文件");
    QString filter = tr("xlsx文件(*.xlsx);;xls文件(*.xls);;所有文件(*.*)");
    QString filename = QFileDialog::getOpenFileName(nullptr, dlgtitle, curpath, filter);
    return filename;
}

QString ExcelHelper::get_save_filename()
{
    // 获取保存文件路径
    QString filename = QFileDialog::getSaveFileName(nullptr, "保存文件", ""
                       , "xlsx(*.xlsx)");
    return filename;
}
