# Simple Provisioning System

---

Tired of maintaining installation scripts and separately a [Markdown](http://daringfireball.net/projects/markdown/) documentation (to be processed by [MkDocs](http://www.mkdocs.org/) or [Sphinx](http://www.sphinx-doc.org)? You only have a few servers and not want to bring out the [big guns](https://en.wikipedia.org/wiki/Comparison_of_open-source_configuration_management_software)?

So maybe Simple Provisioning System (SPS) is made for you : just write your markdown documentation and execute a part of it.

SPS is simple because :

* It's less than 200 lines of code.
* No dependencies' hell.
* No need to install a specific agent, just the ssh server.
* There is only one instruction and four keywords to remember.
* Everything else, you already know how to do it.

# Requirements

Must be installed : `make` and `g++` which can compile in c++11, and `ssh`

# Installation

Just compile to produce the `sps` binary:

    make

# Prepare the host

The host you want to provision must accept an ssh connexion with your gpg key :

    ssh-keygen -t rsa -b 4096
    ssh-copy-id -i ~/.ssh/id_rsa.pub root@server_to_provision

# Few rules

## Write your documentation in Markdown

* The title level 1 mark `# Target` (at the beginning of the line) is used as a target like a target in a Makefile.
* Only the (one or more) target enumerated on the parameters will be executed.
* Default setting: shell commands are executed at the remote server side through the ssh command.
* Shell commands have to be enclosed by triple backquote ``` at the beginning of the line.
* Put the mark `* REMOTE_EXECUTION` (only that keyword) at the beginning of the line and at the previous line the shell command you want to be executed remotely (default setting)
* Put the mark `* LOCAL_EXECUTION` (only that keyword) at the beginning of the line and at the previous line the shell command you want to be executed locally.
* Put the following mark `* PUT` to send a local file `source` to the remote server to `target` (don't forget the back quotes) through scp.

```no-highlight
* PUT `source` `target`
```

* Put the following mark `* GET`to retrieve a remote file `source` to the local machine to `target` (don't forget the back quotes) through scp.

```no-highlight
* GET `source` `target`
```

* That's all ! Everything else will be ignored (in the same way the target you did not mention on the paramaters) : so you can add many comments without problem.

## Execute

```no-highlight
cat file.md | ./sps host target [target]

With:
  file.md    Markdown file
  host       Hostname or ip address where to deploy
  target     Section name in the markdown file.md 
```

Example of sps cards
--------------------

Theses examples need a Debian Wheezy 64 bit for the host to provision (192.168.0.121 in our example).

# Prepare the host

The host you want to provision must accept an ssh connexion with your gpg key :

```bash
ssh-keygen -t rsa -b 4096
ssh-copy-id -i ~/.ssh/id_rsa.pub root@192.168.0.121
```

MkDocs
------

# Description

* Generic installation of [MkDocs](http://www.mkdocs.org/) for Debian Wheezy 64 bit.
* This card respects the [sps formalism](https://github.com/soohwa/sps) (sps card)

# Install

```
apt-get install python-pip python-dev
pip install mkdocs
```

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

## Other example

### Create a file apache.md :

    # Install

    * PUT `custom.list` `/etc/apt/sources.list.d/`

    ```
    apt-get update && apt-get -q -y install apache2
    ```

    # Backup Conf

    ```
    cd /etc/
    tar cpzf /root/apache2.tar.gz apache2
    ```

    * GET `/root/apache2.tar.gz` `.`

    ```
    rm -f /root/apache2.tar.gz
    ```

    * LOCAL_EXECUTION

    ```
    date > last_conf_backup
    ```

    # Remove All

    ```
    apt-get -q -y --purge autoremove apache2
    ```

### Execute

    cat apache.md | ./sps 192.168.0.50 "Install" "Backup Conf"

### Result

Only the section `# Install` and `# Backup Conf` will be executed, not the `# Remove All` section.

# Future

I think this program is simple enough to be quickly understood and modified. This program is intentionally small and will remain because it does the job for me and I will not have the time to manage any contributions.

So I encourage you to fork it and/or transpose it in other languages.

# LICENSE

```no-highlight

 THIS SOFTWARE IS PROVIDED 'AS-IS', WITHOUT ANY EXPRESS OR IMPLIED
 WARRANTY. IN NO EVENT WILL THE AUTHORS BE HELD LIABLE FOR ANY DAMAGES
 ARISING FROM THE USE OF THIS SOFTWARE.
 .
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely.

```
