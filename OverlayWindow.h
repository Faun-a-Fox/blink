#ifndef BLINKOVERLAY_H
#define BLINKOVERLAY_H

#include <QWidget>

class OverlayWindow : public QWidget
{
    Q_OBJECT
public:
    explicit OverlayWindow(QWidget *parent = 0);
    explicit OverlayWindow(const QColor color, QWidget *parent = 0);


    QColor color() const;
    qreal opacity() const;

public slots:
    void setColor(const QColor color);
    void setOpacity(const qreal opacity);

};

#endif // BLINKOVERLAY_H
