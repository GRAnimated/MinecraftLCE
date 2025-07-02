#pragma once

#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.Core/io/OutputStream.h"

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
        virtual ~SocketOutputStreamLocal() override;
        virtual void write(unsigned int) override;
        virtual void write(arrayWithLength<unsigned char>) override;
        virtual void write(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
        virtual void close() override;
        virtual void flush() override;
        virtual void writeWithFlags(arrayWithLength<unsigned char>, unsigned int, unsigned int, int);

        int field_8;
        int field_C;
    };

    class SocketOutputStreamNetwork : public OutputStream {
    public:
        SocketOutputStreamNetwork(Socket*, int);
        virtual ~SocketOutputStreamNetwork() override;
        virtual void write(unsigned int) override;
        virtual void write(arrayWithLength<unsigned char>) override;
        virtual void write(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
        virtual void close() override;
        virtual void flush() override;
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
