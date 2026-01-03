#ifndef CONFIG_WIDGET_H
#define CONFIG_WIDGET_H

#include <QWidget>
#include <QLayout>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScreen>
#include "AbstractWallpaper.h"

class ConfigWidget : public QWidget
{
    Q_OBJECT
public:
    ConfigWidget(QScreen* screen, QWidget* parent=nullptr) noexcept;
    ~ConfigWidget() noexcept;

    void start() noexcept;
    void stop() noexcept;

private:
    QGridLayout* m_layout;
    QLabel* m_typeLabel;
    QComboBox* m_type;
    QLabel* m_fileLabel;
    QLineEdit* m_file;
    QPushButton* m_start;
    QPushButton* m_stop;

    QScreen* m_screen;
    AbstractWallpaper* m_wallpaper;

    struct Choice
    {
        QString name;
        std::function<AbstractWallpaper*()> creator;
    };

    static QVector<Choice> choices;
};

#endif // CONFIG_WIDGET_H