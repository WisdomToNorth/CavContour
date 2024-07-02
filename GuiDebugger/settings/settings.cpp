#include "settings.h"

#include <iostream>

#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>

namespace debugger
{
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
    out << "point_radius=" << point_radius_ << "\n";
    out << "line_width=" << line_width_ << "\n";
    out << "arc_approx_error=" << arc_approx_error_ << "\n";
    out << "use_uint32_index=" << (use_uint32_index_ ? "true" : "false") << "\n";
    out << "color_index=" << color_index << "\n";

    configFile.close();
    return true;
}

bool Settings::load()
{
    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString configFilePath = QDir(documentsPath).filePath(path_to_config_);

    QFile configFile(configFilePath);
    if (!configFile.exists())
    {
        return save();
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

            if (key == "point_radius")
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
        }
    }

    configFile.close();
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
    style.useUInt32Index = use_uint32_index_;

    return style;
}
} // namespace debugger
