#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    libusb_device **devs;       //  devices list
    libusb_context *ctx = NULL; // libusb session context
    unsigned char *buf = (unsigned char *)malloc(256);
    int res;
    res = libusb_init(&ctx);
    if (res < 0)
    {
        fprintf(stderr, "Ошибка: инициализация не выполнена, код: %d.\n", res);
        return 1;
    }
    ssize_t cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0)
    {
        fprintf(stderr,
                "Ошибка: список USB устройств не получен.\n");
        return 1;
    }
    printf("Total devices: %ld\n", cnt);
    printf("Class Vendor_ID Product_ID Serial_Number:\n");
    for (size_t i = 0; i < cnt; i++)
    {
        libusb_device_descriptor desc;
        res = libusb_get_device_descriptor(devs[i], &desc);
        if (res < 0)
        {
            fprintf(stderr,
                    "Ошибка: дескриптор устройства не получен, код: %d.\n", res);
            return 1;
        }
        libusb_device_handle *devHandle = libusb_open_device_with_vid_pid(ctx, desc.idVendor, desc.idProduct);
        libusb_get_string_descriptor_ascii(devHandle, desc.iSerialNumber, buf, 256);
        printf("%.5d %.9d %.10d %s\n",
               (int)desc.bDeviceClass,
               desc.idVendor,
               desc.idProduct,
               buf
               );
    }
    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);
    free(buf);
    return 0;
}