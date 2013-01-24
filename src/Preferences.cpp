/****************************************************************************
**
** Copyright (C) 2012 Woda Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Woda Corporation (woda_2014@labeip.epitech.eu)
**
****************************************************************************/

#include    "Preferences.hh"
#include    "ui_Preferences.h"
#include    "ConfFile.hh"
#include    "FileSystemWatcher.hh"

Preferences::Preferences(QWidget *parent)
 : QDialog(parent), ui(new Ui::Preferences) {
    ui->setupUi(this);
    QObject::connect(ui->buttonGroupNotification, SIGNAL(buttonClicked(int)),
                     this, SLOT(notificationPositionClick(int)));
    ui->buttonGroupNotification->setId(ui->radioButtonBottomLeft, BOTTOM_LEFT);
    ui->buttonGroupNotification->setId(ui->radioButtonBottomRight,BOTTOM_RIGHT);
    ui->buttonGroupNotification->setId(ui->radioButtonTopLeft,    TOP_LEFT);
    ui->buttonGroupNotification->setId(ui->radioButtonTopRight,   TOP_RIGHT);

    this->initCorner();
    this->initDirectory();
}

Preferences::~Preferences() {
    delete ui;
}

void    Preferences::initCorner(void) {
    // check if corner is set in the ini file
    // if present set the radio button to the value in the ini file
    int corner = ConfFile::getSingletonPtr()->getValue(CORNER).toInt();
    if (!corner) {
        ui->radioButtonBottomRight->setChecked(true);
        ConfFile::getSingletonPtr()->setValue(CORNER, QVariant(corner));
    } else {
        ui->buttonGroupNotification->button(corner)->setChecked(true);
    }
}

void    Preferences::initDirectory(void) {
    // check if the directory is set in the ini file
    // if present set the QLineEdit to the value in the ini file
    QString dir = ConfFile::getSingletonPtr()->getValue(DIRECTORY).toString();
    if (dir != QString(""))
        ui->WodaFolder_input->setText(dir);
}

void    Preferences::on_checklimitdl_clicked() {
    if (ui->checklimitdl->isChecked())
        ui->input_limitdl->setEnabled(true);
    else
        ui->input_limitdl->setEnabled(false);
}

void    Preferences::on_checklimitup_clicked() {
    if (ui->checklimitup->isChecked())
        ui->input_limitup->setEnabled(true);
    else
        ui->input_limitup->setEnabled(false);
}

void    Preferences::on_browse_button_clicked() {
    QString dir;
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                            "/home",
                                            QFileDialog::ShowDirsOnly |
                                            QFileDialog::DontResolveSymlinks);
    ui->WodaFolder_input->setText(dir);
    ConfFile::getSingletonPtr()->setValue(DIRECTORY, QVariant(dir));
    FileSystemWatcher * fsWatcher = FileSystemWatcher::getSingletonPtr();
    if (dir != QString("")) {
        QString tmp("");
        fsWatcher->addDirectory(tmp);
        fsWatcher->addDirectory(dir);
    }
}

void    Preferences::notificationPositionClick(int id) {
    ConfFile::getSingletonPtr()->setValue(CORNER, QVariant(id));
}

