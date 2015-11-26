#include <QApplication>
#include <QMainWindow>
#include <QDir>
#include "StandAloneMainController.h"
#include "persistence/Settings.h"
#include "gui/MainWindowStandalone.h"
#include "log/logging.h"
#include "Libs/SingleApplication/singleapplication.h"
#include "configurator.h"

#include "StandAloneMainController.h"

int main(int argc, char* args[] ){

//    QApplication app(argc, args);
//    StandalonePluginFinder finder;
//    finder.addFolderToScan("C:/VstPlugins");
//    finder.scan(QStringList());
//    return app.exec();


    QApplication::setApplicationName("Jamtaba 2");
    QApplication::setApplicationVersion(APP_VERSION);

    //start the configurator
    Configurator* configurator = Configurator::getInstance();
    if(!configurator->setUp(standalone)) qCWarning(jtConfigurator) << "JTBConfig->setUp() FAILED !" ;

    Persistence::Settings settings;
    settings.load();

    SingleApplication* application = new SingleApplication(argc, args);

    Controller::StandaloneMainController mainController(settings, (QApplication*)application);
    mainController.configureStyleSheet("jamtaba.css");
    mainController.start();
    if(mainController.isUsingNullAudioDriver()){
        QMessageBox::about(nullptr, "Fatal error!", "Jamtaba can't detect any audio device in your machine!");
    }
    MainWindowStandalone  mainWindow(&mainController);
    mainController.setMainWindow(&mainWindow);

    mainWindow.show();

    //The SingleApplication class implements a showUp() signal. You can bind to that signal to raise your application's
    //window when a new instance had been started.
    QObject::connect(application, SIGNAL(showUp()), &mainWindow, SLOT(raise()));

    return application->exec();

 }

//++++++++++++++++++++++++++++++++++




