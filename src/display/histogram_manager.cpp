#include "histogram_manager.h"
#include "ui_histogram_manager.h"

#include <QMessageBox>

Histogram_manager::Histogram_manager(int _my_id, int _num_dim, QWidget *parent) :
    DisplayInterface(_my_id, _num_dim, parent),
    ui(new Ui::Histogram_manager)
{
    ui->setupUi(this);
    _histogram = new Display_container_bar(0, this);
    connect(_histogram, &Display_container_bar::settings_updated,
            this, &Histogram_manager::refresh_display);

    ui->verticalLayout_3->addWidget(_histogram);
}

Histogram_manager::~Histogram_manager()
{
    delete ui;
}

void Histogram_manager::on_spinBox_valueChanged(int arg1)
{
    _histogram->setNumBin(arg1);
}

void Histogram_manager::on_doubleSpinBox_valueChanged(double arg1)
{
    _histogram->setCutOff(static_cast<float>(arg1));
}

void Histogram_manager::set_display(void*_in)
{
    //    _histogram->set_display(_in);
}

void Histogram_manager::set_no_controls(bool _f)
{
    ui->groupBox->setHidden(_f);
}

void Histogram_manager::set_display(std::shared_ptr<QVector<double> > _in)
{
    ui->spinBox->setEnabled(true);
    ui->doubleSpinBox->setEnabled(true);
    _histogram->set_display(*_in, _in->size());
}

void Histogram_manager::set_display(const QString &_fileName)
{
    ui->spinBox->setEnabled(false);
    ui->doubleSpinBox->setEnabled(false);
    _input_file = _fileName;
    QFile inFile(_input_file);

    if (!inFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox msgBox;
        msgBox.setText("Error on opening the input file.");
        msgBox.setStandardButtons(QMessageBox::Ok );
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Icon::Critical);
        msgBox.exec();
        return;
    }

    _histogram->set_display(inFile);

    inFile.close();
}

Display_container_bar * Histogram_manager::get_display()
{
    return _histogram;
}

void Histogram_manager::refresh_display()
{
    if (_local_copy_ptr != nullptr)
    {
        _histogram->initialiseHistogram();
        _histogram->set_display(*_local_copy_ptr, _local_copy_ptr->size());
    }
}

void Histogram_manager::setNumBin(const int& _n)
{
    _histogram->setNumBin(_n);
    ui->spinBox->blockSignals(true);
    ui->spinBox->setValue(_n);
    ui->spinBox->blockSignals(false);
}

void Histogram_manager::setCutOff(const float& _n)
{
    _histogram->setCutOff(_n);
    ui->doubleSpinBox->blockSignals(true);
    ui->doubleSpinBox->setValue(_n);
    ui->doubleSpinBox->blockSignals(false);
}