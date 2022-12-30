#include "editorsettings.h"
#include "ui_editorsettings.h"

EditorSettings::EditorSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditorSettings)
{
    ui->setupUi(this);
    ui->wFontSize->setVisible(false);
    connect(ui->pbOK, &QAbstractButton::clicked, this, &EditorSettings::slOKClicked);
    connect(ui->pbOKFontSize, &QAbstractButton::clicked, this, &EditorSettings::slFontSizeAccepted);
}

EditorSettings::~EditorSettings()
{
    delete ui;
}

void EditorSettings::slOKClicked(){

    if(ui->rbFontSize->isChecked()){
        fFontSize();
    }

    //emit siDialogChecked(parameter, ind);
    //close();
}

void EditorSettings::fFontSize(){
    ui->wInitial->setVisible(false);
    ui->wFontSize->setVisible(true);
    ui->cbSize->setEditable(true);
    ui->lNotValid->setVisible(false);
}

void EditorSettings::slFontSizeAccepted(){
    bool ind = true;
    //bool index = ui->cbSize->currentIndex();
    int fontSize = ui->cbSize->currentText().toInt(&ind);
    //int fontSize = ui->leTest->text().toInt(&ind);

    if(!ind || fontSize < 5){
        ui->lNotValid->setVisible(true);
        ind = fontSize > 5 ? ind : false;
        ui->cbSize->setCurrentIndex(0);
        return;
    }

    emit siFontSizeAccepted(fontSize, ind);
    close();
}

