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
#include <QApplication>
#include <QScreen>

#include "eventfilter.h"
#include "worker.h"

Worker::Worker() : QLabel() , m_idx(0)
{
    EventFilter *e = new EventFilter;
    installEventFilter(e);
    setAutoFillBackground(true);
    setBackgroundRole(QPalette::Base);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    setStyleSheet("QLabel { background-color: black; }");
    setAlignment(Qt::AlignCenter);

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
    if (!setImage(path))
        showNext();
}

bool Worker::setImage(QString &path)
{
    QImage source(path), dest;
    if (source.isNull())
        return false;

    QSize size = QApplication::primaryScreen()->availableSize();
    int lw = size.width();
    int lh = size.height();
    float iw = source.width();
    float ih = source.height();

    if ((iw <= lw) && (ih <= lh))
        dest = source;
    else
        if ((iw / lw) > (ih / lh))
            dest = source.scaledToWidth(lw, Qt::SmoothTransformation);
        else
            dest = source.scaledToHeight(lh, Qt::SmoothTransformation);

    setPixmap(QPixmap::fromImage(dest));

    return true;
}
