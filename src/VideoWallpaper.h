#ifndef VIDEO_WINDOW_H
#define VIDEO_WINDOW_H

#include <QDialog>
#include <QLayout>
#include "VideoView.h"
#include "AbstractWallpaper.h"

class VideoWallpaper : public QDialog, public AbstractWallpaper
{
    Q_OBJECT
public:
    VideoWallpaper() noexcept;
    ~VideoWallpaper();

    virtual void start(const QScreen* screen, const QString& file) noexcept override;
    virtual void stop() noexcept override;
    QScreen* screen() const noexcept;

private:
    QHBoxLayout* m_layout;
    VideoView* m_view;
};

#endif // VIDEO_WINDOW_H