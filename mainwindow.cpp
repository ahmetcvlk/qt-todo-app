#include "mainwindow.h"
#include <QFile.h>
#include <QMessageBox>
#include <QStandardPaths>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("To Do App");

    QFile file(path);

    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QListWidgetItem *item = new QListWidgetItem(in.readLine(), ui->listWidget);
        ui->listWidget->addItem(item);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }

    file.close();

    int rowCount = ui->listWidget->count(); // ListWidget'taki satır sayısını al
    ui->label->setText(QString::number(rowCount) + " Item");
}

MainWindow::~MainWindow()
{
    delete ui;

    QFile file(path);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream out(&file);

    for (int i = 0; i < ui->listWidget->count(); ++i) {
        out << ui->listWidget->item(i)->text() << "\n";
    }

    file.close();
}

void MainWindow::on_btnAdd_clicked()
{
    if (ui->txtTask->text().isEmpty()) {
        QMessageBox::warning(nullptr, "Error", "Input field can't be empty!");
        ui->txtTask->setFocus();
    } else {
        QListWidgetItem *item = new QListWidgetItem(ui->txtTask->text(), ui->listWidget);
        ui->listWidget->addItem(item);
        item->setFlags(item->flags()
                       | Qt::ItemIsEditable); //after add item , item is editable with double click
        ui->txtTask->clear();
        ui->txtTask->setFocus();
    }

    int rowCount = ui->listWidget->count(); // ListWidget'taki satır sayısını al
    ui->label->setText(QString::number(rowCount) + " Item");
}

void MainWindow::on_btnRemove_clicked()
{
    // QListWidgetItem *item = ui->listWidget->takeItem(ui->listWidget->currentRow());
    // ui->listWidget->removeItemWidget(item);
    // delete item;

    // Seçilen öğelerin listesini al
    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();

    // Seçilen öğeleri sil
    for (QListWidgetItem *item : selectedItems) {
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }

    int rowCount = ui->listWidget->count(); // ListWidget'taki satır sayısını al
    ui->label->setText(QString::number(rowCount) + " Item");
}

void MainWindow::on_btnRemoveAll_clicked()
{
    // QListWidget *lw = new QListWidget(ui->listWidget)
    ui->listWidget->clear();
    ui->txtTask->setFocus();

    ui->label->setText(QString::number(0) + " Item");
}
