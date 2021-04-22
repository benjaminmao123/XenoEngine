#include "XenoEditor.h"
#include "MainEditor/EditorWindow.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //XenoEditor editor({ "XenoEditor" });
    //editor.Run();

    EditorWindow w;
    w.show();
    return a.exec();
}