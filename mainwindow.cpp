#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QFileDialog>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->leSrcDir->setText(srcDir);
    ui->leDstDir->setText(dstDir);

    mImageType.push_back("png");
    mImageType.push_back("jpg");
    mImageType.push_back("jpeg");
    mImageType.push_back("bmp");

    for (int i = 0; i < (int)mImageType.size(); i++) {
        ui->cb1->addItem(mImageType[i]);
        ui->cb2->addItem(mImageType[i]);
    }

    slotSetSrcImageType(0);
    slotSetDstImageType(0);

    QObject::connect(ui->pbSrcDir, SIGNAL(clicked()), this, SLOT(slotOpenSrcDir()));
    QObject::connect(ui->pbDstDir, SIGNAL(clicked()), this, SLOT(slotOpenDstDir()));
    QObject::connect(ui->cb1, SIGNAL(activated(int)), this, SLOT(slotSetSrcImageType(int)));
    QObject::connect(ui->cb2, SIGNAL(activated(int)), this, SLOT(slotSetDstImageType(int)));
    QObject::connect(ui->cb3, SIGNAL(toggled(bool)), this, SLOT(slotSetDstImagePath(bool)));
    QObject::connect(ui->pbConvert, SIGNAL(clicked()), this, SLOT(slotConvert()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::convertImageFormat(const std::string &src, const std::string &dst)
{
    Mat image;

    image = imread(src);
    if (image.empty()) {
        printf("Error: can't not read image %s\n", src.c_str());
        return;
    }

    showStatusbarMessage(QString(dst.c_str()), 2000);
    imwrite(dst, image);
}

void MainWindow::slotConvert()
{
    if (srcDir.isEmpty() || dstDir.isEmpty()) {
        showStatusbarMessage("Error: dir is empty.", 2000);
        return;
    }

    QDir dir(srcDir);
    //dir.setNameFilters( QStringList() << "*.png" );
    //dir.setNameFilters( QStringList() << "*.exe" << "*.pdf" << "*.docx" << "*.jpg" );
    dir.setNameFilters( mNameFilters );
    QStringList fileList = dir.entryList();

    //qDebug() << fileList[0];

    for (int i = 0; i < fileList.size(); i++) {
        QString srcFilename = srcDir + "/" + fileList[i];
        QFileInfo fileInfo(srcFilename);
        QString dstFilename = dstDir + "/" + fileInfo.baseName() + "." + mDstExtension;
        //qDebug() << srcFilename;
        //qDebug() << dstFilename;
        convertImageFormat(srcFilename.toStdString(), dstFilename.toStdString());
    }

    showStatusbarMessage("covert done.", 2000);
}

void MainWindow::slotSetSrcImageType(int i)
{
    mNameFilters.clear();
    mNameFilters << "*." + mImageType[i];
}

void MainWindow::slotSetDstImageType(int i)
{
    mDstExtension = mImageType[i];
}

void MainWindow::slotSetDstImagePath(bool b)
{
    if (b)
        ui->leDstDir->setText(ui->leSrcDir->text());
}

void MainWindow::slotOpenSrcDir()
{
    QString dir;
    if (srcDir.isEmpty()) {
        dir = QFileDialog::getExistingDirectory(this, "Open Directory",
                                                "/home",
                                                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    } else {
        dir = QFileDialog::getExistingDirectory(this, "Open Directory",
                                                srcDir,
                                                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    }

    srcDir = dir;
    ui->leSrcDir->setText(srcDir);
}

void MainWindow::slotOpenDstDir()
{
    QString dir;
    if (dstDir.isEmpty()) {
        dir = QFileDialog::getExistingDirectory(this, "Open Directory",
                                                "/home",
                                                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    } else {
        dir = QFileDialog::getExistingDirectory(this, "Open Directory",
                                                dstDir,
                                                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    }

    dstDir = dir;
    ui->leDstDir->setText(dstDir);
}

void MainWindow::showStatusbarMessage(const QString &text, int timeout)
{
    ui->statusBar->showMessage(text, timeout);
}
