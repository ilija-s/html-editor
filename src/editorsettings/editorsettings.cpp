#include "editorsettings.h"
#include "ui_editorsettings.h"

EditorSettings::EditorSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditorSettings)
{
    ui->setupUi(this);
    ui->wFontSize->setVisible(false);
    ui->wTheme->setVisible(false);
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
    } else if (ui->rbTheme->isChecked()){
        fTheme();
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
        return;
    }

    emit siFontSizeAccepted(fontSize, ind);
    close();
}

void EditorSettings::fTheme(){
    ui->wInitial->setVisible(false);
    ui->wTheme->setVisible(true);

    connect(ui->pbOKTheme, &QAbstractButton::clicked, this, &EditorSettings::slOKClickedTheme);
}

void EditorSettings::slOKClickedTheme(){
    int ind = 0;
    if(ui->rbSecond->isChecked()){
        ind = 2;
    } else if(ui->rbFirst->isChecked()){
        ind = 1;
    }

    emit siThemeAccepted(ind);
    close();
}

void EditorSettings::changeStyle(){
    ui->pbOK->setStyleSheet("QPushButton {\
                            border-color: white;\
                            border-style: solid;\
                            border-radius: 6px;}");
    ui->pbOKTheme->setStyleSheet("QPushButton {\
                                 border-color: white;\
                                 border-style: solid;\
                                 border-radius: 6px;}");
    ui->pbOKFontSize->setStyleSheet("QPushButton {\
                                    border-color: white;\
                                    border-style: solid;\
                                    border-radius: 6px;}");
}
