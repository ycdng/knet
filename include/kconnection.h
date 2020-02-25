#pragma once
#include "knetfwd.h"


namespace knet
{
    struct buffer
    {
        const void* data;
        size_t size;

        buffer() noexcept : data(nullptr), size(0) {}
        buffer(const void* data_, size_t size_) noexcept : data(data_), size(size_) {}
    };

    class socket;
    class connection
    {
    public:
        virtual ~connection() = default;

        virtual void on_connected() {}
        virtual size_t on_recv_data(char* data, size_t size) = 0;
        virtual void on_disconnect() {}

        bool send_data(buffer* buf, size_t num);
        void disconnect();

    protected:
        virtual void on_attach_socket(rawsocket_t rawsocket) {}

    private:
        friend class socket;
        socket* _socket = nullptr;
    };

    class connection_factory
    {
    public:
        virtual ~connection_factory() = default;

        virtual connection* create_connection() = 0;
        virtual void destroy_connection(connection* conn) { delete conn; }
    };
}
