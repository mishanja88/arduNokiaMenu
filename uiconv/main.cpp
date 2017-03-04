#include <QCoreApplication>
#include <QDebug>
#include <QImage>
#include <QString>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if(a.arguments().count() < 2)
        qCritical() << "Usage:" <<
                       a.arguments().first()
                    << "file names";

    for(int i=1; i<a.arguments().count(); ++i)
    {
        QString fileName = a.arguments().at(i);
        QFileInfo info(fileName);
        if(!info.exists())
        {
            qDebug() << "No file:" << fileName;
            continue;
        }


        QImage image;
        if(!image.load(fileName))
        {
            qDebug() << "Invalid image:" << fileName;
            continue;
        }

        QString result = QString::fromUtf8("#define %1_HEIGHT %3\n#define %1_WIDTH %4\nstatic const unsigned char PROGMEM %2_bmp[] = {\n")
                .arg(info.baseName().toUpper())
                .arg(info.baseName().toLower())
                .arg(image.height())
                .arg(image.width());

        QString line;
        for(int y = 0; y < image.height(); ++y)
        {
            for(int x = 0; x < image.width(); ++x)
            {
                if(!(x & 0x7))
                {
                    if(!line.isEmpty())
                        line.append(", ");
                    line.append("B");
                }
                line.append((image.pixel(x,y) & 0xFFFFF) ? '1' : '0');
            }

            for(int i=0; i < image.width() % 8; ++i)
                line.append("0");
            line.append(",\n");

            result.append(line);
            //            qDebug() << result;
            line.clear();
        }
        result.append("};");

        QFile file(info.absolutePath() + '/' + info.baseName() + ".h");
        if(file.open(QFile::WriteOnly))
        {
            file.write(result.toUtf8());
            qDebug() << "Written to:" << file.fileName();
        }

        result.clear();
    }
    a.quit();
}

