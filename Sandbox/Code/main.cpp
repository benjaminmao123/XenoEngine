#include <Xeno.h>

using namespace std;

int main(int argc, char* argv[])
{
    Logger::Init();

    Application mApp;
    mApp.Run();

    return 0;
}