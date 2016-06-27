#include "httprequest.h"
#include <QStringList>
#include <QString>
#include <QCoreApplication>
#include <QDebug>
#include <QUrlQuery>
#include <QHttpMultiPart>

HTTPRequest::HTTPRequest(QObject *parent, QNetworkAccessManager *networkManager) : QObject(parent)
{
    if (!networkManager) {
        m_manager = new QNetworkAccessManager(this);
    }
    else {
        m_manager = networkManager;
    }
}

HTTPRequest::~HTTPRequest()
{

}

void HTTPRequest::post(const QString &url, QHttpMultiPart *multipart)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    QNetworkReply *reply = m_manager->post(request, multipart);
    multipart->setParent(reply);

    connect(reply, SIGNAL(finished()), this, SLOT(onRequestCompleted()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onRequestFailed(QNetworkReply::NetworkError)));
}

QHttpPart part_parameter(QString key, QString value) {
    QHttpPart part;
    part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + key + "\""));
    part.setBody(value.toLatin1());
    return part;
}

void HTTPRequest::post(const QString &url, QMap<QString, QString> &postData)
{   
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    foreach (QString key, postData.keys()) {
        multiPart->append(part_parameter(key, postData[key]));
    }
    return post(url,multiPart);
}

void HTTPRequest::get(const QString &url)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    QNetworkReply *reply = m_manager->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(onRequestCompleted()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onRequestFailed(QNetworkReply::NetworkError)));
}

void HTTPRequest::onRequestCompleted() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (_handler_func)
    {
        _handler_func(reply);
    }
}

void HTTPRequest::onRequestFailed(QNetworkReply::NetworkError error) {
    if (_handler_func)
    {
        _handler_func(NULL);
    }
}
