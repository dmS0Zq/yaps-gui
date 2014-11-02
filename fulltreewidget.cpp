#include "fulltreewidget.h"
#include "ui_fulltreewidget.h"

#include <iostream>

FullTreeWidget::FullTreeWidget(QWidget *parent) :
    QTreeWidget(parent),
    ui(new Ui::FullTreeWidget)
{
    ui->setupUi(this);
}

FullTreeWidget::~FullTreeWidget()
{
    delete ui;
}

void FullTreeWidget::mousePressEvent(QMouseEvent *event)
{
    switch (event->button())
    {
    case Qt::LeftButton:
        leftSingleClick(event);
        break;
    case Qt::RightButton:
        break;
    default:
        break;
    }
}

void FullTreeWidget::leftSingleClick(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (index.row() != -1 && index.column() != -1)
    {
        QTreeWidgetItem *item = itemAt(event->pos());
        std::cout << item->data(1, Qt::DisplayRole).toULongLong() << std::endl;
        setCurrentItem(item);
        item->setExpanded(!item->isExpanded());
        currentSelectedItem = item;
    }
    else
    {
        clearSelection();
        currentSelectedItem = nullptr;
    }
    emit selectedItemChanged(currentSelectedItem);
}
