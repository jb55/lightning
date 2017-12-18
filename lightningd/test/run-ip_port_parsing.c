
#include <ccan/tal/str/str.h>
#include <common/wireaddr.h>
#include <common/utils.h>
#include <stdbool.h>
#include <assert.h>

int main(void)
{
  struct wireaddr addr;
  tal_t *ctx = tal_tmpctx(NULL);
  char *ip;
  u16 port;

  /* ret = getaddrinfo("[::1]:80", NULL, NULL, &res); */
  assert(parse_ip_port(ctx, "[::1]:80", &ip, &port));
  assert(streq(ip, "::1"));
  assert(port == 80);

  assert(!parse_ip_port(ctx, "ip6-localhost", &ip, &port));
  assert(streq(ip, "ip6-localhost"));
  assert(port == 0);

  assert(!parse_ip_port(ctx, "::1", &ip, &port));
  assert(streq(ip, "::1"));
  assert(port == 0);

  assert(parse_ip_port(ctx, "192.168.1.1:8000", &ip, &port));
  assert(streq(ip, "192.168.1.1"));
  assert(port == 8000);

  assert(!parse_ip_port(ctx, "192.168.2.255", &ip, &port));
  assert(streq(ip, "192.168.2.255"));
  assert(port == 0);

  // string should win the port battle
  parse_wireaddr("localhost", &addr, 200);
  assert(addr.port == 200);

  // string should win the port battle
  parse_wireaddr("[::1]:9735", &addr, 500);
  assert(addr.port == 9735);

  ip = fmt_wireaddr(ctx, &addr);
  assert(streq(ip, "[::1]:9735"));

  // should use argument if we have no port in string
  parse_wireaddr("2001:db8:85a3::8a2e:370:7334", &addr, 9777);
  assert(addr.port == 9777);

  ip = fmt_wireaddr(ctx, &addr);
  assert(streq(ip, "[2001:db8:85a3::8a2e:370:7334]:9777"));

  tal_free(ctx);
  return 0;
}
