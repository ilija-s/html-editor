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

private:
    Ui::EditorSettings *ui;
};

#endif // EDITORSETTINGS_H
