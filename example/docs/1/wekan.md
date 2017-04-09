# Wefork/Wekan (full stack)

## Description

* Wekan "The open-source Trello-like kanban." : [https://wekan.io/](https://wekan.io/)
* Since the original development seems halted, here is a fork : [Wefork Wekan](https://github.com/wefork/wekan)
* This documentation respects the [sps formalism](https://github.com/soohwa/sps) (sps card)
* The purpose of this sps card is only for testing wekan and is obviously not suitable for production.
* This sps card install a full stack mongodb nodejs wekan.
* These installation was tested on a Debian Wheezy 64 bit inside VirtualBox

## Requirements

* The host to provision is a minimal installation of a Debian Wheezy 64 bit
* Be sure your compiled binary sps is in the $PATH
* You already deployed your ssh key with

```bash
ssh-keygen -t rsa -b 4096
ssh-copy-id -i ~/.ssh/id_rsa.pub root@192.168.56.101
```

* Then you can install and start the full stack with :

```bash
cat wekan.md | sps 192.168.56.101 "Install" "Start"
```

* So you can access to wekan [http://192.168.56.101:8080/](http://192.168.56.101:8080/)

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

## Nodejs 0.10.48

```bash
su - wekan -c 'wget https://nodejs.org/dist/v0.10.48/node-v0.10.48-linux-x64.tar.gz ; tar xzf node-v0.10.48-linux-x64.tar.gz'
```


## Wefork/Wekan 0.11.0

```bash
apt-get update
apt-get install -y build-essential
apt-get clean
su - wekan -c 'wget https://github.com/soohwa/sps/raw/master/example/docs/wekan-0.11.0.tar.gz && mkdir wekan && cd wekan && tar xzf ../wekan-0.11.0.tar.gz && cd bundle/programs/server ; export PATH=$PATH:/home/wekan/node-v0.10.48-linux-x64/bin ; npm install'
```

# Start

```bash
su - wekan -c 'export PATH=$PATH:/home/wekan/node-v0.10.48-linux-x64/bin ; export MONGO_URL=mongodb://127.0.0.1:27017/wekan ; export ROOT_URL=https://192.168.0.56.101:8080 ; export MAIL_FM=wekan-admin@localhost ; export PORT=8080 ; cd wekan/bundle && node main.js'
```
