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
    void changeStyle();

signals:
    void siFontSizeAccepted(int fontSize, bool ind);
    void siThemeAccepted(int ind);

private slots:
    void slOKClicked();
    void slFontSizeAccepted();
    void slOKClickedTheme();

private:
    Ui::EditorSettings *ui;
    void fFontSize();
    void fTheme();
};

#endif // EDITORSETTINGS_H
