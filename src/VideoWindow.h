#ifndef VIDEO_WINDOW_H
#define VIDEO_WINDOW_H

#include <QDialog>
#include <QLayout>
#include "VideoView.h"

class VideoWindow : public QDialog
{
    Q_OBJECT
public:
    VideoWindow(QScreen* screen, QWidget* parent=nullptr) noexcept;
    ~VideoWindow();

    void play(const QString& file) noexcept;
    void stop() noexcept;
    QScreen* screen() const noexcept;

private:
    QHBoxLayout* m_layout;
    VideoView* m_view;
    QScreen* m_screen;
};

#endif // VIDEO_WINDOW_H