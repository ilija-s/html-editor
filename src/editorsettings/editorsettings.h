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

    Ui::EditorSettings *getUi() const;
    void fFontSize();

signals:
    void siFontSizeAccepted(int fontSize, bool ind);

public slots:
    void slOKClicked();
    void slFontSizeAccepted();

private:
    Ui::EditorSettings *ui;

};

#endif // EDITORSETTINGS_H
