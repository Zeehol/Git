
#include "netconn.h"
#include "lwip/opt.h" 
#include "lwip/sys.h"
#include "lwip/api.h"
#include <lwip/sockets.h>


#if (LWIP_NETCONN && (LWIP_SOCKET == 0))

static void client_netconn_thread(void *thread_param)
{
	struct netconn *client_conn;   //�½����ӽṹָ��
	int ret;
	ip4_addr_t ipaddr;             //������IP��ַ
	uint8_t send_buf[50] = "�ͻ��˲���";
	while(1)
	{
		client_conn = netconn_new(NETCONN_TCP);//����һ�����ӽṹ��ָ��ΪTCP����
		
		if (client_conn == NULL)
		{
			printf("create conn failed!\n");
			vTaskDelay(10);
			continue;
		}
		
		IP4_ADDR(&ipaddr,192,168,31,202);//���÷�����IP��ַ
		
		ret = netconn_connect(client_conn,&ipaddr,6001);//���ӿͻ��˵���������ָ���˿�Ϊ5001
		
		if (ret == -1)
		{
			printf("Connect failed!\n");
			netconn_close(client_conn);//����ʧ�ܣ��ر����ӽṹ������ѭ���峢����������
			vTaskDelay(10);
			continue;
		}

		printf("Connect to iperf server successful!\n");
		
		while(1)
		{

			ret = netconn_write(client_conn,send_buf,sizeof(send_buf),0);//�������ݵ�������

			vTaskDelay(1000);
		}
	}
}

static void server_netconn_thread(void *thread_param)
{
  struct netconn *conn, *newconn;
  err_t err;
  LWIP_UNUSED_ARG(thread_param);

  /* Create a new connection identifier. */
  /* Bind connection to well known port number 7. */
#if LWIP_IPV6
  conn = netconn_new(NETCONN_TCP_IPV6);
  netconn_bind(conn, IP6_ADDR_ANY, LOCAL_PORT);
#else /* LWIP_IPV6 */
  conn = netconn_new(NETCONN_TCP);//����һ�����ӽṹ��ָ��ΪTCP����
  netconn_bind(conn, IP_ADDR_ANY, LOCAL_PORT);//�󶨱��ص� IP ��ַ��˿ں�
#endif /* LWIP_IPV6 */
  LWIP_ERROR("tcpecho: invalid conn", (conn != NULL), return;);

  printf("���ض˿ں���%d\n\n",LOCAL_PORT);
  
  /* Tell connection to go into listening mode. */
  netconn_listen(conn);//�������״̬

  while (1) {

    /* Grab new connection. */
    err = netconn_accept(conn, &newconn);//�����ȴ��ͻ��˵���������
    /*printf("accepted new connection %p\n", newconn);*/
    /* Process the new connection. */
    if (err == ERR_OK) 
		{
      struct netbuf *buf;
      void *data;
      u16_t len;
      
      while ((err = netconn_recv(newconn, &buf)) == ERR_OK) //�ͻ������ӳɹ�
			{
        /*printf("Recved\n");*/
        do {
             netbuf_data(buf, &data, &len);//�����յ�������buf����д��data�У����ݳ��ȴ���len��
						 err = netconn_write(newconn, data, len, NETCONN_COPY);//�������ݵ��ͻ���
#if 0
							if (err != ERR_OK) 
							{
								printf("tcpecho: netconn_write: error \"%s\"\n", lwip_strerr(err));
							}
#endif
						} while (netbuf_next(buf) >= 0);//netbuf_next()�����ƶ�ָ��buf�������Ϊ0˵���������ݣ�����ѭ������
        netbuf_delete(buf);//���������ݺ����buf������
      }
      /*printf("Got EOF, looping\n");*/ 
      /* Close connection and discard connection identifier. */
      netconn_close(newconn);//�ر���ͻ��˵�����
      netconn_delete(newconn);//ɾ�����ӽṹ
    }
  }	
}

void client_init(void)
{
	sys_thread_new("client", client_netconn_thread, NULL, 512, 4);
}

void server_init(void)
{
	sys_thread_new("server", server_netconn_thread, NULL, 512, 4);
}

#endif /*(LWIP_NETCONN && (LWIP_SOCKET == 0)) */

#if (LWIP_NETCONN && LWIP_SOCKET)


static void client_socket_thread(void *thread_param)
{
	int client_socket = -1;
	struct sockaddr_in client_addr;
	uint8_t send_buf[]= "This is a TCP Client test...\n";
	
	while(1)
	{
		client_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (client_socket < 0)
		{
			printf("Socket error\n");
			vTaskDelay(10);
			continue;
		}
		
		client_addr.sin_family = AF_INET;
		client_addr.sin_port = htons(DEST_PORT);
		client_addr.sin_addr.s_addr = inet_addr("192.168.31.202");
		memset(&(client_addr.sin_zero), 0, sizeof(client_addr.sin_zero));//ʣ�� sin_zero�����8�ֽڱ���δ��
		
		if(connect(client_socket,(struct sockaddr *)&client_addr,sizeof(struct sockaddr)) == -1)
		{
			printf("Connect failed!\n");
			closesocket(client_socket);
			vTaskDelay(10);
			continue;			
		}
		
		printf("Connect to iperf server successful!\n");
		
		while (1)
		{
			if (write(client_socket,send_buf,sizeof(send_buf)) < 0)
			break;
			vTaskDelay(1000);
		}
		closesocket(client_socket);
	}
	
}

static void server_socket_thread(void *thread_param)
{
	
}

void client_init(void)
{
	sys_thread_new("client", client_socket_thread, NULL, 512, 4);
}

void server_init(void)
{
	sys_thread_new("server", server_socket_thread, NULL, 512, 4);
}

#endif /*(LWIP_NETCONN && LWIP_SOCKET) */

