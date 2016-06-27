#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "httprequest_global.h"
#include <QObject>

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

class HTTPREQUESTSHARED_EXPORT HTTPRequest : public QObject
{
    Q_OBJECT
public:
    explicit HTTPRequest(QObject *parent = 0, QNetworkAccessManager *networkManager = 0);

    ~HTTPRequest();

    void post(const QString &url, QHttpMultiPart *multipart);
    void post(const QString &url, QMap<QString, QString> &postData);
    void get(const QString &url);

    void setHandlerFunc (std::function<void (QNetworkReply *reply)> handler_func)
    {
        _handler_func = handler_func;
    }
signals:

public slots:

private slots:
    void onRequestCompleted();
    void onRequestFailed(QNetworkReply::NetworkError error);

private:
    std::function<void (QNetworkReply *reply)> _handler_func;
    QNetworkAccessManager *m_manager;
};


#endif // HTTPREQUEST_H

