#ifndef HUMANINFO_H
#define HUMANINFO_H

#include <QDialog>

namespace Ui {
class HumanInfo;
}

class HumanInfo : public QDialog
{
    Q_OBJECT


public:
    explicit HumanInfo(QWidget *parent = nullptr);
    ~HumanInfo();
    void setText(QString* array);
    QString text() const;





private:
    Ui::HumanInfo *ui;
};





#endif // HUMANINFO_H
