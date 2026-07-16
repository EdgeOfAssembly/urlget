# urlget — Minimal HTTP(S) Client in C

A step-by-step tutorial that builds **urlget**: a small command-line tool for fetching URLs over HTTP and HTTPS, with optional Tor (SOCKS5), redirects, custom headers, POST, Basic auth, and more.

Roughly **~350 lines of C**. A pocket-sized mini-curl you can actually read.

| | |
|---|---|
| **Language** | C11 / POSIX |
| **TLS** | OpenSSL 3 |
| **Tutorial** | LaTeX → PDF |
| **Author** | S.F. |

---

## Why this exists

High-level libraries are great until you need to know what they hide. This project takes the demystification path:

1. **Almost bare-metal networking is not hard.** Open a socket, connect, send, receive. That recipe is short and repeatable. Making the same path much faster in user space usually means assembly (or accepting that the kernel, the NIC, and physics own the rest).
2. **After the building blocks, the pattern barely changes.** Address → socket → connect → write → read → close. Later stages differ mostly in the **payload**: text vs binary protocols, framing, and how you parse them safely.

If you finish thinking *“that was mostly sockets plus parsing,”* the tutorial did its job.

---

## Features (`urlget`)

| Flag | Purpose |
|------|---------|
| `-A`, `--user-agent STR` | Custom User-Agent |
| `-T`, `--tor [host:port]` | Route via SOCKS5 (default `127.0.0.1:9050`) |
| `-H`, `--header STR` | Extra header (repeatable) |
| `-d`, `--data DATA` | POST body (`@file` supported) |
| `-o`, `--output FILE` | Write body to file |
| `-u`, `--user USER:PASS` | HTTP Basic auth (Base64 encoded in-process) |
| `-I`, `--head` | HEAD request |
| `--no-location` | Do not follow redirects |
| `--max-redirects N` | Cap redirect hops (default 10) |

Also: `http://` and `https://`, IPv6 literals in brackets, default ports 80/443.

---

## Quick start

### Dependencies

- C compiler (`gcc` or `clang`)
- OpenSSL development headers (`libssl-dev` on Debian/Ubuntu, `openssl-devel` on Fedora)
- Optional: Tor listening on `127.0.0.1:9050` for `-T`
- Optional (PDF): TeX Live with `pdflatex`

### Build the client

```bash
gcc -Wall -Wextra -O2 -DNDEBUG -o urlget urlget.c -lssl -lcrypto
```

Debug traces (needs a real or stub `debug.h`):

```bash
gcc -Wall -Wextra -O0 -g -o urlget urlget.c -lssl -lcrypto
```

A minimal `debug.h` stub is included so the tree compiles out of the box.

### Try it

```bash
./urlget https://example.com/
./urlget -I https://httpbin.org/get
./urlget -H "X-Test: 1" https://httpbin.org/headers
./urlget -d "hello=world" https://httpbin.org/post
./urlget -u 'user:passwd' https://httpbin.org/basic-auth/user/passwd
./urlget -T https://check.torproject.org/   # requires Tor
```

### Build the tutorial PDF

```bash
make pdf    # runs pdflatex twice (TOC)
# → urlget_tutorial.pdf
```

Or:

```bash
pdflatex urlget_tutorial.tex
pdflatex urlget_tutorial.tex
```

---

## Repository layout

```
urlget.c                 # Finished client (~348 LOC by cloc)
debug.h                  # Minimal debug macro stub
urlget_tutorial.tex      # Main LaTeX document (foreword, styles, includes)
step01_….tex … step11_…  # Incremental tutorial chapters
Makefile                 # PDF build (two pdflatex passes)
urlget_tutorial.pdf      # Prebuilt tutorial (optional to commit)
LICENSE
README.md
```

### Tutorial steps

| Step | Topic |
|------|--------|
| Foreword | Why bare-metal sockets, and what stays the same |
| 1 | Project skeleton |
| 2 | `usage()` |
| 3 | Argument parsing |
| 4 | URL parsing |
| 5 | TCP + plain HTTP |
| 6 | HTTPS (OpenSSL) |
| 7 | Tor / SOCKS5 |
| 8 | Redirect following |
| 9 | Headers, POST, auth, HEAD, `-o` |
| 10 | Debug polish + full source |

Each development step shows **new code** (highlighted) and the **full source so far** (prior lines in gray).

---

## Design notes (honest limits)

This is a **teaching client**, not a curl replacement:

- TLS peer verification is off (`SSL_VERIFY_NONE`) for simplicity — tighten for real use
- Response handling prefers `Connection: close` over full chunked/`Content-Length` parsing
- Redirect `Location:` handling is intentionally minimal
- Fixed-size buffers; oversized inputs are rejected rather than resized

Natural extensions: certificate verification, proper HTTP parsing, chunked encoding, connection reuse.

---

## License

**MIT License** — see [LICENSE](LICENSE).

Use the code and tutorial text freely for learning, teaching, and building on top of them. Attribution is appreciated but the MIT terms are the formal requirement.

---

## Author

**S.F.** — July 2026
