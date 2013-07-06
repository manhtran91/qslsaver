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

#include <QDir>
#include <QSettings>

#include "eventfilter.h"
#include "worker.h"

Worker::Worker() : QLabel() , m_idx(0)
{
    EventFilter *e = new EventFilter;
    installEventFilter(e);
    setBackgroundRole(QPalette::Base);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    setScaledContents(true);

    setMouseTracking(true);

    buildFilesList();

    connect(e, SIGNAL(eventHappened()), this, SLOT(stop()));
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(showNext()));
}

void Worker::buildFilesList()
{
    QSettings settings("qslsaver", "qslsaver");
    QString defaultPath = QDir::homePath();
    defaultPath = QString("%1/Pictures").arg(defaultPath);
    QString path(settings.value("directory", defaultPath).toString());

    QDir dir(path);
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);
    m_files = dir.entryInfoList();
}

void Worker::start()
{
    showFullScreen();
    showNext();
    grabMouse();

    QSettings settings("qslsaver", "qslsaver");
    m_timer.start(settings.value("delay", 10).toInt() * 1000);
}

void Worker::stop()
{
    m_timer.stop();
    hide();
    releaseMouse();
    emit(stopped());
}

void Worker::showNext()
{
    m_idx++;
    if (m_idx == m_files.size())
        m_idx = 0;

    QString path = m_files.at(m_idx).absoluteFilePath();
    QImage image(path);
    if (image.isNull())
        showNext();

    setPixmap(QPixmap::fromImage(image));
}

