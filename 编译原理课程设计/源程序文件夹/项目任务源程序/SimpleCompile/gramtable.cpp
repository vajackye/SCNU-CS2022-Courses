/***************************************************************
 * 版权所有 (C) 20222121007 计算机科学与技术师范 黄泽基
 * 保留所有权利
 *
 * 模块名称：gramtable.cpp
 * 模块功能：本模块用于实现语法分析的DFA图表的展示
 *
 * 当前版本：v1.0
 * 作    者：黄泽基
 * 完成日期：2025年5月6日
 *
 * 修改历史：
 * 版本号     修改者     修改日期     修改内容
 * v1.0       黄泽基       2025/05/06   初始版本，完成模块功能实现
 *
 ***************************************************************/
#include "gramtable.h"

GramTable::GramTable(const QString &title, QWidget *parent)
    : QDialog(parent)
{
    this->setWindowTitle(title);
    this->resize(800, 600);

    tableWidget = new QTableWidget(this);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setVisible(false);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tableWidget);
    this->setLayout(layout);
}

void GramTable::setTable(int rowCount, int columnCount, const QStringList &headers)
{
    tableWidget->setRowCount(rowCount);
    tableWidget->setColumnCount(columnCount);
    tableWidget->setHorizontalHeaderLabels(headers);

    tableWidget->setWordWrap(false);                              // 禁止自动换行，避免被省略
    tableWidget->horizontalHeader()->setStretchLastSection(false); // 不自动拉伸最后一列
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // 自动适应内容宽度
    tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents); // 表格自适应调整
    tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel); // 平滑横向滚动
    tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   // 平滑纵向滚动
    tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded); // 横向滚动条按需出现
    tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);   // 纵向滚动条按需出现

}

QTableWidget *GramTable::getTableWidget()
{
    return tableWidget;
}
