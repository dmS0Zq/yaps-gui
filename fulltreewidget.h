#ifndef FULLTREEWIDGET_H
#define FULLTREEWIDGET_H

#include <QTreeWidget>
#include <QMouseEvent>

namespace Ui {
class FullTreeWidget;
}

class FullTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    explicit FullTreeWidget(QWidget *parent = 0);
    ~FullTreeWidget();
signals:
    void selectedItemChanged(QTreeWidgetItem *item);
    void contextMenuRequested(QPoint *pos);
private:
    void mousePressEvent(QMouseEvent *event);
    void leftSingleClick(QMouseEvent *event);
    void rightSingleClick(QMouseEvent *event);
    void changeSelection(QMouseEvent *event);
    Ui::FullTreeWidget *ui;
    QTreeWidgetItem *currentSelectedItem;
};

#endif // FULLTREEWIDGET_H
