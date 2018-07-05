#ifndef DESCDIALOG_H
#define DESCDIALOG_H

#include <QDialog>

namespace Ui {
class DescDialog;
}

class DescDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DescDialog(QWidget *parent = 0);
    ~DescDialog();

private:
    Ui::DescDialog *ui;
};

#endif // DESCDIALOG_H
