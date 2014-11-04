#ifndef ENTRYDISPLAYWINDOW_H
#define ENTRYDISPLAYWINDOW_H

#include <QDialog>
#include <QComboBox>
#include "Database.h"
#include "Entry.h"

namespace Ui {
class EntryDisplayWindow;
}

class EntryDisplayWindow : public QDialog
{
    Q_OBJECT

public:
    //explicit EntryDisplayWindow(Entry *ent, QWidget *parent = 0);
    explicit EntryDisplayWindow(Entry *ent, Database &database, bool forceEditing, QWidget *parent = 0);
    ~EntryDisplayWindow();

private slots:
    void on_buttonShowHidePassword_clicked();

    void on_buttonEditing_clicked();

    void on_buttonClose_clicked();

    void on_buttonSaveClose_clicked();

    void on_lineEditTitle_textEdited(const QString &arg1);

    void on_lineEditUsername_textEdited(const QString &arg1);

    void on_lineEditPassword_textEdited(const QString &arg1);

    void on_comboParent_activated(int index);

private:
    Ui::EntryDisplayWindow *ui;
    bool isPasswordShown;
    bool isEditing;
    QString tmpPassword;
    uint64_t tmpParentId;
    Entry *entry;

    void buildComboParentFromTree(QComboBox *combo, Tree<Entry> *tree, int indentation = 0);
};

#endif // ENTRYDISPLAYWINDOW_H
