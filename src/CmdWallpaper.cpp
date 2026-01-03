#include "CmdWallpaper.h"
#include "WallpaperTool.h"
#include <QTimer>
#include <QMessageBox>

CmdWallpaper::CmdWallpaper(QString cmd, QStringList args) noexcept:
    QObject{nullptr},
    m_cmd{std::move(cmd)},
    m_args{std::move(args)},
    m_process{new QProcess{this}},
    m_timer{new QTimer{this}}
{
    connect(m_timer, &QTimer::timeout, this, &CmdWallpaper::attach);
}

CmdWallpaper::~CmdWallpaper() noexcept
{
    qDebug() << "~CmdWallpaper";
    this->stop();
}

void CmdWallpaper::start(const QScreen* screen, const QString& file)
{
    if (m_process->state() == QProcess::NotRunning)
    {
        this->launch(screen, file);
    }
    else
    {
        this->stop();
        QTimer::singleShot(100, [this, screen, file](){this->launch(screen, file);});
    }
    
}

void CmdWallpaper::stop()
{
    m_timer->stop();
    DetachWallpaperWindow(nullptr);
    m_process->kill();
}

void CmdWallpaper::launch(const QScreen* screen, const QString& file) noexcept
{
    m_screen = screen;
    QStringList args = m_args;
    args << file;
    m_process->start(m_cmd, args);
    if (m_process->state() == QProcess::NotRunning)
    {
        QMessageBox::critical(nullptr, tr("Error"), m_process->errorString());
        return;
    }
    m_timer->start(100);
}

void CmdWallpaper::attach() const noexcept
{
    HWND win = FindWindowByPid(static_cast<DWORD>(m_process->processId()));
    if (win == 0) return;
    m_timer->stop();
    auto geometry = m_screen->geometry();
    auto refer = m_screen->virtualGeometry();
    auto scale = m_screen->devicePixelRatio();
    SetWindowGeometry(win, geometry.x() - refer.x(), geometry.y() - refer.y(), geometry.width() * scale, geometry.height() * scale);
    SetWallpaperWindow(win);
    SetWindowGeometry(win, geometry.x() - refer.x(), geometry.y() - refer.y(), geometry.width() * scale, geometry.height() * scale);
    m_timer->stop();
}