#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString srcDir;
    QString dstDir;
    std::vector<QString> mImageType;
    QStringList mNameFilters;
    QString mDstExtension;

    void convertImageFormat(const std::string &src, const std::string &dst);
    void showStatusbarMessage(const QString &text, int timeout = 0);

private Q_SLOTS:
    void slotConvert();
    void slotSetSrcImageType(int i);
    void slotSetDstImageType(int i);
    void slotSetDstImagePath(bool b);
    void slotSetSrcDir(const QString &);
    void slotSetDstDir(const QString &);
    void slotOpenSrcDir();
    void slotOpenDstDir();
    void on_actionAbout_triggered();
};

#endif // MAINWINDOW_H
