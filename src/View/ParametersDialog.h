#ifndef PARAMETERSDIALOG_H
#define PARAMETERSDIALOG_H

#include <QDialog>

namespace Ui {
class ParametersDialog;
}

class ParametersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParametersDialog(QWidget *parent = 0);
    ~ParametersDialog();

private slots:
    void on_ffmpegButton_clicked();

    void on_ffmprobeButton_clicked();

    void on_mkvtoolniksButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::ParametersDialog *ui;
    QString getExecutablePath();
};

#endif // PARAMETERSDIALOG_H
