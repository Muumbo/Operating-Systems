# Proseminar Exam — Group 5

*1 hour 45 minutes, open book, no communication*

The assignment is purposefully underspecified.
You have to make, state, and justify assumptions.
You may only ask for clarification regarding the submission part, not the assignment or execution.

The time limit for this exercise is quite tight, time management is key.
However, quality over quantity!
It's more important that your solution is well structured and tidy, than complete.

## Assignment

Your task is to simulate the process of encrypting files via a trusted platform module (TPM)¹.
While there is only a single TPM, it can be used by multiple _clients_.
However, only one file can be encryption at a time.
- Each client is simulated by a dedicated (sub)process
- The TPM is simulated by a dedicated (sub)process
- Client and TPM processes originate from the same "main" process
- The "main" process is only used for setup and teardown
- The simulation also covers transfer of data between clients and TPM

Each client submits encryption jobs according to the table below.
Upon submission, the client outputs² `Client <client-id>: Submitted encryption job for <filename>`.
After a job has been processed by the TPM, the client receives the result (encrypted file) and outputs² `Client <client-id>: Received encrypted <filename>`.
- Clients do _not_ wait until a job has been fully processed before submitting another job

|  Filename  | Submit time [s] | Client | File size [MB] | Priority³ |
| ---------- | --------------: | -----: | -------------: | --------: |
| file_a.dat |               0 |      1 |              2 |         1 |
| file_b.dat |               1 |      1 |              2 |         3 |
| file_c.dat |               1 |      2 |              1 |         2 |
| file_d.dat |               4 |      2 |              2 |         1 |
| file_e.dat |               4 |      3 |              3 |         2 |
| file_f.dat |               6 |      1 |              2 |         2 |
| file_g.dat |               6 |      3 |              2 |         1 |
| file_h.dat |               7 |      2 |              1 |         3 |

Since we are just simulating encryption, for each MB of data the TPM simply outputs² `TPM: Encrypting <filename> <processed-mb>/<file-size-mb> MB` and then sleeps for 1 second.
- The TPM respects the job's priority when selecting among multiple submitted jobs

¹ A TPM is a hardware component of modern computer systems that is used for cryptographic operations (typically encryption, decryption, signing, and verification).
The exact details are irrelevant for this exercise as this is mostly just flavor text.

² Clients and TPM don't need to be synchronized when writing to `stdout`.

³ Priority is an integer ranging from 1 (highest) to 3 (lowest).

## Execution

- Pick a suitable synchronization / concurrency mechanism.
  Justify your decision.
- Explain where synchronization is necessary and why your code is correct (i.e. no race conditions can occur).
- State and justify all assumptions.
- Add a way to gracefully shutdown all processes after all jobs have been processed.
  Note that neither the clients nor the TPM know about the total number of encryption jobs.
  The shutdown procedure is initiated by the "main" process.

Put your answers as comments right above the corresponding code or at the top of the file.

## Submission

You must submit your solution within the time frame of the exam.
If you encounter problems with OLAT, email is an acceptable fallback.

```
exam_csXXXXXX.zip
├── Makefile
└── encrypting.c
```

- Test your solution on ZID-GPL (or ZID-Desk)
- No global variables
- No static local variables
- Variable names, function names, comments, and answers are written in English
- Makefile with `all` (default) and `clean` rules
  - Submitted code compiles with `-Wall -Wextra`
    - Hard requirement: code _must_ compile!
    - No warnings are emitted
    - Suppressed warnings must be justified
  - Compilation and linking steps are separated (creating the `.o` file first, then linking it into an executable)
  - `clean` removes all files generated during the build process
- Errors are properly handled and reported
  - You may omit error handling for `malloc`/`calloc` and writing to `stdout`/`stderr`
  - You may omit error handling during teardown
- Do not copy code verbatim from shared sources.
  If multiple students submit identical code-segments without proper citation (that can be easily verified), it is assumed that these students cooperated during the examination.

Points will be subtracted for various shortcomings — especially ones already discussed in the seminar's feedback documents.
This includes things like:
- Executables _segfaulting_
- Reading from uninitialized memory
- Potential race conditions
- Code that is unnecessarily complicated
- Inconsistently formatted or unreadable source code
- Submission contains generated or irrelevant files
- …