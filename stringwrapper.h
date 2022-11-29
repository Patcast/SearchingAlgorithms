#ifndef STRINGWRAPPER_H
#define STRINGWRAPPER_H

#include <QObject>

class StringWrapper : public QObject
{
   Q_OBJECT
public:
    explicit StringWrapper(QObject *parent = nullptr);

    void SetString(const QString& str);

private:
    QString m_str;

signals:
    void TextChanged(QString str);

public slots:
};

void StringWrapper::SetString(const QString &str)
{
    if (str != m_str) {
        m_str = str;
        emit TextChanged(m_str);
    }
}

#endif // STRINGWRAPPER_H
