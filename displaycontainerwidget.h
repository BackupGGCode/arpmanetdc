/* This file is part of ArpmanetDC. Copyright (C) 2012
 * Source code can be found at http://code.google.com/p/arpmanetdc/
 * 
 * ArpmanetDC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ArpmanetDC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ArpmanetDC.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DISPLAYCONTAINERWIDGET_H
#define DISPLAYCONTAINERWIDGET_H

#include <QtGui>
#include <QHostAddress>
#include "containerthread.h"
#include "checkableproxymodel.h"
#include "customtableitems.h"

class ArpmanetDC;
struct QueueStruct;

class DisplayContainerWidget : public QObject
{
    Q_OBJECT
public:
    //Constructor to open widget with data
    DisplayContainerWidget(QHostAddress host, ContainerContentsType index, QList<ContainerLookupReturnStruct> contents, QString name, QString path, ArpmanetDC *parent);
    //Destructor
    ~DisplayContainerWidget();

    //Get the encapsulating widget
    QWidget *widget();

public slots:

private slots:
    //Checked values were changed
    void checkedNodesChanged();

    void downloadSelectedFilesButtonPressed();
    void downloadAllFilesButtonPressed();

signals:
    //Signal to queue download
    void queueDownload(int priority, QByteArray tth, QString filePath, quint64 fileSize, QHostAddress host);

private:
    //Functions
    void createWidgets();
    void placeWidgets();
    void connectWidgets();

    //Populate tree with contents
    void populateTree();

    //Objects
    QWidget *pWidget;
    ArpmanetDC *pParent;

    //Lists
    QHash<QString, QStandardItem *> *pPathItemHash;
    QHash<QString, QueueStruct> *pDownloadList;
    
    //Container data
    ContainerContentsType pIndex;
    QList<ContainerLookupReturnStruct> pContents;
    QHostAddress pHost;
    QString pName;
    QString pDownloadPath;
    QString pContainerPath;
    qint64 pSelectedFileSize;
    quint32 pSelectedFileCount;

    //GUI
    QLabel *containerNameLabel, *containerSizeLabel, *containerPathLabel, *busyLabel;
    QPushButton *downloadAllFilesButton;
    
    //Selected
    QPushButton *downloadSelectedFilesButton;
    QLabel *selectedFileSizeLabel;
    QLabel *selectedFileCountLabel;

    //Models and views
    QTreeView *containerTreeView;
    QStandardItemModel *containerModel;
    CheckableProxyModel *checkProxyModel;
    QStandardItem *pParentItem;
};

#endif