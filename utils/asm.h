#pragma once
//#include<cstdlib>
//#include<stdint.h>
namespace core
{
  /*
    timestamp counter - accurate count of every cycle that occurs on processor. rdtsc - read time stamp counter or rdtscp instructions to read values
    start at 0 on processor reset and steadily increases.Increments at a constant rate irrespective of load(since Pentium 4)

    Rdtsc value is not correct in case of out of order executions.
    Serializing instruction - cpuid can be used .Force every preceding instruction to complete before allowing program to continue
    When using serializing instruction,cycles spent to execute instruction should also be taken into consideration

    Rdtscp reads timestamp register and cpu identifier.
    waits until all previous instructions have been executed before reading the counter.Subsequent instruction may begin execution before read operation is performed
  */

  /*****RDTSC********/
  //loads high order 32 bits of timestamp register into EDX and low-order 32 bits inot EAX.
  //counter
  //S
  //cpuid - identify the processor on which program is running
  inline uint64_t rdtsc(){
      uint64_t low,high;
      __asm__ __volatile__ ("rdtsc" : "=a" (low), "=d" (high) );
      return (high << 32)| low;
  }

  inline uint64_t rdtscp(){
      uint64_t low,high;

      asm volatile ("rdtscp" : "=a" (low), "=d" (high) : :);
      return (high << 32)| low;
  }

  inline void serialize () {
       __asm__ __volatile__ ( "xorl %%eax, %%eax \n cpuid " : : : "%eax","%ebx","%ecx","%edx" );
  }

}

