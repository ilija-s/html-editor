#include "editorsettings.h"
#include "ui_editorsettings.h"

EditorSettings::EditorSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditorSettings)
{
    ui->setupUi(this);
}

EditorSettings::~EditorSettings()
{
    delete ui;
}


