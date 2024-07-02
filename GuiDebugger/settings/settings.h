#ifndef DEBUGGER_SETTINGS_H
#define DEBUGGER_SETTINGS_H

#include <QQuickItem>

#include "viewer/drawstyle.h"

namespace debugger
{
class Settings
{
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

    // clang-format off
    int getAppAlg() const { return app_alg_; }
    void setAppAlg(int alg) { app_alg_ = alg; }

    qreal pointRadius() const { return point_radius_; }
    void setPointRadius(qreal radius) { point_radius_ = radius; }

    float lineWidth() const { return line_width_; }
    void setLineWidth(float width) { line_width_ = width; }

    double arcApproxError() const { return arc_approx_error_; }
    void setArcApproxError(double error) { arc_approx_error_ = error; }

    bool useUInt32Index() const { return use_uint32_index_; }
    void setUseUInt32Index(bool use) { use_uint32_index_ = use; }

    int colorIndex() const { return color_index; }
    void setColorIndex(int index) { color_index = index; }
    // clang-format on

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
    const QString path_to_config_ = "config.ini";
};

class SettingItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int polyAlg READ polyAlg WRITE setAppAlg NOTIFY appAlgChangedSig)
    Q_PROPERTY(qreal pointRadius READ pointRadius WRITE setPointRadius NOTIFY pointRadiusChangedSig)
    Q_PROPERTY(float lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChangedSig)
    Q_PROPERTY(double arcApproxError READ arcApproxError WRITE setArcApproxError NOTIFY
                   arcApproxErrorChangedSig)
    Q_PROPERTY(bool useUInt32Index READ useUInt32Index WRITE setUseUInt32Index NOTIFY
                   useUInt32IndexChangedSig)
    Q_PROPERTY(int colorIndex READ colorIndex WRITE setColorIndex NOTIFY colorIndexChangedSig)

public:
    SettingItem(QQuickItem *parent = nullptr){};
    ~SettingItem() = default;

    // clang-format off
    int polyAlg() const { return Settings::instance().getAppAlg(); }
    void setAppAlg(int polyAlg){Settings::instance().setAppAlg(polyAlg);}

    qreal pointRadius() const { return Settings::instance().pointRadius(); }
    void setPointRadius(qreal radius) { Settings::instance().setPointRadius(radius); }

    float lineWidth() const { return Settings::instance().lineWidth(); }
    void setLineWidth(float width) { Settings::instance().setLineWidth(width); }

    double arcApproxError() const { return Settings::instance().arcApproxError(); }
    void setArcApproxError(double error) { Settings::instance().setArcApproxError(error); }

    bool useUInt32Index() const { return Settings::instance().useUInt32Index(); }
    void setUseUInt32Index(bool use) { Settings::instance().setUseUInt32Index(use); }

    int colorIndex() const { return Settings::instance().colorIndex(); }
    void setColorIndex(int index) { Settings::instance().setColorIndex(index); }
    // clang-format on

signals:
    void appAlgChangedSig(int polyAlg);
    void pointRadiusChangedSig(qreal radius);
    void lineWidthChangedSig(float width);
    void arcApproxErrorChangedSig(double error);
    void useUInt32IndexChangedSig(bool use);
    void colorIndexChangedSig(int index);
};

} // namespace debugger

#endif