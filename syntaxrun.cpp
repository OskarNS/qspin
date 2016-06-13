#include "syntaxrun.h"

SyntaxRun::SyntaxRun(QString _path, QString _ltl): SpinRun(_path , Syntax)
{
    path = _path;
    ltl = _ltl;
    errors = -1;

}

//TODO: Denne skal måske have en deletelater metode (destructor)
void SyntaxRun::start(){
    process = new QProcess();
    connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(checkSyntax()));
    setStatus("Checking syntax");
    tempPath = createTempPml();
    process->start(SPIN,QStringList() << "-a" << tempPath.replace(" ","\\ "));
}

QString SyntaxRun::createTempPml(){
    QFile::copy(path,path+".qspin");
    QFile tempFile(path+".qspin");

    if ( tempFile.open(QIODevice::Append | QIODevice::ReadWrite) )
    {
        QTextStream stream( &tempFile );
        stream << "\n " + ltl << endl;
    }
    return path+".qspin";
}


void SyntaxRun::checkSyntax(){
    QString str = process->readAllStandardOutput();
    QRegExp rxLine("spin: "+tempPath+":(\\d+),");
    QRegExp rxError("spin: "+tempPath+":\\d+, Error:(\\D*)");
    //QStringList lineNoList;
    //QStringList errorList;
    int pos = 0;
    while ((pos = rxError.indexIn(str , (rxLine.indexIn(str, pos)) )) != -1) {
        QString lineNo = rxLine.cap(1);
        QString error = rxError.cap(1);
        lineNoList << lineNo;
        errorList << error;
        pos += rxLine.matchedLength()+rxError.matchedLength();
    }
    errors = errorList.count();
    QFile::remove(tempPath);
    if (errors>0) {
        setStatus(QString::number(errors)+" errors found");
        emit hasErrors();
    } else {
        setStatus("No errors found :)");
        emit noErrors();
    }
    emit finished(this);

}
