#include "settings.h"

#include <iostream>

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>

namespace debugger
{
int Settings::getAppAlg() const
{
    return app_alg_;
}
void Settings::setAppAlg(int alg)
{
    app_alg_ = alg;
}

qreal Settings::pointRadius() const
{
    return point_radius_;
}
void Settings::setPointRadius(qreal radius)
{
    point_radius_ = radius;
}

float Settings::lineWidth() const
{
    return line_width_;
}
void Settings::setLineWidth(float width)
{
    line_width_ = width;
}

double Settings::arcApproxError() const
{
    return arc_approx_error_;
}
void Settings::setArcApproxError(double error)
{
    arc_approx_error_ = error;
}

bool Settings::useUInt32Index() const
{
    return use_uint32_index_;
}
void Settings::setUseUInt32Index(bool use)
{
    use_uint32_index_ = use;
}

int Settings::colorIndex() const
{
    return color_index;
}
void Settings::setColorIndex(int index)
{
    color_index = index;
}
double Settings::pickTol() const
{
    return pick_tol_;
}
void Settings::setPickTol(double tol)
{
    pick_tol_ = tol;
}

int Settings::showPrecision() const
{
    return show_precision_;
}
void Settings::setShowPrecision(int precision)
{
    show_precision_ = precision;
}
float Settings::uiScaleFactor() const
{
    return ui_scale_factor_;
}
void Settings::setUiScaleFactor(float factor)
{
    ui_scale_factor_ = factor;
}

bool Settings::save() const
{
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString configFilePath = QDir(documentsPath).filePath(path_to_config_);

    QFile configFile(configFilePath);
    if (!configFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream out(&configFile);
    out << "app_alg=" << app_alg_ << "\n";
    out << "point_radius=" << point_radius_ << "\n";
    out << "line_width=" << line_width_ << "\n";
    out << "arc_approx_error=" << arc_approx_error_ << "\n";
    out << "use_uint32_index=" << (use_uint32_index_ ? "true" : "false") << "\n";
    out << "color_index=" << color_index << "\n";
    out << "pick_tol=" << pick_tol_ << "\n";
    out << "show_precision=" << show_precision_ << "\n";
    out << "ui_scale_factor=" << ui_scale_factor_ << "\n";

    return true;
}

bool Settings::load()
{
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString configFilePath = QDir(documentsPath).filePath(path_to_config_);

    QFile configFile(configFilePath);
    if (!configFile.exists())
    {
        app_alg_ = 0;
        point_radius_ = 5.0;
        line_width_ = 1.0f;
        arc_approx_error_ = 0.001;
        use_uint32_index_ = true;
        color_index = 1;
        pick_tol_ = 0.1;
        show_precision_ = 3;
        ui_scale_factor_ = 50;
        emit initDone();

        bool save_succ = save();
        if (!save_succ)
        {
            qDebug() << "[ERROR]: Failed to save default settings";
        }
        return save_succ;
    }

    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream in(&configFile);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split("=");
        if (parts.size() == 2)
        {
            QString key = parts[0].trimmed();
            QString value = parts[1].trimmed();
            // qDebug() << "key: " << key << " value: " << value;
            if (key == "app_alg")
            {
                app_alg_ = value.toInt();
            }
            else if (key == "point_radius")
            {
                point_radius_ = value.toDouble();
            }
            else if (key == "line_width")
            {
                line_width_ = value.toFloat();
            }
            else if (key == "arc_approx_error")
            {
                arc_approx_error_ = value.toDouble();
            }
            else if (key == "use_uint32_index")
            {
                use_uint32_index_ = (value == "true");
            }
            else if (key == "color_index")
            {
                color_index = value.toInt();
            }
            else if (key == "pick_tol")
            {
                pick_tol_ = value.toDouble();
            }
            else if (key == "show_precision")
            {
                show_precision_ = value.toInt();
            }
            else if (key == "ui_scale_factor")
            {
                ui_scale_factor_ = value.toFloat();
            }
        }
    }

    configFile.close();
    emit initDone();
    return true;
}

DrawStyle Settings::getDrawStyle() const
{
    DrawStyle style;
    style.color = DrawStyle::indexToColor(color_index);
    style.linetype = line_draw_mode_;
    style.arcApproxError = arc_approx_error_;
    style.width = line_width_;
    style.visible = true;
    style.useUInt32Index = true; // TODO:  use_uint32_index_;

    return style;
}

SettingItem::SettingItem(QQuickItem *parent)
    : QQuickItem(parent)
{
    connect(&Settings::instance(), &Settings::initDone, this, &SettingItem::initDone);
}

void SettingItem::initDone()
{
    emit appAlgChangedSig(Settings::instance().getAppAlg());
    emit pointRadiusChangedSig(Settings::instance().pointRadius());
    emit lineWidthChangedSig(Settings::instance().lineWidth());
    emit arcApproxErrorChangedSig(Settings::instance().arcApproxError());
    emit useUInt32IndexChangedSig(Settings::instance().useUInt32Index());
    emit colorIndexChangedSig(Settings::instance().colorIndex());
    emit pickTolChangedSig(Settings::instance().pickTol());
    emit showPrecisionChangedSig(Settings::instance().showPrecision());
    emit uiScaleFactorChangedSig(Settings::instance().uiScaleFactor());
}

int SettingItem::polyAlg() const
{
    return Settings::instance().getAppAlg();
}

void SettingItem::setAppAlg(int poly_alg)
{
    // std::cout << "SettingItem::setAppAlg: " << poly_alg << std::endl;
    Settings::instance().setAppAlg(poly_alg);
    emit appAlgChangedSig(poly_alg);
}

qreal SettingItem::pointRadius() const
{
    return Settings::instance().pointRadius();
}

void SettingItem::SettingItem::setPointRadius(qreal radius)
{
    // std::cout << "SettingItem::setPointRadius: " << radius << std::endl;
    Settings::instance().setPointRadius(radius);
    emit pointRadiusChangedSig(radius);
}

float SettingItem::lineWidth() const
{
    return Settings::instance().lineWidth();
}

void SettingItem::setLineWidth(float width)
{
    // std::cout << "SettingItem::setLineWidth: " << width << std::endl;
    Settings::instance().setLineWidth(width);
    emit lineWidthChangedSig(width);
}

double SettingItem::arcApproxError() const
{
    return Settings::instance().arcApproxError();
}

void SettingItem::setArcApproxError(double error)
{
    // std::cout << "SettingItem::setArcApproxError: " << error << std::endl;
    Settings::instance().setArcApproxError(error);
    emit arcApproxErrorChangedSig(error);
}

bool SettingItem::useUInt32Index() const
{
    return Settings::instance().useUInt32Index();
}

void SettingItem::setUseUInt32Index(bool use)
{
    // std::cout << "SettingItem::setUseUInt32Index: " << use << std::endl;
    Settings::instance().setUseUInt32Index(use);
    emit useUInt32IndexChangedSig(use);
}

int SettingItem::colorIndex() const
{
    return Settings::instance().colorIndex();
}

void SettingItem::setColorIndex(int index)
{
    // std::cout << "SettingItem::setColorIndex: " << index << std::endl;
    Settings::instance().setColorIndex(index);
    emit colorIndexChangedSig(index);
}
double SettingItem::pickTol() const
{
    return Settings::instance().pickTol();
}

void SettingItem::setPickTol(double tol)
{
    // std::cout << "SettingItem::setPickTol: " << tol << std::endl;
    Settings::instance().setPickTol(tol);
    emit pickTolChangedSig(tol);
}

int SettingItem::showPrecision() const
{
    return Settings::instance().showPrecision();
}

void SettingItem::setShowPrecision(int precision)
{
    // std::cout << "SettingItem::setShowPrecision: " << precision << std::endl;
    Settings::instance().setShowPrecision(precision);
    emit showPrecisionChangedSig(precision);
}

float SettingItem::uiScaleFactor() const
{
    return Settings::instance().uiScaleFactor();
}

void SettingItem::setUiScaleFactor(float factor)
{
    // std::cout << "SettingItem::setUiScaleFactor: " << factor << std::endl;
    Settings::instance().setUiScaleFactor(factor);
    emit uiScaleFactorChangedSig(factor);
}
} // namespace debugger
