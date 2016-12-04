#include "Portal.h"

#include <QMessageBox>

Portal::Portal(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Portal())
{
    ui->setupUi(this);

    connect(ui->actionDesktop, &QAction::triggered, this, &Portal::onDesktopCapture);
    connect(ui->actionSave, &QAction::triggered, this, &Portal::onSave);
    connect(ui->actionWindow, &QAction::triggered, this, &Portal::onWindowCapture);
    connect(ui->actionAbout, &QAction::triggered, this, &Portal::about);
    connect(ui->actionAboutQt, &QAction::triggered, this, &Portal::aboutQt);
    connect(ui->actionExit, &QAction::triggered, this, &Portal::onExit);
}

Portal::~Portal()
{
    delete ui;
}

/**
 * @brief 截取桌面
 * @return
 */
int Portal::onDesktopCapture()
{
    // 令本窗口隐藏
    this->hide();

    // 隐藏本窗口需要一定时间，故延时一段时间后才开始截图
    QTimer::singleShot(300, this, SLOT(onDelayedCapture()));

    return 0;
}

/**
 * @brief 截取窗口
 * @return
 */
int Portal::onWindowCapture()
{
    // TODO: 完成截取窗口的工作！
    QMessageBox::warning(this, "截取窗口功能", "此功能正在规划中，暂不可用^_^",
        QMessageBox::Ok, QMessageBox::Ok);

    return 0;
}

/**
 * @brief 保存图片
 * @return
 */
int Portal::onSave()
{
    QPixmap picture = ui->frame->pixmap();
    if (picture.isNull()) {
        QMessageBox::warning(this, "图片为空", "图片为空哦，先截个图吧+_+",
            QMessageBox::Ok, QMessageBox::Ok);
        return 0;
    }

    // 保存到目标文件
    QString extension;
    QString filename = QFileDialog::getSaveFileName(this,
        "保存图像", "", "JPEG (*.jpg);;PNG ( *.png);;BMP (*.bmp)", &extension);
    if (filename.length() > 0) {
        if (extension.left(4) == "JPEG") {
            filename += ".jpg";
        } else if (extension.left(3) == "PNG") {
            filename += ".png";
        } else if (extension.left(3) == "BMP") {
            filename += ".bmp";
        }
        picture.save(filename);
    }

    return 0;
}

/**
 * @brief 延迟截图
 * @return
 */
int Portal::onDelayedCapture()
{
    QScreen* screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(QApplication::desktop()->winId());
    AfRegionSelector dlg(pixmap, this);
    if (QDialog::Accepted == dlg.exec()) {
        QPixmap region = pixmap.copy(dlg.selectRegion);
        ui->frame->display(region);
    }

    this->showNormal();
    return 0;
}

/**
 * @brief 关于本程序
 * @return
 */
int Portal::about()
{
    // TODO: 完成关于本程序部分！
    QMessageBox::information(this, "关于 XShot", "XShot，好用易用的跨平台小工具",
        QMessageBox::Ok, QMessageBox::Ok);

    return 0;
}

/**
 * @brief 关于Qt
 * @return
 */
int Portal::aboutQt()
{
    QMessageBox::aboutQt(this, "关于Qt");
    return 0;
}

/**
 * @brief 关闭程序
 * @return
 */
int Portal::onExit()
{
    QApplication::quit();
    return 0;
}

/**
 * @brief 用于程序国际化
 * @param e
 */
void Portal::changeEvent(QEvent* e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
