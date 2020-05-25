#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>


const unsigned char myBitmap []=
{
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f,
    0x1f, 0x9f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x9f, 0x1f, 0x1f, 0x3f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x03, 0x03, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x01, 0x00, 0xf0, 0xfc, 0xfe,
    0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff,
    0xff, 0x3f, 0x1f, 0x0f, 0x87, 0xc7, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xc7, 0x07, 0x0f, 0x1f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x1f, 0x0f, 0x87, 0xc7, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3, 0xe3,
    0xc7, 0x07, 0x0f, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x0f, 0x07, 0xc7, 0xe3, 0xf3, 0xf3,
    0xe3, 0xe3, 0xc3, 0x03, 0x03, 0xf3, 0xf3, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff,
    0xff, 0xff, 0x3f, 0x1f, 0x0f, 0xc7, 0xe7, 0xe3, 0xf3, 0xf3, 0xf3, 0xe3, 0xe7, 0x87, 0x0f, 0x1f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xc0, 0x00, 0x07, 0x1f, 0x3f,
    0x7f, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x7e, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
    0xff, 0x80, 0x00, 0x00, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x00, 0x00,
    0xe0, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x7f, 0x1f, 0x00, 0x00, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x08, 0x00, 0x60, 0xe7, 0xc7, 0xcf, 0xcf,
    0xc7, 0xc7, 0xe3, 0xe0, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff,
    0xff, 0xff, 0x80, 0x00, 0x00, 0x39, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf9, 0xf8, 0xf8,
    0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc,
    0xfc, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8,
    0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0x03, 0x00, 0x38, 0x38, 0x7c, 0x7c, 0x7c,
    0x7c, 0x38, 0x38, 0x38, 0x01, 0x81, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xf8, 0xf8, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xf8, 0xf8, 0xf9, 0xf9, 0xf9, 0xf8, 0xf8, 0xfc, 0xfc,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe,
    0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

const unsigned char init_display[] =
{
    0xA8,0x3F, 0xD3, 0x00, 0x40, 0xA1, 0xC8,0xDA,0x32,0xA4, 0xA6, 0xD5, 0x80, 0x8D, 0x14, 0x20, 0x20
};

const unsigned char display_on[] =
{
    0xAF
};

const unsigned char display_off[] =
{
    0xAE
};


const unsigned char reset_cursor[] =
{
    0x21, 0x00, 0x7F, 0x22, 0x00, 0x07
};

int file;
int daddress = 0x40;
int count;
int i2cbus = 1;
char filename[20];
int address = 0x3C;

void connect()
{
    if (i2cbus > 0)
        {
            int size = sprintf(filename, "/dev/i2c/%d", i2cbus);
            filename[size - 1] = '\0';
            file = open(filename, O_RDWR);

            if (file < 0 && (errno == ENOENT || errno == ENOTDIR))
                {
                    sprintf(filename, "/dev/i2c-%d", i2cbus);
                    file = open(filename, O_RDWR);
                }

            if (file < 0 )
                {
                    if (errno == ENOENT)
                        {
                            fprintf(stderr, "Error: Could not open file "
                                    "`/dev/i2c-%d' or `/dev/i2c/%d': %s\n",
                                    i2cbus, i2cbus, strerror(ENOENT));
                        }
                    else
                        {
                            fprintf(stderr, "Error: Could not open file "
                                    "`%s': %s\n", filename, strerror(errno));
                            if (errno == EACCES)
                                fprintf(stderr, "Run as root?\n");
                        }
                    return 1;
                }
            printf("filename: %s",filename);

            ioctl(file,I2C_SLAVE, address);
        }
}

void func_display_off()
{
    connect();
    for (count = 0; count <sizeof(display_off); count++)
        {

            i2c_smbus_write_byte_data(file, 0x00, display_off[count]);
        }

    close(file);
}


void func_display_init()
{
    connect();
    for (count = 0; count <sizeof(init_display); count++)
        {

            i2c_smbus_write_byte_data(file, 0x00, init_display[count]);
        }

    close(file);
}

void func_display_on()
{
    connect();
    for (count = 0; count <sizeof(display_on); count++)
        {

            i2c_smbus_write_byte_data(file, 0x00, display_on[count]);
        }
    close(file);
}

void func_reset_cursor()
{
    connect();
    for (count = 0; count <sizeof(reset_cursor); count++)
        {

            i2c_smbus_write_byte_data(file, 0x00, reset_cursor[count]);
        }
    close(file);
}

void func_draw_Google()
{
    connect();
    for (count = 0; count <sizeof(myBitmap); count++)
        {

            i2c_smbus_write_byte_data(file, daddress, myBitmap[count]);
        }
    close(file);
}

int main()
{
    func_display_off();
    func_display_init();
    func_display_on();
    func_reset_cursor();
    func_draw_Google();

    return 0;
}