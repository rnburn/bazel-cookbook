// Taken from
// https://stackoverflow.com/a/1925461/4447365
#ifdef WITH_BACKTRACE
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef __USE_GNU
#define __USE_GNU
#endif

#include <array>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <cstdio>
#include <regex>
#include <tuple>
#include <iostream>
#include <string_view>

#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>
#include <unistd.h>

#include "backtrace.h"

//--------------------------------------------------------------------------------------------------
// execute_command
//--------------------------------------------------------------------------------------------------
// The implementation is based off of https://stackoverflow.com/a/478960/4447365
// with some improvements
static std::string execute_command(std::string_view command) noexcept {
  std::string command_str{command};
  std::array<char, 128> buffer;
  std::string result;
  auto pipe = popen(command_str.data(), "r");
  if (pipe == nullptr) {
    std::cerr << "failed to execute \"" << command << "\": " << std::strerror(errno);
    exit(EXIT_FAILURE);
  }
  while (1) {
    auto num_read = std::fread(static_cast<void*>(buffer.data()), sizeof(char),
                               buffer.size(), pipe);
    result.append(buffer.data(), num_read);
    if (num_read < buffer.size()) {
      break;
    }
  }
  if (std::ferror(pipe) != 0) {
    std::cerr << "failed to read output from \"" << command
              << "\": " << std::strerror(errno) << "\n";
    exit(EXIT_FAILURE);
  }
  auto rcode = pclose(pipe);
  pipe = nullptr;
  if (rcode != 0) {
    std::cerr << "failed to execute \"" << command << "\": returned " << rcode;
    exit(EXIT_FAILURE);
  }
  return result;
}

static std::tuple<std::string, std::string, std::string> parse_backtrace(
    std::string_view s) noexcept {
  static const std::regex expression{R"((.*)\((.*)\+.*\)\s*\[(.*)\])"};
  std::cmatch match_groups;
  if (!std::regex_match(s.begin(), s.end(), match_groups, expression)) {
    return {};
  }
  return std::make_tuple(match_groups[1].str(), match_groups[2].str(),
                         match_groups[3].str());
}

/* This structure mirrors the one found in /usr/include/asm/ucontext.h */
typedef struct _sig_ucontext {
 unsigned long     uc_flags;
 ucontext_t        *uc_link;
 stack_t           uc_stack;
 sigcontext      uc_mcontext;
 sigset_t          uc_sigmask;
} sig_ucontext_t;

void crit_err_hdlr(int sig_num, siginfo_t * info, void * ucontext)
{
 void *             array[50];
 void *             caller_address;
 char **            messages;
 int                size, i;
 sig_ucontext_t *   uc;

 uc = static_cast<sig_ucontext_t *>(ucontext);

 /* Get the address at the time the signal was raised */
#if defined(__i386__) // gcc specific
 caller_address = static_cast<void*>(uc->uc_mcontext.eip); // EIP: x86 specific
#elif defined(__x86_64__) // gcc specific
 caller_address = reinterpret_cast<void*>(uc->uc_mcontext.rip); // RIP: x86_64 specific
#else
#error Unsupported architecture. // TODO: Add support for other arch.
#endif

 fprintf(stderr, "signal %d (%s), address is %p from %p\n", sig_num,
         strsignal(sig_num), info->si_addr,
         static_cast<void *>(caller_address));

 size = backtrace(array, 50);

 /* overwrite sigaction with caller's address */
 array[1] = caller_address;

 messages = backtrace_symbols(array, size);

 /* skip first stack frame (points here) */
 for (i = 1; i < size && messages != NULL; ++i)
 {
  auto [filename, function_name, addr] = parse_backtrace(messages[i]);
  if (!filename.empty() && !addr.empty()) {
    std::string cmd = "addr2line -e " + filename + " " + addr;
    auto fileline =
        execute_command(cmd);
    if (fileline.size() > 0 && fileline[0] != '?') {
      std::cout << "#" << i << " " << fileline;
    }
  }
 }

 free(messages);

 exit(EXIT_FAILURE);
}

void setup_backtrace() noexcept {
  struct sigaction sigact;

  sigact.sa_sigaction = crit_err_hdlr;
  sigact.sa_flags = SA_RESTART | SA_SIGINFO;

  if (sigaction(SIGSEGV, &sigact, nullptr) != 0) {
    std::cerr << "failed to set signal handler\n";
    exit(EXIT_FAILURE);
  }
  if (sigaction(SIGABRT, &sigact, nullptr) != 0) {
    std::cerr << "failed to set signal handler\n";
    exit(EXIT_FAILURE);
  }
}
#else
void setup_backtrace() noexcept {}
#endif // WITH_BACKTRACE
