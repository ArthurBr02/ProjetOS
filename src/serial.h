void serial_configure_baud_rate(unsigned short com, unsigned short divisor);
void serial_configure_line(unsigned short com);
void serial_configure_buffers(unsigned short com);
void serial_configure_modem(unsigned short com);
void serial_write(char *buf, unsigned int len);