# Basic C Text Editor

A lightweight command-line utility written in C that allows a user to modify a specific line of a text file. The program reads a file into memory, performs pointer-based string manipulation to edit content, and saves the result back to the disk.

## 🛠 Features

* **Pointer Arithmetic:** Navigates through file content using `strchr`.
* **Buffer Management:** Utilizes a temporary "saved" buffer to preserve file integrity during edits.
* **Direct File I/O:** Handles raw file streams with `fread` and `fwrite`.

---

## 🔍 Technical Breakdown

### 1. The `edit_line` Function

This function performs the core logic of locating and replacing text within the memory buffer.

```c
void edit_line(char* buffer, int current_line)

```

| Component | Logic |
| --- | --- |
| **Line Navigation** | A `for` loop uses `strchr(buffer, '\n') + 1` to move the pointer to the start of the next line. After `current_line` iterations, the `buffer` pointer rests at the beginning of the target line. |
| **Finding the End** | `line_end` captures the position of the next newline character to define the boundary of the edit. |
| **Data Preservation** | Everything following the target line is copied into a `saved[1024]` array using `strcpy`. This prevents the rest of the file from being lost during the overwrite. |
| **The Overwrite** | `scanf("%s", buffer)` writes new user input directly into the memory address where the old line started. |
| **Restoration** | `strcpy(buffer + strlen(buffer), saved)` appends the previously saved content back onto the end of the newly typed string. |

---

### 2. The `main` Function

The entry point manages the lifecycle of the file and coordinates user input.

* **Initialization:** Opens the file provided in `argv[1]` in **Read (`"r"`)** mode.
* **Loading:** `fread` copies the file contents into a local 1024-byte character array.
* **Closing (Initial):** `fclose(f)` is called immediately after reading to free the file resource while the user is typing.
* **Modification:** Captures the target line number and calls `edit_line` to update the RAM buffer.
* **Saving:** * Re-opens the file in **Write (`"w"`)** mode, which automatically **truncates (wipes)** the existing file.
* `fwrite` sends the modified buffer back to the file pointer.
* `strlen(buffer)` ensures only the actual text is written, preventing "garbage" data from filling the file.



---

## 🚀 Usage Instructions

### Prerequisites

* A Linux environment with `gcc` installed.

### Compilation

```bash
gcc editor.c -o editor

```

### Running the Program

1. Create a sample text file:
```bash
echo -e "Line 0\nLine 1\nLine 2" > test.txt

```


2. Run the editor:
```bash
./editor test.txt

```


3. Enter the line number to change (e.g., `1`) and type the new text.

---

## ⚠️ Important Considerations

* **Buffer Limit:** This version is limited to files and inputs under **1024 bytes**.
* **Scanf Limitation:** `scanf("%s")` will stop reading at the first space. For multi-word lines, consider using `fgets`.
* **Safety:** The program assumes the file exists and that the line number requested actually exists in the file.

---
