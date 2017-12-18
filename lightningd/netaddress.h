#ifndef LIGHTNING_LIGHTNINGD_NETADDRESS_H
#define LIGHTNING_LIGHTNINGD_NETADDRESS_H
#include "config.h"
#include <ccan/short_types/short_types.h>

struct lightningd;

void guess_addresses(struct lightningd *ld);

bool parse_ip_port(tal_t *ctx, const char *arg, char **ip, u16 *port);
bool parse_wireaddr(const char *arg, struct wireaddr *addr, u16 port);

#endif /* LIGHTNING_LIGHTNINGD_NETADDRESS_H */
