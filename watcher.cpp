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

#include "watcher.h"

Watcher::Watcher() : QTimer()
{
    connection = xcb_connect (NULL, NULL);
    screen = xcb_setup_roots_iterator (xcb_get_setup (connection)).data;

    connect(this, SIGNAL(timeout()), this, SLOT(onTimeout()));
    setInterval(1000);
    start();
}

void Watcher::onTimeout()
{
    xcb_screensaver_query_info_cookie_t cookie;
    xcb_screensaver_query_info_reply_t *info;

    cookie = xcb_screensaver_query_info (connection, screen->root);
    info = xcb_screensaver_query_info_reply (connection, cookie, NULL);

    uint32_t idle = info->ms_since_user_input;
    free (info);

    QSettings settings("qslsaver", "qslsaver");
    bool enabled = settings.value("enabled", 1).toBool();
    if (!enabled)
        return;

    int time = settings.value("timeout", 10).toInt() * 60000;

    if (idle <= time)
        return;

    stop();

    emit(idling());
}
