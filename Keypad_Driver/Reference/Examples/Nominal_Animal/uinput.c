#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>

int send_event(int fd, __u16 type, __u16 code, __s32 value)
{
    struct input_event event;

    memset(&event, 0, sizeof(event));
    event.type = type;
    event.code = code;
    event.value = value;

    if (write(fd, &event, sizeof(event)) != sizeof(event)) {
        fprintf(stderr, "Error on send_event");
        return -1;
    }

    return 0;
}

int
main()
{
    int i,fd;
    struct uinput_user_dev device;
    memset(&device, 0, sizeof device);

    fd=open("/dev/input/uinput",O_WRONLY);
    strcpy(device.name,"test mouse");

    device.id.bustype=BUS_USB;
    device.id.vendor=1;
    device.id.product=1;
    device.id.version=1;

    for (i=0; i < ABS_MAX; i++) {
        device.absmax[i] = -1;
        device.absmin[i] = -1;
        device.absfuzz[i] = -1;
        device.absflat[i] = -1;
    }

    device.absmin[ABS_X]=0;
    device.absmax[ABS_X]=255;
    device.absfuzz[ABS_X]=0;
    device.absflat[ABS_X]=0;

    if (write(fd,&device,sizeof(device)) != sizeof(device))
    {
        fprintf(stderr, "error setup\n");
    }

    if (ioctl(fd,UI_SET_EVBIT,EV_KEY) < 0)
        fprintf(stderr, "error evbit key\n");

    if (ioctl(fd,UI_SET_KEYBIT, KEY_A) < 0)
        fprintf(stderr, "error evbit key\n");

    if (ioctl(fd,UI_SET_EVBIT,EV_REL) < 0)
            fprintf(stderr, "error evbit rel\n");

    for(i=REL_X;i<REL_MAX;i++)
        if (ioctl(fd,UI_SET_RELBIT,i) < 0)
            fprintf(stderr, "error setrelbit %d\n", i);

    if (ioctl(fd,UI_DEV_CREATE) < 0)
    {
        fprintf(stderr, "error create\n");
    }

    i = getchar();

    send_event(fd, EV_REL, REL_X, 2);
    send_event(fd, EV_SYN, SYN_REPORT, 0);
    send_event(fd, EV_KEY, KEY_A, 1);
    send_event(fd, EV_SYN, SYN_REPORT, 0);
    send_event(fd, EV_KEY, KEY_A, 0);
    send_event(fd, EV_SYN, SYN_REPORT, 0);

    i = getchar();

    printf("%d\n", i);

    close(fd);
}
