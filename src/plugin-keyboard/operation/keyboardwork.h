/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KEYBOARDWORK_H
#define KEYBOARDWORK_H

#include "interface/namespace.h"
#include "src/plugin-keyboard/window/indexmodel.h"
#include "src/plugin-keyboard/window/shortcutmodel.h"
#include "keyboardmodel.h"
#include "keyboarddbusproxy.h"

#include <QObject>
#include <QDBusPendingCallWatcher>
#include <QDBusInterface>

namespace DCC_NAMESPACE {
class KeyboardWorker : public QObject
{
    Q_OBJECT
public:
    explicit KeyboardWorker(KeyboardModel* model, QObject *parent = nullptr);
    enum Modifier {
        control = 1,
        super = 2,
        alt = 4,
        shift = 8
    };

    void resetAll();

    void setShortcutModel(ShortcutModel * model);
    void refreshShortcut();
    void refreshLang();
    void windowSwitch();

    inline QList<MetaData> getDatas() {return m_metaDatas;}
    inline QList<QString> getLetters() {return m_letters;}

    void modifyShortcutEditAux(ShortcutInfo* info, bool isKPDelete = false);
    void modifyShortcutEdit(ShortcutInfo* info);
    void addCustomShortcut(const QString& name, const QString& command, const QString& accels);
    void modifyCustomShortcut(ShortcutInfo *info);

    void grabScreen();
    bool checkAvaliable(const QString& key);
    void delShortcut(ShortcutInfo *info);

    void setRepeatDelay(uint value);
    void setRepeatInterval(int value);
    void setModelRepeatDelay(uint value);
    void setModelRepeatInterval(uint value);

    void setNumLock(bool value);
    void setCapsLock(bool value);
    void active();
    void deactive();
    bool keyOccupy(const QStringList &list);
    void onRefreshKBLayout();

Q_SIGNALS:
    void KeyEvent(bool in0, const QString &in1);
    void searchChangd(ShortcutInfo* info, const QString& key);
    void removed(const QString &id, int type);
    void requestSetAutoHide(const bool visible);
    void onDatasChanged(QList<MetaData> datas);
    void onLettersChanged(QList<QString> letters);
    // 快捷键恢复默认完成
    void onResetFinished();

public Q_SLOTS:
    void setLang(const QString &value);
    void addLang(const QString &value);
    void deleteLang(const QString& value);
    void setLayout(const QString& value);
    void addUserLayout(const QString& value);
    void delUserLayout(const QString& value);
    void onRequestShortcut(QDBusPendingCallWatcher* watch);
    void onAdded(const QString&in0, int in1);
    void onDisableShortcut(ShortcutInfo* info);
    void onAddedFinished(QDBusPendingCallWatcher *watch);
    void onLocalListsFinished(QDBusPendingCallWatcher *watch);
    void onGetWindowWM(bool value);
    void onLayoutListsFinished(QDBusPendingCallWatcher *watch);
    void onUserLayout(const QStringList &list);
    void onUserLayoutFinished(QDBusPendingCallWatcher *watch);
    void onCurrentLayout(const QString &value);
    void onCurrentLayoutFinished(QDBusPendingCallWatcher *watch);
    void onPinyin();
    void onSearchShortcuts(const QString &searchKey);
    void onSearchFinished(QDBusPendingCallWatcher *watch);
    void append(const MetaData& md);
    void onKeyboardPropertiesChanged(QDBusMessage msg);
    void onLangSelectorPropertiesChanged(QDBusMessage msg);
    void onKeybingdingPropertiesChanged(QDBusMessage msg);
    void onWMPropertiesChanged(QDBusMessage msg);
    void onLangSelectorServiceFinished();
    void onShortcutChanged(const QString &id, int type);
    void onGetShortcutFinished(QDBusPendingCallWatcher *watch);
    void updateKey(ShortcutInfo *info);
    void cleanShortcutSlef(const QString &id, const int type, const QString &shortcut);
    void setNewCustomShortcut(const QString &id, const QString &name, const QString &command, const QString &accles);
    void onConflictShortcutCleanFinished(QDBusPendingCallWatcher *watch);
    void onShortcutCleanFinished(QDBusPendingCallWatcher *watch);
    void onCustomConflictCleanFinished(QDBusPendingCallWatcher *w);

private:
    uint converToDBusDelay(uint value);
    uint converToModelDelay(uint value);
    int converToDBusInterval(int value);
    uint converToModelInterval(uint value);

private:
    QList<MetaData> m_datas;
    QList<MetaData> m_metaDatas;
    QList<QString> m_letters;
    int m_delayValue;
    int m_speedValue;
    KeyboardModel* m_model;
    KeyboardDBusProxy *m_keyboardDBusProxy;
    ShortcutModel *m_shortcutModel = nullptr;

};
}
#endif // KEYBOARDWORK_H