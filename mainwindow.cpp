#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionnew_triggered()
{
    //Clear the screen
    currentFile.clear();
    //Create a new text window
    ui->textEdit->setText(QString());

}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the File");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text))

    {
        QMessageBox::warning(this, "Warning", "Can NOT open file: " + file.errorString());
    }

    setWindowTitle(fileName);
    QTextStream in(&file); //make input stream
    QString text = in.readAll();//read everything from buffer
    ui->textEdit->setText(text); //put everything into the text editor
    file.close(); // close file

}

void MainWindow::on_actionSave_triggered()
{

     //open window to save file
     QString fileName = QFileDialog::getSaveFileName(this, "Open the File");
     //create object to hold the file
     QFile file(fileName);

     //Open the file notify user if problem
     if (!file.open(QIODevice::WriteOnly | QFile::Text))

     {
         QMessageBox::warning(this, "Warning", "Can NOT save file: " + file.errorString());
     }
     //Store current file
     currentFile = fileName;
     //Set window title to name of file
     setWindowTitle(fileName);
     //when writing to out we are actually writing to file on line 68 below
     QTextStream out(&file); //make output stream
     //Copy text in textEdit widget to plain text
     QString text = ui->textEdit->toPlainText();

     //write to file
     out << text;
     file.close();


}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();

}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();

}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
