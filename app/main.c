#include <stdlib.h>
#include <stdint.h>
#include "pico_defines.h"
#include "pico_stack.h"
#include "pico_ipv4.h"
#include "pico_bsd_sockets.h"
#include "bsp.h"
#include <stdio.h>
#include <string.h>
#include "fossa.h"

extern struct pico_device * pico_eth_create(char *name, uint8_t *mac);

static const char *s_http_port = "80";
static const char *s_https_port = "443";
static struct ns_serve_http_opts s_http_server_opts;

static struct ns_mgr mgr;
static struct ns_connection *nc;


static void handle_sum_call(struct ns_connection *nc, struct http_message *hm) {
  char n1[50], n2[50];
  long result;

  /* Get form variables */
  ns_get_http_var(&hm->query_string, "n1", n1, sizeof(n1));
  ns_get_http_var(&hm->query_string, "n2", n2, sizeof(n2));

  /* Send headers */
  ns_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

  /* Compute the result and send it back as a JSON object */
  printf("%s + %s\n",n1, n2);
  result = strtol(n1, NULL, 10) + strtol(n2, NULL, 10);
  ns_printf_http_chunk(nc, "{ \"result\": %ld }", result);
  ns_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
}


static void handle_uptime_call(struct ns_connection *nc, struct http_message *hm) {
  /* Send headers */
  ns_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

  /* Compute the result and send it back as a JSON object */
  ns_printf_http_chunk(nc, "{ \"uptime\": %d.%03d s}", PICO_TIME(), PICO_TIME_MS()%1000);
  ns_send_http_chunk(nc, "", 0);  /* Send empty chunk, the end of response */
}


static void ev_handler(struct ns_connection *nc, int ev, void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;

  switch (ev) {
    case NS_HTTP_REQUEST:
      if (ns_vcmp(&hm->uri, "/api/v1/sum") == 0) {
        handle_sum_call(nc, hm);                    /* Handle RESTful call */
      } else if (ns_vcmp(&hm->uri, "/api/v1/uptime") == 0) {
        handle_uptime_call(nc, hm);                 /* Handle RESTful call */
      } else {
        ns_serve_http(nc, hm, s_http_server_opts);  /* Serve static content */
      }
      break;
    default:
      break;
  }
}


static void start_fossa(void) {
    const char * port;

    ns_mgr_init(&mgr, NULL);

    port = s_http_port;
    nc = ns_bind(&mgr, port, ev_handler);

    ns_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = ".";

    printf("RESTful server starter on port %s\n", port);

}


static void picoTickTask(void *pvParameters) {
    uint8_t mac[6] = {0x00,0x00,0x00,0x12,0x34,0x56};
    char ipaddr[]="192.168.2.150";
    struct pico_ip4 my_eth_addr, netmask;
    struct pico_device *pico_dev_eth;

    pico_stack_init();              /* initialize picoTCP library     */
    pico_bsd_init();                /* initialize picotcp-BSD library */

    pico_dev_eth = (struct pico_device *) pico_eth_create("eth", mac);
    if (!pico_dev_eth)
    {
        printf("Failed to create network device.\n");
        while (1);
    }

    pico_string_to_ipv4(ipaddr, &my_eth_addr.addr);
    pico_string_to_ipv4("255.255.255.0", &netmask.addr);
    pico_ipv4_link_add(pico_dev_eth, my_eth_addr, netmask);
    printf("Server has ip: %s\n", ipaddr);

    start_fossa();

    for (;;) {
        pico_bsd_stack_tick();      /* tick picoTCP */
        ns_mgr_poll(&mgr, 1000);    /* tick Fossa   */
    }
}

int main(void)
{
    BSP_Init();
    picoTickTask(NULL);
}

