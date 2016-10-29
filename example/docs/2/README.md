# Installation of separate components

## Wekan

* Wekan "The open-source Trello-like kanban." : [https://wekan.io/](https://wekan.io/)
* Since the development seems a little bit slow, here is a fork : [Wefork Wekan](https://github.com/wefork/wekan)
* This documentation respects the [sps formalism](https://github.com/soohwa/sps) (sps card)

## Description

* This is an example of a installation of more separated generic [sps cards](https://github.com/soohwa/sps).
* The purpose of theses sps cards is only for testing wekan and is obviously not suitable for production.

## Requirements

* The host to provision is a minimal installation of a Debian Wheezy 64 bit
* Be sure your compiled binary sps is in the $PATH
* You already deployed your ssh key

```bash
ssh-keygen -t rsa -b 4096
ssh-copy-id -i ~/.ssh/id_rsa.pub root@192.168.0.121
```

* Then you can install the full stack with :

```bash
cat mongodb.md nodejs.md wekan.md | sps 192.168.0.121 "Install"
```

* Or :

```bash
cat mongodb.md | sps 192.168.0.121 "Install"
```

```bash
cat nodejs.md | sps 192.168.0.121 "Install"
```

```bash
cat wekan.md | sps 192.168.0.121 "Install"
```

## Start Wekan

```bash
cat wekan.md | sps 192.168.0.121 "Start"
```

* So you can access to wekan [http://192.168.0.121:8080/](http://192.168.0.121:8080/)

