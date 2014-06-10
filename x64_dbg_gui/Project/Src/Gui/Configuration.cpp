#include "Configuration.h"

Configuration* Configuration::mPtr = NULL;


Configuration::Configuration()
{
    load("config.json");
    //Colors = new QMap<QString,QColor>();
    //Colors = QMap<QString,QColor>();
    mPtr = this;
}

Configuration *Configuration::instance()
{
    return mPtr;
}

void Configuration::load(QString filename){
    // load configuration file
    QFile configfile(filename);

    if (!configfile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open config file.");
        return ;
    }
    QByteArray saveData = configfile.readAll();
    Config = QJsonDocument(QJsonDocument::fromJson(saveData)).object();

    readColors();

}

void Configuration::readColors() {
    Colors.clear();

    QJsonArray ColorArray = Config["colors"].toArray();
    for (int idx = 0; idx < ColorArray.size(); ++idx) {
        QJsonArray colorObj = ColorArray[idx].toArray();
        Colors.insert(colorObj.at(0).toString(),QColor( colorObj.at(1).toString()));
    }
}

QList<QString> Configuration::ApiFingerprints(){
    QList<QString> files;
    QJsonArray APIArray = Config["apifingerprints"].toArray();
    for (int idx = 0; idx < APIArray.size(); ++idx) {
        QString filename = "data/"+APIArray.at(idx).toString()+".txt";
        QFile mFile(filename);
                if(mFile.open(QFile::ReadOnly | QFile::Text)){
                    files.append(APIArray.at(idx).toString());
                    mFile.close();
                }

    }
    return files;
}

const QColor Configuration::color(QString id) const
{
    if(Colors.contains(id))
        return Colors.constFind(id).value();
    else
        return Qt::black;
}
