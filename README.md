# simple_tap

Experiments with tap devices

Install needed tools:

* sudo apt install openvpn
* sudo apt install tshark

When installing wireshark:

On Debian and Debian derivatives such as Ubuntu, if you have installed Wireshark from a package, try running

    sudo dpkg-reconfigure wireshark-common

selecting "<Yes>" in response to the question

    Should non-superusers be able to capture packets?

adding yourself to the "wireshark" group by running

    sudo usermod -a -G wireshark {your username}

and then logging out and logging back in again.

# Build

Build the app:

    gcc -o tap_access tap_access.c

# Basic Steps

1. sudo ip tuntap add name tapint mode tap
1. sudo ip link set tapint up
1. sudo ip addr add 10.0.0.1/24 dev tapint
1. tshark -i tapint

In a seperate session:

1. tap_access

In a seperate session:

1. ping 10.0.0.2

Wireshark should report something like:

    156.194657538 da:a9:00:1b:e4:e4 → Broadcast    ARP 42 Who has 10.0.0.2? Tell 10.0.0.1

tap_access should show:

            TAP Data (42 bytes): ff:ff:ff:ff:ff:ff:da:a9:00:1b:e4:e4:08:06:00:01:08:00:06:04:00:01:da:a9:00:1b:e4:e4:0a:00:00:01:00:00:00:00:00:00:0a:00:00:08:

Where the adress after the "ff:ff:ff:ff:ff:ff" should be the mac address of the tap interface as reported by 

```
    ifconfig -a

        tapint: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
                inet 10.0.0.1  netmask 255.255.255.0  broadcast 0.0.0.0
                ether da:a9:00:1b:e4:e4  txqueuelen 1000  (Ethernet)
                RX packets 0  bytes 0 (0.0 B)
                RX errors 0  dropped 0  overruns 0  frame 0
                TX packets 438  bytes 18396 (17.9 KiB)
                TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
```

## References

1. [Tun/Tap interface tutorial](https://backreference.org/2010/03/26/tuntap-interface-tutorial/index.html)
1. [Universal TUN/TAP device driver](https://www.kernel.org/doc/html/latest/networking/tuntap.html)
1. [Linux TUN/TAP virtual interfaces TAP Interface - Sample Access Episode 2](https://thelinuxchannel.org/2023/10/linux-tun-tap-virtual-network-interfaces-tap-interface-sample-access-via-c-code/)
1. [TUN/TAP devices in 5 Minute](https://amitniz.github.io/posts/understanding_tuntap/)
1. [Guide to Linux ip Command With Examples](https://www.baeldung.com/linux/ip-command-tutorial)
1. [Creating TUN/TAP interfaces in Linux](https://john-millikin.com/creating-tun-tap-interfaces-in-linux)
1. [TAP interfaces in WSL-2 #11912](https://github.com/microsoft/WSL/discussions/11912)

