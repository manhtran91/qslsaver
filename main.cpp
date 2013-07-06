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

#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>

#include "watcher.h"
#include "worker.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    app.setOverrideCursor(QCursor(Qt::BlankCursor));

    Watcher watcher;
    Worker worker;

    watcher.connect(&watcher, SIGNAL(idling()), &worker, SLOT(start()));
    worker.connect(&worker, SIGNAL(stopped()), &watcher, SLOT(start()));

    app.exec();
}

