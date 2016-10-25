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

vector_string_t tokenize_string(const std::string & source_string, const char separator)
{
	vector_string_t l;
	std::string s;
	std::istringstream i (source_string.c_str());

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

bool remote_execution(std::string & host, std::string & exec_cmd)
{
	bool result = false;
	char temp[] = "/tmp/exec-XXXXXX";
	int fd = mkstemp(temp);

	if (fd > -1)
	{
		write(fd, exec_cmd.c_str(), exec_cmd.length());
		close(fd);
		std::string cmd = std::string("") + "cat " + temp + " | ssh -T " + SSH_OPTS + " root@" + host;
		result = system(cmd.c_str()) > -1;
		unlink(temp);
	}
	return result;
}

bool local_execution(std::string & exec_cmd)
{
	return system(exec_cmd.c_str()) > -1;
}

bool get_transfert(std::string host, std::string exec_cmd)
{
	bool result = false;
	vector_string_t param = tokenize_string(exec_cmd, '`');
	if (param.size() == 4)
	{
		std::string cmd = "scp " + SSH_OPTS + " root@" + host + ":\"'" + param[1] + "'\" '" + param[3] + "'";
		result = system(cmd.c_str()) > -1;
	}
	return result;
}

bool put_transfert(std::string host, std::string exec_cmd)
{
	bool result = false;
	vector_string_t param = tokenize_string(exec_cmd, '`');
	if (param.size() == 4)
	{
		std::string cmd = "scp " + SSH_OPTS + " '" + param[1] + "' root@" + host + ":\"'" + param[3] + "'\"";
		result = system(cmd.c_str()) > -1;
	}
	return result;
}

int main (int argc, char * argv[])
{
	if (argc < 3)
	{
		use();
		return EXIT_FAILURE;
	}
	
	std::string host = argv[1];
	std::map<std::string, bool> target_list;
	for (int i = 2 ; i < argc ; i++)
		target_list[argv[i]] = true;

	std::ios_base::sync_with_stdio(false);
	if (std::cin.rdbuf()->in_avail() <= 0)
	{
		std::cerr << "No data on standard input" << std::endl;
		return EXIT_FAILURE;
	}

	std::string line, section, exec_cmd;
	char * str = nullptr;
	int len = 0;
	bool result = true;
	bool exec_remote = true;
	bool in_section = false;
	bool in_exec = false;
	
	auto check_section = [&]() -> void
	{
		section = line.substr(2, len - 2);
		if (target_list.find(section) != target_list.end())
			in_section = true;
	};
	
	while (!std::cin.eof() && result)
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
						result = get_transfert(host, str + 6);
				}
				if (strncmp(str, "* PUT", 5) == 0)
				{
					if (len > 6)
						result = put_transfert(host, str + 6);
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
					result = exec_remote ? remote_execution(host, exec_cmd) : local_execution(exec_cmd);
				}
				else
				{
					exec_cmd += line + "\n";
				}
			}
		}
	}
	
	return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
