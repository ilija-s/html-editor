#ifndef EDITORSETTINGS_H
#define EDITORSETTINGS_H

#include <QDialog>
#include <QObject>

namespace Ui {
class EditorSettings;
}

class EditorSettings : public QDialog
{
    Q_OBJECT

public:
    explicit EditorSettings(QWidget *parent = nullptr);
    ~EditorSettings();

signals:
    void siFontSizeAccepted(int fontSize, bool ind);

private slots:
    void slOKClicked();
    void slFontSizeAccepted();

private:
    Ui::EditorSettings *ui;
    void fFontSize();
    void fTheme();
};

#endif // EDITORSETTINGS_H
