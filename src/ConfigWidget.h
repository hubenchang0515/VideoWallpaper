#ifndef CONFIG_WIDGET_H
#define CONFIG_WIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "AbstractWallpaper.h"

class ConfigWidget : public QWidget
{
    Q_OBJECT
public:
    ConfigWidget(AbstractWallpaper* wallpaper, QWidget* parent=nullptr) noexcept;
    ~ConfigWidget() noexcept;

    void start() const noexcept;
    void stop() const noexcept;

private:
    QHBoxLayout* m_layout;
    QLabel* m_label;
    QLineEdit* m_edit;
    QPushButton* m_start;
    QPushButton* m_stop;

    AbstractWallpaper* m_wallpaper;
};

#endif // CONFIG_WIDGET_H