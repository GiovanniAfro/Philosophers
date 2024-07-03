# Philosophers' Dinner

## Table of Contents
1. [Introduction](#introduction)
2. [Common Instructions](#common-instructions)
3. [Overview](#overview)
4. [Global Rules](#global-rules)
5. [Mandatory Part](#mandatory-part)
6. [Bonus Part](#bonus-part)
7. [Submission and Peer-evaluation](#submission-and-peer-evaluation)

## Introduction

Philosophy, deriving from the Greek word "philosophia" meaning "love of wisdom," is the study of general and fundamental questions about existence, knowledge, values, reason, mind, and language. These questions are often posed as problems to be studied or resolved. The philosophical method includes questioning, critical discussion, rational argument, and systematic presentation.

## Common Instructions

- **Language:** Your project must be written in C.
- **Norm Compliance:** All code must adhere to the specified norms. Failure to comply will result in a score of 0.
- **Error Handling:** Functions should not quit unexpectedly. Any segmentation fault or similar errors will lead to a non-functional classification.
- **Memory Management:** All heap-allocated memory must be properly freed. Memory leaks will not be tolerated.
- **Compilation:** Include a Makefile to compile the source files with flags `-Wall, -Wextra, -Werror`. Do not allow re-linking.

## Overview

In this project, philosophers are simulated sitting around a table with a bowl of spaghetti. They alternatively eat, think, and sleep. The objective is to ensure no philosopher starves or dies.

## Global Rules

- **No Global Variables:** Ensure all variables are scoped appropriately.
- **Program Arguments:** The program should accept specific arguments related to the philosophers' actions and conditions.
- **Safety:** Implement mechanisms to prevent data races and ensure thread safety.

## Mandatory Part

- **Program Name:** `philo`
- **Files:** Submit a Makefile, header files (*.h), and source files (*.c) in the `philo` directory.
- **Functionality:** Utilize threads and mutexes to manage philosophers' actions and interactions with resources like forks.

## Bonus Part

Additional features and functionalities can be implemented in the bonus part, which will be evaluated separately.

## Submission and Peer-evaluation

Submit your work to the assigned Git repository. The grading includes peer evaluations, and any error found during the automated grading (Deepthought) will halt further evaluation.

---

```makefile
${info ${RED}}
${info • ▄▄ •           ▄▄▄ . ▄▄▄· ▄▄▄▄▄     ▄· ▄▌      ▄• ▄▌▄▄▄      .▄▄ ·  ▄▄▄· ▄▄▄·  ▄▄ •  ▄ .▄▄▄▄ .▄▄▄▄▄▄▄▄▄▄▪       ▄· ▄▌      ▄• ▄▌     ▄▄▄·▄• ▄▌ ▐ ▄ ▄ •▄}
${info ▐█ ▀ ▪▪         ▀▄.▀·▐█ ▀█ •██      ▐█▪██▌▪     █▪██▌▀▄ █·    ▐█ ▀. ▐█ ▄█▐█ ▀█ ▐█ ▀ ▪██▪▐█▀▄.▀·•██  •██  ██     ▐█▪██▌▪     █▪██▌    ▐█ ▄██▪██▌•█▌▐██▌▄▌▪ }
${info ▄█ ▀█▄ ▄█▀▄     ▐▀▀▪▄▄█▀▀█  ▐█.▪    ▐█▌▐█▪ ▄█▀▄ █▌▐█▌▐▀▀▄     ▄▀▀▀█▄ ██▀·▄█▀▀█ ▄█ ▀█▄██▀▐█▐▀▀▪▄ ▐█.▪ ▐█.▪▐█·    ▐█▌▐█▪ ▄█▀▄ █▌▐█▌     ██▀·█▌▐█▌▐█▐▐▌▐▀▀▄· }
${info ▐█▄▪▐█▐█▌.▐▌    ▐█▄▄▌▐█ ▪▐▌ ▐█▌·     ▐█▀·.▐█▌.▐▌▐█▄█▌▐█•█▌    ▐█▄▪▐█▐█▪·•▐█ ▪▐▌▐█▄▪▐███▌▐▀▐█▄▄▌ ▐█▌· ▐█▌·▐█▌     ▐█▀·.▐█▌.▐▌▐█▄█▌    ▐█▪·•▐█▄█▌██▐█▌▐█.█▌ }
${info ·▀▀▀▀  ▀█▄▀▪     ▀▀▀  ▀  ▀  ▀▀▀       ▀ •  ▀█▄▀▪ ▀▀▀ .▀  ▀     ▀▀▀▀ .▀    ▀  ▀ ·▀▀▀▀ ▀▀▀ · ▀▀▀  ▀▀▀  ▀▀▀ ▀▀▀      ▀ •  ▀█▄▀▪ ▀▀▀     .▀    ▀▀▀ ▀▀ █▪·▀  ▀ }
${info ${BOLD}${ITALIC}${YELLOW}                        			eat, sleep, code, repeat}
${info ${RED}}
