#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include "Database.h"
#include "Entry.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void databaseChange();
private slots:
    void updateTreeSub(QTreeWidgetItem *item);

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_treeFull_itemDoubleClicked(QTreeWidgetItem *item);

    void on_actionAddEntry_triggered();

    void updateTreeFull();

    void createContextMenuTreeFull(QPoint *pos);

private:
    void mousePressEvent();

    void displayDatbase(Database *db);
    int displayEntry(Entry *entry, bool forceEditing);
    Ui::MainWindow *ui;
    Entry *highlightedEntry;
};

#endif // MAINWINDOW_H
