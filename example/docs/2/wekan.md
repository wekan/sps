Wekan 0.10.1
------------

# Description

* Generic installation of wekan 0.10.1 for Debian Wheezy 64 bit.
* This card respects the [sps formalism](https://github.com/soohwa/sps) (sps card)

# Requirements

* [MongoDB](mongodb.md)
* [NodeJS 0.10.40](nodejs.md)
* You **MUST** modify the [start_wekan](start_wekan) script with yours settings.

# Install

## Create a local user wekan

```bash
adduser --disabled-password --gecos "" wekan
```

## Wekan 0.10.1

```bash
su - wekan -c 'wget https://github.com/wekan/wekan/releases/download/v0.10.1/wekan-0.10.1.tar.gz ; mkdir wekan-0.10.1 ;	cd wekan-0.10.1 ; tar xzf ../wekan-0.10.1.tar.gz ; cd bundle/programs/server ; npm install'
```
* PUT `start_wekan` `/home/wekan/`

```bash
chown wekan:wekan /home/wekan/start_wekan
chmod +x /home/wekan/start_wekan
apt-get clean
```

# Start

```bash
su - wekan -c '/home/wekan/start_wekan'
```
