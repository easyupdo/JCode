#ifndef DUANALTERDIALOG_H
#define DUANALTERDIALOG_H

#include <QDialog>

namespace Ui {
class DuanAlterDialog;
}

class DuanAlterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DuanAlterDialog(QWidget *parent = 0);
    ~DuanAlterDialog();

private:
    Ui::DuanAlterDialog *ui;
};

#endif // DUANALTERDIALOG_H
