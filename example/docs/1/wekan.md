# Wekan (full stack)

## Description

* Wekan "The open-source Trello-like kanban." : [https://wekan.io/](https://wekan.io/)
* This documentation respects the [sps formalism](https://github.com/soohwa/sps) (sps card)
* The purpose of this sps card is only for testing wekan and is obviously not suitable for production.
* This sps card install a full stack mongodb nodejs wekan.

## Requirements

* The host to provision is a minimal installation of a Debian Wheezy 64 bit
* Be sure your compiled binary sps is in the $PATH
* You already deployed your ssh key

```bash
ssh-keygen -t rsa -b 4096
ssh-copy-id -i ~/.ssh/id_rsa.pub root@192.168.0.121
```

* You **MUST** modify the [start_wekan](start_wekan) script with yours settings.
* Then you can install the full stack with :

```bash
cat wekan.md | sps 192.168.0.121 "Install" "Start"
```

* So you can access to wekan [http://192.168.0.121:8080/](http://192.168.0.121:8080/)

# Install

## MongoDB 3.2

```bash
apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv EA312927
echo "deb http://repo.mongodb.org/apt/debian wheezy/mongodb-org/3.2 main" | tee /etc/apt/sources.list.d/mongodb-org-3.2.list
apt-get update
apt-get install -y mongodb-org
service mongod start
```

## Create a local user wekan

```bash
adduser --disabled-password --gecos "" wekan
```

## Nodejs 0.10.40

```bash
su - wekan -c 'wget https://nodejs.org/dist/v0.10.40/node-v0.10.40-linux-x64.tar.gz ; tar xzf node-v0.10.40-linux-x64.tar.gz'
```


## Wekan 0.10.1

```bash
su - wekan -c 'wget https://github.com/wekan/wekan/releases/download/v0.10.1/wekan-0.10.1.tar.gz ; mkdir wekan-0.10.1 ;	cd wekan-0.10.1 ; tar xzf ../wekan-0.10.1.tar.gz ; cd bundle/programs/server ; export PATH=$PATH:/home/wekan/node-v0.10.40-linux-x64/bin ; npm install'
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
