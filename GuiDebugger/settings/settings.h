#ifndef DEBUGGER_SETTINGS_H
#define DEBUGGER_SETTINGS_H

#include <QQuickItem>

#include "viewer/drawstyle.h"

namespace debugger
{
class Settings : public QObject
{
    Q_OBJECT
public:
    static Settings &instance()
    {
        // Lazy initialization
        static Settings *instance = new Settings();
        return *instance;
    }
    DrawStyle getDrawStyle() const;

    bool save() const;
    bool load();

    int getAppAlg() const;
    void setAppAlg(int alg);

    qreal pointRadius() const;
    void setPointRadius(qreal radius);
    float lineWidth() const;
    void setLineWidth(float width);

    double arcApproxError() const;
    void setArcApproxError(double error);

    bool useUInt32Index() const;
    void setUseUInt32Index(bool use);

    int colorIndex() const;
    void setColorIndex(int index);

signals:
    void initDone();

private:
    Settings() = default;
    ~Settings() = default;
    Settings(const Settings &) = delete;
    Settings &operator=(const Settings &) = delete;

    int app_alg_ = 0;
    qreal point_radius_ = 5.0;
    float line_width_ = 1.0f;
    double arc_approx_error_ = 0.001;
    bool use_uint32_index_ = true;
    int color_index = 1;

    /*Draw style*/
    const QSGGeometry::DrawingMode line_draw_mode_ = QSGGeometry::DrawingMode::DrawLineStrip;
    const QString path_to_config_ = "polyconfig.ini";
};

class SettingItem : public QQuickItem
{
    Q_OBJECT
public:
    Q_PROPERTY(qreal lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChangedSig)
    Q_PROPERTY(qreal pointRadius READ pointRadius WRITE setPointRadius NOTIFY pointRadiusChangedSig)
    Q_PROPERTY(uint polyAlg READ polyAlg WRITE setAppAlg NOTIFY appAlgChangedSig)
    Q_PROPERTY(qreal arcApproxError READ arcApproxError WRITE setArcApproxError NOTIFY
                   arcApproxErrorChangedSig)
    Q_PROPERTY(bool useUInt32Index READ useUInt32Index WRITE setUseUInt32Index NOTIFY
                   useUInt32IndexChangedSig)
    Q_PROPERTY(uint colorIndex READ colorIndex WRITE setColorIndex NOTIFY colorIndexChangedSig)

public:
    SettingItem(QQuickItem *parent = nullptr);
    ~SettingItem() = default;

    int polyAlg() const;
    void setAppAlg(int poly_alg);

    qreal pointRadius() const;
    void setPointRadius(qreal radius);

    float lineWidth() const;
    void setLineWidth(float width);

    double arcApproxError() const;
    void setArcApproxError(double error);

    bool useUInt32Index() const;
    void setUseUInt32Index(bool use);

    int colorIndex() const;
    void setColorIndex(int index);

signals:
    void appAlgChangedSig(int polyAlg);
    void pointRadiusChangedSig(qreal radius);
    void lineWidthChangedSig(float width);
    void arcApproxErrorChangedSig(double error);
    void useUInt32IndexChangedSig(bool use);
    void colorIndexChangedSig(int index);

private slots:
    void initDone();
};

} // namespace debugger

#endif