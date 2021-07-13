#ifndef DATAFILTER_H
#define DATAFILTER_H

#include <QDialog>

namespace Ui {
class DataFilter;
}

class DataFilter : public QDialog
{
    Q_OBJECT

public:
    explicit DataFilter(QWidget *parent = nullptr);
    ~DataFilter();

private:
    Ui::DataFilter *ui;
};

#endif // DATAFILTER_H
