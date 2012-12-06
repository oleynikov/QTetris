#include <QApplication>
#include <WindowMain.h>

int main(int argc, char* argv[])
{

    QApplication app(argc,argv);

    WindowMain windowMain;
    windowMain.show();

    return app.exec();

}

