#pragma once
#include <base/auto_handle.hpp>
#include <winternl.h>
#include <vector>

namespace remote
{
	class process_t;

	struct module_t
	{
		uintptr_t base;
		std::string name;
		IMAGE_NT_HEADERS nt_headers;

		std::vector<std::pair<std::string, uintptr_t>> exports;

		uintptr_t get_proc_address(const char* export_name);
	};

	class peb_t
	{
	public:
		explicit peb_t(process_t* process);

		module_t* get_module(const char* module_name);
		bool reset();
	private:
		bool read();
		std::string read_unicode_string(const UNICODE_STRING& value) const;

		process_t* process_;
		PROCESS_BASIC_INFORMATION pbi_;
		PEB	peb_;

		std::string command_line_;
		std::vector<module_t> modules_;
	};
} // namespace remote