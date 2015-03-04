#ifndef PARAMETERSDIALOG_H
#define PARAMETERSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class ParametersDialog;
}

class ParametersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParametersDialog(QWidget *parent = 0);
    ~ParametersDialog();

    void showWithRefresh();

private slots:
    void on_ffmpegButton_clicked();

    void on_ffmprobeButton_clicked();

    void on_mkvtoolniksButton_clicked();

    void on_buttonBox_accepted();

    void on_magentLinkButton_clicked();

    void on_mkTorrentButton_clicked();


private:
    Ui::ParametersDialog *ui;
    QString getExecutablePath();

    /**
     * @brief The associated settings.
     */
    QSettings                   *m_settings;

};

#endif // PARAMETERSDIALOG_H
