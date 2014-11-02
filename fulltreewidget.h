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
private:
    void mousePressEvent(QMouseEvent *event);
    void leftSingleClick(QMouseEvent *event);
    Ui::FullTreeWidget *ui;
    QTreeWidgetItem *currentSelectedItem;
};

#endif // FULLTREEWIDGET_H
