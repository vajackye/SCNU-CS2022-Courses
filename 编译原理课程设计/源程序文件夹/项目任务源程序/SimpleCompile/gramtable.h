#pragma once

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>

class GramTable : public QDialog
{
    Q_OBJECT
public:
    // 构造函数：指定标题和表格行列
    explicit GramTable(const QString &title, QWidget *parent = nullptr);

    // 提供设置表格结构的方法
    void setTable(int rowCount, int columnCount, const QStringList &headers);

    // 允许外部直接访问表格填充内容
    QTableWidget *getTableWidget();

private:
    QTableWidget *tableWidget;
};

