#ifndef BROWSREXCEPTION_H
#define BROWSREXCEPTION_H

#include <QException>

class BrowsRException : public QException
{
public:
    BrowsRException(QString);
    void raise() const override { throw *this; }
    BrowsRException *clone() const override { return new BrowsRException(*this); }
    QString Message();

private:
    QString sMsg;
};

#endif // BROWSREXCEPTION_H
