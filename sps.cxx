#include <sysexits.h>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using vector_string_t = std::vector<std::string>;

const std::string SSH_OPTS = "-o \"StrictHostKeyChecking no\" -o \"UserKnownHostsFile /dev/null\" -o \"GlobalKnownHostsFile  /dev/null\"";

void use ()
{
	std::cerr << ""
		"Simple Provisionning System\n"
		"Use:\n"
		"  cat file.md | ./sps host target [target]\n"
		"With:\n"
		"  file.md    Markdown file\n"
		"  host       Hostname or ip address where to deploy\n"
		"  target     Section name in the markdown file.md\n"
		<< std::flush
		;
}

int exit_status(int result)
{
	return (WIFEXITED(result) ? WEXITSTATUS(result) : EXIT_FAILURE);
}

vector_string_t tokenize_string(const std::string & source_string, const char separator)
{
	vector_string_t l;
	std::string s;
	std::istringstream i (source_string);

	std::getline(i, s, separator);

	while (!i.eof())
	{
		l.insert (l.end(), s);
		std::getline(i, s, separator);
	}

	if (s != "")
	{
		l.insert (l.end(), s);
	}

	return l;
}

int remote_execution(std::string & host, std::string & exec_cmd)
{
	int result = EXIT_FAILURE;
	char temp[] = "/tmp/exec-XXXXXX";
	int fd = mkstemp(temp);

	if (fd > -1)
	{
		write(fd, exec_cmd.c_str(), exec_cmd.length());
		close(fd);
		std::string cmd = std::string("") + "ssh -T " + SSH_OPTS + " root@" + host + " 'bash --login' < " + temp;
		result = system(cmd.c_str());
		unlink(temp);
		return exit_status(result);
	}
	else
	{
		return EX_TEMPFAIL; // 75
	}
}

int local_execution(std::string & exec_cmd)
{
	return exit_status(system(exec_cmd.c_str()));
}

int get_transfert(std::string host, std::string exec_cmd)
{
	vector_string_t param = tokenize_string(exec_cmd, '`');
	if (param.size() == 4)
	{
		std::string cmd = "scp -T -p " + SSH_OPTS + " root@" + host + ":\"'" + param[1] + "'\" '" + param[3] + "'";
		return exit_status(system(cmd.c_str()));
	}
	else
	{
		return EX_USAGE; // 64
	}
}

int put_transfert(std::string host, std::string exec_cmd)
{
	vector_string_t param = tokenize_string(exec_cmd, '`');
	if (param.size() == 4)
	{
		std::string cmd = "scp -p " + SSH_OPTS + " '" + param[1] + "' root@" + host + ":\"'" + param[3] + "'\"";
		return exit_status(system(cmd.c_str()));
	}
	else
	{
		return EX_USAGE; // 64
	}
}

int main (int argc, char * argv[])
{
	if (argc < 3)
	{
		use();
		return EX_USAGE; // 64
	}
	
	std::string host = argv[1];
	std::map<std::string, bool> target_list;
	for (int i = 2 ; i < argc ; i++)
		target_list[argv[i]] = true;

	std::ios_base::sync_with_stdio(false);
	if (std::cin.rdbuf()->in_avail() <= 0)
	{
		std::cerr << "No data on standard input" << std::endl;
		return EX_NOINPUT; // 65
	}

	std::string line, section, exec_cmd;
	char * str = nullptr;
	int len = 0;
	int exit_code = 0;
	bool exec_remote = true;
	bool in_section = false;
	bool in_exec = false;
	
	auto check_section = [&]() -> void
	{
		section = line.substr(2, len - 2);
		if (target_list.find(section) != target_list.end())
			in_section = true;
	};
	
	while (!std::cin.eof() && exit_code == 0)
	{
		getline(std::cin, line);
		str = (char*) line.c_str();
		len = line.length();

		if (!in_section)
		{
			if (strncmp(str, "# ", 2) == 0)
				check_section();
		}
		else
		{
			if (!in_exec)
			{
				if (strncmp(str, "# ", 2) == 0)
				{
					in_section = false;
					in_exec = false;
					exec_remote = true;
					check_section();
				}

				if (strncmp(str, "* GET", 5) == 0)
				{
					if (len > 6)
						exit_code = get_transfert(host, str + 6);
				}
				if (strncmp(str, "* PUT", 5) == 0)
				{
					if (len > 6)
						exit_code = put_transfert(host, str + 6);
				}
				if (strncmp(str, "* REMOTE_EXECUTION", 18) == 0)
					exec_remote = true;
				if (strncmp(str, "* LOCAL_EXECUTION", 17) == 0)
					exec_remote = false;

				if (strncmp(str, "```", 3) == 0)
				{
					in_exec = true;
					exec_cmd = "";
				}
			}
			else
			{
				if (strncmp(str, "```", 3) == 0)
				{
					in_exec = false;
					exit_code = exec_remote ? remote_execution(host, exec_cmd) : local_execution(exec_cmd);
				}
				else
				{
					exec_cmd += line + "\n";
				}
			}
		}
	}
	
	return exit_code;
}
