#ifndef SAVVY_INTERFACE_H
#define SAVVY_INTERFACE_H

#define ExternalInterface_iid "org.Savvy.ExternalInterface"

#include <QtPlugin>
#include <QDialog>
#include <memory>

#include "src/gui/workspace.h"

class ExternalInterface : public QDialog
{
public:
    explicit ExternalInterface(QWidget *parent = nullptr) :
        QDialog(parent)
    {

    }

    ~ExternalInterface() override = default;

    virtual void link_workspace(std::shared_ptr<Workspace> ) = 0;

    //! \obsolete
    //! Never used
    //inline virtual void return_to_workspace(std::shared_ptr<Workspace> ) = 0;

    //! Never used
    //inline virtual void show_workspace_operations(bool state) = 0;

    QString & get_name()
    {
        return m_name;
    }

private:
    QString m_name;
};

Q_DECLARE_INTERFACE(ExternalInterface,ExternalInterface_iid)

#endif //SAVVY_INTERFACE_H
