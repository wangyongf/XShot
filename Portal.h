#ifndef PORTAL_H
#define PORTAL_H

#include "afqt/AfRegionSelector.h"
#include <QDesktopWidget>
#include <QFileDialog>
#include <QMainWindow>
#include <ui_Portal.h>

namespace Ui {
class Portal;
}

class Portal : public QMainWindow {
    Q_OBJECT

public:
    explicit Portal(QWidget* parent = 0);
    ~Portal();

private slots:
    int onCapture(); //获取截图
    int onSave(); //保存截图
    int onDelayedCapture(); //延迟截图！

protected:
    void changeEvent(QEvent* e);

private:
    Ui::Portal* ui;
};

#endif // PORTAL_H
