#pragma once

class InputStream;
class OutputStream;

class Socket {
public:
    long getRemoteSocketAddress();

    void setSoTimeout(int);
    void setTrafficClass(int);
    InputStream* getInputStream(bool);
    OutputStream* getOutputStream(bool);

    void close(bool);

    bool sub_71000EA668();
};
