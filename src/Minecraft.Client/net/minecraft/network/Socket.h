#pragma once

#include "java/io/OutputStream.h"
#include "net/minecraft/world/ArrayWithLength.h"

class InputStream;

class Socket {
public:
    class SocketOutputStream : public OutputStream {
    public:
        SocketOutputStream();
        virtual void writeWithFlags(arrayWithLength<unsigned char>, unsigned int, unsigned int, int);
    };

    class SocketOutputStreamLocal : public OutputStream {
    public:
        SocketOutputStreamLocal(int);
        ~SocketOutputStreamLocal() override;
        void write(unsigned int) override;
        void write(arrayWithLength<unsigned char>) override;
        void write(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
        void close() override;
        void flush() override;
        virtual void writeWithFlags(arrayWithLength<unsigned char>, unsigned int, unsigned int, int);

        int field_8;
        int field_C;
    };

    class SocketOutputStreamNetwork : public OutputStream {
    public:
        SocketOutputStreamNetwork(Socket*, int);
        ~SocketOutputStreamNetwork() override;
        void write(unsigned int) override;
        void write(arrayWithLength<unsigned char>) override;
        void write(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
        void close() override;
        void flush() override;
        virtual void writeWithFlags(arrayWithLength<unsigned char>, unsigned int, unsigned int, int);

        int field_8;
        int field_C;
        Socket* mSocket;
    };

    long getRemoteSocketAddress();

    void setSoTimeout(int);
    void setTrafficClass(int);
    InputStream* getInputStream(bool);
    SocketOutputStream* getOutputStream(bool);

    void close(bool);

    bool sub_71000EA668();
};
