#ifndef DECRYPTER_H
#define DECRYPTER_H
#include <QDialog>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <iterator>

QT_BEGIN_NAMESPACE
#include <QGroupBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QRadioButton>
#include <QButtonGroup>
QT_END_NAMESPACE

//! [0]
class Decrypter : public QDialog
{
    Q_OBJECT

public:
    Decrypter();

private slots:
    void on_keystreamButton_clicked();
    void on_saveButton_clicked();
    void on_decryptButton_clicked();
    void on_quitButton_clicked();
    QString openBin();

private:
    QLineEdit *keystreamPathDisplay;
    QLineEdit *savePathDisplay;
    QPushButton *decryptButton;
    QRadioButton *xysave;
    QRadioButton *orassave;
    std::string keystreamfilename;
    std::string savefilename;

};
//! [0]

#endif
