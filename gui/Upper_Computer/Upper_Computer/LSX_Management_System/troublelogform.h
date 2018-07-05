#ifndef TROUBLELOGFORM_H
#define TROUBLELOGFORM_H

#include <QWidget>

namespace Ui {
class troubleLogForm;
}

class troubleLogForm : public QWidget
{
    Q_OBJECT

public:
    explicit troubleLogForm(QWidget *parent = 0);
    ~troubleLogForm();

private:
    Ui::troubleLogForm *ui;
};

#endif // TROUBLELOGFORM_H
