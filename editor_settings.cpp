#include "editor_settings.h"
#include "ui_editor_settings.h"

editor_settings::editor_settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editor_settings)
{
    ui->setupUi(this);
}

editor_settings::~editor_settings()
{
    delete ui;
}

//void editor_settings::slFontSizeEnter(){

//}

//void editor_settings::slFontSizeChange(){

//}
