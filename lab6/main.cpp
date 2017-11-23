#include <libusb-1.0/libusb.h>
#include <stdio.h>

int main()
{
    libusb_device **devs; //  devices list
    libusb_context *ctx = NULL; // libusb session context
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
    printf("Total devices: %d\n", cnt);
    printf("Class Vendor_ID Product_ID:\n");
    for (size_t i = 0; i < cnt; i++)
    {                     
        libusb_device_descriptor desc;    // дескриптор устройства
        res = libusb_get_device_descriptor(devs[i], &desc);
        if (res < 0)
        {
            fprintf(stderr,
                    "Ошибка: дескриптор устройства не получен, код: %d.\n", res);
            return;
        }
        printf("%.5d %.9d %.10d\n",
            (int)desc.bDeviceClass,
            desc.idVendor,
            desc.idProduct
        );
    }
    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);
     return 0;
}