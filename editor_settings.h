#ifndef EDITOR_SETTINGS_H
#define EDITOR_SETTINGS_H

#include <QDialog>

namespace Ui {
class editor_settings;
}

class editor_settings : public QDialog
{
    Q_OBJECT

public:
    explicit editor_settings(QWidget *parent = nullptr);
    ~editor_settings();
    Ui::editor_settings* getUi(){
        return ui;
    }

private:
    Ui::editor_settings *ui;
//    void slFontSizeEnter();
//    void slFontSizeChange();
};

#endif // EDITOR_SETTINGS_H
