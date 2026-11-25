*This project has been created as part of the 42 curriculum by elmondo.*

# <img align="middle" height="115" src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/badges/numbered_cpps/CPP09.png" alt="CPP09 badge"/> <picture><source media="(prefers-color-scheme: dark)" srcset="https://readme-typing-svg.demolab.com/?font=Fira+Code&weight=600&size=55&pause=1000&color=58A6FF&vCenter=true&width=400&height=80&lines=CPP09"><source media="(prefers-color-scheme: light)" srcset="https://readme-typing-svg.demolab.com/?font=Fira+Code&weight=600&size=55&pause=1000&color=0366D6&vCenter=true&width=400&height=80&lines=CPP09"><img align="middle" src="https://readme-typing-svg.demolab.com/?font=Fira+Code&weight=600&size=55&pause=1000&color=0366D6&vCenter=true&width=400&height=80&lines=CPP09" alt="CPP09"/></picture>

[![Common Core](https://img.shields.io/badge/-Common%20Core-24292e?style=flat&logo=data:image/svg%2Bxml;base64,PHN2ZyByb2xlPSJpbWciIHZpZXdCb3g9IjAgMCAyNCAzNCIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIj48dGl0bGU+NDI8L3RpdGxlPjxkZXNjPkxvZ28gNDIgY29uIHBhZGRpbmcgaW5mZXJpb3JlOiBHaXRIdWIgcmltdW92ZSBnbGkgYXR0cmlidXRpIHN0eWxlIGRhbCBtYXJrZG93biwgcXVpbmRpIGlsIG1hcmdpbmUgY2hlIGFsbGluZWEgbCdpY29uYSBhbCB0ZXN0byBkZWwgdGl0b2xvIGUnIGluY29ycG9yYXRvIG5lbCB2aWV3Qm94LiBJbCBnbGlmbyBvY2N1cGEgeSAzLjU3NC0yMC40MjYgZSBzb3R0byByZXN0YW5vIDEzLjU3NCB1bml0YScgdnVvdGU6IHJlc28gYSA0MnB4IGNvbiBhbGlnbj1taWRkbGUsIGlsIGdsaWZvIHN0YSB+MnB4IHNvcHJhIGxhIGJhc2VsaW5lIGRlbCB0aXRvbG8uIFBlciBhbHphcmxvIGFuY29yYSBzZXJ2b25vICsxIHVuaXRhJyBkaSB2aWV3Qm94IG9nbmkgKzEuMnB4IGRpIGhlaWdodCAoY2lyY2EgKzAuNnB4IGRpIHNvbGxldmFtZW50bywgYSBwYXJpdGEnIGRpIGRpbWVuc2lvbmUgZGVsIGdsaWZvKS48L2Rlc2M+PHN0eWxlPnBhdGh7ZmlsbDojMDAwMDAwfSBAbWVkaWEgKHByZWZlcnMtY29sb3Itc2NoZW1lOmRhcmspe3BhdGh7ZmlsbDojRkZGRkZGfX08L3N0eWxlPjxwYXRoIGQ9Ik0xOS41ODEgMTYuODUxSDI0di00LjQzOVpNMjQgMy41NzRoLTQuNDE5djQuNDJsLTQuNDE5IDQuNDE4djQuNDRoNC40MTl2LTQuNDRMMjQgNy45OTNabS00LjQxOSAwaC00LjQxOXY0LjQyem0tNi4zMjQgOC44MzhINC40MTlsOC44MzgtOC44MzhIOC44MzhMMCAxMi40MTJ2My41OTVoOC44Mzh2NC40MTloNC40MTl6Ii8+PC9zdmc+Cg==)](https://profile.intra.42.fr/users/elmondo)
![Language](https://img.shields.io/badge/language-C%2B%2B98-blue)
![Flags](https://img.shields.io/badge/flags--Wall%20--Wextra%20--Werror-passing-brightgreen)
![Valgrind](https://img.shields.io/badge/valgrind-no%20leaks-brightgreen)

> STL in depth: choosing the right container for each problem. No container can be reused between exercises.

---

## 📖 Description

`CPP09` is Module 09 of the 42 **C++ modules**. Every exercise is written in **C++98** and compiled with `c++ -Wall -Wextra -Werror -std=c++98`.

What this module covers:

- `std::map` for date → rate lookup with `lower_bound`
- `std::stack` for Reverse Polish Notation evaluation
- `std::vector` and `std::deque` for the Ford-Johnson merge-insert sort
- Strict parsing and error messages for malformed input

---

## 🗂️ Exercises

| Directory | Exercise | Executable | Description |
|:---------:|----------|:----------:|-------------|
| `ex00` | Bitcoin Exchange | `btc` | Reads a `date | value` file and prints the value times the exchange rate of the closest earlier date from `data.csv`. |
| `ex01` | Reverse Polish Notation | `RPN` | Evaluates a postfix expression with `+ - * /` on single-digit operands. |
| `ex02` | PmergeMe | `PmergeMe` | Sorts a sequence of positive integers with the merge-insertion sort, timing it on both a `std::vector` and a `std::deque`. |

---

## ⚙️ Compilation & Usage

Each exercise is independent and has its own `Makefile`:

```bash
make        # build the executable
make clean  # remove object files
make fclean # remove object files and the executable
make re     # fclean + make
```

**`ex00` — Bitcoin Exchange**
```bash
cd ex00 && make
./btc input.txt
```

**`ex01` — Reverse Polish Notation**
```bash
cd ex01 && make
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
```

**`ex02` — PmergeMe**
```bash
cd ex02 && make
./PmergeMe 3 5 9 7 4
```

---

## 📁 Project Structure

```
CPP09/
├── ex00/
│   ├── BitcoinExchange.cpp
│   ├── BitcoinExchange.hpp
│   ├── main.cpp
│   └── Makefile
├── ex01/
│   ├── RPN.cpp
│   ├── RPN.hpp
│   ├── main.cpp
│   └── Makefile
└── ex02/
    ├── PmergeMe.cpp
    ├── PmergeMe.hpp
    ├── main.cpp
    └── Makefile
```

---

## 📚 Resources

- [Merge-insertion sort — Wikipedia](https://en.wikipedia.org/wiki/Merge-insertion_sort)
- [Reverse Polish notation — Wikipedia](https://en.wikipedia.org/wiki/Reverse_Polish_notation)
- [std::map::lower_bound — cppreference](https://en.cppreference.com/w/cpp/container/map/lower_bound)
- [Jacobsthal numbers — Wikipedia](https://en.wikipedia.org/wiki/Jacobsthal_number)
- `man 3 cout`, [GNU Make manual](https://www.gnu.org/software/make/manual/make.html)
- [Valgrind](https://valgrind.org/) — memory error and leak detector used for testing

---

## 🎯 Key Takeaways

- Matching **container to problem** (map, stack, vector, deque).
- Implementing the **Ford-Johnson algorithm** and comparing containers on timing.
- Writing **defensive parsers** for dates, numbers and expressions.
