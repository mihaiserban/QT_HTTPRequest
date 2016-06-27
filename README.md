# QT_HTTPRequest
QT HTTP get/post request implementation using c++11 lambdas as callback function

  HTTPRequest *request = new HTTPRequest(NULL,m_manager);
  request->setHandlerFunc([=] (const QByteArray &data) {
    if (data.size()) {
      QString string_data = QString::fromLatin1(data.data());
    }

    //delete captured request
    request->deleteLater();
  });

  QString url = "http://www.google.com";
  request->get(url);
