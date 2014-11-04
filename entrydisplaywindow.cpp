#include "entrydisplaywindow.h"
#include "ui_entrydisplaywindow.h"

#include "Tree.h"

void EntryDisplayWindow::buildComboParentFromTree(QComboBox *combo, Tree<Entry> *tree, int indentation)
{
    if (tree == nullptr) return;
    if (tree->getRoot() == *entry) return;
    combo->addItem(QString(indentation, QChar::fromLatin1(' ')) + QString::fromStdString(tree->getRoot().getTitle()), QVariant::fromValue(tree->getRoot().getId()));
    indentation += 4;
    for (unsigned int i = 0; i < tree->getBranchCount(); i++)
    {
        buildComboParentFromTree(combo, &tree->getBranch(i), indentation);
    }
    indentation -= 4;
    return;
}

EntryDisplayWindow::EntryDisplayWindow(Entry *ent, Database &database, bool forceEditing, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntryDisplayWindow)
{
    ui->setupUi(this);
    entry = ent;
    tmpPassword = QString::fromStdString(entry->getPassword());
    if (tmpPassword.length() < 1)
        ui->buttonShowHidePassword->setEnabled(false);
    else
        ui->buttonShowHidePassword->setEnabled(true);
    tmpParentId = ent->getParent();
    this->setWindowTitle("Entry: " + QString::fromStdString(entry->getTitle()));
    buildComboParentFromTree(ui->comboParent, &database.getEntries());
    ui->comboParent->setCurrentIndex(ui->comboParent->findData(QVariant::fromValue(tmpParentId)));
    ui->lineEditTitle->setText(QString::fromStdString(entry->getTitle()));
    ui->lineEditUsername->setText(QString::fromStdString(entry->getUsername()));
    ui->lineEditPassword->setText(QString((int)entry->getPassword().length(), QChar::fromLatin1('*')));
    ui->dateTimeEditCreated->setDateTime(QDateTime::fromString(QString::fromStdString(entry->getCreated()), QString("yyyy-MM-dd HH:mm:ss")));
    ui->dateTimeEditModified->setDateTime(QDateTime::fromString(QString::fromStdString(entry->getModified()), QString("yyyy-MM-dd HH:mm:ss")));
    if (forceEditing)
    {
        on_buttonEditing_clicked();
        ui->buttonEditing->setEnabled(false);
    }
    isPasswordShown = forceEditing;
    isEditing = forceEditing;
    if (isPasswordShown) ui->lineEditPassword->setText(QString::fromStdString(entry->getPassword()));
    else ui->lineEditPassword->setText(QString((int)entry->getPassword().length(), QChar::fromLatin1('*')));
}

EntryDisplayWindow::~EntryDisplayWindow()
{
    delete ui;
}

void EntryDisplayWindow::on_buttonShowHidePassword_clicked()
{
    isPasswordShown = !isPasswordShown;
    if (isPasswordShown)
    {
        ui->lineEditPassword->setText(tmpPassword);
        ui->buttonShowHidePassword->setText("Hide Password");
    }
    else
    {
        ui->lineEditPassword->setText(QString(tmpPassword.length(), QChar::fromLatin1('*')));
        ui->buttonShowHidePassword->setText("Show Password");
    }
}

void EntryDisplayWindow::on_buttonEditing_clicked()
{
    isEditing = !isEditing;
    if (isEditing)
    {
        ui->comboParent->setDisabled(false);
        ui->lineEditTitle->setReadOnly(false);
        ui->lineEditUsername->setReadOnly(false);
        ui->lineEditPassword->setReadOnly(false);
        ui->buttonEditing->setText("Disable Editing");
        ui->buttonShowHidePassword->setEnabled(false);
    }
    else
    {
        ui->comboParent->setDisabled(true);
        ui->lineEditTitle->setReadOnly(true);
        ui->lineEditUsername->setReadOnly(true);
        ui->lineEditPassword->setReadOnly(true);
        ui->buttonEditing->setText("Enable Editing");
        if (tmpPassword.length() > 1)
            ui->buttonShowHidePassword->setEnabled(true);
    }
    if (isPasswordShown != isEditing)
        on_buttonShowHidePassword_clicked();
}

void EntryDisplayWindow::on_buttonClose_clicked()
{
    this->done(1); // indicates no changes
}

void EntryDisplayWindow::on_buttonSaveClose_clicked()
{
    entry->setParent(tmpParentId);
    entry->setTitle(ui->lineEditTitle->text().toStdString());
    entry->setUsername(ui->lineEditUsername->text().toStdString());
    entry->setPassword(tmpPassword.toStdString());
    entry->setModified();
    this->done(0); // indiciates change
}

void EntryDisplayWindow::on_lineEditTitle_textEdited(const QString &arg1)
{
    ui->labelTitle->setText("<b><i>Title</i></b>");
    this->setWindowTitle("Entry: " + arg1);
    ui->buttonClose->setText("Discard and Close");
    ui->buttonSaveClose->setEnabled(true);
}

void EntryDisplayWindow::on_lineEditUsername_textEdited(const QString &arg1)
{
    ui->labelUsername->setText("<b><i>Username</i></b>");
    ui->buttonClose->setText("Discard and Close");
    ui->buttonSaveClose->setEnabled(true);
}

void EntryDisplayWindow::on_lineEditPassword_textEdited(const QString &arg1)
{
    tmpPassword = arg1;
    ui->labelPassword->setText("<b><i>Password</i></b>");
    if (tmpPassword.length() < 1)
        ui->buttonShowHidePassword->setEnabled(false);
    else if (!isEditing)
        ui->buttonShowHidePassword->setEnabled(true);
    ui->buttonClose->setText("Discard and Close");
    ui->buttonSaveClose->setEnabled(true);
}

void EntryDisplayWindow::on_comboParent_activated(int index)
{
    if (tmpParentId == ui->comboParent->currentData().toULongLong())
        return;
    tmpParentId = ui->comboParent->currentData().toULongLong();
    ui->labelParent->setText("<b><i>Parent</i></b>");
    ui->buttonClose->setText("Discard and Close");
    ui->buttonSaveClose->setEnabled(true);
}
