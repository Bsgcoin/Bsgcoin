Enabling SSL on original client daemon
======================================
By default, Bsgcoin allows JSON-RPC commands to be sent to http://localhost:36369
and accepts connections only from the localhost.

JSON-RPC Over SSL Setup
-----------------------
It can be configured to allow HTTPS connections.  You must follow the steps below
for this to work properly.

1. Setup a certificate and private key.  A self signed certificate will work.
    * cd ~/.bsgcoind
    * openssl genrsa -out server.pem 4096
    * openssl req -new -x509 -nodes -sha1 -days 3650 -key server.pem > server.cert
    (NOTE: you should NOT enter a passphrase)

2. Configure NeosCoin to use SSL
    * Stop your current bsgcoind or bsgcoin-qt
    * Edit the bsgcoin.conf and add
      rpcssl=1

3. Restart Bsgcoin to make these changes take effect.

4. Optionally you can test SSL functionality using the openssl s_client command
    * openssl s_client -connect localhost:15004