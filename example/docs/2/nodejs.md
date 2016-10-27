Nodejs 0.10.40
--------------

# Description

* Generic installation of nodejs 0.10.40 for Debian Wheezy 64 bit.
* This card respects the [sps formalism](https://github.com/soohwa/sps) (sps card)

# Install

```bash
cd /opt
wget https://nodejs.org/dist/v0.10.40/node-v0.10.40-linux-x64.tar.gz
tar xzf node-v0.10.40-linux-x64.tar.gz
cd /usr/bin
ln -sf /opt/node-v0.10.40-linux-x64/bin/node .
ln -sf /opt/node-v0.10.40-linux-x64/bin/npm .
```
