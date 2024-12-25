#include "slcan/slcan_port.h"



int slcan_clock_gettime (struct timespec *tp)
{
    return -1;//clock_gettime(CLOCK_MONOTONIC, tp);
}


// Преобразует тип последовательного порта в slcan_serial_handle_t.
#define SERIAL_TO_HANDLE(S) ((slcan_serial_handle_t)(long)(S))
// Преобразует slcan_serial_handle_t в тип последовательного порта.
#define HANDLE_TO_SERIAL(H) ((int)(long)(H))


int slcan_serial_open(const char* serial_port_name, slcan_serial_handle_t* serial_port)
{
    return SLCAN_IO_FAIL;
}

int slcan_serial_configure(slcan_serial_handle_t serial_port, const slcan_port_conf_t* conf)
{
    return SLCAN_IO_FAIL;
}

void slcan_serial_close(slcan_serial_handle_t serial_port)
{
    // HANDLE_TO_SERIAL(serial_port);
}

int slcan_serial_read(slcan_serial_handle_t serial_port, void* data, size_t data_size)
{
    return SLCAN_IO_FAIL;
}

int slcan_serial_write(slcan_serial_handle_t serial_port, const void* data, size_t data_size)
{
    return SLCAN_IO_FAIL;
}

int slcan_serial_flush(slcan_serial_handle_t serial_port)
{
    return SLCAN_IO_FAIL;
}

// POLLIN
// POLLPRI
// POLLOUT
// POLLERR
// POLLHUP
// POLLNVAL
int slcan_serial_poll(slcan_serial_handle_t serial_port, int events, int* revents, int timeout)
{
    return SLCAN_IO_FAIL;
}

int slcan_serial_nbytes(slcan_serial_handle_t serial_port, size_t* size)
{
    return SLCAN_IO_FAIL;
}
