#ifndef ABSTRACT_WALLPAPER_H
#define ABSTRACT_WALLPAPER_H

#include <QString>

class AbstractWallpaper
{
public:
    virtual ~AbstractWallpaper() = default;
    virtual void start(const QString& file) = 0;
    virtual void stop() = 0;
};

#endif // ABSTRACT_WALLPAPER_H