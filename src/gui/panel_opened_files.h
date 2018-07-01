#ifndef PANEL_OPENED_FILES_H
#define PANEL_OPENED_FILES_H

#include <QWidget>
#include <QListWidgetItem>

#include "src/display/display_container.h"

namespace Ui {
class Panel_opened_files;
}

//!
//! \brief The Panel_opened_files class
//! This QWidget holds the panel of the QListWidget with the
//! names of the files openned in the QMdi.
class Panel_opened_files : public QWidget
{
    Q_OBJECT

public:
    explicit Panel_opened_files(QWidget *parent = 0);
    ~Panel_opened_files();

    //! Get the row of the Display_container that has _id
    qint16 findQListWidgetItem(QListWidget* this_list,
                               const QString& _id);

public slots:
    //! Append a window on the  ui->listOpenedFiles
    void appendToOpenedList(Display_container* child);

    //! Remove item from the ui->listOpenedFiles list.
    void removeFromOpenedList(Display_container* child);

private:
    Ui::Panel_opened_files *ui;
};

#endif // PANEL_OPENED_FILES_H
