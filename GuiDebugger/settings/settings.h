#ifndef DEBUGGER_SETTINGS_H
#define DEBUGGER_SETTINGS_H

#include <QQuickItem>

#include "viewer/drawstyle.h"

namespace debugger
{
class NgSettings : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(AppAlgorithmCore appAlgorithmCore READ appAlgorithmCore WRITE setAppAlgorithmCore
                   NOTIFY appAlgorithmCoreChanged)

public:
    enum AppAlgorithmCore
    {
        kCavc,
        kNGPoly,
        kClipper
    };
    Q_ENUM(AppAlgorithmCore)

    NgSettings(QQuickItem *parent = nullptr){};
    static AppAlgorithmCore getCurAlgorithmCore()
    {
        return g_machineType;
    }
    static DrawStyle &gDrawStyle()
    {
        return g_drawStyle;
    }
signals:
    void appAlgorithmCoreChanged(AppAlgorithmCore appAlgorithmCore);

public:
    AppAlgorithmCore appAlgorithmCore() const
    {
        return g_machineType;
    }

    void setAppAlgorithmCore(AppAlgorithmCore appAlgorithmCore);

private:
    static AppAlgorithmCore g_machineType;
    static DrawStyle g_drawStyle;
};
} // namespace debugger

#endif