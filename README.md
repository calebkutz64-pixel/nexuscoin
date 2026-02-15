# NexusCoin

NexusCoin is an early-stage C codebase for experimenting with core cryptocurrency primitives:
- SHA-256 hashing helpers
- secp256k1 keypair generation
- basic private-key file persistence

## Current project status

The repository currently contains low-level building blocks, but it does **not** yet provide:
- a complete CLI flow in `main.c`
- transaction structures/signing/verification workflows
- address derivation and wallet UX
- test coverage and CI

## What to add next (priority order)

### 1) A usable CLI entrypoint (highest priority)
Implement `main.c` commands so you can actually use existing functionality:
- `genkey --out signingkey.dat`
- `pubkey --in signingkey.dat`
- `sign --in signingkey.dat --msg "hello"`
- `verify --pub <hex> --msg "hello" --sig <hex>`

Why first: this turns the current library-style code into something testable and demoable.

### 2) Signature verification + message hashing API
You already have key generation and a sign function declaration. Add:
- `verify_secp256k1_signature(...)`
- a clear message-to-`msg32` hashing helper
- deterministic input/output formats (hex in/out)

Why second: it completes the cryptographic round-trip.

### 3) Safer keyfile handling
Harden the keyfile layer:
- avoid mutating `const char *filename`
- set restrictive permissions on private key files (0600)
- add explicit error codes instead of `exit(1)` in library functions

Why third: prevents unsafe key storage patterns early.

### 4) Wallet abstractions
Fill in `wallet.h/.c` with a coherent API:
- wallet creation/loading
- address derivation
- key rotation support

Why fourth: this creates a stable interface for future blockchain/transaction logic.

### 5) Tests + CI
Add unit tests for:
- SHA-256 known vectors
- byte/hex conversion
- key generation validity
- sign/verify success + failure cases
- keyfile read/write integrity

Then wire up CI (GitHub Actions) for `make`, tests, and static checks.

## Suggested immediate milestone

**Milestone M1: “sign + verify CLI demo”**
- complete CLI commands for keygen/sign/verify
- add a small integration test script for end-to-end usage
- document commands in this README

This gives the project a concrete, demonstrable “working crypto wallet core” baseline.
