#ifndef LCDWIDGET_H
#define LCDWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCore/QTimer>
#include <QtCore/QMutex>
#include <chrono>

#include "../../core/lcd.h"

class LCDWidget : public QWidget {
  Q_OBJECT

public:
    explicit LCDWidget(QWidget *p = Q_NULLPTR);
    QImage getImage();
    void setMain();
    void draw();
    void setFrameskip(int value);
    void setMode(bool state);

signals:
    void updateLcd(double emuFps);

public slots:
    double refresh();

protected:
    virtual void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
    virtual void dropEvent(QDropEvent*) Q_DECL_OVERRIDE;
    virtual void dragEnterEvent(QDragEnterEvent*) Q_DECL_OVERRIDE;
    virtual void dragLeaveEvent(QDragLeaveEvent*) Q_DECL_OVERRIDE;
    virtual void dragMoveEvent(QDragMoveEvent*) Q_DECL_OVERRIDE;

signals:
    void sendROM(const QString& romPath);

private:
    enum lcd_side {
        LCD_LEFT = 0,
        LCD_RIGHT
    };

    enum array_info {
        ARRAY_SIZE = 50
    };

    unsigned int sideDrag;
    bool drag = false;
    QRect left, right;
    QImage image;
    QMutex mutex;

    // for dragable roms
    QString dragROM;
    bool isSendingROM;

    unsigned int array[ARRAY_SIZE];
    int index = 0;
    bool spiMode;
    int skip = 0;
    int frameskip = 0;
};

#endif
