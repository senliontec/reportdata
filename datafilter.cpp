#include "datafilter.h"
#include "ui_datafilter.h"

DataFilter::DataFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataFilter)
{
    ui->setupUi(this);
}

DataFilter::~DataFilter()
{
    delete ui;
}
