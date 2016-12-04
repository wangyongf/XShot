#include "Portal.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Portal w;
    w.move((QApplication::desktop()->width() - w.width()) / 2,
        (QApplication::desktop()->height() - w.height()) / 2); //窗口居中显示
    w.show();

    return a.exec();
}
