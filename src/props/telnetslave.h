// -=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-
// FGx FlightGear Launcher // telnetslave.h
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-
// (c) 2010-2012
// Yves Sablonier, Pete Morgan
// Geoff McLane
// GNU GPLv2, see main.cpp and shipped licence.txt for further information

#ifndef TELNETSLAVE_H
#define TELNETSLAVE_H

#include <QObject>
#include <QString>
#include <QQueue>
#include <QTcpSocket>

/*
void	connected ()
void	disconnected ()
void	error ( QAbstractSocket::SocketError socketError )
void	hostFound ()
void	proxyAuthenticationRequired ( const QNetworkProxy & proxy, QAuthenticator * authenticator )
void	stateChanged ( QAbstractSocket::SocketState socketState )
*/

class TelnetSlave : public QObject
{
Q_OBJECT
public:
    explicit TelnetSlave(QObject *parent = 0);

    QString hostAddress;
    int port;
	QQueue<QString> que;

    QString current_node_path;

    bool in_request;

	void telnet_connect(QString address, int port);
	void telnet_disconnect();
	void get_node(QString path);
	void set_property(QString path, QString value);

	void add_que(QString node);

private:
    QTcpSocket *socket;

signals:
    void telnet_error(QAbstractSocket::SocketError, QString);
    void telnet_connected(bool);

	void props_folder(QString, QString);
	void props_value(QString, QString, QString, QString);
    //void telnet_data(Q);

public slots:
    void on_connected();
    void on_ready_read();
    void on_disconnected();
    void on_error(QAbstractSocket::SocketError);
    void on_host_found();
    void on_state_changed(QAbstractSocket::SocketState);
};

#endif // TELNETSLAVE_H
