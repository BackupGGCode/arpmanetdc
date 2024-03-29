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

#ifndef SHAREWIDGET_H
#define SHAREWIDGET_H

#include <QtGui>
#include "checkableproxymodel.h"
#include "sharesearch.h"
#include "customtableitems.h"

typedef QPair<quint64, QHash<QString, quint64> > ContainerContentsType;

class ArpmanetDC;

//Class encapsulating all widgets/signals for search tab
class ShareWidget : public QObject
{
    Q_OBJECT

public:
    enum MagnetCalculationType
    {
        SingleMagnetType = 0x0,
        MultipleListMagnetType = 0x1
    };

    ShareWidget(ShareSearch *share, ArpmanetDC *parent);
    ~ShareWidget();

    //Get the encapsulating widget
    QWidget *widget();


private slots:
    //Context menu for magnets
    void contextMenuRequested(const QPoint &pos);
    void containerContextMenuRequested(const QPoint &pos);

    //Magnet request from ShareSearch
    void returnTTHFromPath(quint8 type, QString filePath, QByteArray tthRoot, quint64 fileSize);

    //Return slot for current shares in the DB
    void returnShares(QList<QDir> list);

    //Item dropped in container
    void droppedURLList(QList<QUrl> list);

    void switchedContainer(const QString &name);

    //===== CONTAINERS =====

    //Return the containers requested
    void returnContainers(QHash<QString, ContainerContentsType> containerHash);

    //===== GUI =====
    //Slots
    void selectedItemsChanged();

    void saveSharePressed();
    void refreshButtonPressed();
    void containerButtonPressed();
    void addContainerButtonPressed();
    void removeContainerButtonPressed();
    void renameContainerButtonPressed();

    void calculateMagnetActionPressed();
    void removeContainerEntryActionPressed();

    void addToMagnetListActionPressed();
    void copyListToClipboardActionPressed();
    void clearMagnetListActionPressed();
    void magnetRemoveListContextMenuPressed(QAction *action);

    void containerTreeViewKeyPressed(Qt::Key key);

    void changeRoot(QString path);
    void pathLoaded(QString path);

signals:
    //Signals
    void saveButtonPressed();

    //Private signal - update shares
    void updateShares(QList<QDir> *list);

    //Update shares without saving
    void updateShares();

    //Request TTH from filePath for magnets
    void requestTTHFromPath(quint8 type, QString filePath);

    //Request total shares
    void requestShares();

    //===== CONTAINERS =====

    //Request all containers in a directory
    void requestContainers(QString containerDirectory);
    
    //Process a container
    void processContainer(QString containerPath);
    
    //Save the containers to files in the directory specified
    void saveContainers(QHash<QString, ContainerContentsType> containerHash, QString containerDirectory);

private:
    //Functions
    void createWidgets();
    void placeWidgets();
    void connectWidgets();

    //Objects
    QWidget *pWidget;
    ArpmanetDC *pParent;
    ShareSearch *pShare;

    //Params
    QList<QString> pSharesList;

    //Loading paths
    QList<QString> pLoadingPaths;
    bool finishedLoading;

    //Containers
    QHash<QString, ContainerContentsType> pContainerHash;
    QStandardItem *pParentItem;
    QString pContainerDirectory;

    //GUI elements
    QTreeView *fileTree;
    QFileSystemModel *fileModel;
    CheckableProxyModel *checkProxyModel;

    QSplitter *splitter;

    QComboBox *containerCombo;
    CDropTreeView *containerTreeView;
    QStandardItemModel *containerModel;

    QLabel *busyLabel;

    QPushButton *saveButton, *refreshButton, *containerButton, *addContainerButton, *removeContainerButton, *renameContainerButton;

    QMenu *contextMenu, *containerContextMenu;
    QAction *calculateMagnetAction, *removeContainerEntryAction;
    
    //Magnet lists
    QHash<QString, QString> pMagnetList;
    QAction *addToMagnetListAction, *copyListToClipboardAction, *clearMagnetListAction;
    QMenu *magnetRemoveListContextMenu;
};

#endif
