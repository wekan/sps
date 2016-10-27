Example of sps cards
--------------------

Theses examples need a Debian Wheezy 64 bit for the host to provision (192.168.0.121 in our example).

# Prepare the host

The host you want to provision must accept an ssh connexion with your gpg key :

```bash
ssh-keygen -t rsa -b 4096
ssh-copy-id -i ~/.ssh/id_rsa.pub root@192.168.0.121
```