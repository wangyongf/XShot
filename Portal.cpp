#include "Portal.h"

Portal::Portal(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Portal())
{
    ui->setupUi(this);

    connect(ui->actionCapture, &QAction::triggered, this, &Portal::onCapture);
    connect(ui->actionSave, &QAction::triggered, this, &Portal::onSave);
}

Portal::~Portal()
{
    delete ui;
}

int Portal::onCapture()
{
    // 令本窗口隐藏
    this->hide();

    // 隐藏本窗口需要一定时间，故延时一段时间后才开始截图
    QTimer::singleShot(300, this, SLOT(onDelayedCapture()));

    return 0;
}

int Portal::onSave()
{
    QPixmap picture = ui->frame->pixmap();
    if (picture.isNull())
        return 0;

    // 保存到目标文件
    QString filename = QFileDialog::getSaveFileName(this,
        "Save Picture", "", "Image File(*.jpg)");
    if (filename.length() > 0) {
        picture.save(filename + ".jpg");
    }
    return 0;
}

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
