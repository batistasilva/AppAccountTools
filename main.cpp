#include "src/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);

//     QTranslator translator;
//     const QStringList uiLanguages = QLocale::system().uiLanguages();
//     for (const QString &locale : uiLanguages) {
//         const QString baseName = "App_"+ QLocale(locale).name();
//         if (translator.load(":/i18n/" + baseName)) {
//             a.installTranslator(&translator);
//             break;
//         }
//     }

//     MainWindow w;
//     w.show();

//     return a.exec();
// }

#include "DBUtil.h"
#include "MngLogFile.h"
#include "ShowMsg.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    Q_INIT_RESOURCE(images);

    QApplication app(argc, argv);
    //
    //app.setStyle("QWindowsStyle");
    //app.setStyle("QCDEStyle");
    //app.setStyle("QPlastiqueStyle");
    //app.setStyle("QGtkStyle");
    //app.setStyle("QMotifStyle");
    //app.setStyle("QCleanlooksStyle");
    //
    MainWindow mainWin;
    mainWin.show();
    mainWin.setMinimumSize(1024, 700);

   // mainWin.setFixedSize(1024, 768);

    // DBUtil * mdbc;
    // ShowMsg * m_msg = new ShowMsg();
    // mdbc = new DBUtil();
    // bool result = mdbc->openConnInPGree();

    // if (result) {
    //     m_msg->ShowMessage("Conexao com PostgreSql feita com sucesso!! ", COLOR_BLUE, COLOR_PINK);
    // }


    // QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    // db.setHostName("localhost");
    // db.setDatabaseName("customdb");
    // db.setUserName("admin");
    // db.setPassword("admin");
    // bool ok = db.open();
    // if (ok) {
    //     m_msg->ShowMessage("Conexao com PostgreSql feita com sucesso!! ", COLOR_BLUE, COLOR_PINK);
    // }else{
    //     m_msg->ShowMessage("Error In Connection PostgreSql: "+ QString(db.lastError().text()), COLOR_BLUE, COLOR_RED);
    // }

    return app.exec();
}
