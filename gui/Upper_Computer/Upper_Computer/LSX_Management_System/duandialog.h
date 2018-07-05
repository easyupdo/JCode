#ifndef DUANDIALOG_H
#define DUANDIALOG_H

#include <QDialog>

namespace Ui {
class DuanDialog;
}

class DuanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DuanDialog(QWidget *parent = 0);
    ~DuanDialog();

private:
    Ui::DuanDialog *ui;
};

#endif // DUANDIALOG_H
