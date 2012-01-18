#ifndef DEFINE_H
#define DEFINE_H

#define OUTS(x) buffer_puts(buffer_1, x);
#define OUTB(x) buffer_put(buffer_1, x.s, x.len);
#define OUTSB(x, len) buffer_put(buffer_1, x, len);
#define OUTULONG(x) buffer_putulong(buffer_1, x);
#define OUTLONG(x) buffer_putlong(buffer_1, x);
#define OUTF()  buffer_flush(buffer_1);
#define OUTNF() buffer_putnlflush(buffer_1);
#define OUTERROR() buffer_puterror(buffer_1);


#define ERRS(x) buffer_puts(buffer_2, x);
#define ERRB(x) buffer_put(buffer_2, x.s, x.len);
#define ERRULONG(x) buffer_putulong(buffer_2, x);
#define ERRLONG(x) buffer_putlong(buffer_2, x);
#define ERRSB(x,len) buffer_put(buffer_2, x, len);
#define ERRF() buffer_flush(buffer_2);
#define ERRNF() buffer_putnlflush(buffer_2);
#define ERRERROR() buffer_puterror(buffer_2);

#endif
