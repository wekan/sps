# Wekan Only-For-Testing (full stack)

## Description

* Wekan "The open-source web kanban." : [https://wekan.io/](https://wekan.io/)
* This documentation respects the [sps formalism](https://github.com/soohwa/sps) (sps card)
* The purpose of this sps card is only for testing wekan and is obviously not suitable for production.
* This sps card install a full stack mongodb nodejs wekan.
* This installation was tested on a Debian Wheezy 64 bit and [Devuan](https://devuan.org/) Jessie 64 bit inside VirtualBox (yes, the same script with the same packages for both)

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
apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv EA312927
echo "deb http://repo.mongodb.org/apt/debian wheezy/mongodb-org/3.2 main" | tee /etc/apt/sources.list.d/mongodb-org-3.2.list
apt-get update
apt-get install -y mongodb-org

wget https://github.com/soohwa/sps/raw/master/example/docs/1/node-v0.10.48-oft_1.0_amd64.deb
wget https://github.com/soohwa/sps/raw/master/example/docs/1/wekan-oft_0.18-git-1_amd64.deb

dpkg -i node-v0.10.48-oft_1.0_amd64.deb
dpkg -i wekan-oft_0.18-git-1_amd64.deb

```

# Configuration

Change the default values in the file

```bash
/etc/default/wefork-oft
```

And restart the service

```bash
/etc/init.d/wekan-oft restart
```

Now you can access to wekan [http://192.168.56.101:3000/](http://192.168.56.101:3000/) if you changed ROOT_URL='http://192.168.56.101:3000' in the /etc/default/wefork-oft file.