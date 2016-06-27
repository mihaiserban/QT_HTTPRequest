# QT_HTTPRequest
Shared library containing a simple get/post request implementation using c++11 lambdas as callback function.

    //create a network access manager instance
    QNetworkAccessManager *m_manager = new QNetworkAccessManager(this);
    
    HTTPRequest *request = new HTTPRequest(NULL,m_manager); //or null network acess manager instance, http request can create it's own access manager
    request->setHandlerFunc([=] (QNetworkReply *reply) {
        if (reply) {
            QByteArray data = reply->readAll();
            QString string_data = QString::fromLatin1(data.data());
        }

        //delete captured request
        request->deleteLater();
    });

    QString url = "http://www.google.com";
    request->get(url);
