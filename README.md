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

## Example

* [MkDocs](https://github.com/soohwa/sps/blob/master/example/docs/0/mkdocs.md)
* [Wekan for Debian Wheezy 64 bit & Devuan Jessie 64 bit](https://github.com/soohwa/sps/blob/master/example/docs/1/wekan.md)

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
