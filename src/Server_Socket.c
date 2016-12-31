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

#include "Server_Socket.h"

int accept_client_connection (int descriptor)
{
	socklen_t client_length;
	struct sockaddr client;
	int child;

	client_length = sizeof (client);
	child = accept (descriptor, &client, &client_length);
	if (child == -1)
		return -1;

	return child;
}

int open_inet_socket (char *service)
{
	struct sockaddr_in address;
	struct servent *port;
	int descriptor;

	descriptor = socket (AF_INET, SOCK_STREAM, 0);
	if (descriptor == -1)
	 	return -1;

	port = getservbyname (service, "tcp");
	if (port == NULL)
		return -1;

	address.sin_family = AF_INET;
	address.sin_port = port->s_port;
	address.sin_addr.s_addr =INADDR_ANY;
	if (bind (
			descriptor, 
			(struct sockaddr *)&address, 
			sizeof (address)) == -1)
	{
		close (descriptor);
		return -1;
	}

	if (listen (descriptor, 1) == -1)
	{
		close (descriptor);
		return -1;
	}

	return descriptor;
}
