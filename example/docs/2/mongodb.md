MongoDB 3.2
-----------

# Description

* Generic installation of mongodb for Debian Wheezy 64 bit.
* This card respects the [sps formalism](https://github.com/soohwa/sps) (sps card)

# Install

```bash
apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv EA312927
echo "deb http://repo.mongodb.org/apt/debian wheezy/mongodb-org/3.2 main" | tee /etc/apt/sources.list.d/mongodb-org-3.2.list
apt-get update
apt-get install -y mongodb-org
service mongod start
```
