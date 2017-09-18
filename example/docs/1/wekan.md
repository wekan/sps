# Wekan Only-For-Testing (full stack)

## Description

* Wekan "The open-source web kanban." : [https://wekan.io/](https://wekan.io/)
* This documentation respects the [sps formalism](https://github.com/soohwa/sps) (sps card)
* The purpose of this sps card is only for testing wekan and is obviously not suitable for production.
* This sps card install a full stack mongodb nodejs wekan.
* This installation was tested on a Debian Wheezy 64 bit and [Devuan](https://devuan.org/) Jessie 64 bit inside VirtualBox (yes, the same script with the same packages for both)
* Reference : [Wekan Install](https://github.com/soohwa/apt/blob/master/Wekan.md)

## Requirements

* The host to provision is a minimal installation of a Debian Wheezy 64 bit or a [Devuan](https://devuan.org/) Jessie 64 bit
* Be sure your compiled binary sps is in the $PATH
* You already deployed your ssh key with

```bash
ssh-keygen -t rsa -b 4096
ssh-copy-id -i ~/.ssh/id_rsa.pub root@192.168.56.101
```

* Then you can install and start the full stack with :

```bash
cat wekan.md | sps 192.168.56.101 "Install"
```

# Install

```bash
apt-get install apt-transport-https

apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv EA312927
echo "deb https://repo.mongodb.org/apt/debian wheezy/mongodb-org/3.2 main" > /etc/apt/sources.list.d/mongodb-org-3.2.list

apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv FDEB78E7
echo "deb https://soohwa.github.io/apt/debian wheezy main" > /etc/apt/sources.list.d/wekan-oft.listen

apt-get update
apt-get install -y wekan-oft-0

```

# Configuration

Change the default values in the file

```bash
/etc/default/wefork-oft-0
```

And restart the service

```bash
/etc/init.d/wekan-oft-0 restart
```

Now you can access to wekan [http://192.168.56.101:3000/](http://192.168.56.101:3000/) if you changed ROOT_URL='http://192.168.56.101:3000' in the /etc/default/wefork-oft file.

# Behind a reverse proxy

Your reverse proxy must be able to manage websocket : apache 2.2 in wheezy can not so you must install nginx from wheezy-backports (only apache >= 2.4 can).

If the external exposed port is 4444 and the internal port of wekan is 3000 you must set :

```bash
export ROOT_URL='http://yourserver:4444'
export PORT=3000
```

If your reverse proxy manage the SSL certificat for HTTPS, just replace http by https.

```bash
export ROOT_URL='https://yourserver:4444'
export PORT=3000
```

And set at least but (obviously) not sufficient :

```
server {
	listen       4444;
	server_name  yourserver;
	
	location {
		proxy_pass http://127.0.0.1:3000/;
	}
}
```
