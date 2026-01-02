#include "VideoWallpaper.h"
#include <QScreen>
#include <Windows.h>
#include "WallpaperTool.h"

VideoWallpaper::VideoWallpaper(QScreen* screen) noexcept:
    QDialog{nullptr},   // 不能设置 parent,否则设为壁纸后无法渲染
    m_layout{new QHBoxLayout},
    m_view{new VideoView},
    m_screen{screen}
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);
    this->setAttribute(Qt::WA_NativeWindow);
    m_layout->addWidget(m_view);
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout);
    this->setContentsMargins(0,0,0,0);
    m_view->setLoop();
}

VideoWallpaper::~VideoWallpaper()
{
    qDebug() << "~VideoWallpaper";
    this->stop();
}

void VideoWallpaper::start(const QString& file) noexcept
{
    m_view->setFile(file);
    m_view->setVolume(0);
    m_view->play();
    this->show();
    auto geometry = m_screen->geometry();
    auto refer = m_screen->virtualGeometry();

    HWND win = reinterpret_cast<HWND>(this->winId());
    SetWindowPos(win, nullptr, geometry.x() - refer.x(), geometry.y() - refer.y(), geometry.width() * m_screen->devicePixelRatio(), geometry.height() * m_screen->devicePixelRatio(), SWP_NOZORDER);
    SetWallpaperWindow(win);
    SetWindowPos(win, nullptr, geometry.x() - refer.x(), geometry.y() - refer.y(), geometry.width() * m_screen->devicePixelRatio(), geometry.height() * m_screen->devicePixelRatio(), SWP_NOZORDER);
}

void VideoWallpaper::stop() noexcept
{
    m_view->pause();
    DetachWallpaperWindow(reinterpret_cast<HWND>(this->effectiveWinId()));
    this->hide();
}
