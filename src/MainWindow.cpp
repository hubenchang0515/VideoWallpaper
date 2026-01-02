#include "MainWindow.h"
#include <QScreen>
#include <QFile>
#include "ConfigWidget.h"
#include "WallpaperTool.h"
#include "VideoWallpaper.h"

MainWindow::MainWindow(QWidget* parent) noexcept:
    QDialog{parent},
    m_layout{new QVBoxLayout},
    m_tabs{new QTabWidget}
{
    for(QScreen* screen : QGuiApplication::screens())
    {
        m_tabs->addTab(new ConfigWidget{new VideoWallpaper{screen}}, screen->name());
    }

    m_layout->addWidget(m_tabs);
    this->setLayout(m_layout);
}


MainWindow::~MainWindow() noexcept
{
    qDebug() << "~MainWindow";
}
