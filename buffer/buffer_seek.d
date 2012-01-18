#include "buffer.h"

void buffer_seek(buffer *s,unsigned int len)
{
	s->n += len;
	s->p -= len;
}
