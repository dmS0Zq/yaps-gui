#include "fulltreewidget.h"
#include "ui_fulltreewidget.h"

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
        rightSingleClick(event);
        break;
    default:
        break;
    }
}

void FullTreeWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (index.row() != -1 && index.column() != -1)
    {
        emit doubleClick(itemAt(event->pos()));
    }
}

void FullTreeWidget::leftSingleClick(QMouseEvent *event)
{
    //QTreeWidgetItem *previousItem = currentSelectedItem;
    changeSelection(event);
    if (currentSelectedItem != nullptr)
        currentSelectedItem->setExpanded(!currentSelectedItem->isExpanded());
}

void FullTreeWidget::rightSingleClick(QMouseEvent *event)
{
    changeSelection(event);
    QModelIndex index = indexAt(event->pos());
    if (index.row() != -1 && index.column() != -1)
    {
        QPoint pos = event->pos();
        emit contextMenuRequested(&pos);
    }
}

void FullTreeWidget::changeSelection(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (index.row() != -1 && index.column() != -1)
    {
        QTreeWidgetItem *item = itemAt(event->pos());
        setCurrentItem(item);
        currentSelectedItem = item;
    }
    else
    {
        clearSelection();
        currentSelectedItem = nullptr;
    }
    emit selectedItemChanged(currentSelectedItem);
}
