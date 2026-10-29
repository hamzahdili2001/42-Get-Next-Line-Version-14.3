# Get Next Line: A Complete Guide

*This project has been created as part of the 42 curriculum by hhdili.*

## 1. Description
`get_next_line` is a C function that reads a single line from a file descriptor. Calling this function in a loop allows you to read an entire file, one line at a time, regardless of the file size or the length of the lines. 

The goal of this project is to learn about **static variables**, **file descriptor management**, and **dynamic memory allocation** (`malloc`, `free`). 

This repository includes both the mandatory part (reading a single file descriptor) and the bonus part (reading multiple file descriptors simultaneously without losing track of their reading states).

## 2. Instructions

To compile the **mandatory** part:
```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c
```

To compile the **bonus** part:
```bash
cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

**Note on `BUFFER_SIZE`:** 
You can adjust the buffer size using the `-D BUFFER_SIZE=n` flag. If compiled without it, the header defaults to `30720`. The code is designed to work perfectly with *any* value (1, 42, 9999, etc.).

## 3. Algorithm & Justification (Mandatory)

### The Problem with the "Standard" Approach
The most common way students approach this project is by using `ft_strjoin` to append a temporary buffer to a static "stash" on every `read()` call. 
If a file contains a single massive line (e.g., 10 MB) and `BUFFER_SIZE` is `1`, the standard approach re-copies the entire accumulated string on *every single byte read*. This results in **O(N²) time complexity**. Evaluators test this specific case; it causes the program to hang, resulting in a timeout and a failure.

### My Approach: Direct Tail-Reading & Dynamic Growth
Instead of using `strjoin`, my code reads **directly into the tail of the saved string**. It uses a custom `grow` function to manage memory capacity dynamically. This guarantees **O(N) amortized time complexity**, completely eliminating the timeout issue on massive files.

### Deep Dive: How `grow` Works
```c
char *grow(char *s, size_t len, size_t *cap)
{
    *cap = 2 * len + BUFFER_SIZE + 1; // 1. Pick new size
    char *new = malloc(*cap);         // 2. Allocate it
    if (!new)
        return (free(s), NULL);       // 3. Handle malloc failure
    for (size_t i = 0; i <= len; i++) // 4. Copy len+1 bytes (data + '\0')
        new[i] = s[i];
    free(s);                          // 5. Free the old buffer
    return (new);                     // 6. Return the new one
}
```

**The Formula: `2 * len + BUFFER_SIZE + 1`**
This formula does two jobs simultaneously:
1.  **Correctness (`+ BUFFER_SIZE + 1`):** The `fill_save` function reads `BUFFER_SIZE` bytes directly into the string. The string *must* have room for the current length (`len`), plus a full `BUFFER_SIZE` chunk, plus the `\0` terminator.
2.  **Performance (`2 * len`):** By adding an extra `len`, the capacity *doubles* every time `grow` is called. Total copying for a 10MB line goes from ~50 GB (with `strjoin`) down to ~20 MB (with doubling). This is called **Amortized O(1) time complexity**.

**The Copy Loop (`i <= len`):** 
We copy `len + 1` bytes because `s[len]` holds the `\0` terminator. The `<=` ensures the new string is properly null-terminated before we free the old one.

### Memory Lifecycle
*   `grow` frees the old `s` and returns the new `new` pointer.
*   `trim_saved` allocates an exact-size buffer for the leftover string, and **frees the giant buffer created by `grow`**.
*   **Result:** Between calls to `get_next_line`, the static `saved` variable holds *exactly* the number of leftover bytes (plus `\0`). There is no memory bloat.

## 4. Algorithm & Justification (Bonus)

### The Problem
The mandatory part uses a single `static char *saved`. If you call `get_next_line(3)`, read half a line, and then call `get_next_line(4)`, the static variable is overwritten, and you lose the reading state of file descriptor 3.

### My Approach: An Array of Stashes
In `get_next_line_bonus.c`, the static variable becomes an array:
```c
static char *saved[FD_MAX];
```
*(Where `FD_MAX` is defined as 1024 in the header).*

When `get_next_line(fd)` is called:
1.  We check `if (fd < 0 || fd >= FD_MAX)`. This prevents out-of-bounds array access.
2.  We initialize `saved[fd]` if it's `NULL`.
3.  We pass `saved[fd]` to `fill_save`, `extract_line`, and `trim_saved`.

**Why this works:** Each file descriptor acts as an index in our array. File descriptor 3 has its own independent stash at `saved[3]`, and file descriptor 4 has its own at `saved[4]`. When we alternate between reading `fd 3` and `fd 4`, we are simply alternating between which index of the array we are modifying. The reading states are perfectly preserved without data mixing.

## 5. File Breakdown

### Mandatory Files
*   **`get_next_line.c`**:
    *   `get_next_line()`: The main coordinator. Guards inputs, initializes `saved`, calls the filler, extractor, and trimmer. Frees everything and returns `NULL` on EOF or error.
    *   `fill_save()`: Reads into the tail of `saved`. Calls `grow` when there isn't enough room. Breaks the loop when a `\n` is found in the newly read bytes.
    *   `extract_line()`: Copies the line (including `\n`) into a new exact-size string using `ft_substr`.
    *   `trim_saved()`: Frees the old `saved` and replaces it with the leftover bytes after the `\n`.
*   **`get_next_line_utils.c`**: Contains `ft_strlen`, `l_count` (finds newline/end), `ft_substr` (string slicing), and `grow` (capacity manager).

### Bonus Files
*   **`get_next_line_bonus.c`**: Identical logic to the mandatory part, but uses `static char *saved[FD_MAX]` to handle multiple file descriptors.
*   **`get_next_line_utils_bonus.c`**: Identical utilities to the mandatory part.

## 6. Defense & Edge Cases

*   **What happens if `BUFFER_SIZE` is 1?**
    The formula `2 * len + BUFFER_SIZE + 1` scales perfectly. It allocates 2 bytes, reads 1, then allocates 4 bytes, reads 1. The capacity still doubles, maintaining linear time complexity.
*   **What if the file ends without a newline?**
    `read()` returns `0`. `fill_save` breaks. `extract_line` sees the end of the string (`\0`, not `\n`) and returns the string as-is. `trim_saved` returns an empty string. The next call returns `NULL`.
*   **What if `malloc` fails during `grow`?**
    `grow` frees the old `s` to prevent leaks and returns `NULL`. `fill_save` detects this, returns `NULL`, and `get_next_line` returns `NULL`.
*   **Are there memory leaks?**
    No. `grow` frees the old buffer. `trim_saved` frees the large buffer. At EOF, the static stash is freed and set to `NULL`.

## 7. Resources & AI Usage
*   **Documentation:** [Linux `read(2)` man page](https://man7.org/linux/man-pages/man2/read.2.html).
*   **AI Usage:** AI was used as a peer-learning assistant. It was used to verify the mathematical formula for amortized O(1) memory growth (`2 * len + BUFFER_SIZE + 1`), to cross-check edge cases (e.g., `malloc` failures, null-termination), and to format this README. All code logic was reasoned through, tested locally, and fully understood by the student. No code was copied blindly.

