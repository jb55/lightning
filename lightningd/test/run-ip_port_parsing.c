#include <ccan/tal/str/str.h>
#include <common/wireaddr.h>
#include <common/utils.h>
#include <stdbool.h>
#include <assert.h>

int main(void)
{
	tal_t *ctx = tal_tmpctx(NULL);
	char *ip;
	u16 port;

	/* ret = getaddrinfo("[::1]:80", NULL, NULL, &res); */
	assert(parse_ip_port(ctx, "[::1]:80", &ip, &port));
	assert(streq(ip, "::1"));
	assert(port == 80);

	assert(!parse_ip_port(ctx, "::1", &ip, &port));
	assert(streq(ip, "::1"));
	assert(port == 0);

	assert(parse_ip_port(ctx, "192.168.1.1:8000", &ip, &port));
	assert(streq(ip, "192.168.1.1"));
	assert(port == 8000);

	assert(!parse_ip_port(ctx, "192.168.2.255", &ip, &port));
	assert(streq(ip, "192.168.2.255"));
	assert(port == 0);

	tal_free(ctx);
	return 0;
}
