#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entrydisplaywindow.h"
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardItem>

#include <iostream>

Database database;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeFull->setColumnHidden(1, true);
    connect(this, SIGNAL(databaseChange()), this, SLOT(updateTreeFull()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QTreeWidgetItem* recursiveBuildFullTree(Tree<Entry> &tree)
{
    Entry root = tree.getRoot();
    QStringList dataPoints;
    dataPoints.append(QString::fromStdString(root.getTitle()));
    dataPoints.append(QString::number(root.getId()));
    QTreeWidgetItem *newItem = new QTreeWidgetItem((QTreeWidget*)0, dataPoints);
    newItem->setExpanded(false);
    for (unsigned int i = 0; i < tree.getBranchCount(); i++)
    {
        newItem->addChild(recursiveBuildFullTree(tree.getBranch(i)));
    }

    return newItem;
}

void MainWindow::updateTreeFull()
{
    ui->treeFull->setHeaderLabel(QString::fromStdString(database.getName()));
    ui->treeFull->setHeaderHidden(false);

    QList<QTreeWidgetItem *> items;
    for (unsigned int i = 0; i < database.getEntries().getBranchCount(); i++)
    {
        items.append(recursiveBuildFullTree(database.getEntries().getBranch(i)));
    }
    while (ui->treeFull->takeTopLevelItem(0) != 0);
    ui->treeFull->insertTopLevelItems(0, items);
}

void MainWindow::updateTreeSub(QTreeWidgetItem *item)
{
    if (current == nullptr)
    {

    }
    else
    {
        uint64_t id = current->data(1, Qt::DisplayRole).toULongLong();
        auto byId = [&id](Tree<Entry>* tree) -> Tree<Entry>* {return (id == tree->getRoot().getId() ? tree : nullptr);};
        Tree<Entry> *selectedTree = database.getEntries().findUsing(byId);
        if (selectedTree != nullptr)
        {
            this->highlightedEntry = selectedTree->getRoot();
            QList<QTreeWidgetItem *> subItems;
            QStringList dataPoints;
            if (selectedTree->getBranchCount() == 0)
            {
                Entry &entry = selectedTree->getRoot();
                dataPoints = QStringList();
                dataPoints.push_back(QString::fromStdString(entry.getTitle()));
                dataPoints.push_back(QString::fromStdString(entry.getUsername()));
                dataPoints.push_back(QString::fromStdString(entry.getUrl()));
                subItems.append(new QTreeWidgetItem((QTreeWidget*)0, dataPoints));
            }
            else
            {
                for (unsigned int i = 0; i < selectedTree->getBranchCount(); i++)
                {
                    if (selectedTree->getBranch(i).getBranchCount() > 0)
                        continue;
                    Entry &entry = selectedTree->getBranch(i).getRoot();
                    dataPoints = QStringList();
                    dataPoints.push_back(QString::fromStdString(entry.getTitle()));
                    dataPoints.push_back(QString::fromStdString(entry.getUsername()));
                    dataPoints.push_back(QString::fromStdString(entry.getUrl()));
                    subItems.append(new QTreeWidgetItem((QTreeWidget*)0, dataPoints));
                }
            }
            while (ui->treeSub->takeTopLevelItem(0) != 0);
            ui->treeSub->insertTopLevelItems(0, subItems);
        }
    }
}

void MainWindow::on_actionNew_triggered()
{
    database = Database();
    std::string parentTitle = "Password Safe";
    database.setName(parentTitle);
    Entry e = Entry();
    auto byTitle = [&parentTitle](Tree<Entry>* tree) -> Tree<Entry>* {return (parentTitle == tree->getRoot().getTitle() ? tree : nullptr);};
    e.setTitle("Shopping");
    database.addEntry(e, database.getEntries().findUsing(byTitle)->getRoot().getId());
    parentTitle = "Shopping";
    e = Entry();
    e.setTitle("Etsy");
    e.setUsername("ladyfucker");
    database.addEntry(e, database.getEntries().findUsing(byTitle)->getRoot().getId());
    e = Entry();
    e.setTitle("Amazon");
    database.addEntry(e, database.getEntries().findUsing(byTitle)->getRoot().getId());
    e = Entry();
    e.setTitle("Newegg");
    database.addEntry(e, database.getEntries().findUsing(byTitle)->getRoot().getId());
    parentTitle = "Amazon";
    e = Entry();
    e.setTitle("Mom's Account");
    e.setUsername("nicegal@cox.net");
    database.addEntry(e, database.getEntries().findUsing(byTitle)->getRoot().getId());
    e = Entry();
    e.setTitle("My Account");
    e.setUsername("fatjoe@hotmail.com");
    database.addEntry(e, database.getEntries().findUsing(byTitle)->getRoot().getId());
    parentTitle = "Newegg";
    e = Entry();
    e.setTitle("Mine");
    database.addEntry(e, database.getEntries().findUsing(byTitle)->getRoot().getId());
    parentTitle = "Password Safe";
    e = Entry();
    e.setTitle("Email");
    database.addEntry(e, database.getEntries().findUsing(byTitle)->getRoot().getId());
    e = Entry();
    e.setTitle("Windows");
    e.setUsername("matt");
    e.setPassword("pASSw0rd");
    e.setUrl("http://example.com");
    database.addEntry(e, database.getEntries().findUsing(byTitle)->getRoot().getId());

    emit databaseChange();
}

void MainWindow::on_actionOpen_triggered()
{
    database = Database();
    database.readFromFile("pwsafe.yaps");
    emit databaseChange();
}

void MainWindow::on_actionSave_triggered()
{
    database.saveToFile("pwsafe.yaps");
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit(0);
}


void MainWindow::on_treeFull_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    uint64_t id = item->data(1, Qt::DisplayRole).toULongLong();
    auto byId = [&id](Tree<Entry>* tree) -> Tree<Entry>* {return (id == tree->getRoot().getId() ? tree : nullptr);};
    Entry entry = database.getEntries().findUsing(byId)->getRoot();

    database.removeEntry(entry.getId());
    emit databaseChange();

    return;


    /*uint64_t id = item->data(1, Qt::DisplayRole).toULongLong();
    auto byId = [&id](Tree<Entry>* tree) -> Tree<Entry>* {return (id == tree->getRoot().getId() ? tree : nullptr);};
    Entry *entry = &database.getEntries().findUsing(byId)->getRoot();
    EntryDisplayWindow *edw = new EntryDisplayWindow(entry, database, false, this);
    if (edw->exec() == 0)
    {
        emit databaseChange();
    }*/
}

void MainWindow::on_actionAddEntry_triggered()
{
    Entry newEntry = Entry();
    EntryDisplayWindow *edw = new EntryDisplayWindow(&newEntry, database, true, this);
    //connect(edw, SIGNAL(destroyed()), this, SLOT(updateTreeFull()));
    if (edw->exec() == 0)
    {
        database.addEntry(newEntry, newEntry.getParent());
        emit databaseChange();
    }

}
