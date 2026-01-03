#include "CmdWallpaper.h"
#include "WallpaperTool.h"
#include <QTimer>
#include <QMessageBox>

CmdWallpaper::CmdWallpaper(QString cmd, QStringList args) noexcept:
    QObject{nullptr},
    m_cmd{std::move(cmd)},
    m_args{std::move(args)},
    m_process{new QProcess{this}}
{
    connect(m_process, &QProcess::errorOccurred, this, [this]() {
        QMessageBox::critical(nullptr, tr("Error"), m_process->errorString());
    });
}

CmdWallpaper::~CmdWallpaper() noexcept
{
    qDebug() << "~CmdWallpaper";
    this->stop();
}

void CmdWallpaper::start(const QScreen* screen, const QString& file)
{
    QStringList args = m_args;
    args << file;
    qDebug() << args;
    m_process->start(m_cmd, args);
    auto pid = m_process->processId();

    QTimer::singleShot(1000, [screen, pid](){
        auto geometry = screen->geometry();
        auto refer = screen->virtualGeometry();
        HWND win = FindWindowByPid(static_cast<DWORD>(pid));
        SetWindowGeometry(win, geometry.x() - refer.x(), geometry.y() - refer.y(), geometry.width() * screen->devicePixelRatio(), geometry.height() * screen->devicePixelRatio());
        SetWallpaperWindow(win);
        SetWindowGeometry(win, geometry.x() - refer.x(), geometry.y() - refer.y(), geometry.width() * screen->devicePixelRatio(), geometry.height() * screen->devicePixelRatio());
    });
}

void CmdWallpaper::stop()
{
    DetachWallpaperWindow(nullptr);
    m_process->terminate();
    // QTimer::singleShot(500, [this](){
    //     if (m_process->state() == QProcess::NotRunning) {
    //         return;
    //     }
    //     m_process->kill();
    // });
}