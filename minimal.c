#include <linux/types.h>
#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/icmp.h>
#include <arpa/inet.h>

static void (*bpf_printk)(const char *fmt, int fmt_size, ...) = (void *)BPF_FUNC_trace_printk;

__attribute__((section("classifier")))
int ingress(struct __sk_buff *skb)
{
    if (skb->protocol != htons(ETH_P_IP)) goto exit;

    struct ethhdr *eth;
    struct iphdr *ip;
    struct icmphdr *icmp;

    if (skb->data + sizeof(*eth) + sizeof(*ip) + sizeof(*icmp) > skb->data_end)
        goto exit;

    eth = (void *)(long)skb->data;
    ip = (void *)(eth + 1);
    icmp = (void *)(ip + 1);

    if (ip->protocol != IPPROTO_ICMP)
        goto exit;

    char fmt[] = "ICMP type %d code %d\n";
    bpf_printk(fmt, sizeof(fmt), icmp->type, icmp->code);

exit:
    return 0;
}

char _license[] __attribute__((section("license"))) = "GPL";
