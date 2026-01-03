#ifndef CMD_WALLPAPER_H
#define CMD_WALLPAPER_H

#include "AbstractWallpaper.h"
#include <QObject>
#include <QScreen>
#include <QProcess>
#include <QTimer>

class CmdWallpaper : public QObject, public AbstractWallpaper
{
    Q_OBJECT
public:
    CmdWallpaper(QString cmd, QStringList args) noexcept;
    ~CmdWallpaper() noexcept;
    
    virtual void start(const QScreen* screen, const QString& file) override;
    virtual void stop() override;

private:
    QString m_cmd;
    QStringList m_args;
    QProcess* m_process;
    QTimer* m_timer;
    const QScreen* m_screen;

    void launch(const QScreen* screen, const QString& file) noexcept;
    void attach() const noexcept;
};

#endif // CMD_WALLPAPER_H