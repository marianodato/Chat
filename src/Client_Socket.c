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

#include "Client_Socket.h"

int open_inet_connection ()
{
	struct sockaddr_in address;
	int descriptor;

	address.sin_family = AF_INET;
	address.sin_port = htons(15556);
	inet_pton(AF_INET, "192.168.1.249", &address.sin_addr);
	
	descriptor = socket (AF_INET, SOCK_STREAM, 0);
	if (descriptor == -1)
		return -1;

	if (connect (
			descriptor, 
			(struct sockaddr *)&address, 
			sizeof (address)) == -1)
	{
		return -1;
	}

	return descriptor;
}
