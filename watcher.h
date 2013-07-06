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

#ifndef WATCHER_H
#define WATCHER_H

#include <xcb/xcb.h>
#include <xcb/screensaver.h>

#include <QLabel>
#include <QImage>
#include <QTimer>

class Watcher : public QTimer
{
    Q_OBJECT

public:
    Watcher();

private:
    xcb_connection_t *connection;
    xcb_screen_t *screen;

private slots:
    void onTimeout();

signals:
    void idling();
};

#endif
