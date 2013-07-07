/*
 * Copyright (C) 2013 Gauvain Pocentek <gauvain@pocentek.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QSettings>
#include <QDir>
#include <QFileDialog>

#include "options.h"

Options::Options() : QDialog()          
{   
    ui.setupUi(this);

    QSettings settings("qslsaver", "qslsaver");

    ui.timeoutSpin->setValue(settings.value("timeout", 10).toInt());
    ui.delaySpin->setValue(settings.value("delay", 10).toInt());

    bool state = settings.value("enabled", 1).toBool();
    ui.enableChk->setChecked(state);
    ui.frame->setEnabled(state);

    QString defaultPath = QDir::homePath();
    defaultPath = QString("%1/Pictures").arg(defaultPath);
    QString path(settings.value("directory", defaultPath).toString());
    ui.directoryEdit->setText(path);
}

void Options::on_timeoutSpin_valueChanged(int value)
{
    QSettings settings("qslsaver", "qslsaver");
    settings.setValue("timeout", value);
}

void Options::on_directoryBtn_clicked()
{
    QString dirname = QFileDialog::getExistingDirectory(this);
    ui.directoryEdit->setText(dirname);

    QSettings settings("qslsaver", "qslsaver");
    settings.setValue("directory", dirname);
}

void Options::on_delaySpin_valueChanged(int value)
{
    QSettings settings("qslsaver", "qslsaver");
    settings.setValue("delay", value);
}

void Options::on_enableChk_stateChanged(int state)
{
    QSettings settings("qslsaver", "qslsaver");
    settings.setValue("enabled", (bool)state);
    ui.frame->setEnabled(state);
}
