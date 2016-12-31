/*!
*	Copyright (c) 2016 Mariano Dato <marianodato@gmail.com>
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
*	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
*	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
*	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
*	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
*	IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*	THE SOFTWARE.
*/

#include "Socket.h"

int read_socket (int fd, char *data, int length)
{
	int read_length = 0;
	int aux = 0;

	if ((fd == -1) || (data == NULL) || (length < 1))
		return -1;

	while (read_length < length)
	{
		aux = read (fd, data + read_length, length - read_length);
		if (aux > 0)
		{
			read_length = read_length + aux;
		}
		else
		{
			if (aux == 0) 
				return read_length;
			if (aux == -1)
			{
				switch (errno)
				{
					case EINTR:
					case EAGAIN:
						usleep (100);
						break;
					default:
						return -1;
				}
			}
		}
	}

	return read_length;
}

int write_socket (int fd, char *data, int length)
{
	int written_length = 0;
	int aux = 0;

	if ((fd == -1) || (data == NULL) || (length < 1))
		return -1;

	while (written_length < length)
	{
		aux = write (fd, data + written_length, length - written_length);
		if (aux > 0)
		{
			written_length = written_length + aux;
		}
		else
		{
			if (aux == 0)
				return written_length;
			else
				return -1;
		}
	}

	return written_length;
}