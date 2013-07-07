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

#ifndef OPTIONS_H
#define OPTIONS_H

#include "ui_options.h"

class Options : public QDialog
{
    Q_OBJECT

public:
    Options();

private:
    Ui::Options ui;

private slots:
    void on_timeoutSpin_valueChanged(int value);
    void on_directoryBtn_clicked();
    void on_delaySpin_valueChanged(int value);
    void on_enableChk_stateChanged(int state);
};

#endif
